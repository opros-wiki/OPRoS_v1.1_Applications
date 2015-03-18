

#ifndef _FaceDetectImgService_PROVIDED_PORT_H
#define _FaceDetectImgService_PROVIDED_PORT_H

#include <OPRoSTypes.h>
#include <InputDataPort.h>
#include <OutputDataPort.h>
#include <InputEventPort.h>
#include <OutputEventPort.h>
#include <ProvidedServicePort.h>
#include <RequiredServicePort.h>
#include <ProvidedMethod.h>
#include <RequiredMethod.h>


#include <string>


#ifndef _IFaceDetectImgService_CLASS_DEF
#define _IFaceDetectImgService_CLASS_DEF
/*
 * IFaceDetectImgService
 *
 *  The comonent inherits this class and implements methods. 
 */
class IFaceDetectImgService
{
 public:


    virtual std::vector<RECT> GetImgFD(std::string imgFileName)=0;


 };
#endif

/*
 * 
 * FaceDetectImgService : public ProvidedServicePort
 *
 */
class FaceDetectImgServiceProvided
	:public ProvidedServicePort, public IFaceDetectImgService
{
protected:
    IFaceDetectImgService *pcom;


   typedef ProvidedMethod< std::vector<RECT> > GetImgFDFuncType;
   GetImgFDFuncType *GetImgFDFunc;


public: // default method
   virtual std::vector<RECT> GetImgFD(std::string imgFileName)
   {
		opros_assert(GetImgFDFunc != NULL);
		
            return (*GetImgFDFunc)(imgFileName);
		
   }


public:
    //
    // Constructor
    //
    FaceDetectImgServiceProvided(IFaceDetectImgService *fn)
    {
        pcom = fn;

        GetImgFDFunc = NULL;
        

        setup();
    }



    // generated setup function
    virtual void setup()
    {
        Method *ptr_method;
    
        ptr_method = makeProvidedMethod(&IFaceDetectImgService::GetImgFD,pcom,"GetImgFD");

        opros_assert(ptr_method != NULL);
        addMethod("GetImgFD",ptr_method);
        GetImgFDFunc = reinterpret_cast<GetImgFDFuncType *>(ptr_method);
        ptr_method = NULL;

    
    }
};
#endif
