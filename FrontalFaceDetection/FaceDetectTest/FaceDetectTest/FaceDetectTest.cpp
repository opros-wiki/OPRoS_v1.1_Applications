
/*
 *  Generated sources by OPRoS Component Generator (OCG V2.1 [Symbol,Topic])
 *  
 */
#include <Component.h>
#include <InputDataPort.h>
#include <OutputDataPort.h>
#include <InputEventPort.h>
#include <OutputEventPort.h>
#include <OPRoSTypes.h>
#include <EventData.h>
#include <ServiceUtils.h>



#include "FaceDetectTest.h"

//
// constructor declaration
//
FaceDetectTest::FaceDetectTest()
{

	
	portSetup();
}

//
// constructor declaration (with name)
//
FaceDetectTest::FaceDetectTest(const std::string &name):Component(name)
{

	
	portSetup();
}

//
// destructor declaration
//

FaceDetectTest::~FaceDetectTest() {
}

void FaceDetectTest::portSetup() {
	//event port setup
	addPort("imgFileName", &imgFileName);




	// export variable setup


}

// Call back Declaration
ReturnType FaceDetectTest::onInitialize()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType FaceDetectTest::onStart()
{
	// user code here
	fileName=getProperty("imgFileName");
	if(fileName.empty()==1)
		fileName="kara.bmp";

	return OPROS_SUCCESS;
}
	
ReturnType FaceDetectTest::onStop()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType FaceDetectTest::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType FaceDetectTest::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType FaceDetectTest::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType FaceDetectTest::onDestroy()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType FaceDetectTest::onEvent(Event *evt)
{
	// user code here


	return OPROS_SUCCESS;
}

ReturnType FaceDetectTest::onExecute()
{
	// user code here

	EventData<std::string> evtData;
	evtData.setId("FileName");
	evtData.setContentData(fileName);
	imgFileName.push(&evtData);


	return OPROS_SUCCESS;
}
	
ReturnType FaceDetectTest::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType FaceDetectTest::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}







#ifndef MAKE_STATIC_COMPONENT
#ifdef WIN32

extern "C"
{
__declspec(dllexport) Component *getComponent();
__declspec(dllexport) void releaseComponent(Component *pcom);
}

Component *getComponent()
{
	return new FaceDetectTest();
}

void releaseComponent(Component *com)
{
	delete com;
}

#else
extern "C"
{
	Component *getComponent();
	void releaseComponent(Component *com);
}
Component *getComponent()
{
	return new FaceDetectTest();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

