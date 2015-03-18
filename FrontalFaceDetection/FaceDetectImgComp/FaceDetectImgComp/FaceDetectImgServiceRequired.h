

#ifndef _FaceDetectImgService_REQUIRED_PORT_H
#define _FaceDetectImgService_REQUIRED_PORT_H

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
		



/*
 * 
 * FaceDetectImgService : public RequiredServicePort
 *
 */
class FaceDetectImgServiceRequired
   :public RequiredServicePort
{
protected:

	typedef RequiredMethod<RectArray> GetImgFDFuncType;
	GetImgFDFuncType *GetImgFDFunc;

public:
	//
	// Constructor
	//
	FaceDetectImgServiceRequired()
	{
            GetImgFDFunc = NULL;
            
	   setup();
	}

	// method implementation for required method
	RectArray GetImgFD(std::string imgFileName)
	{
            opros_assert(GetImgFDFunc != NULL);
	
            return (*GetImgFDFunc)(imgFileName);
		
	}

	

    // generated setup function
    virtual void setup()
    {
        Method *ptr_method;
    
        ptr_method = makeRequiredMethod(&FaceDetectImgServiceRequired::GetImgFD,"GetImgFD");
        opros_assert(ptr_method != NULL);
        addMethod("GetImgFD",ptr_method);
        GetImgFDFunc = reinterpret_cast<GetImgFDFuncType *>(ptr_method);
        ptr_method = NULL;

    
    }
};
#endif
