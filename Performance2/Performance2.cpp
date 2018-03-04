// Performance2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Performance2.h"

#include <iostream>
/*#include <GdiPlusHeaders.h>
#include <GdiPlusColor.h>
using namespace Gdiplus; */

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Timer - used to established precise timings for code.
class TIMER
{
	LARGE_INTEGER t_;

	__int64 current_time_;

	public:
		TIMER()	// Default constructor. Initialises this timer with the current value of the hi-res CPU timer.
		{
			QueryPerformanceCounter(&t_);
			current_time_ = t_.QuadPart;
		}

		TIMER(const TIMER &ct)	// Copy constructor.
		{
			current_time_ = ct.current_time_;
		}

		TIMER& operator=(const TIMER &ct)	// Copy assignment.
		{
			current_time_ = ct.current_time_;
			return *this;
		}

		TIMER& operator=(const __int64 &n)	// Overloaded copy assignment.
		{
			current_time_ = n;
			return *this;
		}

		~TIMER() {}		// Destructor.

		static __int64 get_frequency()
		{
			LARGE_INTEGER frequency;
			QueryPerformanceFrequency(&frequency); 
			return frequency.QuadPart;
		}

		__int64 get_time() const
		{
			return current_time_;
		}

		void get_current_time()
		{
			QueryPerformanceCounter(&t_);
			current_time_ = t_.QuadPart;
		}

		inline bool operator==(const TIMER &ct) const
		{
			return current_time_ == ct.current_time_;
		}

		inline bool operator!=(const TIMER &ct) const
		{
			return current_time_ != ct.current_time_;
		}

		__int64 operator-(const TIMER &ct) const		// Subtract a TIMER from this one - return the result.
		{
			return current_time_ - ct.current_time_;
		}

		inline bool operator>(const TIMER &ct) const
		{
			return current_time_ > ct.current_time_;
		}

		inline bool operator<(const TIMER &ct) const
		{
			return current_time_ < ct.current_time_;
		}

		inline bool operator<=(const TIMER &ct) const
		{
			return current_time_ <= ct.current_time_;
		}

		inline bool operator>=(const TIMER &ct) const
		{
			return current_time_ >= ct.current_time_;
		}
};

CWinApp theApp;  // The one and only application object

using namespace std;


CImage* Copy(CImage *source)
{
	CImage *dest = new CImage;
	dest -> Create(source -> GetWidth(), source -> GetHeight(), source -> GetBPP());
	source -> Draw(dest -> GetDC(), 0, 0, dest -> GetWidth(), dest -> GetHeight(), 0, 0, source -> GetWidth(), source -> GetHeight());
	dest -> ReleaseDC();
	return dest;
}

CImage* BrightenFast(CImage *i)
{
	CImage *dest = Copy(i);

	int width = dest->GetWidth();
	int height = dest->GetHeight();

	int pitch = i->GetPitch();
	BYTE* pInImage = (BYTE*)i->GetBits();
	BYTE* pOutImage = (BYTE*)dest->GetBits();

	long lAdrs;
	BYTE bRed, bGreen, bBlue;


	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{

			lAdrs = y * pitch + x * 3;
			bRed = *(pInImage + lAdrs);
			bGreen = *(pInImage + lAdrs + 1);
			bBlue = *(pInImage + lAdrs + 2);

			if ((bRed + 10) > 255) bRed = 255; else bRed += 10;
			if ((bGreen + 10) > 255) bGreen = 255; else bGreen += 10;
			if ((bBlue + 10) > 255) bBlue = 255; else bBlue += 10;



			*(pOutImage + lAdrs) = static_cast<BYTE>(bRed);
			*(pOutImage + lAdrs + 1) = static_cast<BYTE>(bGreen);
			*(pOutImage + lAdrs + 2) = static_cast<BYTE>(bBlue);

		}
	}

	return dest;
}

CImage* GreyscaleFast(CImage *i)
{
	CImage *dest = Copy(i);

	int width = dest->GetWidth();
	int height = dest->GetHeight();

	int pitch = i->GetPitch();
	BYTE* pInImage = (BYTE*)i->GetBits();
	BYTE* pOutImage = (BYTE*)dest->GetBits();

	long lAdrs;
	double gray;
	BYTE bRed, bGreen, bBlue;


	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			lAdrs = y * pitch + x * 3;
			bRed = *(pInImage + lAdrs);
			bGreen = *(pInImage + lAdrs + 1);
			bBlue = *(pInImage + lAdrs + 2);

			gray = bRed * 0.587 + bGreen * 0.299 + bBlue * 0.114;
			*(pOutImage + lAdrs) = static_cast<BYTE>(gray);
			*(pOutImage + lAdrs + 1) = static_cast<BYTE>(gray);
			*(pOutImage + lAdrs + 2) = static_cast<BYTE>(gray);
		}
	}
	return dest;
}

CImage* RotateFast(CImage *i)
{
	CImage *dest = Copy(i);



	int width = dest->GetWidth();
	int height = dest->GetHeight();

	int pitch = i->GetPitch();
	BYTE* pInImage = (BYTE*)i->GetBits();
	BYTE* pOutImage = (BYTE*)dest->GetBits();

	long lAdrs;
	double gray;
	BYTE bRed, bGreen, bBlue;


	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			lAdrs = y * pitch + x * 3;
			bRed = *(pInImage + lAdrs);
			bGreen = *(pInImage + lAdrs + 1);
			bBlue = *(pInImage + lAdrs + 2);

			//swap(image[i][j], image[image.size() - j - 1][image.size() - i - 1]);

			*(pOutImage + lAdrs) = static_cast<BYTE>(bRed);
			*(pOutImage + lAdrs + 1) = static_cast<BYTE>(bGreen);
			*(pOutImage + lAdrs + 2) = static_cast<BYTE>(bBlue);

		}
	}

	return dest;

	/*HBITMAP  hsrc = i->Detach();
	Bitmap* gdiPlusBitmap = Bitmap::FromHBITMAP(hsrc, NULL);
	gdiPlusBitmap->RotateFlip(Rotate90FlipXY);
	HBITMAP hdst;
	gdiPlusBitmap->GetHBITMAP(Color::White, &hdst);
	dest->Attach(hdst);
	return dest;*/
}



int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize Microsoft Foundation Classes, and print an error if failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		// Application starts here...

		cout << "Select Task:";
		cout << endl;



		char taskSelection;
		cin >> taskSelection;
		CImage*(*mainTask)(CImage*);
		switch (taskSelection)
		{
		case '1':
			mainTask = BrightenFast;
			break;
		case '2':
			mainTask = GreyscaleFast;
			break;
		case '3':
			mainTask = RotateFast;
			break;
		}
		






		// Time the application's execution time.
		TIMER start;	// DO NOT CHANGE THIS LINE

		//--------------------------------------------------------------------------------------
		// Process the images...  
		
		// Put your changes from here...

		CImage b1, *dest1;
		b1.Load(L"IMG_1.JPG");
		dest1 = mainTask(&b1);
		dest1 -> Save(L"IMG_1.PNG");
		delete dest1;

		CImage b2, *dest2;
		b2.Load(L"IMG_2.JPG");
		dest2 = mainTask(&b2);
		dest2 -> Save(L"IMG_2.PNG");
		delete dest2;

		CImage b3, *dest3;
		b3.Load(L"IMG_3.JPG");
		dest3 = mainTask(&b3);
		dest3 -> Save(L"IMG_3.PNG");
		delete dest3;

		CImage b4, *dest4;
		b4.Load(L"IMG_4.JPG");
		dest4 = mainTask(&b4);
		dest4 -> Save(L"IMG_4.PNG");
		delete dest4;

		CImage b5, *dest5;
		b5.Load(L"IMG_5.JPG");
		dest5 = mainTask(&b5);
		dest5 -> Save(L"IMG_5.PNG");
		delete dest5;

		CImage b6, *dest6;
		b6.Load(L"IMG_6.JPG");
		dest6 = mainTask(&b6);
		dest6 -> Save(L"IMG_6.PNG");
		delete dest6;

		CImage b7, *dest7;
		b7.Load(L"IMG_7.JPG");
		dest7 = mainTask(&b7);
		dest7 -> Save(L"IMG_7.PNG");
		delete dest7;

		CImage b8, *dest8;
		b8.Load(L"IMG_8.JPG");
		dest8 = mainTask(&b8);
		dest8 -> Save(L"IMG_8.PNG");
		delete dest8;

		CImage b9, *dest9;
		b9.Load(L"IMG_9.JPG");
		dest9 = mainTask(&b9);
		dest9 -> Save(L"IMG_9.PNG");
		delete dest9;

		CImage b10, *dest10;
		b10.Load(L"IMG_10.JPG");
		dest10 = mainTask(&b10);
		dest10 -> Save(L"IMG_10.PNG");
		delete dest10;

		CImage b11, *dest11;
		b11.Load(L"IMG_11.JPG");
		dest11 = mainTask(&b11);
		dest11 -> Save(L"IMG_11.PNG");
		delete dest11;

		CImage b12, *dest12;
		b12.Load(L"IMG_12.JPG");
		dest12 = mainTask(&b12);
		dest12 -> Save(L"IMG_12.PNG");
		delete dest12;

		CImage b13, *dest13;
		b13.Load(L"IMG_13.JPG");
		dest13 = mainTask(&b13);
		dest13->Save(L"IMG_13.PNG");
		delete dest13;

		CImage b14, *dest14;
		b14.Load(L"IMG_14.JPG");
		dest14 = mainTask(&b14);
		dest14->Save(L"IMG_14.PNG");
		delete dest14;

		CImage b15, *dest15;
		b15.Load(L"IMG_15.JPG");
		dest15 = mainTask(&b15);
		dest15->Save(L"IMG_15.PNG");
		delete dest15;
		
		CImage b16, *dest16;
		b16.Load(L"IMG_16.JPG");
		dest16 = mainTask(&b16);
		dest16->Save(L"IMG_16.PNG");
		delete dest16;

		CImage b17, *dest17;
		b17.Load(L"IMG_17.JPG");
		dest17 = mainTask(&b17);
		dest17->Save(L"IMG_17.PNG");
		delete dest17;

		CImage b18, *dest18;
		b18.Load(L"IMG_18.JPG");
		dest18 = mainTask(&b18);
		dest18->Save(L"IMG_18.PNG");
		delete dest18;

		CImage b19, *dest19;
		b19.Load(L"IMG_19.JPG");
		dest19 = mainTask(&b19);
		dest19->Save(L"IMG_19.PNG");
		delete dest19;

		CImage b20, *dest20;
		b20.Load(L"IMG_20.JPG");
		dest20 = mainTask(&b20);
		dest20->Save(L"IMG_20.PNG");
		delete dest20;

		CImage b21, *dest21;
		b21.Load(L"IMG_21.JPG");
		dest21 = mainTask(&b21);
		dest21->Save(L"IMG_21.PNG");
		delete dest21;

		CImage b22, *dest22;
		b22.Load(L"IMG_22.JPG");
		dest22 = mainTask(&b22);
		dest22->Save(L"IMG_22.PNG");
		delete dest22;

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

	return nRetCode;
}
