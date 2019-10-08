#include "WrapperColorDetector.h"

#include <string>
#include <map>

using namespace std;
using namespace cv;

// namespace CameraManager
using namespace cm;

static CameraManager cM;

static map<string, cd::ColorDetector> colorDetectors;

static Mat frame;

CameraManager& cameraManager = cM;

int ColorDetector(const char* id, ColorRange color)
{
	if(colorDetectors.insert({ string(id), cd::ColorDetector(color) }).second)
		return 1;
	
	return 0;
}

int removeColorDetector(const char* id)
{
	return (int)colorDetectors.erase(string(id));
}

int prepareFrame(Mat& frame, ColorConversionCodes code)
{
	if (!frame.empty())
	{
		cd::ColorDetector::prepareFrame(frame, code);
		return 1;
	}
	
	return 0;
}

int prepareImage(Color32* image, int height, int width)
{
	Mat frame = Mat(height, width, CV_8UC4, image);
	
	return prepareFrame(frame, COLOR_RGB2HSV);
}

int prepareCameraImage()
{
	cameraManager.getFrame(frame);

	return prepareFrame(frame, COLOR_BGR2HSV);
}

int detectColorPosition(const char* id, int* x, int* y)
{
	auto pair = colorDetectors.find(string(id));
	if (pair != colorDetectors.end())
	{
		cd::ColorDetector& cD = pair->second;
		cD.detectColor();
		cD.improveMask();
		cD.findPosition();

		*x = cD.getPoint().x;
		*y = cD.getPoint().y;

		return 1;
	}
	
	return 0;
}

/*
void imwrite(const char* id)
{
	cv::Mat mat = colorDetector.getCannyMask().clone();
	cv::circle(mat, { colorDetector.getPoint().x, colorDetector.getPoint().y }, 7, (255, 255, 255), -1);

	imwrite("../images/" + string(id) + ".jpeg", mat);
}

void writeFrame()
{
	imwrite("../images/frame.jpeg", cd::ColorDetector::getFrame());
}
*/
void imshow(const char* id)
{
	auto pair = colorDetectors.find(string(id));
	if (pair != colorDetectors.end())
	{
		cd::ColorDetector& colorDetector = pair->second;
		Mat mat(colorDetector.getFinalMask().clone());
		circle(mat, { colorDetector.getPoint().x, colorDetector.getPoint().y }, 7, (255, 255, 255), -1);
		putText(mat, string(id), { colorDetector.getPoint().x, colorDetector.getPoint().y }, 
			FONT_HERSHEY_PLAIN,	1, Scalar(120, 120, 255));

		string name(id);
		namedWindow(name, cv::WINDOW_AUTOSIZE);
		imshow(name, mat);
	}
}

void showFrame()
{
	string name("Frame");
	namedWindow(name, cv::WINDOW_AUTOSIZE);
	imshow(name, frame);
}

void destroyWindow(const char* id)
{
	destroyWindow(string(id));
}