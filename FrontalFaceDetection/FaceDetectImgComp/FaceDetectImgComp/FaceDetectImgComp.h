
#ifndef _FaceDetectImgComp_COMPONENT_H
#define _FaceDetectImgComp_COMPONENT_H
/*
 *  Generated sources by OPRoS Component Generator (OCG V2.0[Symbol])
 *   
 */
#include <Component.h>
#include <InputDataPort.h>
#include <OutputDataPort.h>
#include <InputEventPort.h>
#include <OutputEventPort.h>
#include <Event.h>
#include <OPRoSTypes.h>




#include "tagRECT.h"
//#include "RectArray.h"

#include "FaceDetectImgServiceProvided.h"

class FaceDetectImgComp: public Component
	,public IFaceDetectImgService
{
protected:
//data
	OutputDataPort< tagRECT > DetectedFaces;

protected:
// event
	InputEventPort< std::string > ImgFileName;

protected:
// service
// method for provider
	IFaceDetectImgService *ptrFaceDetectImgService;

public:
virtual std::vector<RECT> GetImgFD(std::string imgFileName);

protected:
// data


//event


// method for provider
	

// method for required
	


// symbol value generation
	

public:
	FaceDetectImgComp();
	FaceDetectImgComp(const std::string &compId);
	virtual ~FaceDetectImgComp();
	virtual void portSetup();

protected:
	virtual ReturnType onInitialize();
	virtual ReturnType onStart();
	virtual ReturnType onStop();
	virtual ReturnType onReset();
	virtual ReturnType onError();
	virtual ReturnType onRecover();
	virtual ReturnType onDestroy();

public:
	virtual ReturnType onEvent(Event *evt);
	virtual ReturnType onExecute();
	virtual ReturnType onUpdated();
	virtual ReturnType onPeriodChanged();


};

#endif

