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

// If trying to debug the color detector code, enable SHOW_DEBUG_IMAGE:
#define SHOW_DEBUG_IMAGE

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
	static vector<cv::Rect> faceDetection(std::string filePath, bool display);
	static void fullbodyDetectAndDisplay_Haar(std::string filePath);
	static void fullbodyDetectAndDisplay_Hog(std::string filePath);
	//@see http://stackoverflow.com/questions/11987483/opencvs-canny-edge-detection-in-c
	static void edgeDetection(std::string filePath, bool display);
	//@see http://blog.csdn.net/yangtrees/article/details/7482587
	static void maxContourDetection(std::string filePath, bool display);
	//@see http://docs.opencv.org/doc/tutorials/imgproc/shapedescriptors/bounding_rects_circles/bounding_rects_circles.html
	static void contoursDetection(std::string filePath, bool display);
	//@see http://shervinemami.info/shirtDetection.html
	static char* shirtDetection(std::string filePath, bool display);
	//Background subtraction using MOG
	//@see http://stackoverflow.com/questions/19221877/opencv-how-to-use-createbackgroundsubtractormog
	static void backgroundSubstraction_MOG_1(std::string filePath);
	static void backgroundSubstraction_MOG_2(std::string filePath);
	//@see http://theembeddedsystems.blogspot.com/2011/05/background-subtraction-using-opencv.html
	static void backgroundSubstraction_(std::string filePath);
	//@see http://docs.opencv.org/trunk/doc/py_tutorials/py_imgproc/py_grabcut/py_grabcut.html
	static bool foregroundGrabcut(std::string filePath, int width, int height, bool display, bool interactive);
	//@see http://docs.opencv.org/doc/tutorials/core/adding_images/adding_images.html
	static bool addingTwoImages(std::string filePath_foreground, std::string filePath_background, std::string dest, bool display);
	//Save image file with transform
	static bool saveRotatedImgeFile(double angle, std::string src, std::string dst);
	static bool saveScaledImageFile(double rate, std::string src, std::string dst);
	static bool saveMovedImageFile(double offsetX, double offsetY, std::string src, std::string dst);
	//OpenCV image free transform with rotate/scale/move
	//@see http://opencv-tutorial.com/introduction/rotate-image-video/
	static bool saveTransformedImageFile(double angle, double scale, double offsetX, double offsetY, std::string src, std::string dst);
	//Save image file with solid color
	static bool saveColoredImageFile(cv::Scalar colorScalar, int width, int height, std::string context);
	//@see http://funwithkinect.blogspot.com.br/2012/02/copying-and-tiling-with-opencv.html
	static bool tilingImages(int row, int column, std::string context, std::string outputDest, bool display);
	//@see http://blog.csdn.net/chenjiazhou12/article/details/29222619
	static void on_mouse(int event, int x, int y, int flags, void* param);
	
private:
	//OpenCV related variables
	//
	static bool saveMatImageFile(cv::Mat image, std::string context);
	static bool saveIplImageFile(IplImage *image, std::string context);
	//PNG with alpha
	static void createAlphaMat(cv::Mat4b &mat);
	
	// Determine what type of color the HSV pixel is. Returns the colorType between 0 and NUM_COLOR_TYPES.
	static int getPixelColorType(int H, int S, int V);
	// Returns a new image that is a cropped version of the original image. 
	// Remember to free the new image later.
	static IplImage* cropRectangle(IplImage *img, CvRect region);
	// Draw a rectangle around the given object (use CV_RGB(200,0,0) for red color)
	static void drawRectangle(IplImage *img, CvRect face, CvScalar col);
};

#endif