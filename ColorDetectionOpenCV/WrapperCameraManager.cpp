#include "WrapperCameraManager.h"
#include "CameraManager.h"

using namespace cv;

cm::CameraManager cameraManager;

void CameraManager(int device)
{
	cameraManager = cm::CameraManager(device);
}

bool isOpened()
{
	return cameraManager.isOpened();
}

double getProperty(int propId)
{
	return cameraManager.getProperty(propId);
}

bool openCamera(int device)
{
	return cameraManager.openCamera(device);
}

void releaseCamera()
{
	cameraManager.releaseCamera();
}

bool setProperty(int propId, double value)
{
	return cameraManager.setProperty(propId, value);
}
