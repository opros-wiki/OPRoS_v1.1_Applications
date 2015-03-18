/****************************************************************
*                                                               *
*       CDib Class (Bitmap Manipulation Class)               *
*                                                               *
*...............................................................*
*       jLee    revised 97/01/24                                *
*****************************************************************/
//#ifdef _WINDOWS
#include "stdafx.h"
//#endif

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

unsigned char CDib::m_BitMask[8] = {
        0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01
        };

/////////////////////////////////////////////////////////////////
// Constructors and Destructors
CDib::CDib()
{
        ResetVariables();
}

CDib::CDib(const char *pFileName)
{
        ResetVariables();
        ReadImage(pFileName);
}

CDib::CDib(int width, int height, int bitcount, unsigned char *pPattern, RGBQUAD *pRgbQuad)
{
        ResetVariables();
        Initialize(width, height, bitcount, pPattern, pRgbQuad);
}

CDib::~CDib()
{
        DestroyContents();
}

/////////////////////////////////////////////////////////////////
// Protected Operations
void CDib::ResetVariables()
{
        m_pPackedDib = NULL;
        m_pInfo = NULL;
        m_pInfoHeader = NULL;
        m_pRgbQuad = NULL;
        m_pPattern = NULL;
}

void CDib::DestroyContents()
{
        delete [] m_pPackedDib;
        ResetVariables();
}

void CDib::AssignReferenceVariables()
// AssignReferenceVariables는 최소한 BITMAPINFOHEADER가 setting된 이후 call 해야 한다.
{
        m_pInfo = (BITMAPINFO *) m_pPackedDib;
        m_pInfoHeader = (BITMAPINFOHEADER *) m_pPackedDib;
        m_pRgbQuad = (RGBQUAD *) (m_pPackedDib + sizeof(BITMAPINFOHEADER));
        m_pPattern = m_pPackedDib + sizeof(BITMAPINFOHEADER) + PaletteSize();
}

BITMAPINFO *CDib::GetCopyOfBitmapInfo()
{
        if (!IsInitialized()) return NULL;

        UINT size = sizeof(BITMAPINFOHEADER) + (UINT) PaletteSize();
        BITMAPINFO *pInfo = (BITMAPINFO *) (new unsigned char [size]);

        memcpy(pInfo, m_pInfo, size);

        return pInfo;
}

/////////////////////////////////////////////////////////////////
// Static Functions
DWORD CDib::CalcPackedDibSize(BITMAPINFOHEADER *pBi)
{
        DWORD size = sizeof(BITMAPINFOHEADER);
        
        switch (pBi->biBitCount) {
          case 1 :
            size += ( sizeof(RGBQUAD)*2 + ByteWidth(pBi->biWidth*pBi->biBitCount)*pBi->biHeight );
            break;
          case 4 :
            size += ( sizeof(RGBQUAD)*16 + ByteWidth(pBi->biWidth*pBi->biBitCount)*pBi->biHeight );
            break;
          case 8 :
            size += ( sizeof(RGBQUAD)*256 + ByteWidth(pBi->biWidth*pBi->biBitCount)*pBi->biHeight );
            break;
          case 16 :
          case 24 :
          case 32 :
            size += ( ByteWidth(pBi->biWidth*pBi->biBitCount)*pBi->biHeight );
            break;
          default :
            break;
        }

        return size;
}

void CDib::RGBtoYIQ(RGBQUAD rgb, unsigned char *y, unsigned char *i, unsigned char *q)
{
        *y = (unsigned char) ( 0.299 * (double) rgb.rgbRed 
                             + 0.587 * (double) rgb.rgbGreen
                             + 0.114 * (double) rgb.rgbBlue + 0.5);
        *i = (unsigned char) ( 0.596 * (double) rgb.rgbRed 
                             + 0.274 * (double) rgb.rgbGreen
                             + 0.311 * (double) rgb.rgbBlue + 0.5);
        *q = (unsigned char) ( 0.211 * (double) rgb.rgbRed 
                             + 0.522 * (double) rgb.rgbGreen
                             + 0.299 * (double) rgb.rgbBlue + 0.5);
}

unsigned char CDib::GetBrightness(RGBQUAD rgb)
{
        return (unsigned char) ( 0.299 * (double) rgb.rgbRed 
                             + 0.587 * (double) rgb.rgbGreen
                             + 0.114 * (double) rgb.rgbBlue + 0.5);
}

BOOL CDib::ReadImage(const char *pFileName)
{
    if (IsInitialized()) DestroyContents();

	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;

printf("In ReadImage\n");
	FILE *fp = fopen(pFileName, "rb");
	if (!fp) {
          printf("! File Open Error\n");
	  return false;
	}
printf("File Open Over: %d\n", sizeof(BITMAPFILEHEADER));

	fread(&bf.bfType, 2, 1, fp);
printf("Bf Type: %d\n", bf.bfType);
	fread(&bf.bfSize, 4, 1, fp);
printf("Bf Size: %d\n", bf.bfSize);
	fread(&bf.bfReserved1, 2, 1, fp);
printf("Bf Res1: %d\n", bf.bfReserved1);
	fread(&bf.bfReserved2, 2, 1, fp);
printf("Bf Res2: %d\n", bf.bfReserved2);
	fread(&bf.bfOffBits, 4, 1, fp);
printf("Bf OffB: %d\n", bf.bfOffBits);
	//fread(&bf, sizeof(BITMAPFILEHEADER), 1, fp);
	if (bf.bfType!=TYPE_BITMAP) // this file is NOT a BMP file
		return false; 

printf("BF read over: %d\n", bf.bfOffBits);

	fread(&bi, sizeof(BITMAPINFOHEADER), 1, fp);
printf("BI read over: %d %d\n", bi.biWidth, bi.biHeight);
printf("BI size: %d\n", sizeof(BITMAPINFOHEADER));


    int p_size; 
    switch (bi.biBitCount) {
      case 1 : p_size = 2 * sizeof(PALETTEENTRY); break;
      case 4 : p_size = 16 * sizeof(PALETTEENTRY); break;
      case 8 : p_size = 256 * sizeof(PALETTEENTRY); break;
      default : p_size = 0;
    }
    
	int skip = bf.bfOffBits - 14 /*sizeof(BITMAPFILEHEADER)*/ - sizeof(BITMAPINFOHEADER) - p_size;
    if (skip>0) 	// skip additional info
	  fseek(fp, skip, SEEK_CUR);

    DWORD size = CalcPackedDibSize(&bi);

printf("PackedDib Size: %ld\n", size);
    m_pPackedDib = new unsigned char[size];
    memcpy(m_pPackedDib, &bi, sizeof(BITMAPINFOHEADER));

	fread(m_pPackedDib+sizeof(BITMAPINFOHEADER), size-sizeof(BITMAPINFOHEADER), 1, fp);

    AssignReferenceVariables();

	fclose(fp);

	return true;
}

BOOL CDib::SaveImage(const char *pFileName)
{
    if (!IsInitialized()) return false;

    // write bitmap file header
    BITMAPFILEHEADER bf;
    bf.bfType = TYPE_BITMAP;
    bf.bfOffBits = (DWORD) 14 //sizeof(BITMAPFILEHEADER)
                 + (DWORD) sizeof(BITMAPINFOHEADER)
                 + (DWORD) PaletteSize();
    bf.bfSize = bf.bfOffBits + ByteWidth()*Height();
    bf.bfReserved1 = bf.bfReserved2 = 0;

	FILE *fp = fopen(pFileName, "wb");
	if (!fp) return false;

	//fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, fp);
	fwrite(&bf.bfType, 2, 1, fp);
	fwrite(&bf.bfSize, 4, 1, fp);
	fwrite(&bf.bfReserved1, 2, 1, fp);
	fwrite(&bf.bfReserved2, 2, 1, fp);
	fwrite(&bf.bfOffBits, 4, 1, fp);
	fwrite(m_pInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);

    // write palette
    if (PaletteSize()>0) fwrite(m_pRgbQuad, PaletteSize(), 1, fp);

    // write image data
	fwrite(m_pPattern, ByteWidth(), Height(), fp);

	fclose(fp);

    return true;
}

BOOL CDib::GetImageInfoBmp(const char *pFileName, UINT *pWidth, UINT *pHeight, UINT *pBitCount)
{
	FILE *fp = fopen(pFileName, "rb");
	if (!fp) return false;

    fseek(fp, 14, SEEK_SET);
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, fp);

    *pWidth = bi.biWidth;
    *pHeight = bi.biHeight;
    *pBitCount = bi.biBitCount;

    return true;
}

void CDib::Initialize(int width, int height, int bitcount, unsigned char *pPattern,
						 RGBQUAD *pRgbQuad)
{
        // if data already exist, destroy the contents
        if (IsInitialized()) DestroyContents();

        // assign bitmap info header
        BITMAPINFOHEADER biInfo;
        biInfo.biSize = sizeof(BITMAPINFOHEADER);
        biInfo.biWidth = (LONG) width;
        biInfo.biHeight = (LONG) height;
        biInfo.biPlanes = 1;
        biInfo.biBitCount = bitcount;
        biInfo.biCompression = BI_RGB;
        biInfo.biSizeImage = 0;
        biInfo.biXPelsPerMeter = 0;
        biInfo.biYPelsPerMeter = 0;
        biInfo.biClrUsed = 0;
        biInfo.biClrImportant = 0;
        
        // memory allocation
        DWORD size = CalcPackedDibSize(&biInfo);
        m_pPackedDib = new unsigned char [size];
                
        // copy bitmap info header                                        
        memcpy(m_pPackedDib, &biInfo, sizeof(BITMAPINFOHEADER));

        AssignReferenceVariables();

        // copy palette table
        switch (bitcount) {
          case 1 :
		    memcpy(m_pRgbQuad, pRgbQuad, sizeof(RGBQUAD)*2);
            break;
          case 4 :
		    memcpy(m_pRgbQuad, pRgbQuad, sizeof(RGBQUAD)*16);
            break;
          case 8 :
		    memcpy(m_pRgbQuad, pRgbQuad, sizeof(RGBQUAD)*256);
            break;
          case 16 :
          case 24 :
          case 32 :
          default :
            break;    
        }

        // copy pattern
        memcpy(m_pPattern, pPattern, ByteWidth(width*bitcount)*height);
}

void CDib::Allocate(int width, int height, int bitcount)
{
        // if data already exist, destroy the contents
        if (IsInitialized()) DestroyContents();

        // assign bitmap info header
        BITMAPINFOHEADER biInfo;
        biInfo.biSize = sizeof(BITMAPINFOHEADER);
        biInfo.biWidth = (LONG) width;
        biInfo.biHeight = (LONG) height;
        biInfo.biPlanes = 1;
        biInfo.biBitCount = bitcount;
        biInfo.biCompression = BI_RGB;
        biInfo.biSizeImage = 0;
        biInfo.biXPelsPerMeter = 0;
        biInfo.biYPelsPerMeter = 0;
        biInfo.biClrUsed = 0;
        biInfo.biClrImportant = 0;
        
        // memory allocation
        DWORD size = CalcPackedDibSize(&biInfo);
        m_pPackedDib = new unsigned char [size];
        memset(m_pPackedDib, 0, size);
                
        // copy bitmap info header                                        
        memcpy(m_pPackedDib, &biInfo, sizeof(BITMAPINFOHEADER));

        AssignReferenceVariables();
}          

void CDib::LoadPackedDib(void *pPackedDib)
{
        if (IsInitialized()) DestroyContents();

        DWORD size = CalcPackedDibSize((BITMAPINFOHEADER *) pPackedDib);
        m_pPackedDib = new unsigned char [size];

        memcpy(m_pPackedDib, pPackedDib, size);
        AssignReferenceVariables();
}

/////////////////////////////////////////////////////////////////
// Information Functions
DWORD CDib::PaletteSize()
{
        switch (BitCount()) {
          case 1 :
            return sizeof(PALETTEENTRY)*2;
          case 4 :
            return sizeof(PALETTEENTRY)*16;
          case 8 :
            return sizeof(PALETTEENTRY)*256;
          default :
            return 0;
        }
}

DWORD CDib::NumberOfColors()
{
        switch (BitCount()) {
          case 1 :
            return 2;
          case 4 :
            return 16;
          case 8 :
            return 256;
          case 16 :
            return 0x00010000;
          case 24 :
          case 32 :
            return 0x01000000;
          default :
            return 0;
        }
}

unsigned char * CDib::GetPointer(int x, int y)
{
        if ( (x<0) || (x>=Width()) || (y<0) || (y>=Height()) ) return NULL;

        unsigned char *pLine = m_pPattern + (Height()-1-y)*ByteWidth();

        switch (BitCount()) {
          case 1 :
            return pLine + x/8;
          case 4 :
            return pLine + x/2;
          case 8 :
            return pLine + x;
          case 16 :
            return pLine + x*2;
          case 24 :
            return pLine + x*3;
          case 32 :
            return pLine + x*4;
          default :
            return NULL;
        }
}

// convert RGB color model to YIQ color model
unsigned char CDib::Intensity(int x, int y)
{
        unsigned char value = *GetPointer(x, y);
        unsigned char intensity=0;

        switch (BitCount()) {
          case 1 :
            if (value & m_BitMask[(x%8)]) value = 1;
            else value = 0;
            intensity = GetBrightness(m_pRgbQuad[value]);
            break;
          case 4 :
            if ((x%2)==0) value >>= 4;
            else value &= 0x0F;
            intensity = GetBrightness(m_pRgbQuad[value]);
            break;
          case 8 :
            intensity = GetBrightness(m_pRgbQuad[value]);
            break;
          case 16 :
            {
              WORD *pPtr = (WORD *) GetPointer(x, y);
              RGBQUAD rgb;
              
              rgb = Decode16(*pPtr);
              intensity = GetBrightness(rgb);
            }
            break;
          case 24 :
          case 32 :
            {
              unsigned char *pPtr = GetPointer(x, y);
              RGBQUAD rgb;
              rgb.rgbBlue = *pPtr++;
              rgb.rgbGreen = *pPtr++;
              rgb.rgbRed = *pPtr++;
              rgb.rgbReserved = 0;
              intensity = GetBrightness(rgb);
            }
            break;
          default :
            break;
        }

        return intensity;
}

unsigned char CDib::GetIndex(int x, int y)
{
        unsigned char value = *GetPointer(x, y);

        switch (BitCount()) {
          case 1 :
            return (m_BitMask[x%8] & value) ? 1 : 0;
          case 4 :
            return ((x%2)==0) ? (value>>4) : (value & 0x0F);
          case 8 :
            return value;
          case 16 :
          case 24 :
          case 32 :
          default :
            return 0;
        }
}

RGBQUAD CDib::GetColor(int x, int y)
{
        switch (BitCount()) {
          case 1 :
          case 4 :
          case 8 :
            return m_pRgbQuad[GetIndex(x,y)];
          case 16 :
            {
              WORD *pPtr = (WORD *) GetPointer(x, y);
              RGBQUAD quad;
              
              quad = Decode16(*pPtr);

              return quad;  
            }
          case 24 :
          case 32 :
            {
              unsigned char *pPtr = GetPointer(x, y);
              RGBQUAD quad;

              quad.rgbBlue = *pPtr++;
              quad.rgbGreen = *pPtr++;
              quad.rgbRed = *pPtr++;
              quad.rgbReserved = 0;

              return quad;
            }
          default :
            {
              RGBQUAD quad;
              memset(&quad, 0, sizeof(RGBQUAD));

              return quad;
            }
        }
}

RGBQUAD CDib::Decode16(WORD data)
{                         
        RGBQUAD quad;
        quad.rgbRed = (unsigned char) ((data>>7) & 0x00F8);
        quad.rgbGreen = (unsigned char) ((data>>2) & 0x00F8);
        quad.rgbBlue = (unsigned char) ((data<<3) & 0x00F8);
        quad.rgbReserved = 0;

        return quad;
}

WORD CDib::Encode16(unsigned char red, unsigned char green, unsigned char blue)
{
        //   0rrr rrgg gggb bbbb
        WORD data = ((((WORD) (red & 0xF8)) << 7) & 0x7C00) |
                    ((((WORD) (green & 0xF8)) << 2) & 0x03E0) |
                    ((((WORD) (blue & 0xF8)) >> 3) & 0x001F);

        return data;
}

/////////////////////////////////////////////////////////////////
// Data Operations
void CDib::UpsideDown()
{
        if (!IsInitialized()) return;

        unsigned char *pBuffer = new unsigned char [ByteWidth()];
        unsigned char *pUp, *pDown;

        for (int i=0; i<Height()/2 ;i++) {
          pUp = GetPointer(0, i);
          pDown = GetPointer(0, Height()-i-1);
          memcpy(pBuffer, pUp, ByteWidth());
          memcpy(pUp, pDown, ByteWidth());
          memcpy(pDown, pBuffer, ByteWidth());
        }

        delete [] pBuffer;
}

void CDib::Inverse()
{
    for (int i=0; i<Height() ;i++) {
      unsigned char *ptr = GetPointer(0, i);
      for (int j=0; j<ByteWidth() ;j++, ptr++)
        *ptr = 255 - *ptr;
    }
}

void CDib::ResetContents()
{
        if (!IsInitialized()) return;

        memset(m_pPattern, 0, ByteWidth()*Height());
}

BOOL CDib::CopyRect(RECT *pTargetRect, CDib *pSrCDib, RECT *pSrcRect, int BackColor)
{
	int tWidth = pTargetRect->right - pTargetRect->left;
	int tHeight = pTargetRect->bottom - pTargetRect->top;
	int sWidth = pSrcRect->right - pSrcRect->left;
	int sHeight = pSrcRect->bottom - pSrcRect->top;

    if (pSrCDib->BitCount()!=BitCount()) {
      printf("??? Can't Copy Pattern with Different BitCount\n");
      return false;
    }

    if ((tWidth!=sWidth) || (tHeight!=sHeight)) {
      printf("??? Can't Copy Rect Region with Different Size\n");
      return false;
    }

    unsigned char *pTarget, *pSrc;

    if ((BackColor==-1) || (BitCount()!=8)) {       // transparent copy is allowed only for 8 bit bitmap
      for (int i=0; i<tHeight ;i++) {
        pTarget = GetPointer(pTargetRect->left, pTargetRect->top+i);
        pSrc = pSrCDib->GetPointer(pSrcRect->left, pSrcRect->top+i);
        memcpy(pTarget, pSrc, sWidth*BitCount()/8);
      }
    }
    else {
      for (int i=0; i<tHeight ;i++) {
        pTarget = GetPointer(pTargetRect->left, pTargetRect->top+i);
        pSrc = pSrCDib->GetPointer(pSrcRect->left, pSrcRect->top+i);
        for (int j=0; j<sWidth ;j++, pTarget++, pSrc++)
          if (*pSrc!=BackColor) *pTarget = *pSrc;
      }
    }

    return true;
}

/////////////////////////////////////////////////////////////////
// Create New CDibs
CDib *CDib::GetGrayCDib()
{
        CDib *pDib = new CDib;

        pDib->Allocate(Width(), Height(), 8);
        pDib->SetGrayPalette();

        for (int y=0; y<Height() ;y++) {
          unsigned char *pNew = pDib->GetPointer(0, y);
          for (int x=0; x<Width() ;x++, pNew++)
            *pNew = Intensity(x, y);
        }

        return pDib;
}


CDib *CDib::GetGrayCDibAver()
{
	CDib *pRes = new CDib;
	pRes->Allocate(Width(), Height(), 8);
	pRes->SetGrayPalette();
	
	int value;
	for (int i=0; i<Height() ;i++) {
		unsigned char *pD = GetPointer(0, i);
		unsigned char *pR = pRes->GetPointer(0, i);
		for (int j=0; j<Width() ;j++) {
			value = (int) *pD++ + (int) *pD++ + (int) *pD++;
			*pR++ = (unsigned char) (value/3);
		}
	}
	return pRes;
}


CDib *CDib::GetGrayCDibInt()
{
	CDib *pRes = new CDib;
	pRes->Allocate(Width(), Height(), 8);
	pRes->SetGrayPalette();
	
	int b, g, r;
	for (int i=0; i<Height() ;i++) {
		unsigned char *pD = GetPointer(0, i);
		unsigned char *pR = pRes->GetPointer(0, i);
		for (int j=0; j<Width() ;j++) {
			b = (int) *pD++;
			g = (int) *pD++;
			r = (int) *pD++;
			*pR++ = (unsigned char)( ((r*66 + g*129 + b*25 +128)>>8) + 16 );

		}
	}
	return pRes;
}


CDib *CDib::CopyCDib()
{
        CDib *pDib = new CDib;

        pDib->Allocate(Width(), Height(), BitCount());
        
        DWORD size = CalcPackedDibSize(m_pInfoHeader);
        memcpy(pDib->GetPackedDibPointer(), GetPackedDibPointer(), size);

        return pDib;
}

CDib *CDib::GetSizedCDib(int width, int height)
{
        CDib *pDib = new CDib;

        if (height==0) {        // set new height so as the aspect ratio is preserved
          height = width * Height() / Width();
        }

        pDib->Allocate(width, height, 24);

        double fx = (double) Width() / (double) width;
        double fy = (double) Height() / (double) height;
        int ix, iy;
        RGBQUAD quad;

        for (int y=0; y<height ;y++) {
          unsigned char *pPtr = pDib->GetPointer(0, y);
          for (int x=0; x<width ;x++) {
            ix = (int) (fx * x + 0.5); ix = min(ix, Width()-1);
            iy = (int) (fy * y + 0.5); iy = min(iy, Height()-1);
            quad = GetColor(ix, iy);
            *pPtr++ = quad.rgbBlue;
            *pPtr++ = quad.rgbGreen;
            *pPtr++ = quad.rgbRed;
          }
        }

        return pDib;
}

CDib *CDib::GetEdgeCDib(double threshold, BOOL bIsGray)
{
        CDib *pGray = bIsGray ? this : GetGrayCDib();
        CDib *pDib = new CDib;
        int h, v;
        double magnitude;
         
        pDib->Allocate(Width(), Height(), 8);
        pDib->SetGrayPalette();

        for (int y=1; y<Height()-1 ;y++) {
          unsigned char *pUp = pGray->GetPointer(1, y-1);
          unsigned char *pNow = pGray->GetPointer(1, y);
          unsigned char *pDown = pGray->GetPointer(1, y+1);
          unsigned char *pNew = pDib->GetPointer(1, y);
          for (int x=1; x<Width()-1 ;x++, pUp++, pNow++, pDown++, pNew++) {
            v = *(pUp-1) + *(pNow-1) + *(pDown-1)
              - *(pUp+1) - *(pNow+1) - *(pDown+1);
            h = *(pUp-1) + *pUp + *(pUp+1)
              - *(pDown-1) - *pDown - *(pDown+1);
            magnitude = sqrt((double) v * (double) v + (double) h * (double) h);
            if (magnitude>threshold) *pNew = 255;
            else *pNew = 0;
          }
        }

        if (!bIsGray) delete pGray;

        return pDib;
}

CDib *CDib::ClipCDib(RECT *pRect)
{
	return ClipCDib(pRect->left, pRect->top, pRect->right, pRect->bottom);
}

CDib *CDib::ClipCDib(int left, int top, int right, int bottom)
{
	RECT target;
	target.left = max(left, 0);
	target.top = max(top, 0);
	target.right = min(right, (int) Width());
	target.bottom = min(bottom, (int) Height());
	int tWidth = target.right - target.left;
	int tHeight = target.bottom - target.top;

	CDib *pRes = new CDib;
	pRes->Allocate(tWidth, tHeight, BitCount());

	if (PaletteSize()>0) memcpy(pRes->GetRgbQuadPointer(), m_pRgbQuad, PaletteSize());

	int bwidth = tWidth * BitCount() / 8;
	for (int i=0; i<tHeight ;i++) 
	  memcpy(pRes->GetPointer(0, i), GetPointer(target.left, target.top+i), bwidth);


    return pRes;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Additional Functions
void CDib::SetGrayPalette()
{
	RGBQUAD *p = m_pRgbQuad;
	int i;
	switch (BitCount()) {
	  case 1:
	    p->rgbRed = p->rgbGreen = p->rgbBlue = p->rgbReserved = 0;
		p++;
		p->rgbRed = p->rgbGreen = p->rgbBlue = 255; p->rgbReserved = 0;
		break;
	  case 4:
	    for (i=0; i<16 ;i++, p++) {
		  p->rgbRed = p->rgbGreen = p->rgbBlue = i * 16;
		  p->rgbReserved = 0;
		}
		break;
	  case 8:
		for (i=0; i<256 ;i++, p++) {
		  p->rgbRed = p->rgbGreen = p->rgbBlue = i;
		  p->rgbReserved = 0;
		}
		break;
	  default:
	    return;
	}
}

BOOL CDib::IsGrayImage()
{
        if (8!=BitCount()) return false;

        RGBQUAD *pQuad = m_pRgbQuad;
        for (int i=0; i<256 ;i++, pQuad++)
          if ((pQuad->rgbRed!=i) || (pQuad->rgbGreen!=i) || (pQuad->rgbBlue!=i)) return false;

        return true;
}

void CDib::SplitChannel(CDib **pDibR, CDib **pDibG, CDib **pDibB)
{
        (*pDibR) = new CDib;
        (*pDibR)->Allocate(Width(), Height(), 8);
        (*pDibR)->SetGrayPalette();
        (*pDibG) = new CDib;
        (*pDibG)->Allocate(Width(), Height(), 8);
        (*pDibG)->SetGrayPalette();
        (*pDibB) = new CDib;
        (*pDibB)->Allocate(Width(), Height(), 8);
        (*pDibB)->SetGrayPalette();

        int nBit = BitCount();
        switch (nBit) {
          case 24 :
          case 32 :
            {
              for (int i=0; i<Height() ;i++) {
                unsigned char *pSrc = GetPointer(0, i);
                unsigned char *pR = (*pDibR)->GetPointer(0, i);
                unsigned char *pG = (*pDibG)->GetPointer(0, i);
                unsigned char *pB = (*pDibB)->GetPointer(0, i);
                for (int j=0; j<Width() ;j++) {
                  *pB++ = *pSrc++;
                  *pG++ = *pSrc++;
                  *pR++ = *pSrc++;
                  if (nBit==32) pSrc++;
                }
              }
            }
            return;
          case 16 :
            {
              RGBQUAD quad;  
              for (int i=0; i<Height() ;i++) {
                unsigned char *pSrc = GetPointer(0, i);
                unsigned char *pR = (*pDibR)->GetPointer(0, i);
                unsigned char *pG = (*pDibG)->GetPointer(0, i);
                unsigned char *pB = (*pDibB)->GetPointer(0, i);
                for (int j=0; j<Width() ;j++, pSrc+=2) {
                  quad = Decode16(*((WORD *) pSrc));
                  *pR++ = quad.rgbRed;
                  *pG++ = quad.rgbGreen;
                  *pB++ = quad.rgbBlue;
                }
              }
            }            
            return;
          case 8 :
            {
              for (int i=0; i<Height() ;i++) {
                unsigned char *pSrc = GetPointer(0, i);
                unsigned char *pR = (*pDibR)->GetPointer(0, i);
                unsigned char *pG = (*pDibG)->GetPointer(0, i);
                unsigned char *pB = (*pDibB)->GetPointer(0, i);
                for (int j=0; j<Width() ;j++, pSrc++) {
                  *pR++ = m_pRgbQuad[*pSrc].rgbRed;
                  *pG++ = m_pRgbQuad[*pSrc].rgbGreen;
                  *pB++ = m_pRgbQuad[*pSrc].rgbBlue;
                }
              }          
            }
            return;    
          case 4 :
          case 1 :
            {
              RGBQUAD quad;
              for (int i=0; i<Height() ;i++) {
                unsigned char *pR = (*pDibR)->GetPointer(0, i);
                unsigned char *pG = (*pDibG)->GetPointer(0, i);
                unsigned char *pB = (*pDibB)->GetPointer(0, i);
                for (int j=0; j<Width() ;j++) {
                  quad = GetColor(j, i);
                  *pR++ = quad.rgbRed;
                  *pG++ = quad.rgbGreen;
                  *pB++ = quad.rgbBlue;
                }
              }          
            }
            return;    
          default :
#ifdef _DEBUG
            AfxMessageBox("??? Unknown BitCount in SplitChannel");
#endif
            return;
        }
}

CDib *CDib::MergeChannel(CDib *pDibR, CDib *pDibG, CDib *pDibB, int bitcount)
{
        if (bitcount<16) {
#ifdef _DEBUG
          AfxMessageBox("??? Bitcount for the result CDib of MergeChannel should be larger or equal to 16");
#endif
          return NULL;
        }

        CDib *pDib = new CDib;
        pDib->Allocate(pDibR->Width(), pDibR->Height(), bitcount);

        for (int i=0; i<pDib->Height() ;i++) {
          unsigned char *pTarget = pDib->GetPointer(0, i);
          unsigned char *pR = pDibR->GetPointer(0, i);
          unsigned char *pG = pDibG->GetPointer(0, i);
          unsigned char *pB = pDibB->GetPointer(0, i);
          for (int j=0; j<pDib->Width() ;j++) {
            switch (bitcount) {
              case 24 :
                *pTarget++ = *pB++;
                *pTarget++ = *pG++;
                *pTarget++ = *pR++;
                break;
              case 32 :
                *pTarget++ = *pB++;
                *pTarget++ = *pG++;
                *pTarget++ = *pR++;
                *pTarget++ = 0;
                break;
              case 16 :
                *((WORD *) pTarget) = Encode16(*pR++, *pG++, *pB++);
                pTarget += 2;
                break;
              default :
#ifdef _DEBUG
                AfxMessageBox("??? Unknown Bitcount in MergeChannel");
#endif
                break;
            }
          }
        }

        return pDib;
}


#ifdef _WINDOWS
/////////////////////////////////////////////////////////////////
// Clipboard Functions
BOOL CDib::GetClipboard()
{
        if (!IsClipboardFormatAvailable(CF_DIB)) return false;
        
        OpenClipboard(NULL);
        HANDLE handle = GetClipboardData(CF_DIB);

        if (!handle) {
          CloseClipboard();
          return false;
        }

        unsigned char *ptr = (unsigned char *) GlobalLock(handle);
        BITMAPINFOHEADER *pHeader = (BITMAPINFOHEADER *) ptr;

        Allocate(pHeader->biWidth, pHeader->biHeight, pHeader->biBitCount);
        memcpy(GetPackedDibPointer(), ptr, CalcPackedDibSize(pHeader));
         
        GlobalUnlock(handle);

        CloseClipboard();

        return true;
}

BOOL CDib::SetClipboard()
{
        if (!IsInitialized()) return false;

        HANDLE handle = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, CalcPackedDibSize(GetBitmapInfoHeader()));
        if (!handle) return false;
        unsigned char *ptr = (unsigned char *) GlobalLock(handle);
        memcpy(ptr, GetPackedDibPointer(), CalcPackedDibSize(GetBitmapInfoHeader()));
        GlobalUnlock(handle);

        OpenClipboard(NULL);
        SetClipboardData(CF_DIB, handle);
        CloseClipboard();

        return true;
}

CBitmap *CDib::GetCBitmap(CDC *pDC)
{
        int byte_width = (int) ByteWidth(((long) m_pInfoHeader->biWidth)*((long) m_pInfoHeader->biBitCount));
        long image_size = ((long) byte_width) * ((long) m_pInfoHeader->biHeight);
        HDC hDC;

        if (pDC) hDC = pDC->GetSafeHdc();
        else hDC = ::GetDC(NULL);

        CBitmap *pBitmap = new CBitmap;
        BITMAPINFO *pBInfo = (BITMAPINFO *) GetBitmapInfo();
        HBITMAP hBitmap = ::CreateDIBitmap(hDC, m_pInfoHeader, CBM_INIT,
                                GetPattern(), pBInfo, DIB_RGB_COLORS); //DIB_PAL_COLORS);
        pBitmap->Attach(hBitmap);
        //pBitmap->CreateBitmap(Width(), Height(), 1, BitCount(), GetPattern());

        return pBitmap;
}                

void CDib::GetPaletteEntries(UINT nStartIndex, UINT nNumEntries, PALETTEENTRY *pEntries)
{
        int num_color = NumberOfColors();
        num_color = (num_color<=256) ? num_color : 0;
        if (nNumEntries>(UINT) num_color) {
#ifdef _DEBUG
          AfxMessageBox("??? This CDib does not have so many colors");
#endif
          return;
        }
        
        RgbQuadToPaletteEntry(m_pRgbQuad+nStartIndex, pEntries, nNumEntries);
}

void CDib::SetPaletteEntries(UINT nStartIndex, UINT nNumEntries, PALETTEENTRY *pEntries)
{
        int num_color = NumberOfColors();
        num_color = (num_color<=256) ? num_color : 0;
        if (nNumEntries>(UINT) num_color) {
#ifdef _DEBUG
          AfxMessageBox("??? This CDib does not have so many colors");
#endif
          return;
        }

        PaletteEntryToRgbQuad(pEntries, m_pRgbQuad+nStartIndex, nNumEntries);
}                                

/////////////////////////////////////////////////////////////////
// GDI Functions
void CDib::PaletteEntryToRgbQuad(PALETTEENTRY *pEntries, RGBQUAD *pRgbQuad, int count)
{
        for (int i=0; i<count ;i++, pEntries++, pRgbQuad++) {
          pRgbQuad->rgbRed = pEntries->peRed;
          pRgbQuad->rgbGreen = pEntries->peGreen;
          pRgbQuad->rgbBlue = pEntries->peBlue;
          pRgbQuad->rgbReserved = 0;
        }
}


void CDib::RgbQuadToPaletteEntry(RGBQUAD *pRgbQuad, PALETTEENTRY *pEntries, int count)
{
        for (int i=0; i<count ;i++, pEntries++, pRgbQuad++) {
          pEntries->peRed = pRgbQuad->rgbRed;
          pEntries->peGreen = pRgbQuad->rgbGreen;
          pEntries->peBlue = pRgbQuad->rgbBlue;
          pEntries->peFlags = 0;
        }
}

CPalette *CDib::GetPaletteNoFlag()
{
        if (!IsInitialized() || !HavePalette()) return NULL;

        unsigned char *pBuffer = new unsigned char [sizeof(LOGPALETTE) + sizeof(PALETTEENTRY)*256];
        LOGPALETTE *pLogPalette = (LOGPALETTE *) pBuffer;
        pLogPalette->palVersion = 0x300;
        pLogPalette->palNumEntries = (unsigned short) NumberOfColors();
        RgbQuadToPaletteEntry(m_pRgbQuad, pLogPalette->palPalEntry, NumberOfColors());

        CPalette *pPalette = new CPalette;
        pPalette->CreatePalette(pLogPalette);

        delete [] pBuffer;

        return pPalette;
}

void CDib::LoadImage(CDC *pDC, CRect *pTargetRect, CRect *pSrcRect, DWORD dwRop)
{
        if (!IsInitialized()) return;

        CRect draw_rect;
        if (!pTargetRect) draw_rect.SetRect(0, 0, Width(), Height());
        else draw_rect = *pTargetRect;

        CRect src_rect;
        if (!pSrcRect) src_rect.SetRect(0, 0, Width(), Height());
        else src_rect = *pSrcRect;

        int sy = max(0, (Height()-draw_rect.Height()));
        if (BitCount()>8) {   // Full Color Image
          StretchDIBits(pDC->GetSafeHdc(), draw_rect.left, draw_rect.top, draw_rect.Width(), draw_rect.Height(),
                        src_rect.left, src_rect.top, src_rect.Width(), src_rect.Height(),
                        m_pPattern, GetBitmapInfo(), DIB_RGB_COLORS, dwRop);
        }
        else {          // Palette Image
          BITMAPINFO *pInfo = GetCopyOfBitmapInfo();
          WORD *pIndex = (WORD *) pInfo->bmiColors;
          for (int i=0; i<(int) NumberOfColors() ;i++) pIndex[i] = i;

          StretchDIBits(pDC->GetSafeHdc(), draw_rect.left, draw_rect.top, draw_rect.Width(), draw_rect.Height(),
                        src_rect.left, src_rect.top, src_rect.Width(), src_rect.Height(),
                        m_pPattern, pInfo, DIB_PAL_COLORS, dwRop);

          delete pInfo;
        }
}

void CDib::LoadPaletteImage(CDC *pDC, CRect *pTargetRect, CRect *pSrcRect, DWORD dwRop)
{
        if (!IsInitialized()) return;

        CRect draw_rect;
        if (!pTargetRect) draw_rect.SetRect(0, 0, Width(), Height());
        else draw_rect = *pTargetRect;

        CRect src_rect;
        if (!pSrcRect) src_rect.SetRect(0, 0, Width(), Height());
        else src_rect = *pSrcRect;

        int sy = max(0, (Height()-draw_rect.Height()));
        if (BitCount()>8) {   // Full Color Image
          StretchDIBits(pDC->GetSafeHdc(), draw_rect.left, draw_rect.top, draw_rect.Width(), draw_rect.Height(),
                        src_rect.left, src_rect.top, src_rect.Width(), src_rect.Height(),
                        m_pPattern, GetBitmapInfo(), DIB_RGB_COLORS, dwRop);
        }
        else {          // Palette Image
          BITMAPINFO *pInfo = GetCopyOfBitmapInfo();
          WORD *pIndex = (WORD *) pInfo->bmiColors;
          for (int i=0; i<(int) NumberOfColors() ;i++) pIndex[i] = i;

          CPalette *pPalette = GetPaletteNoFlag();
          CPalette *pOldPalette = pDC->SelectPalette(pPalette, false);
          pDC->RealizePalette();

          StretchDIBits(pDC->GetSafeHdc(), draw_rect.left, draw_rect.top, draw_rect.Width(), draw_rect.Height(),
                        src_rect.left, src_rect.top, src_rect.Width(), src_rect.Height(),
                        m_pPattern, pInfo, DIB_PAL_COLORS, dwRop);

          pDC->SelectPalette(pOldPalette, false);
          delete pPalette;

          delete pInfo;
        }
}

/////////////////////////////////////////////////////////////////
// Serialization
void CDib::Serialize(CArchive& ar)
{
        if (ar.IsStoring()) {
          if (!IsInitialized()) return;

          // write bitmap file header
          BITMAPFILEHEADER bfHeader;
          bfHeader.bfType = TYPE_BITMAP;
          bfHeader.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER)
                             + (DWORD) sizeof(BITMAPINFOHEADER)
                             + (DWORD) PaletteSize();
          bfHeader.bfSize = bfHeader.bfOffBits + ByteWidth()*Height();
          bfHeader.bfReserved1 = bfHeader.bfReserved2 = 0;

          ar.Write(&bfHeader, sizeof(BITMAPFILEHEADER));

          // write bitmap info header
          ar.Write(m_pInfoHeader, sizeof(BITMAPINFOHEADER));

          // write palette
          if (PaletteSize()>0) 
            ar.Write(m_pRgbQuad, PaletteSize());

          // write image data
          ar.Write(m_pPattern, ByteWidth()*Height());
        }
        else {
          if (IsInitialized()) DestroyContents();

          // read in BITMAPFILEHEADER
          BITMAPFILEHEADER bfHeader;
          ar.Read(&bfHeader, sizeof(BITMAPFILEHEADER));
          if (bfHeader.bfType!=TYPE_BITMAP) {
            TRACE0("??? This File is NOT a BMP File");
            return;
          }
          
          // read in BITMAPINFOHEADER
          BITMAPINFOHEADER biHeader;
          ar.Read(&biHeader, sizeof(BITMAPINFOHEADER));

          int p_size; 
          switch (biHeader.biBitCount) {
            case 1 : p_size = 2 * sizeof(PALETTEENTRY); break;
            case 4 : p_size = 16 * sizeof(PALETTEENTRY); break;
            case 8 : p_size = 256 * sizeof(PALETTEENTRY); break;
            default : p_size = 0;
          }
          int skip = bfHeader.bfOffBits - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER) - p_size;
          if (skip>0) {
            char *pTemp = new char [skip];
            ar.Read(pTemp, skip);
            delete [] pTemp;
          }

          DWORD size = CalcPackedDibSize(&biHeader);

          m_pPackedDib = new unsigned char[size];
          memcpy(m_pPackedDib, &biHeader, sizeof(BITMAPINFOHEADER));

          ar.Read(m_pPackedDib+sizeof(BITMAPINFOHEADER), size-sizeof(BITMAPINFOHEADER));

          AssignReferenceVariables();
        }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// CDibArray
CDibArray::CDibArray()
{
}

CDibArray::~CDibArray()
{
	ResetContents();
}

void CDibArray::RemoveTail(int nFrom)
{
	int count=0;
	for (int i=nFrom; i<GetSize() ;i++) {
	  delete GetAt(i);
	  count++;
	}
	if (count>0) RemoveAt(nFrom, count);
}

void CDibArray::ResetContents()
{
	for (int i=0; i<GetSize() ;i++)
	  delete GetAt(i);
	RemoveAll();
}

#endif

