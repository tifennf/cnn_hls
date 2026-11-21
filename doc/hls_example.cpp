
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/ml/ml.hpp>
#include <opencv2/core/core_c.h>
#include <opencv2/core/types_c.h>
#include <fstream>
#include <iostream>
#include <stdio.h>

#include <string>




#define NB 4000
#define IMG_HEIGHT 384
#define IMG_WIDTH 288

using namespace cv;
using namespace std;

/** @function main */

void seuillage(int src[IMG_HEIGHT*IMG_WIDTH], int rows, int cols)
{
#pragma HLS INTERFACE m_axi port=src bundle=src_b depth=IMG_HEIGHT*IMG_WIDTH
// #pragma HLS ARRAY_PARTITION variable=src type=block dim=2
// #pragma HLS UNROLL factor=4
// #pragma HLS PIPELINE II=1



	for(int i=0; i < rows; i++)
			for(int j=0; j < cols; j++)
				{
				if(src[i*cols+j] < 127)
					src[i*cols+j]=0;
				else
					src[i*cols+j]=255;
				}
}


int main(int argc, char** argv)
{

  	///////////////////////////////////////////////////////////////////////
	///////////////////////// Creating Variables //////////////////////////


  	// Image Variables ////
	Size size_screen(1280,1024); // screen size for afichage on vga

 	Mat src;
 	Mat srcgray;
 	Mat srdcMedian;

	int resolution[2] = {IMG_HEIGHT, IMG_WIDTH};
	int seuil;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////// Start Processing /////////////////////////////////////////////////////////////

	// Chargin Images of video
	cout<<"Traitement "<<endl;

	cv::namedWindow("Panneau de Contrôle",WINDOW_NORMAL);
	cv::createTrackbar("Seuil de Détection","Panneau de Contrôle",&seuil,80,NULL);
	waitKey();

	src=cv::imread("/users/cao/granado/Zybo/TraitIm/test.png",1);
	imshow("Image",src);
	waitKey();
	cv::cvtColor(src, srcgray, CV_RGB2GRAY);
	imshow("Image",srcgray);
	waitKey();
	cout << " Taille des Données " << srcgray.elemSize() << endl;
	cout << "Hauteur " << srcgray.rows << " Largeur " << srcgray.cols << endl;

	int N=srcgray.rows;
	int M=srcgray.cols;

	int tab[N*M];

	for(int i=0; i < N; i++)
				for(int j=0; j < M; j++)
					{
					tab[i*M+j] = srcgray.at<uchar>(i,j);
					}


	seuillage(tab,N,M);

	Mat dst(N,M,CV_8U);
	for(int i=0; i < N; i++)
			for(int j=0; j < M; j++)
				{
				dst.at<uchar>(i,j) = tab[i*M+j];
				//cout << "valeur srcgray("i")("j") = " srcgray.at<uchar>(i,j)"- valeur dst("i")("j") = "dst.at<uchar>(i,j) << endl;
				}

	imshow("Image",dst);

	waitKey();
	cout << dst << endl;
   	return 0;
}
