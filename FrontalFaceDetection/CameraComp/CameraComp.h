
#ifndef _CameraComp_COMPONENT_H
#define _CameraComp_COMPONENT_H
/*
 *  Generated sources by OPRoS Component Generator (OCG V2.0[Symbol])
 *   
 */
#include "opencv/cv.h"
#include "opencv/highgui.h"

#include <Component.h>
#include <InputDataPort.h>
#include <OutputDataPort.h>
#include <InputEventPort.h>
#include <OutputEventPort.h>
#include <Event.h>
#include <OPRoSTypes.h>
//#include <//OprosLock.h>



#include "CameraServiceProvided.h"
#include "Camera.h"

#define IMAGE_FORMAT_GRAY	0
#define IMAGE_FORMAT_YCBCR	1
#define IMAGE_FORMAT_RGB		2
#define IMAGE_FORMAT_JPEG		3
#define IMAGE_FORMAT_PNG		4

class CameraComp: public Component
	,public ICameraService
{
protected:
	//data
	OutputDataPort< OPRoS::CameraData > cameraData;

	//	Shared(Dynamic Linked) Library's Handle
#if defined(WIN32)
	OprosDeviceHandle hOprosAPI;
#else
	void *hOprosAPI;
#endif

	//	Last Error
	ReturnType lastError;

	//	API's Handle
	Camera *camera;	

	OPRoS::Property parameter;
	
	IplImage *image;
	int32_t _width;
	int32_t _height;
	int32_t _colorType;
	int32_t _compressType;
	std::vector<char*> compTypeStr;
protected:
// service
// method for provider
	ICameraService *ptrCameraService;

public:
virtual ReturnType SetProperty(OPRoS::Property props);
virtual OPRoS::Property GetProperty();
virtual ReturnType GetError();
virtual ReturnType Enable();
virtual ReturnType Disable();

virtual OPRoS::CameraData GetImage();

protected:
// data


//event


// method for provider
	

// method for required
	


// symbol value generation
	

public:
	CameraComp();
	CameraComp(const std::string &compId);
	virtual ~CameraComp();
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

