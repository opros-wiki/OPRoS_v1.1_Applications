
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



#include "FaceDetectImgComp.h"

//
// constructor declaration
//
FaceDetectImgComp::FaceDetectImgComp()
{

	
	portSetup();
}

//
// constructor declaration (with name)
//
FaceDetectImgComp::FaceDetectImgComp(const std::string &name):Component(name)
{

	
	portSetup();
}

//
// destructor declaration
//

FaceDetectImgComp::~FaceDetectImgComp() {
}

std::vector<RECT> FaceDetectImgComp::GetImgFD(std::string imgFileName)
{
	//user code hear
std::cout<<"FaceDetectImgComp: GetImgFD: imgFileName"<<imgFileName<<std::endl;
	std::vector<RECT> rRect;

	//----------------------------
	//	�󱼰��⿣�� �ʱ�ȭ
	//----------------------------
	char *pFDFileName = "data_fd.dat";
	char *pFVFileName = "data_fv.dat";
	ETRIFD_Initialize(pFDFileName, pFVFileName);

	//------------------------------------------------------
	//	�󱼰���⿡ �Էµ� ��Ʈ�� ���� ���� �ε�
	//------------------------------------------------------
	CDib *pDib = NULL;
	pDib = new CDib(imgFileName.c_str());


	//----------------------------
	//	�󱼰���	
	//----------------------------
	RectArray *pRectArray = ETRIFD_DetectFace(pDib);

/*
	//----------------------------
	//	������ ȭ�� ���	
	//----------------------------
	CDC *pDC = m_picMain1.GetDC();
	pDC->SelectStockObject(NULL_BRUSH);
	pDib->LoadPaletteImage(pDC);	// ������ �׸���
	delete pDib;

	if(pRectArray == NULL)		return;	// ���� �ϳ��� ������� ���� ���
	for(int i = 0; i < pRectArray->GetSize(); i++)
	{
		RECT rt = pRectArray->GetAt(i);
		pDC->Rectangle(&rt);	// ���⿵�� �׸���
	}
	ReleaseDC(pDC);
*/

	if(pRectArray == NULL)		std::cout<<"No faces!"<<std::endl; // ���� �ϳ��� ������� ���� ���
	else
	{
		for(int i = 0; i < pRectArray->GetSize(); i++)
		{
			RECT rt = pRectArray->GetAt(i);
			rRect.push_back(rt); 
		}
		std::cout<<"face is detected!!"<<std::endl;
	}

	delete pRectArray;

	return rRect;
}


void FaceDetectImgComp::portSetup() {
	ProvidedServicePort *pa1;
	pa1=new FaceDetectImgServiceProvided(this);
	addPort("FaceDetectImgService",pa1);

	//event port setup
	addPort("ImgFileName", &ImgFileName);
	ImgFileName.setOwner(this);

	//data port setup
	addPort("DetectedFaces", &DetectedFaces);




	// export variable setup


}

// Call back Declaration
ReturnType FaceDetectImgComp::onInitialize()
{
	// user code here
std::cout<<"FaceDetectImgComp: onInitialize"<<std::endl;
	return OPROS_SUCCESS;
}

ReturnType FaceDetectImgComp::onStart()
{
	// user code here
std::cout<<"FaceDetectImgComp: onStart"<<std::endl;
	return OPROS_SUCCESS;
}
	
ReturnType FaceDetectImgComp::onStop()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType FaceDetectImgComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType FaceDetectImgComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType FaceDetectImgComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType FaceDetectImgComp::onDestroy()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType FaceDetectImgComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType FaceDetectImgComp::onExecute()
{
	// user code here
std::cout<<"FaceDetectImgComp: onExecute"<<std::endl;
	return OPROS_SUCCESS;
}
	
ReturnType FaceDetectImgComp::onUpdated()
{
	// user code here
std::cout<<"FaceDetectImgComp: onUpdate"<<std::endl;
	return OPROS_SUCCESS;
}

ReturnType FaceDetectImgComp::onPeriodChanged()
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
	return new FaceDetectImgComp();
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
	return new FaceDetectImgComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

