
#include "stdafx.h"
	
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


#include "FaceDetectImgServiceRequired.h"
	

#include "ImgViewer.h"


//
// constructor declaration
//
ImgViewer::ImgViewer()
		:DetectedFaces(OPROS_FIFO,10)
{
	ptrFaceDetectImgService = NULL;
	
	portSetup();
}

//
// constructor declaration (with name)
//
ImgViewer::ImgViewer(const std::string &name):Component(name)
		,DetectedFaces(OPROS_FIFO,10)
{
	ptrFaceDetectImgService = NULL;

	dlg = NULL;

	portSetup();
}

//
// destructor declaration
//

ImgViewer::~ImgViewer() {

	if (dlg != NULL) dlg->EndDialog(1);

	dlg = NULL;

}

void ImgViewer::portSetup() {

	// required service port setup

	ptrFaceDetectImgService=new FaceDetectImgServiceRequired();
	addPort("FaceDetectImgService",ptrFaceDetectImgService);

	// data port setup

	addPort("DetectedFaces", &DetectedFaces);

	// event port setup

	addPort("ImgFileName", &ImgFileName);
	ImgFileName.setOwner(this);



	// export variable setup


}


ReturnType ImgViewer::onStart()
{
std::cout<<"ImgViewer : onStart : "<<std::endl;
	// user code here
	imgName=getProperty("ImgFileName");
	if(imgName.empty()==1)
		imgName="kara.bmp";
	return OPROS_SUCCESS;
}
	
ReturnType ImgViewer::onStop()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType ImgViewer::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType ImgViewer::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType ImgViewer::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType ImgViewer::onDestroy()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType ImgViewer::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType ImgViewer::onExecute()
{
	// user code here
std::cout<<"ImgViewer : onExecute : "<<std::endl;
	//rectVector=ptrFaceDetectImgService->GetImgFD(imgName);
	
	int size=rectVector.size();
	std::cout<<size<<" faces are detected! "<<std::endl;

	return OPROS_SUCCESS;
}
	
ReturnType ImgViewer::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType ImgViewer::onPeriodChanged()
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

UINT MyThreadProc( LPVOID pParam )
{    
	AFX_MANAGE_STATE(AfxGetStaticModuleState());	

	ImgViewer *pcom = (ImgViewer *)pParam;

	
	

	ViewerDlg dlg; //::AfxGetMainWnd());
	


	pcom->dlg =  &dlg;
	
	dlg.DoModal();;
	pcom->dlg = NULL;	
	

    return 0;   // thread completed successfully
}

// Call back Declaration
ReturnType ImgViewer::onInitialize()
{
std::cout<<"ImgViewer : onInitialize : "<<std::endl;
	// user code here
	AfxBeginThread(MyThreadProc,this);	

	return OPROS_SUCCESS;
}

Component *getComponent()
{
	return new ImgViewer();
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
	return new ImgViewer();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

