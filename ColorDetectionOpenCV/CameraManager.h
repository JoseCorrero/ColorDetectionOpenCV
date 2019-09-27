#pragma once

#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include "opencv2/opencv.hpp"

using namespace cv;

class CameraManager {
public:

	CameraManager() {}
	CameraManager(int);

	bool isOpened() const;
	double getProperty(int) const;

	bool openCamera(int);
	void releaseCamera();
	bool getFrame(Mat&);
	bool setProperty(int, double);

private:

	VideoCapture camera_;

};

#endif