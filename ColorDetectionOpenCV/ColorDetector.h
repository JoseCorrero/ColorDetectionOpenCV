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

		static void prepareFrame(cv::Mat&, cv::ColorConversionCodes);

		void detectColor();
		void improveMask();
		void findPosition();

		static inline void setLowThreshold(int value) { lowThreshold_ = value; }
		static inline void setHighThreshold(int value) { highThreshold_ = value; }

		static inline const cv::Mat& getHsv() { return hsv_; }

		inline const cv::Mat& getBinaryMask() const { return binaryMask_; }
		inline const cv::Mat& getFinalMask() const { return finalMask_; }
		inline const cv::Point& getPoint() const { return point_; }
		inline const ColorRange& getColor() const { return color_; }

	private:

		int findBestContour(std::vector<std::vector<cv::Point>>&) const;

		// Compartido por todas las instancias de la clase.
		static cv::Mat hsv_;
		static int lowThreshold_, highThreshold_;

		// Propios de cada instancia.
		cv::Mat binaryMask_, finalMask_;
		cv::Point point_;
		ColorRange color_;

	};
}
#endif