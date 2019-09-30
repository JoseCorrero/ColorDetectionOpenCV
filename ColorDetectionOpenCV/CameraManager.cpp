#include "CameraManager.h"

using namespace cv;

// namespace CameraManager
using namespace cm;

CameraManager::CameraManager(int device) {
	camera_ = VideoCapture(device);
}

bool CameraManager::isOpened() const
{
	return camera_.isOpened();
}

double CameraManager::getProperty(int propId) const
{
	return camera_.get(propId);
}

bool CameraManager::openCamera(int device)
{
	return camera_.open(device);
}

void CameraManager::releaseCamera()
{
	camera_.release();
}

bool CameraManager::getFrame(Mat& frame)
{
	return camera_.read(frame);
}

bool CameraManager::setProperty(int propId, double value)
{
	return camera_.set(propId, value);
}