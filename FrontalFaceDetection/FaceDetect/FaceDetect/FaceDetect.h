
#ifndef _FaceDetect_COMPONENT_H
#define _FaceDetect_COMPONENT_H
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

class FaceDetect: public Component
{
protected:
//data
	OutputDataPort< tagRECT > detectedFaces;

protected:
// event
	InputEventPort< std::string > imgFileName;

protected:
// data


//event


// method for provider
	

// method for required
	


// symbol value generation
	

public:
	FaceDetect();
	FaceDetect(const std::string &compId);
	virtual ~FaceDetect();
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

	std::string imgName;
};

#endif

