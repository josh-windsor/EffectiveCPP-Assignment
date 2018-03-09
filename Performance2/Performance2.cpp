// Performance2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Performance2.h"
#include "OpenCVImplementation.h"
#include "Timer.h"

#include <iostream>
#include <GdiPlusHeaders.h>
#include <GdiPlusColor.h>
using namespace Gdiplus; 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



CWinApp theApp;  // The one and only application object

using namespace std;


CImage* Copy(CImage *source)
{
	CImage *dest = new CImage;
	dest->Create(source->GetWidth(), source->GetHeight(), source->GetBPP());
	source->Draw(dest->GetDC(), 0, 0, dest->GetWidth(), dest->GetHeight(), 0, 0, source->GetWidth(), source->GetHeight());
	dest->ReleaseDC();
	return dest;
}
CImage* CopyScale(CImage *source)
{
	CImage *dest = new CImage;
	dest->Create(source->GetWidth() * 2, source->GetHeight() * 2 , source->GetBPP());
	source->Draw(dest->GetDC(), 0, 0, dest->GetWidth() / 2, dest->GetHeight() / 2, 0, 0, source->GetWidth(), source->GetHeight());
	dest->ReleaseDC();
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

	Bitmap* gdiPlusBitmap = Bitmap::FromHBITMAP(dest->Detach(), NULL);
	gdiPlusBitmap->RotateFlip(Rotate90FlipNone);
	HBITMAP hbmp;
	gdiPlusBitmap->GetHBITMAP(Color::White, &hbmp);
	dest->Attach(hbmp);
	return dest;
}

float lerp(float s, float e, float t) { return s + (e - s)*t; }
float blerp(float c00, float c10, float c01, float c11, float tx, float ty) {
	return lerp(lerp(c00, c10, tx), lerp(c01, c11, tx), ty);
}
#define getByte(value, n) (value >> (n*8) & 0xFF)

CImage* Scale(CImage *i)
{

	CImage *dest = CopyScale(i);


	int oldWidth = (int)i->GetWidth();
	int oldHeight = (int)i->GetHeight();

	int newWidth = (int)dest->GetWidth();
	int newHeight = (int)dest->GetHeight();

	float xDiv = (float)(newWidth) * (oldWidth - 1);
	float yDiv = (float)(newHeight) * (oldHeight - 1);


	int x, y;
	for (x = 0, y = 0; y < newHeight - 1; x++) {
		if (x >= newWidth) {
			x = 0; y++;
			//printf("%i\n", y);
		}
		float gx = x / xDiv;
		float gy = y / yDiv;
		int gxi = (int)gx;
		int gyi = (int)gy;
		uint32_t result = 0;
		uint32_t c00 = i->GetPixel(gxi, gyi);
		uint32_t c10 = i->GetPixel(gxi + 1, gyi);
		uint32_t c01 = i->GetPixel(gxi, gyi + 1);
		uint32_t c11 = i->GetPixel(gxi + 1, gyi + 1);
		uint8_t i;
		for (i = 0; i < 3; i++) {
			//((uint8_t*)&result)[i] = blerp( ((uint8_t*)&c00)[i], ((uint8_t*)&c10)[i], ((uint8_t*)&c01)[i], ((uint8_t*)&c11)[i], gxi - gx, gyi - gy); // this is shady
			result |= (uint8_t)blerp(getByte(c00, i), getByte(c10, i), getByte(c01, i), getByte(c11, i), gx - gxi, gy - gyi) << (8 * i);
		}
		dest->SetPixel(x, y, result);
	}
	return dest;
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
		case '4':
			mainTask = Scale;
			break;
		case '5':
			RunOpenCVFuncts(taskSelection);
			return nRetCode;
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
