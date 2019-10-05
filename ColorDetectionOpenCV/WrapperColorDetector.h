#pragma once

#ifndef WRAPPERCOLORDETECTOR_H
#define WRAPPERCOLORDETECTOR_H

#include "ColorDetector.h"

extern "C" __declspec(dllexport) int ColorDetector(const char*, ColorRange);

extern "C" __declspec(dllexport) int removeColorDetector(const char*);

extern "C" __declspec(dllexport) void setCameraManager();

extern "C" __declspec(dllexport) void showCannyTrackbar();

extern "C" __declspec(dllexport) void prepareFrame();

extern "C" __declspec(dllexport) int select(const char*);

extern "C" __declspec(dllexport) void detectColor();

extern "C" __declspec(dllexport) void findPosition(int*, int*);

extern "C" __declspec(dllexport) void imwrite(const char*);

extern "C" __declspec(dllexport) void writeFrame();

extern "C" __declspec(dllexport) void imshow(const char*);

extern "C" __declspec(dllexport) void showFrame();

extern "C" __declspec(dllexport) void destroyWindow(const char*);

#endif