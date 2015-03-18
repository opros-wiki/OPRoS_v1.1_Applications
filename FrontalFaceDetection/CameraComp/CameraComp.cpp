/*************************************************************

 file: CameraComp.cpp
 author: E.C. Shin
begin: January 31 2011
 copyright: (c) 2011 KITECH, OPRoS
 email: unchol@kitech.re.kr

***************************************************************

OPRoS source code is provided under a dual license mode:
 LGPL and OPRoS individually.

LGPL: You can redistribute it and/or modify it under the terms
 of the Less GNU General Public License as published by the Free
 Software Foundation, either version 3 of the License.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of 
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 Less GNU General Public License for more details. 

 You should have received a copy of the Less GNU General Public
 License along with this program. If not, see 
 <http://www.gnu.org/licenses/>.

OPRoS individual license: An individual license is a license for
 modifying the source code of OPRoS and distiributing it in a
 closed format for commercial purposes.

 If you are interested in this option, please see 
 <http://www.opros.or.kr>.

This license policy may be changed without prior notice.

***************************************************************/

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



#include "CameraComp.h"
#include "OprosPrintMessage.h"
//#include "../CommonLib/StatusTester.h"

//
// constructor declaration
//
CameraComp::CameraComp()
{
	hOprosAPI = NULL;
	camera = NULL;
	lastError = OPROS_SUCCESS;

	portSetup();
}

//
// constructor declaration (with name)
//
CameraComp::CameraComp(const std::string &name):Component(name)
{
	hOprosAPI = NULL;
	camera = NULL;
	lastError = OPROS_SUCCESS;
	
	portSetup();
}

//
// destructor declaration
//

CameraComp::~CameraComp() {
	onDestroy();
}

ReturnType CameraComp::SetProperty(OPRoS::Property props)
{
	// Check property integrity
	if(props.FindName("Version") == false) {
		return lastError = OPROS_BAD_INPUT_PARAMETER;
	}
	if(atof(props.GetValue("Version").c_str()) != 1.1) {
		return lastError = OPROS_BAD_INPUT_PARAMETER;
	}

	char name[1024];
	sprintf(name, "CameraID");		if(props.FindName(name) == false)	return lastError = OPROS_BAD_INPUT_PARAMETER;
	sprintf(name, "x");		if(props.FindName(name) == false)	return lastError = OPROS_BAD_INPUT_PARAMETER;
	sprintf(name, "y");		if(props.FindName(name) == false)	return lastError = OPROS_BAD_INPUT_PARAMETER;
	sprintf(name, "z");		if(props.FindName(name) == false)	return lastError = OPROS_BAD_INPUT_PARAMETER;
	sprintf(name, "roll");		if(props.FindName(name) == false)	return lastError = OPROS_BAD_INPUT_PARAMETER;
	sprintf(name, "pitch");	if(props.FindName(name) == false)	return lastError = OPROS_BAD_INPUT_PARAMETER;
	sprintf(name, "yaw");		if(props.FindName(name) == false)	return lastError = OPROS_BAD_INPUT_PARAMETER;
	sprintf(name, "Width");		if(props.FindName(name) == false)	return lastError = OPROS_BAD_INPUT_PARAMETER;
	sprintf(name, "Height");		if(props.FindName(name) == false)	return lastError = OPROS_BAD_INPUT_PARAMETER;
	sprintf(name, "ColorType");		if(props.FindName(name) == false)	return lastError = OPROS_BAD_INPUT_PARAMETER;
	sprintf(name, "CompressType");		if(props.FindName(name) == false)	return lastError = OPROS_BAD_INPUT_PARAMETER;
		
	parameter = props;

	// Set property
	if(camera != NULL) {
		int32_t ret = camera->SetProperty(props);
		if(ret == API_ERROR) {
			return lastError = OPROS_CALL_API_ERROR;
		}
	}
	return lastError = OPROS_SUCCESS;
}

OPRoS::Property CameraComp::GetProperty()
{
	OPRoS::Property retParameter = parameter;
	if (retParameter.GetProperty().size() == 0)
	{
		lastError = OPROS_FIND_PROPERTY_ERROR;
		retParameter.status = lastError;
	}

	LifecycleState lifeStat = getStatus() ;
	if (lifeStat == OPROS_CS_CREATED || lifeStat == OPROS_CS_DESTROYED)
	{
		lastError = OPROS_ERROR;
		retParameter.status = lastError;
	}
	return retParameter;
}

ReturnType CameraComp::GetError()
{
	return lastError;
}

ReturnType CameraComp::Enable()
{
	if(camera == NULL) {
		PrintMessage("[ERROR : %s::%s] : The handle of API is not created.\n", __FILE__, __FUNCTION__);
		return lastError = OPROS_PRECONDITION_NOT_MET;
	}

	int32_t ret = camera->Enable();
	if(ret == API_ERROR) {
		return lastError = OPROS_ENABLE_API_ERROR;
	}
	else if(ret == API_NOT_SUPPORTED) {
		return lastError = OPROS_API_NOT_SUPPORTED_ERROR;
	}
	
	return lastError = OPROS_SUCCESS;
}

ReturnType CameraComp::Disable()
{
	if(camera == NULL) {
		PrintMessage("[ERROR : %s::%s] : The handle of API is not created.\n", __FILE__, __FUNCTION__);
		return lastError = OPROS_PRECONDITION_NOT_MET;
	}

	int32_t ret = camera->Disable();
	if(ret == API_ERROR) {
		return lastError = OPROS_DISABLE_API_ERROR;
	}
	else if(ret == API_NOT_SUPPORTED) {
		return lastError = OPROS_API_NOT_SUPPORTED_ERROR;
	}
	
	return lastError = OPROS_SUCCESS;
}

OPRoS::CameraData CameraComp::GetImage()
{
	OPRoS::CameraData tmp;

	LifecycleState lifeStat = getStatus();
	if (lifeStat != OPROS_CS_ACTIVE)
	{
		lastError = OPROS_ERROR;
	}
	else if(camera == NULL) {
		PrintMessage("[ERROR : %s::%s] : The handle of API is not created.\n", __FILE__, __FUNCTION__);
		lastError = OPROS_PRECONDITION_NOT_MET;
	}
	else
	{
		int32_t ret = camera->GetImage((unsigned char*)image->imageData);
		if(ret == API_ERROR) {
			lastError = OPROS_CALL_API_ERROR;
		}
		else if(ret == API_NOT_SUPPORTED) {
			lastError = OPROS_API_NOT_SUPPORTED_ERROR;
		}
		else {
			lastError = OPROS_SUCCESS;
		}
	}
	
	tmp.format = IMAGE_FORMAT_JPEG;
	tmp.width = _width;
	tmp.height = _height;

	if (lastError == OPROS_SUCCESS)
	{
		cv::Mat matSrc(image);
		cv::imencode(compTypeStr[_compressType], matSrc, tmp.data, std::vector<int>());
	}
	else
	{
		tmp.status = OPROS_ERROR;
	}
	
	return tmp;
}

void CameraComp::portSetup() {
	
	//data port setup
	addPort("cameraData", &cameraData);

	ProvidedServicePort *pa1;
	pa1=new CameraServiceProvided(this);
	addPort("CameraService",pa1);

	// export variable setup

}

// Call back Declaration
ReturnType CameraComp::onInitialize()
{
	// Check if already initialized
	if (hOprosAPI != NULL)
		return lastError = OPROS_SUCCESS;

	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	if(parameter.FindName("ApiName") == false) {
		PrintMessage("[ERROR : %s::%s] : Can't find the ApiName in property.\n", __FILE__, __FUNCTION__);
		return lastError = OPROS_FIND_PROPERTY_ERROR;
	}

	
#if defined(WIN32)
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("ApiName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("[ERROR : %s::%s] : Can't find the %s\n", __FILE__, __FUNCTION__, parameter.GetValue("ApiName").c_str());
		return lastError = OPROS_FIND_DLL_ERROR;
	}
	
	GET_OPROS_DEVICE getOprosAPI;
	getOprosAPI = (GET_OPROS_DEVICE)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("[ERROR : %s::%s] : Can't get a handle of GetAPI Funtion\n", __FILE__, __FUNCTION__);
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return lastError = OPROS_LOAD_DLL_ERROR;
	}
#else
	hOprosAPI = dlopen(parameter.GetValue("ApiName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("[ERROR : %s::%s] : Can't find the %s\n", __FILE__, __FUNCTION__, parameter.GetValue("ApiName").c_str());
		return lastError = OPROS_FIND_DLL_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage("[ERROR : %s::%s] : Can't get a handle of GetAPI Funtion\n", __FILE__, __FUNCTION__);
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return lastError = OPROS_LOAD_DLL_ERROR;
	}
#endif
	
	camera = dynamic_cast<Camera *>(getOprosAPI());
	if(camera == NULL) {
		PrintMessage("[ERROR : %s::%s] : Can't get a handle of Camera API\n", __FILE__, __FUNCTION__);
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return lastError = OPROS_LOAD_DLL_ERROR;
	}

	if(camera->Initialize(parameter) != API_SUCCESS) {
		delete camera;
		camera = NULL;

#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return lastError = OPROS_INITIALIZE_API_ERROR;
	}

	_width = atoi(parameter.GetValue("Width").c_str());
	_height = atoi(parameter.GetValue("Height").c_str());
	_colorType = atoi( (parameter.GetValue("ColorType")).c_str() );
	_compressType = atoi( (parameter.GetValue("CompressType")).c_str() );
	
	switch (_colorType)
	{
	case 2:
		image = cvCreateImage(cvSize(_width, _height), 8, 1);
		break;
	default:
		image = cvCreateImage(cvSize(_width, _height), 8, 3);
		break;
	}
	
	compTypeStr.push_back(".jpg");
	compTypeStr.push_back(".bmp");
	compTypeStr.push_back(".gif");
	compTypeStr.push_back(".png");

#ifdef __STATUS_TEST_MODE__
	START_TEST(this);
#endif
	
	return lastError = OPROS_SUCCESS;
}

ReturnType CameraComp::onStart()
{
	return Enable();
}
	
ReturnType CameraComp::onStop()
{
	return Disable();
}

ReturnType CameraComp::onReset()
{
	// user code here
	if(camera == NULL) {
		PrintMessage("[ERROR : %s::%s] : The handle of API is not created.\n", __FILE__, __FUNCTION__);
		return lastError = OPROS_PRECONDITION_NOT_MET;
	}
	
	if (camera->Finalize() != API_SUCCESS)
		return lastError = OPROS_RESET_API_ERROR;

	if (camera->Initialize(parameter) != API_SUCCESS)
		return lastError = OPROS_RESET_API_ERROR;

	if (camera->Enable() != API_SUCCESS)
	{
		if (camera->Finalize() != API_SUCCESS)
		{
			return lastError = OPROS_RESET_API_ERROR;
		}
	}	

	return  lastError = OPROS_SUCCESS;
}

ReturnType CameraComp::onError()
{
	// user code here
	return Disable();
}

ReturnType CameraComp::onRecover()
{
	// user code here
	if(camera == NULL) {
		PrintMessage("[ERROR : %s::%s] : The handle of API is not created.\n", __FILE__, __FUNCTION__);
		return lastError = OPROS_PRECONDITION_NOT_MET;
	}

	if (camera->Finalize() != API_SUCCESS)
		return lastError = OPROS_RECOVER_API_ERROR;

	if (camera->Initialize(parameter) != API_SUCCESS)
		return lastError = OPROS_RECOVER_API_ERROR;

	return lastError = OPROS_SUCCESS;
}

ReturnType CameraComp::onDestroy()
{
	if (getStatus() == OPROS_CS_DESTROYED)
		return lastError = OPROS_SUCCESS;

	if(camera != NULL) {
		camera->Finalize();
		delete camera;
		camera = NULL;
	}

	if(hOprosAPI != NULL) {
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
	}

	return lastError = OPROS_SUCCESS;
}

ReturnType CameraComp::onEvent(Event *evt)
{
	// user code here
	return lastError = OPROS_SUCCESS;
}

ReturnType CameraComp::onExecute()
{
	if(camera == NULL) {
		PrintMessage("[ERROR : %s::%s] : The handle of API is not created.\n", __FILE__, __FUNCTION__);
		return lastError = OPROS_PRECONDITION_NOT_MET;
	}

	cameraData.push(GetImage());

	return lastError = OPROS_SUCCESS;
}
	
ReturnType CameraComp::onUpdated()
{
	// user code here
	return lastError = OPROS_SUCCESS;
}

ReturnType CameraComp::onPeriodChanged()
{
	// user code here
	return lastError = OPROS_SUCCESS;
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
	return new CameraComp();
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
	return new CameraComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

