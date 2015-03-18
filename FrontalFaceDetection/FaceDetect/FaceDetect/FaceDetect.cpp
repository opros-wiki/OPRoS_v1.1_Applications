
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



#include "FaceDetect.h"

//
// constructor declaration
//
FaceDetect::FaceDetect()
{

	
	portSetup();
}

//
// constructor declaration (with name)
//
FaceDetect::FaceDetect(const std::string &name):Component(name)
{

	
	portSetup();
}

//
// destructor declaration
//

FaceDetect::~FaceDetect() {
}

void FaceDetect::portSetup() {
	//event port setup
	addPort("imgFileName", &imgFileName);
	imgFileName.setOwner(this);

	//data port setup
	addPort("detectedFaces", &detectedFaces);




	// export variable setup


}

// Call back Declaration
ReturnType FaceDetect::onInitialize()
{
	// user code here

	//----------------------------
	//	얼굴검출엔지 초기화
	//----------------------------
	char *pFDFileName = "data_fd.dat";
	char *pFVFileName = "data_fv.dat";
	ETRIFD_Initialize(pFDFileName, pFVFileName);

	return OPROS_SUCCESS;
}

ReturnType FaceDetect::onStart()
{
	// user code here

	return OPROS_SUCCESS;
}
	
ReturnType FaceDetect::onStop()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType FaceDetect::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType FaceDetect::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType FaceDetect::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType FaceDetect::onDestroy()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType FaceDetect::onEvent(Event *evt)
{
	// user code here

	if(evt->getId().compare("FileName") == 0 )
	{
		EventData<std::string> *pStrEvt=(EventData<std::string> *)(evt);
		imgName=*(pStrEvt->getContentData());
//std::cout<<"FDComp : file name: "<<imgName<<std::endl;
		
	}

	return OPROS_SUCCESS;
}

ReturnType FaceDetect::onExecute()
{
	// user code here
//std::cout<<"send detected face data"<<std::endl;

	if(imgName.empty() != 1)
	{
	//------------------------------------------------------
	//	얼굴검출기에 입력될 비트맵 정지 영상 로딩
	//------------------------------------------------------
	  CDib *pDib = NULL;
	  pDib = new CDib(imgName.c_str());


	//----------------------------
	//	얼굴검출
	//----------------------------
	  RectArray *pRectArray = ETRIFD_DetectFace(pDib);

	  delete pDib;


		if(pRectArray!= NULL)
		{
			int numFaces = pRectArray->GetSize();
std::cout<<"[FaceDetect] : there are "<<numFaces<<" detected faces. "<<std::endl;
			for(int i = 0; i < numFaces; i++)
			{
				RECT rt = pRectArray->GetAt(i);
				detectedFaces.push(rt);
			}
		
		  delete pRectArray;
		}
		else
std::cout<<"[FaceDetect] : no face!"<<std::endl;


	}

	return OPROS_SUCCESS;
}
	
ReturnType FaceDetect::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType FaceDetect::onPeriodChanged()
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
	return new FaceDetect();
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
	return new FaceDetect();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

