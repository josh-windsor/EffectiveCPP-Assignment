#include "stdafx.h"
#include "OpenCVImplementation.h"
#include <iostream>
#include <cstdlib>
#include <thread>
#include "Timer.h"

#include "../Performance2/Libraries/opencv/include/opencv2/core/core.hpp"
#include "../Performance2/Libraries/opencv/include/opencv2/highgui/highgui.hpp"
#include "../Performance2/Libraries/opencv/include/opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

inline static Mat Scale(Mat i)
{
	Mat dest = i.clone();
	resize(i, dest, Size(), 2.0, 2.0);
	return dest;
}

inline static Mat Brighten(Mat i)
{
	Mat dest;
	i.convertTo(dest, -1, 1, 10);
	return dest;
}

inline static Mat Rotate(Mat i)
{
	Mat dest;
	rotate(i, dest, ROTATE_90_CLOCKWISE);
	return dest;
}
inline static Mat GrayScale(Mat i)
{
	Mat dest;
	cvtColor(i, dest, CV_RGB2GRAY);
	return dest;
}

inline static Mat CombinedProcess(Mat i) 
{
	i.convertTo(i, -1, 1, 10);
	rotate(i, i, ROTATE_90_CLOCKWISE);
	resize(i, i, Size(), 2.0, 2.0);
	return i;
}


static inline void ThreadProcess(const char* inName, const char* outName) 
{
	//read in jpeg
	Mat b1 = imread(inName, CV_LOAD_IMAGE_GRAYSCALE);
	//brighten by 50
	b1.convertTo(b1, -1, 1, 10);
	//rotate clockwise
	rotate(b1, b1, ROTATE_90_CLOCKWISE);
	//scales using bilinear interpolation by default
	resize(b1, b1, Size(), 2.0, 2.0);
	//write to png file
	imwrite(outName, b1);

}


void RunOpenCVFuncts(char taskSelection)
{

	int loops = 50;


	// Time the application's execution time.
	TIMER start;	// DO NOT CHANGE THIS LINE

					//--------------------------------------------------------------------------------------
					// Process the images...  

					// Put your changes from here...
	//41.8922 secs with loop
	//41.2769

	for (int i = 0; i < loops; ++i)
	{
		//starts each thread
		thread t1 (ThreadProcess, "IMG_1.JPG" , "IMG_1.PNG" );
		thread t2 (ThreadProcess, "IMG_2.JPG" , "IMG_2.PNG" );
		thread t3 (ThreadProcess, "IMG_3.JPG" , "IMG_3.PNG" );
		thread t4 (ThreadProcess, "IMG_4.JPG" , "IMG_4.PNG" );
		thread t5 (ThreadProcess, "IMG_5.JPG" , "IMG_5.PNG" );
		thread t6 (ThreadProcess, "IMG_6.JPG" , "IMG_6.PNG" );
		thread t7 (ThreadProcess, "IMG_7.JPG" , "IMG_7.PNG" );
		thread t8 (ThreadProcess, "IMG_8.JPG" , "IMG_8.PNG" );
		thread t9 (ThreadProcess, "IMG_9.JPG" , "IMG_9.PNG" );
		thread t10(ThreadProcess, "IMG_10.JPG", "IMG_10.PNG");
		thread t11(ThreadProcess, "IMG_11.JPG", "IMG_11.PNG");
		thread t12(ThreadProcess, "IMG_12.JPG", "IMG_12.PNG");
		thread t13(ThreadProcess, "IMG_13.JPG", "IMG_13.PNG");
		thread t14(ThreadProcess, "IMG_14.JPG", "IMG_14.PNG");
		thread t15(ThreadProcess, "IMG_15.JPG", "IMG_15.PNG");
		thread t16(ThreadProcess, "IMG_16.JPG", "IMG_16.PNG");
		thread t17(ThreadProcess, "IMG_17.JPG", "IMG_17.PNG");
		thread t18(ThreadProcess, "IMG_18.JPG", "IMG_18.PNG");
		thread t19(ThreadProcess, "IMG_19.JPG", "IMG_19.PNG");
		thread t20(ThreadProcess, "IMG_20.JPG", "IMG_20.PNG");
		thread t21(ThreadProcess, "IMG_21.JPG", "IMG_21.PNG");
		thread t22(ThreadProcess, "IMG_22.JPG", "IMG_22.PNG");
		//waits for the thread to finish
		t1.join();
		t2.join();
		t3.join();
		t4.join();
		t5.join();
		t6.join();
		t7.join();
		t8.join();
		t9.join();
		t10.join();
		t11.join();
		t12.join();
		t13.join();
		t14.join();
		t15.join();
		t16.join();
		t17.join();
		t18.join();
		t19.join();
		t20.join();
		t21.join();
		t22.join();
	}

	//-------------------------------------------------------------------------------------------------------

	// How long did it take?...   DO NOT CHANGE FROM HERE...

	TIMER end;

	TIMER elapsed;

	elapsed = end - start;

	__int64 ticks_per_second = start.get_frequency();

	// Display the resulting time...

	double elapsed_seconds = (double)elapsed.get_time() / (double)ticks_per_second;

	cout << "Elapsed time (seconds): " << elapsed_seconds / loops;
	cout << " after " << loops << " repeats.";
	cout << endl;
	cout << "Press a key to continue" << endl;


	char c;
	cin >> c;
}