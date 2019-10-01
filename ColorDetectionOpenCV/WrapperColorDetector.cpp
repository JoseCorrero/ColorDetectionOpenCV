#include "WrapperColorDetector.h"

#include <string>
#include <map>

using namespace std;

// namespace CameraManager
using namespace cm;

extern CameraManager cameraManager;

map<string, cd::ColorDetector> colorDetectors;

cd::ColorDetector& colorDetector = cd::ColorDetector();

int ColorDetector(const char* id, ColorRange color)
{
	if(colorDetectors.insert({ string(id), cd::ColorDetector(color) }).second)
		return 1;
	else
		return 0;
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

int select(const char* id)
{
	auto cD = colorDetectors.find(string(id));
	if (cD != colorDetectors.end())
	{
		colorDetector = cD->second;
		return 1;
	}
	else
		return 0;
}

void detectColor()
{
	colorDetector.detectColor();
}

cv::Point2f findPosition()
{
	return colorDetector.findPosition();
}