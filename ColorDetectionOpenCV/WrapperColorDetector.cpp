#include "WrapperColorDetector.h"

#include <map>

using namespace std;

// namespace CameraManager
using namespace cm;

extern CameraManager cameraManager;

static map<char*, cd::ColorDetector> colorDetectors;

static cd::ColorDetector& colorDetector = cd::ColorDetector();

void ColorDetector(char* id, ColorRange color)
{
	colorDetectors.insert({id, cd::ColorDetector(color)});
}

void setCameraManager()
{
	cd::ColorDetector::setCameraManager(cameraManager);
}

void showCannyTrackbar()
{
	cd::ColorDetector::showCannyTrackbar();
}

void prepareFrame()
{
	cd::ColorDetector::prepareFrame();
}

bool select(char* id)
{
	auto cD = colorDetectors.find(id);
	if (cD != colorDetectors.end())
	{
		colorDetector = cD->second;
		return true;
	}
	else
		return false;
}

void detectColor()
{
	colorDetector.detectColor();
}

cv::Point2f findPosition()
{
	return colorDetector.findPosition();
}