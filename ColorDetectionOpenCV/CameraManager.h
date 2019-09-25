#pragma once

#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

class CameraManager {
public:

	// Constructors
	CameraManager(int);

	// Observers
	bool isOpened() const;
	double getProperty(int) const;

	// Modifiers
	bool openCamera(int);
	void releaseCamera();
	bool getFrame(Mat&);
	bool setProperty(int, double);

private:

	VideoCapture camera;

};

#endif