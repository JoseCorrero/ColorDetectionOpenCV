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
	return (int)colorDetectors.erase(string(id));
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

void findPosition(int* x, int* y)
{
	colorDetector.findPosition();

	*x = colorDetector.getPoint().x;
	*y = colorDetector.getPoint().y;
}

void imwrite(const char* id)
{
	cv::Mat mat = colorDetector.getCannyMask().clone();
	cv::circle(mat, { colorDetector.getPoint().x, colorDetector.getPoint().y }, 7, (255, 255, 255), -1);

	cv::imwrite("../images/" + string(id) + ".jpeg", mat);
}

void writeFrame()
{
	cv::imwrite("../images/frame.jpeg", cd::ColorDetector::getFrame());
}

void imshow(const char* id)
{
	cv::Mat mat(colorDetector.getCannyMask().clone());
	cv::circle(mat, { colorDetector.getPoint().x, colorDetector.getPoint().y }, 7, (255, 255, 255), -1);
	
	string name(id);
	cv::namedWindow(name, cv::WINDOW_AUTOSIZE);
	cv::imshow(name, mat);
}

void showFrame()
{
	string name("Frame");
	cv::namedWindow(name, cv::WINDOW_AUTOSIZE);
	cv::imshow(name, cd::ColorDetector::getFrame());
}

void destroyWindow(const char* id)
{
	cv::destroyWindow(string(id));
}