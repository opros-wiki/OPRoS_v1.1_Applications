
#include "ViewerApp.h"
	
#ifndef _Viewer_COMPONENT_H
#define _Viewer_COMPONENT_H
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
		
//#include <string>
		
#include "ViewerDlg.h"

 class ViewerDlg;

class Viewer: public Component
{
protected:
// data

	InputDataPort< tagRECT > detectedFaces;

//event

	InputEventPort< std::string > imgFileName;

// method for provider
	

// method for required
	


// symbol value generation
	

public:
	Viewer();
	Viewer(const std::string &compId);
	virtual ~Viewer();
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

};

#endif

