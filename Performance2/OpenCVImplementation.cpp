#include "stdafx.h"
#include "OpenCVImplementation.h"
#include <iostream>
#include "Timer.h"

#include "../Libraries/opencv/include/opencv2/core/core.hpp"
#include "../Libraries/opencv/include/opencv2/highgui/highgui.hpp"
#include "../Libraries/opencv/include/opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

inline static Mat Scale(Mat i)
{
	Mat dest = i.clone();
	resize(i, dest, Size(), 2.0, 2.0);
	return dest;
}


void RunOpenCVFuncts(char taskSelection) 
{

	Mat(*mainTask)(Mat);
	switch (taskSelection)
	{
	case '5':
		mainTask = Scale;
		break;
	}

	// Time the application's execution time.
	TIMER start;	// DO NOT CHANGE THIS LINE

					//--------------------------------------------------------------------------------------
					// Process the images...  

					// Put your changes from here...


	Mat b1, dest1;
	b1 = imread("IMG_1.JPG", CV_LOAD_IMAGE_COLOR);
	dest1 = mainTask(b1);
	imwrite("IMG_1.PNG", dest1);


	b1 = imread("IMG_2.JPG", CV_LOAD_IMAGE_COLOR);
	dest1 = mainTask(b1);
	imwrite("IMG_2.PNG", dest1);

	b1 = imread("IMG_3.JPG", CV_LOAD_IMAGE_COLOR);
	dest1 = mainTask(b1);
	imwrite("IMG_3.PNG", dest1);

	b1 = imread("IMG_4.JPG", CV_LOAD_IMAGE_COLOR);
	dest1 = mainTask(b1);
	imwrite("IMG_4.PNG", dest1);

	b1 = imread("IMG_5.JPG", CV_LOAD_IMAGE_COLOR);
	dest1 = mainTask(b1);
	imwrite("IMG_5.PNG", dest1);

	b1 = imread("IMG_6.JPG", CV_LOAD_IMAGE_COLOR);
	dest1 = mainTask(b1);
	imwrite("IMG_6.PNG", dest1);

	b1 = imread("IMG_7.JPG", CV_LOAD_IMAGE_COLOR);
	dest1 = mainTask(b1);
	imwrite("IMG_7.PNG", dest1);

	b1 = imread("IMG_8.JPG", CV_LOAD_IMAGE_COLOR);
	dest1 = mainTask(b1);
	imwrite("IMG_8.PNG", dest1);

	b1 = imread("IMG_9.JPG", CV_LOAD_IMAGE_COLOR);
	dest1 = mainTask(b1);
	imwrite("IMG_9.PNG", dest1);

	b1 = imread("IMG_10.JPG", CV_LOAD_IMAGE_COLOR);
	dest1 = mainTask(b1);
	imwrite("IMG_10.PNG", dest1);

	b1 = imread("IMG_11.JPG", CV_LOAD_IMAGE_COLOR);
	dest1 = mainTask(b1);
	imwrite("IMG_11.PNG", dest1);

	b1 = imread("IMG_12.JPG", CV_LOAD_IMAGE_COLOR);
	dest1 = mainTask(b1);
	imwrite("IMG_12.PNG", dest1);

	b1 = imread("IMG_13.JPG", CV_LOAD_IMAGE_COLOR);
	dest1 = mainTask(b1);
	imwrite("IMG_13.PNG", dest1);

	b1 = imread("IMG_14.JPG", CV_LOAD_IMAGE_COLOR);
	dest1 = mainTask(b1);
	imwrite("IMG_14.PNG", dest1);

	b1 = imread("IMG_15.JPG", CV_LOAD_IMAGE_COLOR);
	dest1 = mainTask(b1);
	imwrite("IMG_15.PNG", dest1);

	b1 = imread("IMG_16.JPG", CV_LOAD_IMAGE_COLOR);
	dest1 = mainTask(b1);
	imwrite("IMG_16.PNG", dest1);

	b1 = imread("IMG_17.JPG", CV_LOAD_IMAGE_COLOR);
	dest1 = mainTask(b1);
	imwrite("IMG_17.PNG", dest1);

	b1 = imread("IMG_18.JPG", CV_LOAD_IMAGE_COLOR);
	dest1 = mainTask(b1);
	imwrite("IMG_18.PNG", dest1);

	b1 = imread("IMG_19.JPG", CV_LOAD_IMAGE_COLOR);
	dest1 = mainTask(b1);
	imwrite("IMG_19.PNG", dest1);

	b1 = imread("IMG_20.JPG", CV_LOAD_IMAGE_COLOR);
	dest1 = mainTask(b1);
	imwrite("IMG_20.PNG", dest1);

	b1 = imread("IMG_21.JPG", CV_LOAD_IMAGE_COLOR);
	dest1 = mainTask(b1);
	imwrite("IMG_21.PNG", dest1);

	b1 = imread("IMG_22.JPG", CV_LOAD_IMAGE_COLOR);
	dest1 = mainTask(b1);
	imwrite("IMG_22.PNG", dest1);

	//-------------------------------------------------------------------------------------------------------

	// How long did it take?...   DO NOT CHANGE FROM HERE...

	TIMER end;

	TIMER elapsed;

	elapsed = end - start;

	__int64 ticks_per_second = start.get_frequency();

	// Display the resulting time...

	double elapsed_seconds = (double)elapsed.get_time() / (double)ticks_per_second;

	cout << "Elapsed time (seconds): " << elapsed_seconds;
	cout << endl;
	cout << "Press a key to continue" << endl;

	char c;
	cin >> c;
}