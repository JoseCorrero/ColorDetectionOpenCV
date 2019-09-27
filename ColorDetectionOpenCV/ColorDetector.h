#pragma once

#ifndef COLORDETECTOR_H
#define COLORDETECTOR_H

#include "CameraManager.h"

#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

struct ColorRange {

	int iLowH;
	int iHighH;

	int iLowS;
	int iHighS;

	int iLowV;
	int iHighV;
};

class ColorDetector {
public:

	ColorDetector(ColorRange&);

	static void setCameraManager(CameraManager&);
	static void showCannyTrackbar();
	static void prepareFrame();

	void detectColor();
	Point2f findPosition();

	static inline const Mat& getFrame() { return frame_; }
	static inline const Mat& getHsv() { return hsv_; }

	inline const Mat& getBinaryMask() const { return binaryMask_; }
	inline const Mat& getCannyMask() const { return cannyMask_; }
	inline const vector<vector<Point>>& getContours() const { return contours_; }

private:

	// Compartido por todas las instancias de la clase.
	static CameraManager& cameraManager_;
	static Mat frame_, hsv_;
	static int lowThreshold_, highThreshold_;

	// Propios de cada instancia.
	Mat binaryMask_, cannyMask_;
	vector<vector<Point>> contours_;
	vector<Vec4i> hierarchy_;
	ColorRange& color_;

};

#endif