#pragma once

#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include "opencv2/opencv.hpp"

namespace cm {

	class CameraManager {
	public:

		CameraManager() {}
		CameraManager(int);

		bool isOpened() const;
		double getProperty(int) const;

		bool openCamera(int);
		void releaseCamera();
		bool getFrame(cv::Mat&);
		bool setProperty(int, double);

	private:

		cv::VideoCapture camera_;

	};
}

#endif