#pragma once

#ifndef WRAPPERCAMERAMANAGER_H
#define WRAPPERCAMERAMANAGER_H

#include "opencv2/opencv.hpp"

extern "C" __declspec(dllexport) void CameraManager(int);

extern "C" __declspec(dllexport) bool isOpened();

extern "C" __declspec(dllexport) double getProperty(int);

extern "C" __declspec(dllexport) bool openCamera(int);

extern "C" __declspec(dllexport) void releaseCamera();

extern "C" __declspec(dllexport) bool setProperty(int, double);

#endif