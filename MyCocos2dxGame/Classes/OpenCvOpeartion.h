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
#include <opencv2\gpu\gpu.hpp>
#include <opencv2\video\background_segm.hpp>

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
	//static void faceDetectAndDisplay(std::string filePath);
	static int faceDetection(std::string filePath, bool display);
	static void fullbodyDetectAndDisplay_Haar(std::string filePath);
	static void fullbodyDetectAndDisplay_Hog(std::string filePath);
	//Background subtraction using MOG
	//@see http://stackoverflow.com/questions/19221877/opencv-how-to-use-createbackgroundsubtractormog
	static void backgroundSubstraction_MOG_1(std::string filePath);
	static void backgroundSubstraction_MOG_2(std::string filePath);
	//@see http://theembeddedsystems.blogspot.com/2011/05/background-subtraction-using-opencv.html
	static void backgroundSubstraction_(std::string filePath);
	//@see http://docs.opencv.org/trunk/doc/py_tutorials/py_imgproc/py_grabcut/py_grabcut.html
	static bool foregroundGrabcut(std::string filePath, int width, int height, bool display);
	//@see http://docs.opencv.org/doc/tutorials/core/adding_images/adding_images.html
	static bool addingTwoImages(std::string filePath_foreground, std::string filePath_background, std::string dest, bool display);
	//Save image file with transform
	static bool saveRoatedImgeFile(double angle, std::string context);
	static bool saveScaledImageFile(double rate, std::string context);
	//Save image file with solid color
	static bool saveColoredImageFile(cv::Scalar colorScalar, int width, int height, std::string context);
	//@see http://funwithkinect.blogspot.com.br/2012/02/copying-and-tiling-with-opencv.html
	static bool tilingImages(int row, int column, std::string context, std::string outputDest, bool display);
private:
	//OpenCV related variables
	//
	static bool saveMatImageFile(cv::Mat image, std::string context);
	static bool saveIplImageFile(IplImage image, std::string context);
	//PNG with alpha
	static void createAlphaMat(cv::Mat4b &mat);
};

#endif