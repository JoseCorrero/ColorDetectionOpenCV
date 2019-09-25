#include "CameraManager.h"

CameraManager::CameraManager(int device) {
	camera.open(device);
}

bool CameraManager::isOpened() const
{
	return camera.isOpened();
}

double CameraManager::getProperty(int propId) const
{
	return camera.get(propId);
}

bool CameraManager::openCamera(int device)
{
	return camera.open(device);
}

void CameraManager::releaseCamera()
{
	camera.release();
}

bool CameraManager::getFrame(Mat& frame)
{
	return camera.read(frame);
}

bool CameraManager::setProperty(int propId, double value)
{
	return camera.set(propId, value);
}