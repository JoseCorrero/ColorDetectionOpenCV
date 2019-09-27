#include "ColorDetector.h"

#include "opencv2/highgui.hpp"

// Valores predeterminados.
CameraManager& ColorDetector::cameraManager_ = CameraManager();
Mat ColorDetector::frame_ = Mat();
Mat ColorDetector::hsv_ = Mat();
int ColorDetector::lowThreshold_ = 85;
int ColorDetector::highThreshold_ = 255;

ColorDetector::ColorDetector(ColorRange& color) : color_(color)
{}

void ColorDetector::setCameraManager(CameraManager& cam)
{
	cameraManager_ = cam;
}

void ColorDetector::showCannyTrackbar()
{
	string windowName = "Canny";
	namedWindow(windowName);
	createTrackbar("Low threshold:", windowName, &lowThreshold_, 255);
	createTrackbar("High threshold:", windowName, &highThreshold_, 255);
}

void ColorDetector::prepareFrame()
{	
	cameraManager_.getFrame(frame_);
	cvtColor(frame_, hsv_, COLOR_BGR2HSV);
}

void ColorDetector::detectColor()
{
	// El color rojo oscila entre los valores de H 0-30 y 150-180, por lo que
	// puede ser necesario utilizar dos máscaras y unir los resultados.
	if (color_.iHighH < color_.iLowH)
	{
		Mat mask2;
		inRange(hsv_, Scalar(color_.iLowH, color_.iLowS, color_.iLowV),
			Scalar(180, color_.iHighS, color_.iHighV), binaryMask_);
		inRange(hsv_, Scalar(0, color_.iLowS, color_.iLowV),
			Scalar(color_.iHighH, color_.iHighS, color_.iHighV), mask2);
		binaryMask_ = binaryMask_ + mask2;
	}
	else
		inRange(hsv_, Scalar(color_.iLowH, color_.iLowS, color_.iLowV),
			Scalar(color_.iHighH, color_.iHighS, color_.iHighV), binaryMask_);
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
		Moments m = moments(contours_[0], false);

		return Point2f(m.m10 / m.m00, m.m01 / m.m00);
	}

	return Point2f();
}