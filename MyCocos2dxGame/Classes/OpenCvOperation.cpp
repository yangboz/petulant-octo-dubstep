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
	static std::string face_cascade_name = "..//data//haarcascades//haarcascade_frontalface_alt_tree.xml";
	static std::string eyes_cascade_name = "..//data//haarcascades//haarcascade_eye.xml";
	static std::string smile_cascade_name = "..//data//haarcascades//haarcascade_smile.xml";
	//
	static CascadeClassifier face_cascade;
	static CascadeClassifier eyes_cascade;
	static CascadeClassifier smile_cascade;
	static std::string window_name = "Image_Face_detection";
	//
	if (!frame.empty())
	{
		//-- 1. Load the cascades
		if (!face_cascade.load(face_cascade_name)){ CCLOG("face_cascade(!)Error loading\n"); return; };
		if (!eyes_cascade.load(eyes_cascade_name)){ CCLOG("eyes_cascade(!)Error loading\n"); return; };
		if (!smile_cascade.load(smile_cascade_name)){ CCLOG("smile_cascade(!)Error loading\n"); return; };
	}

	std::vector<cv::Rect> faces;
	Mat frame_gray;

	cvtColor(frame, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);
	//-- Detect fullbody
	vector<cv::Rect> bodys;
	//-- Detect faces
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

	for (size_t i = 0; i < faces.size(); i++)
	{
		cv::Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
		//ellipse(frame, center, cv::Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, cv::Scalar(255, 0, 255), 4, 8, 0);
		cv::rectangle(frame, cv::Rect(faces[i].x, faces[i].y,faces[i].width, faces[i].height), cv::Scalar(255, 0, 255));

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
	//
	//-- Show what you got
	imshow(window_name, frame);
}
//IplImage attributes check
bool OpenCvOperation::iplImageAttributesCheck(std::string filePath)
{
	//Create an IplImage object *image
	IplImage *image = cvLoadImage(filePath.c_str());
	// Display Image Attributes by accessing a IplImage object's data members
	//CCLOG("Image filename: %s", filePath.c_str());
	int targetWidth = HW_DataModel::HW_DataModel::ARRAY_OF_CERT_SIZES[HW_UserDataModel::Instance()->cur_listView_selected_index].width;
	int targetHeight = HW_DataModel::HW_DataModel::ARRAY_OF_CERT_SIZES[HW_UserDataModel::Instance()->cur_listView_selected_index].height;
	CCLOG("Width: %d",image->width);
	CCLOG("Height: %d", image->height);
	//CCLOG("Pixel Depth: %d", image->depth);
	//CCLOG("Channels: %d", image->nChannels);
	//CCLOG("Width Step: %d", image->widthStep);
	CCLOG("Image Size: %d", image->imageSize);
	int targetFileSizeMin = HW_DataModel::HW_DataModel::ARRAY_OF_CERT_FILE_SIZES[HW_UserDataModel::Instance()->cur_listView_selected_index].width;
	int targetFileSizeMax = HW_DataModel::HW_DataModel::ARRAY_OF_CERT_FILE_SIZES[HW_UserDataModel::Instance()->cur_listView_selected_index].height;
	//Sort of check conditions here.
	bool widthChecker = (targetWidth <= image->width);
	bool heightChecker = (targetHeight <= image->height);
	bool fileSizeChecker = (targetFileSizeMin <= image->imageSize) && (targetFileSizeMax >= image->imageSize);
	//Release
	cvReleaseImage(&image);
	//
	//return widthChecker && heightChecker && fileSizeChecker;
	return widthChecker && heightChecker;
}

void OpenCvOperation::fullbodyDetectAndDisplay_Haar(std::string filePath)
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
	static std::string fullbody_cascade_name = "..//data//haarcascades//haarcascade_fullbody.xml";
	static std::string upperbody_cascade_name = "..//data//haarcascades//haarcascade_upperbody.xml";
	//
	static CascadeClassifier fullbody_cascade;
	static CascadeClassifier upperbody_cascade;
	static std::string window_name = "Image_Fullbody_detection_Haar";
	//
	if (!frame.empty())
	{
		//-- 1. Load the cascades
		if (!fullbody_cascade.load(fullbody_cascade_name)){ CCLOG("fullbody_cascade(!)Error loading\n"); return; };
		if (!upperbody_cascade.load(upperbody_cascade_name)){ CCLOG("upperbody_cascade(!)Error loading\n"); return; };
	}

	std::vector<cv::Rect> faces;
	Mat frame_gray;

	cvtColor(frame, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);
	//-- Detect fullbody
	vector<cv::Rect> bodys;

	//-- detect body */
	fullbody_cascade.detectMultiScale(frame_gray, bodys, 1.1, 3, 3,cv::Size(45, 80));
	for (int j = 0; j < bodys.size(); j++)
	{
		cv::Point center(bodys[j].x + bodys[j].width*1.0, bodys[j].y + +bodys[j].height*1.0);
		cv::ellipse(frame, center, cv::Size(bodys[j].width*0.5, bodys[j].height*0.5), 0, 0, 360, cv::Scalar(255, 0, 255), 4, 8, 0);
	}
	//-- detect upperbody */
	upperbody_cascade.detectMultiScale(frame_gray, bodys, 1.1, 2, 18 | 9, cv::Size(3, 7));
	for (int j = 0; j < bodys.size(); j++)
	{
		cv::Point center(bodys[j].x + bodys[j].width*1.0, bodys[j].y + +bodys[j].height*1.0);
		cv::ellipse(frame, center, cv::Size(bodys[j].width*0.5, bodys[j].height*0.5), 0, 0, 360, cv::Scalar(255, 200, 255), 4, 8, 0);
	}
	//-- Show what you got
	imshow(window_name, frame);
}

//cvMat image attributes check
bool OpenCvOperation::cvMatImageAttributesCheck(std::string filePath)
{
	//
	cv::Mat image = cv::imread(filePath);
	if (!image.data)
	{
		//TODO:image attributes check
	};
	//Be tidy
	//cvReleaseMat(image);
	return true;
}

//OpenCV function header
void OpenCvOperation::fullbodyDetectAndDisplay_Hog(std::string filePath)
{
	cv::Mat src_img;
	cv::Mat target_img = cv::imread(filePath);

#ifdef USE_GPU
	cv::gpu::GpuMat src_gpu, mono_gpu;
	cv::gpu::HOGDescriptor hog;
	hog.setSVMDetector(cv::gpu::HOGDescriptor::getDefaultPeopleDetector());
#else
	cv::HOGDescriptor hog;
	cv::Mat mono_img;
	hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
#endif

	std::vector<cv::Rect> found;
	//
	src_img = target_img.clone();

#ifdef USE_GPU
		src_gpu.upload(src_img);
		cv::gpu::cvtColor(src_gpu, mono_gpu, CV_BGR2GRAY);
		hog.detectMultiScale(mono_gpu, found);
#else
		cv::cvtColor(src_img, mono_img, CV_BGR2GRAY);
		hog.detectMultiScale(mono_img, found);
#endif

	for (unsigned i = 0; i < found.size(); i++) {
		cv::Rect r = found[i];
		rectangle(src_img, r.tl(), r.br(), cv::Scalar(0, 255, 0), 2);
	}
	cv::imshow("Image_Fullbody_detection_Hog", src_img);

}