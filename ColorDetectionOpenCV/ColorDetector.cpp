#include "ColorDetector.h"

#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

// namespace CameraManager
using namespace cm;
// namespace ColorDetector
using namespace cd;

Mat ColorDetector::hsv_ = Mat();
int ColorDetector::lowThreshold_ = 85;
int ColorDetector::highThreshold_ = 255;

ColorDetector::ColorDetector(ColorRange color) : color_(color), point_(Point())
{}

/*
void ColorDetector::showCannyTrackbar()
{
	static string windowName = "Canny Values";
	namedWindow(windowName);
	createTrackbar("Low threshold:", windowName, &lowThreshold_, 255);
	createTrackbar("High threshold:", windowName, &highThreshold_, 255);
}*/

void ColorDetector::prepareFrame(Mat& frame, cv::ColorConversionCodes code)
{	
	cvtColor(frame, hsv_, code);
}

void ColorDetector::detectColor()
{
	// El color rojo oscila entre los valores de H 0-30 y 150-180, por lo que
	// puede ser necesario utilizar dos máscaras y unir los resultados.
	if (color_.highH < color_.lowH)
	{
		Mat mask2;
		inRange(hsv_, Scalar(color_.lowH, color_.lowS, color_.lowV),
			Scalar(180, color_.highS, color_.highV), binaryMask_);
		inRange(hsv_, Scalar(0, color_.lowS, color_.lowV),
			Scalar(color_.highH, color_.highS, color_.highV), mask2);
		binaryMask_ = binaryMask_ + mask2;
	}
	else
		inRange(hsv_, Scalar(color_.lowH, color_.lowS, color_.lowV),
			Scalar(color_.highH, color_.highS, color_.highV), binaryMask_);
}

void ColorDetector::improveMask()
{
	Mat kernel = Mat::ones(3, 3, CV_32F);
	morphologyEx(binaryMask_, binaryMask_, cv::MORPH_OPEN, kernel);
	morphologyEx(binaryMask_, binaryMask_, cv::MORPH_DILATE, kernel);

	cvtColor(binaryMask_, binaryMask_, CV_GRAY2BGRA);
	Canny(binaryMask_, finalMask_, lowThreshold_, highThreshold_);
}

void ColorDetector::findPosition()
{
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(finalMask_, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	if (contours.size() > 0)
	{
		vector<Point> result;
		
		for (size_t i = 0; i < contours.size(); i++)
		{
			convexHull(contours[i], result);
			contours[i] = result;
		}

		int index = findBestContour(contours);
		if (index >= 0)
		{
			Rect br = boundingRect(contours[index]);

			point_.x = br.x + br.width / 2;
			point_.y = br.y + br.height / 2;

			return;
		}
	}

	point_.x = -1;
	point_.y = -1;
}

int ColorDetector::findBestContour(vector<vector<Point>>& contours) const
{
	int biggest_contour_index = -1;
	double biggest_area = 0.0;

	for (int i = 0; i < contours.size(); i++) {
		double area = contourArea(contours[i], false);
		if (area > biggest_area) {
			biggest_area = area;
			biggest_contour_index = i;
		}
	}

	return biggest_contour_index;
}