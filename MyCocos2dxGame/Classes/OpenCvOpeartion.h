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

#include <opencv\cv.h>

// to enable CCLOG()
#define COCOS2D_DEBUG 1
#include "cocos2d.h"

#include "HW_DataModel.h"
#include "HW_UserDataModel.h"

class OpenCvOperation
{
public:
	//@see http://www.cs.iit.edu/~agam/cs512/lect-notes/opencv-intro/opencv-intro.html
	//IplImage attribute check
	static bool iplImageAttributesCheck(std::string filePath);
	//cv::Mat image attribute check
	static bool cvMatImageAttributesCheck(std::string filePath);
	//OpenCV function header
	static void faceDetectAndDisplay(std::string filePath);
private:
	//OpenCV related variables
};

#endif