#include "ColorDetector.h"

#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

// namespace CameraManager
using namespace cm;
// namespace ColorDetector
using namespace cd;

CameraManager& ColorDetector::cameraManager_ = CameraManager();
Mat ColorDetector::frame_ = Mat();
Mat ColorDetector::hsv_ = Mat();
int ColorDetector::lowThreshold_ = 85;
int ColorDetector::highThreshold_ = 255;

ColorDetector::ColorDetector(ColorRange color) : color_(color)
{}

void ColorDetector::setCameraManager(CameraManager& cam)
{
	cameraManager_ = cam;
}

void ColorDetector::showCannyTrackbar()
{
	static string windowName = "Canny Values";
	namedWindow(windowName);
	createTrackbar("Low threshold:", windowName, &lowThreshold_, 255);
	createTrackbar("High threshold:", windowName, &highThreshold_, 255);
}

void ColorDetector::prepareFrame()
{	
	if(cameraManager_.getFrame(frame_))
		cvtColor(frame_, hsv_, COLOR_BGR2HSV);
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

Point2f ColorDetector::findPosition()
{
	cvtColor(binaryMask_, binaryMask_, COLOR_GRAY2BGRA);
	Canny(binaryMask_, cannyMask_, lowThreshold_, highThreshold_);

	findContours(cannyMask_, contours_, hierarchy_, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	if (contours_.size() > 0)
	{
		// Utiliza el primer contorno.
		// Implementar búsqueda del contorno más prometedor.
		vector<Point>& contour = contours_[0];
		
		Moments m = moments(contour, false);

		return Point2f(m.m10 / m.m00, m.m01 / m.m00);
	}

	return Point2f();
}