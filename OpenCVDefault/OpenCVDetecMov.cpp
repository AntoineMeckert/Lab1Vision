// OpenCVDefault.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "device_launch_parameters.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>


using namespace std;
using namespace cv;

Mat edges;
Mat cam;
Vec3b NewColor;
Vec3b LastColor;
bool RCLick;
bool LClick;
int LY;
int RY;
int LX;
int RX;
int MousePositionX;
int MousePositionY;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if  ( event == EVENT_LBUTTONDOWN )
	{
		
		LClick = true;
		LX = x;
		LY = y;
	}
	else if  ( event == EVENT_RBUTTONDOWN )
	{
		
		RX = x;
		RY = y;
		RCLick = true;
	}
	else if  ( event == EVENT_MBUTTONDOWN )
	{
		
	}
	MousePositionX = x;
	MousePositionY = y;
}



int main(int argc, char** argv)
{

	VideoCapture cap(0);
	int LastKey = 0;
	string s;
	RCLick = false;
	LClick = false;

	bool ModeImage = true;
	std::cout<<"Entrer le fabuleux chemin d'acces : ";
	std::cin>>s;
	namedWindow("cam", WINDOW_AUTOSIZE );
	namedWindow("edges",WINDOW_AUTOSIZE);
	setMouseCallback("edges", CallBackFunc, NULL);
	setMouseCallback("cam", CallBackFunc, NULL);
	
	
	while(waitKey(1))
	{
		cap >> cam;
		edges = imread(s, CV_LOAD_IMAGE_COLOR);


		switch(waitKey(1))
		{
		case 114: LastKey = 114;
				 line(edges, Point(0,0), Point(edges.cols,edges.rows), Scalar( 0, 0, 255 ), 1, 8, 0);
				 break;
		case 13: imwrite("camera.png",cam);
			break;
		case 32: LastKey = 32;
				 edges = NULL;
				 break;
		case 9: if (ModeImage)
				{
					ModeImage = false;
					LastKey = 0;
				}
				else
				{
					ModeImage = true;
					LastKey = 0;
				}
				break;
		}
		

		switch(LastKey)
		{
		case 114:line(edges, Point(0,0), Point(edges.cols,edges.rows), Scalar( 0, 0, 255 ), 1, 8, 0);
			break;
		case 32: edges = NULL;
			break;
		}

		//Right Click
		if(RCLick == true)
		{
			LastColor = edges.at<cv::Vec3b>(RY,RX);
			
			
			line(edges, Point(LX-10,LY), Point(LX+10 ,LY),Scalar(NewColor[0],NewColor[1],NewColor[2]), 1, 8, 0);
			line(edges, Point(LX,LY-10), Point(LX ,LY+10),Scalar(NewColor[0],NewColor[1],NewColor[2]), 1, 8, 0);
			
		}

		//Left Click
		if (LClick == true)
		{
			LClick = false;
			
			NewColor = LastColor;
			line(edges, Point(LX-10,LY), Point(LX+10 ,LY),Scalar(NewColor[0],NewColor[1],NewColor[2]), 1, 8, 0);
			line(edges, Point(LX,LY-10), Point(LX ,LY+10),Scalar(NewColor[0],NewColor[1],NewColor[2]), 1, 8, 0);
			imwrite(s,edges);
			
		}


		ostringstream posXs;
		ostringstream posYs;
		posXs << MousePositionX;
		posYs << MousePositionY;

		string PosX = posXs.str();
		string PosY = posYs.str();
		if(!ModeImage)
		{
			destroyWindow("edges");
			putText(cam, "X: " +PosX + " - " + "Y: " + PosY, Point(cam.cols - 150, cam.rows - 10), FONT_HERSHEY_COMPLEX_SMALL, 0.8, Scalar(cam.at<cv::Vec3b>(MousePositionY,MousePositionX)[0],cam.at<cv::Vec3b>(MousePositionY,MousePositionX)[1],cam.at<cv::Vec3b>(MousePositionY,MousePositionX)[2]), 1, 8, false );
			imshow("cam",cam);
		}
		else
		{
			destroyWindow("cam");
			imshow("edges", edges);
		}
		
		setMouseCallback("edges", CallBackFunc, NULL);
		setMouseCallback("cam", CallBackFunc, NULL);


		

		

		//
	}

	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}







