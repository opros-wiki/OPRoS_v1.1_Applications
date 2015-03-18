
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



#include "Viewer.h"

//
// constructor declaration
//
Viewer::Viewer()
		:detectedFaces(OPROS_FIFO,10)
{

	
	portSetup();
}

//
// constructor declaration (with name)
//
Viewer::Viewer(const std::string &name):Component(name)
		,detectedFaces(OPROS_FIFO,10)
{

	dlg = NULL;
	
	portSetup();
}

//
// destructor declaration
//

Viewer::~Viewer() {

	if (dlg != NULL) dlg->EndDialog(1);

	dlg = NULL;

}

void Viewer::portSetup() {

	// data port setup

	addPort("detectedFaces", &detectedFaces);

	// event port setup

	addPort("imgFileName", &imgFileName);
	imgFileName.setOwner(this);



	// export variable setup


}


ReturnType Viewer::onStart()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType Viewer::onStop()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType Viewer::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType Viewer::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType Viewer::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType Viewer::onDestroy()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType Viewer::onEvent(Event *evt)
{
	// user code here

	if(evt->getId().compare("FileName") == 0 )
	{
		EventData<std::string> *pStrEvt=(EventData<std::string> *)(evt);
		imgName=*(pStrEvt->getContentData());
//std::cout<<"FDComp : file name: "<<imgName<<std::endl;
		dlg->setFileName(imgName.c_str());
	}

	return OPROS_SUCCESS;
}

ReturnType Viewer::onExecute()
{
	// user code here

	opros_any *pData;

	int numFaces=detectedFaces.getSize();

	for(int i=0; i<numFaces; i++)
	{
		pData=detectedFaces.pop();
		inRectArray.Add(detectedFaces.getContent(*pData));
	}

std::cout<<"[Viewer] : num faces : "<< numFaces <<std::endl;

	dlg->setRectArray(&inRectArray);

	delete pData;





	return OPROS_SUCCESS;
}
	
ReturnType Viewer::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType Viewer::onPeriodChanged()
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

	Viewer *pcom = (Viewer *)pParam;

	
	

	ViewerDlg dlg; //::AfxGetMainWnd());
	


	pcom->dlg =  &dlg;
	
	dlg.DoModal();;
	pcom->dlg = NULL;	
	

    return 0;   // thread completed successfully
}

// Call back Declaration
ReturnType Viewer::onInitialize()
{
	// user code here
	AfxBeginThread(MyThreadProc,this);	

	return OPROS_SUCCESS;
}


Component *getComponent()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	Viewer *pcom = new Viewer();
	
	return pcom;
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
	return new Viewer();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

