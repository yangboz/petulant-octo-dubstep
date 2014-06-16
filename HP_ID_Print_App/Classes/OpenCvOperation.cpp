#include "OpenCvOpeartion.h"

// to enable CCLOG()
#define COCOS2D_DEBUG 1
#include "cocos2d.h"
//
const Scalar RED = Scalar(0, 0, 255);
const Scalar PINK = Scalar(230, 130, 255);
const Scalar BLUE = Scalar(255, 0, 0);
const Scalar LIGHTBLUE = Scalar(255, 255, 160);
const Scalar GREEN = Scalar(0, 255, 0);

const int BGD_KEY = CV_EVENT_FLAG_CTRLKEY;
const int FGD_KEY = CV_EVENT_FLAG_SHIFTKEY;

// Various color types for detected shirt colors.
enum  { cBLACK = 0, cWHITE, cGREY, cRED, cORANGE, cYELLOW, cGREEN, cAQUA, cBLUE, cPURPLE, cPINK, NUM_COLOR_TYPES };
char* sCTypes[NUM_COLOR_TYPES] = { "Black", "White", "Grey", "Red", "Orange", "Yellow", "Green", "Aqua", "Blue", "Purple", "Pink" };
uchar cCTHue[NUM_COLOR_TYPES] = { 0, 0, 0, 0, 20, 30, 55, 85, 115, 138, 161 };
uchar cCTSat[NUM_COLOR_TYPES] = { 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255 };
uchar cCTVal[NUM_COLOR_TYPES] = { 0, 255, 120, 255, 255, 255, 255, 255, 255, 255, 255 };

static void getBinMask(const Mat& comMask, Mat& binMask)
{
	if (comMask.empty() || comMask.type() != CV_8UC1)
		CV_Error(CV_StsBadArg, "comMask is empty or has incorrect type (not CV_8UC1)");
	if (binMask.empty() || binMask.rows != comMask.rows || binMask.cols != comMask.cols)
		binMask.create(comMask.size(), CV_8UC1);
	binMask = comMask & 1;
}

class GCApplication
{
public:
	enum{ NOT_SET = 0, IN_PROCESS = 1, SET = 2 };
	static const int radius = 2;
	static const int thickness = -1;

	void reset();
	void setImageAndWinName(const Mat& _image, const string& _winName);
	void showImage() const;
	void mouseClick(int event, int x, int y, int flags, void* param);
	int nextIter();
	int getIterCount() const { return iterCount; }
private:
	void setRectInMask();
	void setLblsInMask(int flags, cv::Point p, bool isPr);

	const string* winName;
	const Mat* image;
	Mat mask;
	Mat bgdModel, fgdModel;

	uchar rectState, lblsState, prLblsState;
	bool isInitialized;

	cv::Rect rect;
	vector<cv::Point> fgdPxls, bgdPxls, prFgdPxls, prBgdPxls;
	int iterCount;
};

void GCApplication::reset()
{
	if (!mask.empty())
		mask.setTo(Scalar::all(GC_BGD));
	bgdPxls.clear(); fgdPxls.clear();
	prBgdPxls.clear();  prFgdPxls.clear();

	isInitialized = false;
	rectState = NOT_SET;
	lblsState = NOT_SET;
	prLblsState = NOT_SET;
	iterCount = 0;
}

void GCApplication::setImageAndWinName(const Mat& _image, const string& _winName)
{
	if (_image.empty() || _winName.empty())
		return;
	image = &_image;
	winName = &_winName;
	mask.create(image->size(), CV_8UC1);
	reset();
}

void GCApplication::showImage() const
{
	if (image->empty() || winName->empty())
		return;

	Mat res;
	Mat binMask;
	if (!isInitialized)
		image->copyTo(res);
	else
	{
		getBinMask(mask, binMask);
		image->copyTo(res, binMask);
	}

	vector<cv::Point>::const_iterator it;
	for (it = bgdPxls.begin(); it != bgdPxls.end(); ++it)
		circle(res, *it, radius, BLUE, thickness);
	for (it = fgdPxls.begin(); it != fgdPxls.end(); ++it)
		circle(res, *it, radius, RED, thickness);
	for (it = prBgdPxls.begin(); it != prBgdPxls.end(); ++it)
		circle(res, *it, radius, LIGHTBLUE, thickness);
	for (it = prFgdPxls.begin(); it != prFgdPxls.end(); ++it)
		circle(res, *it, radius, PINK, thickness);

	if (rectState == IN_PROCESS || rectState == SET)
		rectangle(res, cv::Point(rect.x, rect.y), cv::Point(rect.x + rect.width, rect.y + rect.height), GREEN, 2);

	imshow(*winName, res);
}

void GCApplication::setRectInMask()
{
	assert(!mask.empty());
	mask.setTo(GC_BGD);
	rect.x = max(0, rect.x);
	rect.y = max(0, rect.y);
	rect.width = min(rect.width, image->cols - rect.x);
	rect.height = min(rect.height, image->rows - rect.y);
	(mask(rect)).setTo(Scalar(GC_PR_FGD));
}

void GCApplication::setLblsInMask(int flags, cv::Point p, bool isPr)
{
	vector<cv::Point> *bpxls, *fpxls;
	uchar bvalue, fvalue;
	if (!isPr)
	{
		bpxls = &bgdPxls;
		fpxls = &fgdPxls;
		bvalue = GC_BGD;
		fvalue = GC_FGD;
	}
	else
	{
		bpxls = &prBgdPxls;
		fpxls = &prFgdPxls;
		bvalue = GC_PR_BGD;
		fvalue = GC_PR_FGD;
	}
	if (flags & BGD_KEY)
	{
		bpxls->push_back(p);
		circle(mask, p, radius, bvalue, thickness);
	}
	if (flags & FGD_KEY)
	{
		fpxls->push_back(p);
		circle(mask, p, radius, fvalue, thickness);
	}
}

void GCApplication::mouseClick(int event, int x, int y, int flags, void*)
{
	// TODO add bad args check
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN: // set rect or GC_BGD(GC_FGD) labels
	{
								   bool isb = (flags & BGD_KEY) != 0,
									   isf = (flags & FGD_KEY) != 0;
								   if (rectState == NOT_SET && !isb && !isf)
								   {
									   rectState = IN_PROCESS;
									   rect = cv::Rect(x, y, 1, 1);
								   }
								   if ((isb || isf) && rectState == SET)
									   lblsState = IN_PROCESS;
	}
		break;
	case CV_EVENT_RBUTTONDOWN: // set GC_PR_BGD(GC_PR_FGD) labels
	{
								   bool isb = (flags & BGD_KEY) != 0,
									   isf = (flags & FGD_KEY) != 0;
								   if ((isb || isf) && rectState == SET)
									   prLblsState = IN_PROCESS;
	}
		break;
	case CV_EVENT_LBUTTONUP:
		if (rectState == IN_PROCESS)
		{
			rect = cv::Rect(cv::Point(rect.x, rect.y), cv::Point(x, y));
			rectState = SET;
			setRectInMask();
			assert(bgdPxls.empty() && fgdPxls.empty() && prBgdPxls.empty() && prFgdPxls.empty());
			showImage();
		}
		if (lblsState == IN_PROCESS)
		{
			setLblsInMask(flags, cv::Point(x, y), false);
			lblsState = SET;
			showImage();
		}
		break;
	case CV_EVENT_RBUTTONUP:
		if (prLblsState == IN_PROCESS)
		{
			setLblsInMask(flags, cv::Point(x, y), true);
			prLblsState = SET;
			showImage();
		}
		break;
	case CV_EVENT_MOUSEMOVE:
		if (rectState == IN_PROCESS)
		{
			rect = cv::Rect(cv::Point(rect.x, rect.y), cv::Point(x, y));
			assert(bgdPxls.empty() && fgdPxls.empty() && prBgdPxls.empty() && prFgdPxls.empty());
			showImage();
		}
		else if (lblsState == IN_PROCESS)
		{
			setLblsInMask(flags, cv::Point(x, y), false);
			showImage();
		}
		else if (prLblsState == IN_PROCESS)
		{
			setLblsInMask(flags, cv::Point(x, y), true);
			showImage();
		}
		break;
	}
}

int GCApplication::nextIter()
{
	if (isInitialized)
		grabCut(*image, mask, rect, bgdModel, fgdModel, 1);
	else
	{
		if (rectState != SET)
			return iterCount;

		if (lblsState == SET || prLblsState == SET)
			grabCut(*image, mask, rect, bgdModel, fgdModel, 1, GC_INIT_WITH_MASK);
		else
			grabCut(*image, mask, rect, bgdModel, fgdModel, 1, GC_INIT_WITH_RECT);

		isInitialized = true;
	}
	iterCount++;

	bgdPxls.clear(); fgdPxls.clear();
	prBgdPxls.clear(); prFgdPxls.clear();

	return iterCount;
}

GCApplication gcapp;

//OpenCV function header
//void OpenCvOperation::faceDetectAndDisplay(std::string filePath)
vector<cv::Rect> OpenCvOperation::faceDetection(std::string filePath, bool display)
{
	//
	cv::Mat frame = imread(filePath);
	//@see http://docs.opencv.org/doc/tutorials/objdetect/cascade_classifier/cascade_classifier.html
	/** Global variables */
	static std::string face_cascade_name = "data//haarcascades//haarcascade_frontalface_alt_tree.xml";
	static std::string eyes_cascade_name = "data//haarcascades//haarcascade_eye.xml";
	static std::string smile_cascade_name = "data//haarcascades//haarcascade_smile.xml";
	//
	static CascadeClassifier face_cascade;
	static CascadeClassifier eyes_cascade;
	static CascadeClassifier smile_cascade;
	static std::string window_name = "Image_Face_detection";
	//
	std::vector<cv::Rect> faces;
	Mat frame_gray;
	//
	if (!frame.empty())
	{
		//-- 1. Load the cascades
		if (!face_cascade.load(face_cascade_name)){ CCLOG("face_cascade(!)Error loading\n"); return faces; };
		//if (!eyes_cascade.load(eyes_cascade_name)){ CCLOG("eyes_cascade(!)Error loading\n"); return; };
		//if (!smile_cascade.load(smile_cascade_name)){ CCLOG("smile_cascade(!)Error loading\n"); return; };
	}
	//
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
	// Free resources.
	//cvReleaseHaarClassifierCascade(&face_cascade);
	//
	return faces;
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
	static std::string fullbody_cascade_name = "data//haarcascades//haarcascade_fullbody.xml";
	static std::string upperbody_cascade_name = "data//haarcascades//haarcascade_upperbody.xml";
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
bool OpenCvOperation::foregroundGrabcut(std::string filePath, int width, int height, bool display,bool interactive)
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
	const std::string winName = "Segmented Image";
	if (display)
	{
		// draw rectangle on original image
		cv::rectangle(image, rectangle, cv::Scalar(255, 0, 255), 1);
		//cv::namedWindow("Image");
		//cv::imshow("Image", image);
		// display result
		cv::namedWindow(winName);
		cv::imshow(winName, foreground);
	}
	if (interactive)
	{
		//const std::string winName = "Segmented Image";
		Mat image = imread(filePath, 1);
		//设置鼠标响应函数  
		//cv::setMouseCallback(winName, on_mouse, 0);
		cv::setMouseCallback(winName, OpenCvOperation::on_mouse, 0);
		//初始化窗口和图片  
		gcapp.setImageAndWinName(image, winName);
		gcapp.showImage();
		//
		for (;;)
		{
			int c = waitKey(0);
			switch ((char)c)
			{
				//ESC按键退出  
			case '\x1b':
				cout << "Exiting ..." << endl;
				//goto exit_main;
				//r按键重置图像  
			case 'r':
				cout << endl;
				gcapp.reset();
				gcapp.showImage();
				break;
				//n按键进行一次处理  
			case 'n':
				int iterCount = gcapp.getIterCount();
				cout << "<" << iterCount << "... ";
				int newIterCount = gcapp.nextIter();
				if (newIterCount > iterCount)
				{
					gcapp.showImage();
					cout << iterCount << ">" << endl;
				}
				else
					cout << "rect must be determined>" << endl;
				break;
			}
		}
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
	//Resize the Mat
	Mat resized;
	cv::resize(dst, resized, cvSize(width, height));
	//Save the result(image file)
	return OpenCvOperation::saveMatImageFile(resized, HW_DataModel::HW_DataModel::OUT_PUT_FOREGROUND_FILE_NAME);
}
//@see http://docs.opencv.org/doc/tutorials/core/adding_images/adding_images.html
//@see http://eric-yuan.me/poisson-blending/
bool OpenCvOperation::addingTwoImages(std::string filePath_foreground, std::string filePath_background, std::string dest, bool display)
{
	double alpha = 1.0; double beta;
	Mat src1, src2, dst;
	/// Read image ( same size, same type )
	src1 = imread(filePath_foreground);
	src2 = imread(filePath_background);

	if (!src1.data) { CCLOG("Error loading foreground with filePath: %s", filePath_foreground.c_str()); return false; }
	if (!src2.data) { CCLOG("Error loading background with filePath: %s", filePath_background.c_str()); return false; }
	
	//beta = (1.0 - alpha);
	beta = 1.0;
	//addWeighted(src1, alpha, src2, beta, 0.0, dst);
	addWeighted(src1, alpha, src2, beta, 0.0, dst);//Notice:same width/height required.
	//
	if (display)
	{
		/// Create Windows
		cv::namedWindow("Linear Blend(AddImages)", 1);
		cv::imshow("Linear Blend(AddImages)", dst);
	}
	//Save the result(image file)
	return OpenCvOperation::saveMatImageFile(dst, dest);
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
	//free mem
	image.release();
	//
	return saved;
}
bool OpenCvOperation::saveIplImageFile(IplImage *image,std::string context)
{
	bool saved = true;
	//
	cv::Mat matImage = cvarrToMat(image);
	saved = imwrite(context, matImage);
	//free mem
	cvReleaseImage(&image);
	matImage.release();
	//
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
bool OpenCvOperation::saveRotatedImgeFile(double angle, std::string src, std::string dst)
{
	bool saved = false;
	//Using normal OpenCV warpAffine function
	/*
	cv::Mat src = cv::imread(context);
	cv::Mat dst;
	//Rotate an image
	int len = std::max(src.cols, src.rows);
	cv::Point2f pt(len / 2., len / 2.);
	cv::Mat r = cv::getRotationMatrix2D(pt, -angle, 1.0);
	cv::warpAffine(src, dst, r, cv::Size(len, len));
	//
	saved = cv::imwrite(context, dst);
	*/
	//@see http://www.shervinemami.info/imageTransforms.html
	// Rotate the image clockwise (or counter-clockwise if negative).
	// Remember to free the returned image.
	// Create a map_matrix, where the left 2x2 matrix
	// is the transform and the right 2x1 is the dimensions.
	IplImage *srcImage = cvLoadImage(src.c_str());
	float m[6];
	CvMat M = cvMat(2, 3, CV_32F, m);
	int w = srcImage->width;
	int h = srcImage->height;
	float angleRadians = angle * ((float)CV_PI / 180.0f);
	m[0] = (float)(cos(angleRadians));
	m[1] = (float)(sin(angleRadians));
	m[3] = -m[1];
	m[4] = m[0];
	m[2] = w*0.5f;
	m[5] = h*0.5f;

	// Make a spare image for the result
	CvSize sizeRotated;
	sizeRotated.width = cvRound(w);
	sizeRotated.height = cvRound(h);

	// Rotate
	IplImage *imageRotated = cvCreateImage(sizeRotated,
		srcImage->depth, srcImage->nChannels);

	// Transform the image
	cvGetQuadrangleSubPix(srcImage, imageRotated, &M);
	//
	saved = OpenCvOperation::saveIplImageFile(imageRotated, dst);
	//free mem
	
	return saved;
}
bool OpenCvOperation::saveScaledImageFile(double rate, std::string src, std::string dst)
{
	bool saved = false;
	//
	IplImage *srcImage = cvLoadImage(src.c_str());
	IplImage *imageScaled = cvCloneImage(srcImage);

	CvMat* rot_mat = cvCreateMat(2, 3, CV_32FC1);

	// Compute revolution matrix
	CvPoint2D32f core = cvPoint2D32f(cvGetSize(imageScaled).width / 2, cvGetSize(imageScaled).height / 2);
	cv2DRotationMatrix(core, 1.0, rate, rot_mat);

	// Do a transformation
	cvWarpAffine(srcImage, imageScaled, rot_mat);
	//
	saved = OpenCvOperation::saveIplImageFile(imageScaled, dst);
	//free mem
	return saved;
}
bool OpenCvOperation::saveMovedImageFile(double offsetX, double offsetY, std::string src, std::string dst)
{
	bool saved = false;
	//
	IplImage *srcImage = cvLoadImage(src.c_str());
	IplImage *imageScaled = cvCloneImage(srcImage);

	CvMat* rot_mat = cvCreateMat(2, 3, CV_32FC1);

	// Compute revolution matrix
	CvPoint2D32f core = cvPoint2D32f(cvGetSize(imageScaled).width / 2 + offsetX, cvGetSize(imageScaled).height / 2 + offsetY);
	cv2DRotationMatrix(core, 1.0, 1.0, rot_mat);

	// Do a transformation
	cvWarpAffine(srcImage, imageScaled, rot_mat);
	//
	saved = OpenCvOperation::saveIplImageFile(imageScaled, dst);
	//free mem
	return saved;
}
bool OpenCvOperation::saveTransformedImageFile(double angle, double scale, double offsetX, double offsetY, std::string src, std::string dst)
{
	bool saved = false;
	//
	IplImage *srcImage = cvLoadImage(src.c_str());
	IplImage *imageTransformed = cvCloneImage(srcImage);

	CvMat* rot_mat = cvCreateMat(2, 3, CV_32FC1);

	// Compute revolution matrix
	CvPoint2D32f core = cvPoint2D32f(cvGetSize(imageTransformed).width / 2 + offsetX, cvGetSize(imageTransformed).height / 2 + offsetY);
	cv2DRotationMatrix(core, angle, scale, rot_mat);

	// Do a transformation
	cvWarpAffine(srcImage, imageTransformed, rot_mat);
	//
	saved = OpenCvOperation::saveIplImageFile(imageTransformed, dst);
	//free mem
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
//@see http://funwithkinect.blogspot.com.br/2012/02/copying-and-tiling-with-opencv.html
bool OpenCvOperation::tilingImages(int row, int column, std::string context, std::string outputDest,bool display)
{
	bool saved = false;
	//create a new image pointer to point to the source image
	IplImage *img = cvLoadImage(context.c_str(), 1);
	//take care of non existent source images
	if (!img)
	{
		MessageBox(" Image could not be loaded, check if file exists!", "ERROR");
		return false;
	}


	//let us say, u want to tile this m times horizontally, and n times vertically
	// calculate size of new image

	int newWidth = img->width * column;
	int newHeight = img->height *row;

	// Create a new image to store the tiled image
	// 2nd parameter is the pixel size and 3rd parmeter is the number of
	// channels(R,G,B)

	IplImage *newImg = cvCreateImage(cvSize(newWidth, newHeight), IPL_DEPTH_8U, 3);


	// loop counters
	int left_top_x = 0;
	int left_top_y = 0;

	//loop from starting position to end
	for (; left_top_y < newHeight; left_top_x += (img->width))
	{
		if (left_top_x >= newWidth)
		{
			left_top_x = -img->width;
			left_top_y += img->height;
			continue;
		}
		// set the desired region of interest        
		cvSetImageROI(newImg, cvRect(left_top_x, left_top_y, img->width, img->height));
		// copy to that region
		cvCopy(img, newImg);
		// reset region of interest
		cvResetImageROI(newImg);
	}
	// show images of happy faces :)
	if (display)
	{
		cvNamedWindow("TiliedImage");
		cvShowImage("TiliedImage", newImg);
	}
	try
	{
		saved = cvSaveImage(outputDest.c_str(), newImg);
	}
	catch (...)
	{
		MessageBox("Destination file name invalid!","ERROR");
	}
	return saved;
}
///
void OpenCvOperation::on_mouse(int event, int x, int y, int flags, void* param)
{
	gcapp.mouseClick(event, x, y, flags, param);
}
//@see http://stackoverflow.com/questions/11987483/opencvs-canny-edge-detection-in-c
void OpenCvOperation::edgeDetection(std::string filePath, bool display)
{
	cv::Mat image = cv::imread(filePath);
	cv::Mat contours;
	cv::Mat gray_image;

	//cvtColor(image, gray_image, CV_RGB2GRAY);
	std::vector<cv::Mat> channels;
	cv::Mat hsv;
	cv::cvtColor(image, hsv, CV_RGB2HSV);
	cv::split(hsv, channels);
	gray_image = channels[0];

	cv::Canny(image, contours, 10, 350);

	if (display)
	{
		cv::namedWindow("Image");
		cv::imshow("Image", image);

		cv::namedWindow("Gray");
		cv::imshow("Gray", gray_image);

		cv::namedWindow("Canny");
		cv::imshow("Canny", contours);
	}
}
//@see http://blog.csdn.net/yangtrees/article/details/7482587
void OpenCvOperation::maxContourDetection(std::string filePath, bool display)
{
	IplImage* src;
	src = cvLoadImage(filePath.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* dst = cvCreateImage(cvGetSize(src), 8, 3);
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contour = 0;
	cvThreshold(src, src, 120, 255, CV_THRESH_BINARY);//二值化  
	if (display)
	{
		cvNamedWindow("Source", 1);
		cvShowImage("Source", src);
	}
	//提取轮廓  
	cvFindContours(src, storage, &contour, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	cvZero(dst);//清空数组  
	CvSeq* _contour = contour;
	double maxarea = 0;
	double minarea = 100;
	int n = -1, m = 0;//n为面积最大轮廓索引，m为迭代索引  
	for (; contour != 0; contour = contour->h_next)
	{

		double tmparea = fabs(cvContourArea(contour));
		if (tmparea < minarea)
		{
			cvSeqRemove(contour, 0); //删除面积小于设定值的轮廓  
			continue;
		}
		CvRect aRect = cvBoundingRect(contour, 0);
		if ((aRect.width / aRect.height)<1)
		{
			cvSeqRemove(contour, 0); //删除宽高比例小于设定值的轮廓  
			continue;
		}
		if (tmparea > maxarea)
		{
			maxarea = tmparea;
			n = m;
		}
		m++;
		//  CvScalar color = CV_RGB( rand()&255, rand()&255, rand()&255 );//创建一个色彩值  
		CvScalar color = CV_RGB(0, 255, 255);

		//max_level 绘制轮廓的最大等级。如果等级为0，绘制单独的轮廓。如果为1，绘制轮廓及在其后的相同的级别下轮廓。  
		//如果值为2，所有的轮廓。如果等级为2，绘制所有同级轮廓及所有低一级轮廓，诸此种种。  
		//如果值为负数，函数不绘制同级轮廓，但会升序绘制直到级别为abs(max_level)-1的子轮廓。   
		cvDrawContours(dst, contour, color, color, -1, 1, 8);//绘制外部和内部的轮廓  
	}
	contour = _contour; /*int k=0;*/
	int count = 0;
	for (; contour != 0; contour = contour->h_next)
	{
		count++;
		double tmparea = fabs(cvContourArea(contour));
		if (tmparea == maxarea /*k==n*/)
		{
			CvScalar color = CV_RGB(255, 0, 0);
			cvDrawContours(dst, contour, color, color, -1, 1, 8);
		}
		/*k++;*/
	}
	CCLOG("The total number of contours is:%d", count);
	if (display)
	{
		cvNamedWindow("Contours", 1);
		cvShowImage("Contours", dst);
	}
}
//@see http://docs.opencv.org/doc/tutorials/imgproc/shapedescriptors/bounding_rects_circles/bounding_rects_circles.html
void OpenCvOperation::contoursDetection(std::string filePath, bool display)
{
	Mat src; Mat src_gray;
	int thresh = 100;
	int max_thresh = 255;
	RNG rng(12345);
	/// Load source image and convert it to gray
	src = imread(filePath);

	/// Convert image to gray and blur it
	cvtColor(src, src_gray, CV_BGR2GRAY);
	blur(src_gray, src_gray, cv::Size(3, 3));

	/// Create Window
	char* source_window = "Source";
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, src);
	//
	Mat threshold_output;
	vector<vector<cv::Point> > contours;
	vector<Vec4i> hierarchy;

	/// Detect edges using Threshold
	threshold(src_gray, threshold_output, thresh, 255, THRESH_BINARY);
	/// Find contours
	findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	/// Approximate contours to polygons + get bounding rects and circles
	vector<vector<cv::Point> > contours_poly(contours.size());
	vector<cv::Rect> boundRect(contours.size());
	vector<Point2f>center(contours.size());
	vector<float>radius(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
		boundRect[i] = boundingRect(Mat(contours_poly[i]));
		minEnclosingCircle((Mat)contours_poly[i], center[i], radius[i]);
	}


	/// Draw polygonal contour + bonding rects + circles
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, cv::Point());
		rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
		circle(drawing, center[i], (int)radius[i], color, 2, 8, 0);
	}

	/// Show in a window
	namedWindow("Contours", CV_WINDOW_AUTOSIZE);
	imshow("Contours", drawing);
}
//@see http://shervinemami.info/shirtDetection.html
char* OpenCvOperation::shirtDetection(std::string filePath, bool display)
{
	// Open the image, either as greyscale or color
	IplImage* imageIn = cvLoadImage(filePath.c_str(), CV_LOAD_IMAGE_UNCHANGED);
	IplImage* imageDisplay = cvCloneImage(imageIn);
	char* shirtColor;
	//
	vector<cv::Rect> rectFaces = OpenCvOperation::faceDetection(filePath, display);
	// Process each detected face
	CCLOG("Detecting shirt colors below the faces.");
	for (int r = 0; r<rectFaces.size(); r++) {
		float initialConfidence = 1.0f;
		int bottom;
		cv::Rect rectFace = rectFaces[r];
		drawRectangle(imageDisplay, rectFace, CV_RGB(255, 0, 0));

		// Create the shirt region, to be below the detected face and of similar size.
		float SHIRT_DY = 1.2f;	// Distance from top of face to top of shirt region, based on detected face height.
		float SHIRT_SCALE_X = 0.6f;	// Width of shirt region compared to the detected face
		float SHIRT_SCALE_Y = 0.6f;	// Height of shirt region compared to the detected face
		CvRect rectShirt;
		rectShirt.x = rectFace.x + (int)(0.5f * (1.0f - SHIRT_SCALE_X) * (float)rectFace.width);
		rectShirt.y = rectFace.y + (int)(SHIRT_DY * (float)rectFace.height) + (int)(0.5f * (1.0f - SHIRT_SCALE_Y) * (float)rectFace.height);
		rectShirt.width = (int)(SHIRT_SCALE_X * rectFace.width);
		rectShirt.height = (int)(SHIRT_SCALE_Y * rectFace.height);
		CCLOG("Shirt region is from %d,%d to %d,%d",rectShirt.x,rectShirt.y,rectShirt.x + rectShirt.width - 1,rectShirt.y + rectShirt.height - 1);

		// If the shirt region goes partly below the image, try just a little below the face
		bottom = rectShirt.y + rectShirt.height - 1;
		if (bottom > imageIn->height - 1) {
			SHIRT_DY = 0.95f;	// Distance from top of face to top of shirt region, based on detected face height.
			SHIRT_SCALE_Y = 0.3f;	// Height of shirt region compared to the detected face
			// Use a higher shirt region
			rectShirt.y = rectFace.y + (int)(SHIRT_DY * (float)rectFace.height) + (int)(0.5f * (1.0f - SHIRT_SCALE_Y) * (float)rectFace.height);
			rectShirt.height = (int)(SHIRT_SCALE_Y * rectFace.height);
			initialConfidence = initialConfidence * 0.5f;	// Since we are using a smaller region, we are less confident about the results now.
			CCLOG("Warning: Shirt region goes past the end of the image. Trying to reduce the shirt region position to ",rectShirt.y," with a height of ",rectShirt.height);
		}

		// Try once again if it is partly below the image.
		bottom = rectShirt.y + rectShirt.height - 1;
		if (bottom > imageIn->height - 1) {
			bottom = imageIn->height - 1;	// Limit the bottom
			rectShirt.height = bottom - (rectShirt.y - 1);	// Adjust the height to use the new bottom
			initialConfidence = initialConfidence * 0.7f;	// Since we are using a smaller region, we are less confident about the results now.
			CCLOG("Warning: Shirt region still goes past the end of the image. Trying to reduce the shirt region height to ",rectShirt.height);
		}

		// Make sure the shirt region is in the image
		if (rectShirt.height <= 1) {
			CCLOG("Warning: Shirt region is not in the image at all, so skipping this face." );
		}
		else {

			// Show the shirt region
			drawRectangle(imageDisplay, rectShirt, CV_RGB(255, 255, 255));

			// Convert the shirt region from RGB colors to HSV colors
			//cout << "Converting shirt region to HSV" << endl;
			IplImage *imageShirt = cropRectangle(imageIn, rectShirt);
			IplImage *imageShirtHSV = cvCreateImage(cvGetSize(imageShirt), 8, 3);
			cvCvtColor(imageShirt, imageShirtHSV, CV_BGR2HSV);	// (note that OpenCV stores RGB images in B,G,R order.
			if (!imageShirtHSV) {
				CCLOG("ERROR: Couldn't convert Shirt image from BGR2HSV.");
				exit(1);
			}

			//cout << "Determining color type of the shirt" << endl;
			int h = imageShirtHSV->height;				// Pixel height
			int w = imageShirtHSV->width;				// Pixel width
			int rowSize = imageShirtHSV->widthStep;		// Size of row in bytes, including extra padding
			char *imOfs = imageShirtHSV->imageData;	// Pointer to the start of the image HSV pixels.
			// Create an empty tally of pixel counts for each color type
			int tallyColors[NUM_COLOR_TYPES];
			for (int i = 0; i<NUM_COLOR_TYPES; i++)
				tallyColors[i] = 0;
			// Scan the shirt image to find the tally of pixel colors
			for (int y = 0; y<h; y++) {
				for (int x = 0; x<w; x++) {
					// Get the HSV pixel components
					uchar H = *(uchar*)(imOfs + y*rowSize + x * 3 + 0);	// Hue
					uchar S = *(uchar*)(imOfs + y*rowSize + x * 3 + 1);	// Saturation
					uchar V = *(uchar*)(imOfs + y*rowSize + x * 3 + 2);	// Value (Brightness)

					// Determine what type of color the HSV pixel is.
					int ctype = getPixelColorType(H, S, V);
					// Keep count of these colors.
					tallyColors[ctype]++;
				}
			}

			// Print a report about color types, and find the max tally
			//cout << "Number of pixels found using each color type (out of " << (w*h) << ":\n";
			int tallyMaxIndex = 0;
			int tallyMaxCount = -1;
			int pixels = w * h;
			for (int i = 0; i<NUM_COLOR_TYPES; i++) {
				int v = tallyColors[i];
				CCLOG("%s,%d %, ",sCTypes[i],(v * 100 / pixels));
				if (v > tallyMaxCount) {
					tallyMaxCount = tallyColors[i];
					tallyMaxIndex = i;
				}
			}
			cout << endl;
			int percentage = initialConfidence * (tallyMaxCount * 100 / pixels);
			shirtColor = sCTypes[tallyMaxIndex];
			CCLOG("Color of shirt: %s (%d % confidence).", shirtColor, percentage);

			// Display the color type over the shirt in the image.
			CvFont font;
			//cvInitFont(&font,CV_FONT_HERSHEY_PLAIN,0.55,0.7, 0,1,CV_AA);	// For OpenCV 1.1
			cvInitFont(&font, CV_FONT_HERSHEY_PLAIN, 0.8, 1.0, 0, 1, CV_AA);	// For OpenCV 2.0
			char text[256];
			sprintf_s(text, sizeof(text)-1, "%d%%", percentage);
			cvPutText(imageDisplay, sCTypes[tallyMaxIndex], cvPoint(rectShirt.x, rectShirt.y + rectShirt.height + 12), &font, CV_RGB(255, 0, 0));
			cvPutText(imageDisplay, text, cvPoint(rectShirt.x, rectShirt.y + rectShirt.height + 24), &font, CV_RGB(255, 0, 0));


			// Free resources.
			cvReleaseImage(&imageShirtHSV);
			cvReleaseImage(&imageShirt);
		}//end if valid height
	}//end for loop

	if (display)
	{
		// Display the RGB debugging image
		cvNamedWindow("Shirt_Detection", 1);
		cvShowImage("Shirt_Detection", imageDisplay);
	}
	return shirtColor;
}
// Determine what type of color the HSV pixel is. Returns the colorType between 0 and NUM_COLOR_TYPES.
int  OpenCvOperation::getPixelColorType(int H, int S, int V)
{
	int color;
	if (V < 75)
		color = cBLACK;
	else if (V > 190 && S < 27)
		color = cWHITE;
	else if (S < 53 && V < 185)
		color = cGREY;
	else {	// Is a color
		if (H < 14)
			color = cRED;
		else if (H < 25)
			color = cORANGE;
		else if (H < 34)
			color = cYELLOW;
		else if (H < 73)
			color = cGREEN;
		else if (H < 102)
			color = cAQUA;
		else if (H < 127)
			color = cBLUE;
		else if (H < 149)
			color = cPURPLE;
		else if (H < 175)
			color = cPINK;
		else	// full circle 
			color = cRED;	// back to Red
	}
	return color;
}
// Returns a new image that is a cropped version of the original image. 
IplImage* OpenCvOperation::cropRectangle(IplImage *img, CvRect region)
{
	IplImage *imageTmp, *imageRGB;
	CvSize size;
	size.height = img->height;
	size.width = img->width;

	if (img->depth != IPL_DEPTH_8U) {
		std::cerr << "ERROR: Unknown image depth of " << img->depth << " given in cropRectangle() instead of 8." << std::endl;
		exit(1);
	}

	// First create a new (color or greyscale) IPL Image and copy contents of img into it.
	imageTmp = cvCreateImage(size, IPL_DEPTH_8U, img->nChannels);
	cvCopy(img, imageTmp);

	// Create a new image of the detected region
	//printf("Cropping image at x = %d, y = %d...", faces[i].x, faces[i].y);
	//printf("Setting region of interest...");
	// Set region of interest to that surrounding the face
	cvSetImageROI(imageTmp, region);
	// Copy region of interest (i.e. face) into a new iplImage (imageRGB) and return it
	size.width = region.width;
	size.height = region.height;
	imageRGB = cvCreateImage(size, IPL_DEPTH_8U, img->nChannels);
	cvCopy(imageTmp, imageRGB);	// Copy just the region.

	cvReleaseImage(&imageTmp);
	return imageRGB;
}


// Draw a rectangle around the given object (defaults to a red color)
void OpenCvOperation::drawRectangle(IplImage *img, CvRect face, CvScalar col)	{
	CvPoint p1, p2;
	p1.x = face.x;
	p1.y = face.y;
	p2.x = face.x + face.width;
	p2.y = face.y + face.height;
	cvRectangle(img, p1, p2, col, 2);
}