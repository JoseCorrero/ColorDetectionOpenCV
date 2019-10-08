#pragma once

#ifndef WRAPPERCOLORDETECTOR_H
#define WRAPPERCOLORDETECTOR_H

#include "ColorDetector.h"

struct Color32 {

	uchar r;
	uchar g;
	uchar b;
	uchar a;
};

extern "C" __declspec(dllexport) int ColorDetector(const char*, ColorRange);

extern "C" __declspec(dllexport) int removeColorDetector(const char*);

extern "C" __declspec(dllexport) int prepareImage(Color32*, int, int);

extern "C" __declspec(dllexport) int prepareCameraImage();

extern "C" __declspec(dllexport) int detectColorPosition(const char*, int*, int*);
/*
extern "C" __declspec(dllexport) void imwrite(const char*);

extern "C" __declspec(dllexport) void writeFrame();
*/
extern "C" __declspec(dllexport) void imshow(const char*);

extern "C" __declspec(dllexport) void showFrame();

extern "C" __declspec(dllexport) void destroyWindow(const char*);

#endif