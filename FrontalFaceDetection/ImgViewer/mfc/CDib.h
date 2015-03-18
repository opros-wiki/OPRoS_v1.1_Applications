/////////////////////////////////////////////////////////////////////////
// CDib class : bitmap image manipulation
//.......................................................................
// 2004/05/15, Intelligent Robot Research Division, ETRI
/////////////////////////////////////////////////////////////////////////

//#ifndef _WINDOWS
//#include </home/hschae/leejy/Windef.h>
//#endif


#ifndef _CDIB_H_
#define _CDIB_H_

typedef CArray<RECT, RECT> RectArray;



#define WIDTHBYTES(bits)        (((bits) + 31) / 32 * 4)
#define TYPE_BITMAP             ((WORD) ('M' << 8) | 'B')

class CDib
{
// protected data members
protected:
        unsigned char           *m_pPackedDib;

        // references
        BITMAPINFO              *m_pInfo;
        BITMAPINFOHEADER        *m_pInfoHeader;
        RGBQUAD                 *m_pRgbQuad;
        unsigned char           *m_pPattern;

// static data member
public:
        static unsigned char m_BitMask[8];

// constructor and destructors
public:
        CDib();
        CDib(const char *pFileName);
        CDib(int width, int height, int bitcount, unsigned char *pPattern,
				RGBQUAD *pRgbQuad=NULL);
        ~CDib();

// Protected Operations
protected:
        void ResetVariables();
        void DestroyContents();
        void AssignReferenceVariables();
        BITMAPINFO *GetCopyOfBitmapInfo();

// File Operations
public:
        BOOL ReadImage(const char *pFileName);
        BOOL SaveImage(const char *pFileName);

// Data Allocation
public:
        // raw pattern을 가지고 있는 경우, CDib를 초기화
        void Initialize(int width, int height, int bitcount, unsigned char *pPattern,
					    RGBQUAD *pRgbQuad=NULL);
        // pattern은 지정하지 않고, memory만 allocate
        void Allocate(int width, int height, int bitcount);
        // Windows의 Packed DIB format에 의한 CDib의 초기화 
        void LoadPackedDib(void *pPackedDib);

// Information Functions
public:
        inline LONG Width();
        inline LONG Height();
        inline WORD BitCount();         // Windows BMP의 경우, bitcount는 1, 4, 8, 16, 24, 32임.
        inline BOOL HavePalette();      // 16 bit 이하의 Dib는 Palette를 가짐.
        inline BITMAPINFO *GetBitmapInfo();
        inline BITMAPINFOHEADER *GetBitmapInfoHeader();
        inline WORD ByteWidth();        // Width in Bytes (aligned to 4 bytes)
        static inline WORD ByteWidth(LONG nbits);
        inline BOOL IsInitialized();

        inline unsigned char *GetPackedDibPointer();
        inline unsigned char *GetPattern();             // pattern부에 대한 pointer
        unsigned char *GetPointer(int x, int y);        // 좌표 (x, y)에 대한 pointer
        unsigned char Intensity(int x, int y);          // 좌표 (x, y)의 pixel의 gray값 (color image의 경우, gray로 conversion 됨)
        unsigned char GetIndex(int x, int y);           // Palette Image의 index, full color의 경우는 0이 return됨
        RGBQUAD GetColor(int x, int y);                 // 좌표 위치 pixel의 color 값
		inline RGBQUAD *GetRgbQuadPointer();
        DWORD PaletteSize();     // size of palette entry data in bytes
        DWORD NumberOfColors();  // number of palette colors
        static DWORD CalcPackedDibSize(BITMAPINFOHEADER *pBi);
        static void RGBtoYIQ(RGBQUAD rgb, unsigned char *y, unsigned char *i, unsigned char *q);
        static unsigned char GetBrightness(RGBQUAD rgb);

// Create New CDib Functions
public:
        // Color CDib로부터 흑백 CDib를 작성
        CDib *GetGrayCDib();

		CDib *GetGrayCDibAver();
		CDib *GetGrayCDibInt();




        // 똑같은 CDib를 작성
        CDib *CopyCDib();
        // Size를 변경한 CDib를 작성
        CDib *GetSizedCDib(int width, int height=0);
        // Edge를 추출한 CDib를 작성 (8 bit gray image)
        CDib *GetEdgeCDib(double threshold, BOOL bIsGray=false);
		// Clipping of the Image
		CDib *ClipCDib(RECT *pRect);
		CDib *ClipCDib(int left, int top, int right, int bottom);

// Operations
public:
        void SetPaletteEntries(UINT nStartIndex, UINT nNumEntries, PALETTEENTRY *pEntries);     // set color table
        void GetPaletteEntries(UINT nStartIndex, UINT nNumEntries, PALETTEENTRY *pEntries);     // get color table
        void SetGrayPalette();          // set current palette to gray palette
        void Inverse();
        void UpsideDown();              // 패턴의 상하 바꿈
        void ResetContents();           // pattern을 무조건 0으로
        static RGBQUAD Decode16(WORD data);
        static WORD Encode16(unsigned char red, unsigned char green, unsigned char blue);

        // 패턴의 일부를 copy 할 경우
        BOOL CopyRect(RECT *pTargetRect, CDib *pSrCDib, RECT *pSrcRect, int BackColor);

        // Get Image Dimension Without Loading it
        static BOOL GetImageInfoBmp(const char *pFileName, UINT *pWidth, UINT *pHeight, UINT *pBitCount);


// Additional Functions
        BOOL IsGrayImage();
        void SplitChannel(CDib **pDibR, CDib **pDibG, CDib **pDibB);
        static CDib *MergeChannel(CDib *pDibR, CDib *pDibG, CDib *pDibB, int bitcount=24);

// Windows Specific Functions
#ifdef _WINDOWS
public:
        BOOL GetClipboard();
        BOOL SetClipboard();
        void Serialize(CArchive& ar);

// GDI Operations
        //CPalette *GetPalette();
        //CPalette *GetPaletteNoCollapse();
        CPalette *GetPaletteNoFlag();
        CBitmap *GetCBitmap(CDC *pDC=NULL);

        static void PaletteEntryToRgbQuad(PALETTEENTRY *pEntries, RGBQUAD *pRgbQuad, int count); 
        static void RgbQuadToPaletteEntry(RGBQUAD *pRgbQuad, PALETTEENTRY *pEntries, int count);

        // CDib Object를 화면 (pDC)에 그림 
        void LoadImage(CDC *pDC, CRect *pRectTarget=NULL, 
                       CRect *pRectSource=NULL, DWORD dwRop=SRCCOPY);
        // LoadImage와 같은 기능이나, Palette Operation까지를 function내에서 처리
        void LoadPaletteImage(CDC *pDC, CRect *pRectTarget=NULL,
                       CRect *pRectSource=NULL, DWORD dwRop=SRCCOPY);
#endif
};

inline LONG CDib::Width()
{
        return m_pInfoHeader->biWidth;
}

inline LONG CDib::Height()
{
        return m_pInfoHeader->biHeight;
}

inline WORD CDib::BitCount()
{
        return m_pInfoHeader->biBitCount;
}

inline BOOL CDib::HavePalette()
{
        return (BitCount()<=8);
}

inline BITMAPINFO * CDib::GetBitmapInfo()
{
        return m_pInfo;
}

inline BITMAPINFOHEADER * CDib::GetBitmapInfoHeader()
{
        return m_pInfoHeader;
}

inline WORD CDib::ByteWidth()
{
        return (WORD) ByteWidth(m_pInfoHeader->biWidth * m_pInfoHeader->biBitCount);
}

inline WORD CDib::ByteWidth(LONG nbits)
{
        return WIDTHBYTES(nbits);
}

inline BOOL CDib::IsInitialized()
{
        return (m_pPackedDib!=NULL);
}

inline unsigned char * CDib::GetPattern()
{
        return m_pPattern;
}

inline unsigned char * CDib::GetPackedDibPointer()
{
        return m_pPackedDib;
}

inline RGBQUAD *CDib::GetRgbQuadPointer()
{
    return m_pRgbQuad;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
// CDib Array type
class CDibArray : public CArray<CDib *, CDib *>
{
// constructors and destructors
public:
	CDibArray();
	~CDibArray();

// public operations
public:
	void RemoveTail(int nFrom);
	void ResetContents();
/*
	// ms try
	CDibArray(const CDibArray &s)
	{ *this = s; }
	CDibArray& operator=( const CDibArray &s )
	{ return *this; }
*/
};


#endif //CDIB