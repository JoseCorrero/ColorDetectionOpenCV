#pragma once

#ifndef WRAPPERCOLORDETECTOR_H
#define WRAPPERCOLORDETECTOR_H

#include "ColorDetector.h"

extern "C" __declspec(dllexport) void ColorDetector(char*, ColorRange);

extern "C" __declspec(dllexport) void setCameraManager();

extern "C" __declspec(dllexport) void showCannyTrackbar();

extern "C" __declspec(dllexport) void prepareFrame();

extern "C" __declspec(dllexport) bool select(char*);

extern "C" __declspec(dllexport) void detectColor();

extern "C" __declspec(dllexport) cv::Point2f findPosition();

#endif