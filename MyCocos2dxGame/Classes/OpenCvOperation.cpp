#include "OpenCvOpeartion.h"

// to enable CCLOG()
#define COCOS2D_DEBUG 1
#include "cocos2d.h"

//OpenCV function header
void OpenCvOperation::faceDetectAndDisplay(std::string filePath)
{
	//
	cv::Mat frame = imread(filePath);
	//Window display for testing.
	/*
	cv::namedWindow("image", CV_WINDOW_AUTOSIZE);
	cv::imshow("image", frame);
	cv::waitKey();
	*/
	//@see http://docs.opencv.org/doc/tutorials/objdetect/cascade_classifier/cascade_classifier.html
	/** Global variables */
	static std::string face_cascade_name = "..//data//haarcascades//haarcascade_frontalface_alt.xml";
	static std::string eyes_cascade_name = "..//data//haarcascades//haarcascade_eye.xml";
	static std::string fullbody_cascade_name = "..//data//haarcascades//haarcascade_fullbody.xml";
	static std::string smile_cascade_name = "..//data//haarcascades//haarcascade_smile.xml";
	//
	static CascadeClassifier face_cascade;
	static CascadeClassifier eyes_cascade;
	static CascadeClassifier fullbody_cascade;
	static CascadeClassifier smile_cascade;
	static std::string window_name = "Image_Face_detection";
	//
	if (!frame.empty())
	{
		//-- 1. Load the cascades
		if (!face_cascade.load(face_cascade_name)){ CCLOG("face_cascade(!)Error loading\n"); return; };
		if (!eyes_cascade.load(eyes_cascade_name)){ CCLOG("eyes_cascade(!)Error loading\n"); return; };
		if (!fullbody_cascade.load(fullbody_cascade_name)){ CCLOG("fullbody_cascade(!)Error loading\n"); return; };
		if (!smile_cascade.load(fullbody_cascade_name)){ CCLOG("fullbody_cascade(!)Error loading\n"); return; };
	}

	std::vector<cv::Rect> faces;
	Mat frame_gray;

	cvtColor(frame, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);
	//-- Detect fullbody
	vector<Rect> bodys;
	//cv::Mat frame_gray;

	cvtColor(frame, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);
	//-- detect body */
	fullbody_cascade.detectMultiScale(frame_gray, bodys, 1.1, 2, 18 | 9, cv::Size(3, 7));
	for (int j = 0; j < bodys.size(); j++)
	{
		cv::Point center(bodys[j].x + bodys[j].width*0.5, bodys[j].y + +bodys[j].height*0.5);
		ellipse(frame, center, cv::Size(bodys[j].width*0.5, bodys[j].height*0.5), 0, 0, 360, cv::Scalar(255, 0, 255), 4, 8, 0);
	}
	//-- Detect faces
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

	for (size_t i = 0; i < faces.size(); i++)
	{
		cv::Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
		ellipse(frame, center, cv::Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, cv::Scalar(255, 0, 255), 4, 8, 0);

		Mat faceROI = frame_gray(faces[i]);
		std::vector<cv::Rect> eyes;

		//-- In each face, detect eyes
		eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

		for (size_t j = 0; j < eyes.size(); j++)
		{
			cv::Point center(faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5);
			int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
			circle(frame, center, radius, cv::Scalar(255, 0, 0), 4, 8, 0);
		}
	}
	//-- Show what you got
	imshow(window_name, frame);
}
//IplImage attributes check
void OpenCvOperation::iplImageAttributesCheck(std::string filePath)
{
	//Create an IplImage object *image
	IplImage *image = cvLoadImage(filePath.c_str());
	// Display Image Attributes by accessing a IplImage object's data members

	CCLOG("Image filename: %s", filePath.c_str());

	CCLOG("Width: %d",image->width);
	CCLOG("Height: %d", image->height);

	CCLOG("Pixel Depth: %d", image->depth);
	CCLOG("Channels: %d", image->nChannels);

	CCLOG("Width Step: %d", image->widthStep);
	CCLOG("Image Size: %d", image->imageSize);
	//Release
	cvReleaseImage(&image);
}

//cvMat image attributes check
void OpenCvOperation::cvMatImageAttributesCheck(std::string filePath)
{
	//
	cv::Mat image = cv::imread(filePath);
	if (!image.data)
	{
		
	};
	//Be tidy
	cvReleaseMat(image.data);
}