// Opencvtest.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include<fstream>
#include<string.h>
#include <time.h>

using namespace cv;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	Mat image = imread("lena.bmp");
	Mat grayimage;
	Mat qunimage;
	cvtColor(image,grayimage, CV_BGR2GRAY);
	cvtColor(image,qunimage, CV_BGR2GRAY);
	float his[256];
	float p[256];
	float s[256];
	int pixel = 0;


	//initial
	for(int i=0; i<256; i++){
		his[i] = 0 ;
		p[i] = 0 ;
		s[i] =0 ;
	}

	for(int i=0; i<grayimage.rows; i++){
		for(int j=0; j<grayimage.cols; j++){
			pixel = grayimage.at<uchar>(i,j);
			grayimage.at<uchar>(i,j) = pixel/3;
			his[pixel/3]++;
		}
	}

	//origin histogram
	//find largest
	int largest=0;
	for(int i=0; i<256; i++){
		if(largest<his[i]){
			largest = his[i] ;
		}
	}
	//set largest
	for(int i=0; i<256; i++){
		his[i] = his[i]*255/largest;
	}

	//draw histogram
	Mat histImg (256,256,CV_8UC3,Scalar(0,0,0));
	for(int i=0; i<256; i++){
		line(histImg,Point(i,256-his[i]),Point(i,256),Scalar(255,255,255));
	}
	imshow("histogram",histImg);

	//equalization
	float totalpixel = 0;
	for(int i=0; i<256; i++){
		totalpixel = totalpixel + his[i];
	}

	for(int i=0; i<256; i++){
		p[i] = his[i]/totalpixel;
	}

	for(int i=0; i<256; i++){
		for(int j=0; j<i; j++){
			s[i] = s[i] + 255*p[j];
		}
	}

	for(int i=0; i<qunimage.rows; i++){
		for(int j=0; j<qunimage.cols; j++){
			pixel = grayimage.at<uchar>(i,j);
			qunimage.at<uchar>(i,j) = s[pixel];
		}
	}

	imshow("Equalization",qunimage);
	imwrite("equalization.bmp",qunimage);

	for(int i=0; i<256; i++){
		his[i] = 0 ;
	}


	for(int i=0; i<qunimage.rows; i++){
		for(int j=0; j<qunimage.cols; j++){
			pixel = qunimage.at<uchar>(i,j);
			his[pixel]++;
		}
	}
	
	//equalization histogram
	//find largest
	largest=0;
	for(int i=0; i<256; i++){
		if(largest<his[i]){
			largest = his[i] ;
		}
	}
	//set largest
	for(int i=0; i<256; i++){
		his[i] = his[i]*255/largest;
	}

	//draw histogram
	Mat histImg2 (256,256,CV_8UC3,Scalar(0,0,0));
	for(int i=0; i<256; i++){
		line(histImg2,Point(i,256-his[i]),Point(i,256),Scalar(255,255,255));
	}
	imshow("equalization histogram",histImg2);
	imwrite("equhistogram.bmp",histImg2);

	waitKey(0);
	return 0;
}