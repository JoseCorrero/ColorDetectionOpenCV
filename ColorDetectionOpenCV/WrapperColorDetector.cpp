#include "WrapperColorDetector.h"

#include <string>
#include <map>

using namespace std;

// namespace CameraManager
using namespace cm;

extern CameraManager cameraManager;

static map<string, cd::ColorDetector> colorDetectors;

static cd::ColorDetector& colorDetector = cd::ColorDetector();

int ColorDetector(const char* id, ColorRange color)
{
	if(colorDetectors.insert({ string(id), cd::ColorDetector(color) }).second)
		return 1;
	else
		return 0;
}

int removeColorDetector(const char* id)
{
	return colorDetectors.erase(string(id));
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

void findPosition(float* x, float* y)
{
	cv::Point2f point = colorDetector.findPosition();

	*x = point.x;
	*y = point.y;
}

void imwrite(const char* route, int printFrame)
{
	if (printFrame == 1)
		cv::imwrite("C:/Users/Jose/Desktop/frame.jpeg", colorDetector.getFrame());

	cv::imwrite(string(route), colorDetector.getCannyMask());
}

void imshow(const char* id, int printFrame)
{
	if (printFrame == 1)
	{
		cv::namedWindow("Frame", CV_WINDOW_AUTOSIZE);
		cv::imshow("Frame", colorDetector.getFrame());
	}
	
	string name(id);
	cv::namedWindow(name, CV_WINDOW_AUTOSIZE);
	cv::imshow(name, colorDetector.getCannyMask());
}