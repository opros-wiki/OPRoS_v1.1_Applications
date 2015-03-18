

typedef CArray<RECT, RECT> RectArray;

// function declarations
#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

__declspec(dllexport) bool ETRIFD_Initialize(char *pFDFileName, char *pFVFileName);
__declspec(dllexport) RectArray* ETRIFD_DetectFace(CDib *pDib);


#ifdef __cplusplus
}
#endif


