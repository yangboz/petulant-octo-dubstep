#include "OpenCvOpeartion.h"

// to enable CCLOG()
#define COCOS2D_DEBUG 1
#include "cocos2d.h"

//OpenCV function header
//void OpenCvOperation::faceDetectAndDisplay(std::string filePath)
int OpenCvOperation::faceDetection(std::string filePath, bool display)
{
	//
	cv::Mat frame = imread(filePath);
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
		if (!face_cascade.load(face_cascade_name)){ CCLOG("face_cascade(!)Error loading\n"); return -1; };
		//if (!eyes_cascade.load(eyes_cascade_name)){ CCLOG("eyes_cascade(!)Error loading\n"); return; };
		//if (!smile_cascade.load(smile_cascade_name)){ CCLOG("smile_cascade(!)Error loading\n"); return; };
	}

	std::vector<cv::Rect> faces;
	Mat frame_gray;

	cvtColor(frame, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);
	//-- Detect faces
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));
	if (display)
	{
		for (size_t i = 0; i < faces.size(); i++)
		{
			cv::Point center(faces[i].x + faces[i].width*0.8, faces[i].y + faces[i].height*0.8);
			//ellipse(frame, center, cv::Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, cv::Scalar(255, 0, 255), 4, 8, 0);
			cv::rectangle(frame, cv::Rect(faces[i].x, faces[i].y, faces[i].width, faces[i].height), cv::Scalar(255, 0, 255));

			/*
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

			std::vector<cv::Rect> smiles;

			//-- In each face, detect smiles
			smile_cascade.detectMultiScale(faceROI, smiles, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

			for (size_t k = 0; k < smiles.size(); k++)
			{
				cv::Point center(faces[i].x + smiles[k].x + smiles[k].width*0.5, faces[i].y + smiles[k].y + smiles[k].height*0.5);
				int radius = cvRound((smiles[k].width + smiles[k].height)*0.125);
				//circle(frame, center, radius, cv::Scalar(255, 100, 0), 4, 8, 0);
				cv::ellipse(frame, center, cv::Size(smiles[k].width*0.5, smiles[k].height*0.5), 0, 0, 360, cv::Scalar(255, 200, 0), 4, 8, 0);
			}
			*/
		}
		//-- Show what you got
		imshow(window_name, frame);
	}
	return faces.size();
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

//Background substraction using MOG
void OpenCvOperation::backgroundSubstraction_MOG_1(std::string filePath)
{
	cv::Mat fgMaskMOG; //fg mask generated by MOG method
	Ptr<BackgroundSubtractor> pMOG; //MOG Background subtractor
	//create Background Subtractor objects
	pMOG = new BackgroundSubtractorMOG(); //MOG approach
	//read the first file of the sequence
	cv::Mat frame = imread(filePath);
	if (!frame.data){
		//error in opening the first image
		CCLOG("Unable to open first image frame: ",filePath);
		exit(EXIT_FAILURE);
	}
	//update the background model
	pMOG->operator()(frame, fgMaskMOG);
	cv::rectangle(frame, cv::Point(10, 2), cv::Point(100, 20),
		cv::Scalar(255, 255, 255), -1);
	cv::putText(frame, filePath.c_str(), cv::Point(15, 15),
		FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0));
	//show the current frame and the fg masks
	cv::imshow("Frame", frame);
	cv::imshow("FG Mask MOG_1", fgMaskMOG);
}

void OpenCvOperation::backgroundSubstraction_MOG_2(std::string filePath)
{
	cv::Mat fgMaskMOG; //fg mask fg mask generated by MOG2 method
	Ptr<BackgroundSubtractor> pMOG2; //MOG2 Background subtractor
	//create Background Subtractor objects
	pMOG2 = new BackgroundSubtractorMOG2(); //MOG2 approach
	//read the first file of the sequence
	cv::Mat frame = imread(filePath);
	if (!frame.data){
		//error in opening the first image
		CCLOG("Unable to open first image frame: ", filePath);
		exit(EXIT_FAILURE);
	}
	//update the background model
	pMOG2->operator()(frame, fgMaskMOG);
	cv::rectangle(frame, cv::Point(10, 2), cv::Point(100, 20),
		cv::Scalar(255, 255, 255), -1);
	cv::putText(frame, filePath.c_str(), cv::Point(15, 15),
		FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0));
	//show the current frame and the fg masks
	cv::imshow("Frame", frame);
	cv::imshow("FG Mask MOG_2", fgMaskMOG);
}
void OpenCvOperation::backgroundSubstraction_(std::string filePath)
{
	//
	cvNamedWindow("frameForeground", 1);
	IplImage *image = 0, *frameTime1 = 0, *frameTime2 = 0, *frameForeground = 0, *img1 = 0, *img2 = 0;
	//read the first file of the sequence
	//cv::Mat frameImage = imread(filePath);
	IplImage* frame = cvLoadImage(filePath.c_str());
	//*frame = IplImage(frameImage);   //every time create/initialize an image (which name is frame) to process
	if (!image)    //if there is no image, do the followings
	{
		/* allocate all the buffers */
		image = cvCreateImage(cvGetSize(frame), 8, 3);
		frameTime1 = cvCreateImage(cvGetSize(frame), 8, 1);
		frameTime2 = cvCreateImage(cvGetSize(frame), 8, 1);
		frameForeground = cvCreateImage(cvGetSize(frame), 8, 1);
		img1 = cvCreateImage(cvGetSize(frame), 8, 1);
		img2 = cvCreateImage(cvGetSize(frame), 8, 1);
	}
	cvCopy(frame, image, 0);
	cvCvtColor(image, img1, CV_BGR2GRAY);
	cvCopy(img1, frameTime1, 0);    //currently frame in grayscale
	cvAbsDiff(
		frameTime1,
		frameTime2,
		frameForeground
		);

	cvThreshold(
		frameForeground,
		frameForeground,
		10,
		255,
		CV_THRESH_BINARY);
	cvErode(
		frameForeground,
		frameForeground,
		0,
		1);
	cvDilate(
		frameForeground,
		frameForeground,
		0,
		1);
	cvDilate(
		frameForeground,
		frameForeground,
		0,
		1);
	cvErode(
		frameForeground,
		frameForeground,
		0,
		1);
	cvShowImage("Image before backgroundSubstraction", image);  //displays the image in the specified window  
	cvShowImage("frameForeground", frameForeground);

	cvCopy(frameTime1, frameTime2, 0);
	//
	//cvDestroyWindow("Camera");
	//cvDestroyWindow("frameForeground");
}
//@see http://docs.opencv.org/trunk/doc/py_tutorials/py_imgproc/py_grabcut/py_grabcut.html
bool OpenCvOperation::foregroundGrabcut(std::string filePath,bool display)
{
	//
	cv::Mat image = cv::imread(filePath);
	// define bounding rectangle 
	cv::Rect rectangle(0, 0, image.cols-1, image.rows-1);
	cv::Mat result; // segmentation result (4 possible values)
	cv::Mat bgModel, fgModel; // the models (internally used)
	// GrabCut segmentation
	cv::grabCut(image,    // input image
		result,   // segmentation result
		rectangle,// rectangle containing foreground 
		bgModel, fgModel, // models
		1,        // number of iterations
		cv::GC_INIT_WITH_RECT); // use rectangle
	CCLOG( "cv::grabCut complete!");
	// Get the pixels marked as likely foreground
	cv::compare(result, cv::GC_PR_FGD, result, cv::CMP_EQ);
	// Generate output image
	cv::Mat foreground(image.size(), CV_8UC3, cv::Scalar(255, 255, 255));
	image.copyTo(foreground, result); // bg pixels not copied
	if (display)
	{
		// draw rectangle on original image
		cv::rectangle(image, rectangle, cv::Scalar(255, 0, 255), 1);
		cv::namedWindow("Image");
		cv::imshow("Image", image);
		// display result
		cv::namedWindow("Segmented Image");
		cv::imshow("Segmented Image", foreground);
	}
	//@see http://answers.opencv.org/question/24463/how-to-remove-black-background-from-grabcut-output/
	Mat dst;//(src.rows,src.cols,CV_8UC4);
	Mat tmp, alpha;

	cvtColor(foreground, tmp, CV_BGR2GRAY);
	threshold(tmp, alpha, 100, 255, THRESH_BINARY);

	Mat rgb[3];
	split(foreground, rgb);

	Mat rgba[4] = { rgb[0], rgb[1], rgb[2], alpha };
	merge(rgba, 4, dst);
	//Save the result(image file)
	return OpenCvOperation::saveMatImageFile(dst, HW_DataModel::HW_DataModel::OUT_PUT_FOREGROUND_FILE_NAME);
}
//@see http://docs.opencv.org/doc/tutorials/core/adding_images/adding_images.html
void OpenCvOperation::addingTwoImages(std::string filePath_foreground, std::string filePath_background, std::string dest)
{
	double alpha = 0.5; double beta;
	Mat src1, src2, dst;
	/// Read image ( same size, same type )
	src1 = imread(filePath_foreground);
	src2 = imread(filePath_background);

	if (!src1.data) { CCLOG("Error loading foreground with filePath: %s", filePath_foreground.c_str()); return; }
	if (!src2.data) { CCLOG("Error loading background with filePath: %s", filePath_background.c_str()); return; }

	/// Create Windows
	cv::namedWindow("Linear Blend(AddImages)", 1);

	beta = (1.0 - alpha);
	addWeighted(src1, alpha, src2, beta, 0.0, dst);

	cv::imshow("Linear Blend(AddImages)", dst);
}
//
bool OpenCvOperation::saveMatImageFile(cv::Mat image,std::string context)
{
	bool saved = false;
	/*
	// Create mat with alpha channel
	cv::Mat4b mat(640, 480);
	OpenCvOperation::createAlphaMat(mat);
    std::vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);
	*/
	saved = cv::imwrite(context, image);
	// Set image quality to 100
	//int imageParams[3] = { CV_IMWRITE_PNG_BILEVEL, 100, 0 };
	// Save image
	//saved = cvSaveImage(HW_DataModel::HW_DataModel::OUT_PUT_FOREGROUND_FILE_NAME.c_str(), image, imageParams);
	return saved;
}
bool OpenCvOperation::saveIplImageFile(IplImage image,std::string context)
{
	bool saved = true;
	//TODO:

	return saved;
}
void OpenCvOperation::createAlphaMat(cv::Mat4b &mat)
{
	for (int j = 0; j < mat.rows; ++j) {
		for (int i = 0; i < mat.cols; ++i) {
			cv::Vec4b& rgba = mat.at<cv::Vec4b>(j, i);
			rgba[0] = UCHAR_MAX;
			rgba[1] = (float(mat.cols - i)) / ((float)mat.cols) * UCHAR_MAX;
			rgba[2] = (float(mat.rows - j)) / ((float)mat.rows) * UCHAR_MAX;
			rgba[3] = 0.5 * (rgba[1] + rgba[2]);
		}
	}
}
///Save image file with transform
bool OpenCvOperation::saveRoatedImgeFile(double angle, std::string context)
{
	bool saved = false;
	//
	cv::Mat src = cv::imread(context);
	cv::Mat dst;
	//Rotate an image
	int len = std::max(src.cols, src.rows);
	cv::Point2f pt(len / 2., len / 2.);
	cv::Mat r = cv::getRotationMatrix2D(pt, -angle, 1.0);
	cv::warpAffine(src, dst, r, cv::Size(len, len));
	//
	saved = cv::imwrite(context, dst);
	return saved;
}
bool OpenCvOperation::saveScaledImageFile(double rate, std::string context)
{
	bool saved = false;
	//
	return saved;
}
//Save image file with solid color
bool OpenCvOperation::saveColoredImageFile(cv::Scalar colorScalar,int width,int height, std::string context)
{
	bool saved = false;
	//
	IplImage *image = cvCreateImage(cvSize(width, height), 8, 3);
	cv::Mat matImage = cvarrToMat(image);
	matImage.setTo(colorScalar);
	saved = imwrite(context, matImage);
	return saved;
}