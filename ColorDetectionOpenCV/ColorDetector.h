#pragma once

#ifndef COLORDETECTOR_H
#define COLORDETECTOR_H

#include "CameraManager.h"

#include "opencv2/opencv.hpp"

struct ColorRange {

	int lowH;
	int highH;

	int lowS;
	int highS;

	int lowV;
	int highV;
};

namespace cd {

	class ColorDetector {
	public:

		ColorDetector() {}
		ColorDetector(ColorRange);

		static void setCameraManager(cm::CameraManager&);
		static void showCannyTrackbar();
		static void prepareFrame();

		void detectColor();
		cv::Point2f findPosition();

		static inline const cv::Mat& getFrame() { return frame_; }
		static inline const cv::Mat& getHsv() { return hsv_; }

		inline const cv::Mat& getBinaryMask() const { return binaryMask_; }
		inline const cv::Mat& getCannyMask() const { return cannyMask_; }
		inline const ColorRange& getColor() const { return color_; }

	private:

		int findBestContour(std::vector<std::vector<cv::Point>>&) const;

		// Compartido por todas las instancias de la clase.
		static cm::CameraManager& cameraManager_;
		static cv::Mat frame_, hsv_;
		static int lowThreshold_, highThreshold_;

		// Propios de cada instancia.
		cv::Mat binaryMask_, cannyMask_;
		ColorRange color_;

	};
}
#endif