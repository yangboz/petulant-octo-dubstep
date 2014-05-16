#ifndef __HELLOWORLD_OPENCV_OPERATION__
#define __HELLOWORLD_OPENCV_OPERATION__

#include <string>
using namespace std;

//OpenCV core
#include <opencv2\opencv.hpp>
using namespace cv;
//OpenCV face detection
#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

// to enable CCLOG()
#define COCOS2D_DEBUG 1
#include "cocos2d.h"

class OpenCvOperation
{
public:
	//OpenCV function header
	static void faceDetectAndDisplay(std::string filePath);
private:
	//OpenCV related variables
};

#endif