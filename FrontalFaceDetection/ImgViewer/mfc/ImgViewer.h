
#include "ImgViewerApp.h"
	
#ifndef _ImgViewer_COMPONENT_H
#define _ImgViewer_COMPONENT_H
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
		
#include <string>
		
#include "FaceDetectImgServiceRequired.h"

#include "ViewerDlg.h"	
class ViewerDlg;

class ImgViewer: public Component
{
protected:
// data

	InputDataPort< tagRECT > DetectedFaces;

//event

	InputEventPort< std::string > ImgFileName;

// method for provider
	

// method for required
	FaceDetectImgServiceRequired *ptrFaceDetectImgService;



// symbol value generation
	

public:
	ImgViewer();
	ImgViewer(const std::string &compId);
	virtual ~ImgViewer();
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

	ViewerDlg *dlg;
	std::string imgName;
	RECT inRect;
	RectArray inRectArray;
	std::vector<RECT> rectVector;

};

#endif

