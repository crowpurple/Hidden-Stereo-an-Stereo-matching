// cg1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <stdio.h>
#include <math.h>

using namespace cv;

int temp[375][450][3];


int main()
{
	const char* filename = "E:\\Downloads\\disp2.jpg";
	const char* filename1 = "E:\\Downloads\\im2.jpg";
	const char* filename2 = "E:\\Downloads\\im3.jpg";
	char input;
	scanf_s("%c", &input);
	if ('1' == input) {
		// Loads an image
		Mat src = imread(filename);
		Mat dispa1, dispa2, dispa3;
		Mat src1 = imread(filename1);
		Mat source1, source2, source3;
		int i, j;
		double tempmax;
		//printf("%d,%d,%d,%d", src.type(), src1.type(), CV_8U, CV_8UC3);
		// Check if image is loaded fine
		if (src.empty() && src1.empty()) {
			printf(" Error opening image\n");
			return -1;
		}
		//imshow("disparity map", src);
		pyrDown(src, dispa1, Size(src.cols / 2, src.rows / 2));
		//imshow("first Gaussian pyramid for disparity map", dispa1);
		pyrDown(dispa1, dispa2, Size(dispa1.cols / 2, dispa1.rows / 2));
		//imshow("second Gaussian pyramid for disparity map", dispa2);
		pyrDown(dispa2, dispa3, Size(dispa2.cols / 2, dispa2.rows / 2));
		//imshow("third Gaussian pyramid for disparity map", dispa3);

		//imshow("original pic", src1);
		pyrDown(src1, source1, Size(src1.cols / 2, src1.rows / 2));
		//imshow("first Gaussian pyramid for original pic", source1);
		pyrDown(source1, source2, Size(source1.cols / 2, source1.rows / 2));
		//imshow("second Gaussian pyramid for original pic", source2);
		pyrDown(source2, source3, Size(source2.cols / 2, source2.rows / 2));
		//imshow("third Gaussian pyramid for original pic", source3);


		//printf("%d,%d,%d", dispa1.at<cv::Vec3b>(122, 23)[0], dispa1.at<cv::Vec3b>(122, 23)[1], dispa1.at<cv::Vec3b>(122, 23)[2]);
		tempmax = 0;
		for (i = 0; i < dispa1.rows; i++) {
			for (j = 0; j < dispa1.cols; j++) {
				temp[i][j][0] = source1.at<cv::Vec3b>(i, j)[0] * tan(dispa1.at<cv::Vec3b>(i, j)[0]/2);
				if (temp[i][j][0] > tempmax)
					tempmax = temp[i][j][0];
				temp[i][j][1] = source1.at<cv::Vec3b>(i, j)[1] * tan(dispa1.at<cv::Vec3b>(i, j)[1]/2);
				if (temp[i][j][1] > tempmax)
					tempmax = temp[i][j][1];
				temp[i][j][2] = source1.at<cv::Vec3b>(i, j)[2] * tan(dispa1.at<cv::Vec3b>(i, j)[2]/2);
				if (temp[i][j][2] > tempmax)
					tempmax = temp[i][j][2];
			}
		}
		for (i = 0; i < dispa1.rows; i++) {
			for (j = 0; j < dispa1.cols; j++) {
				source1.at<cv::Vec3b>(i, j)[0] = (uchar)(255 * temp[i][j][0] / tempmax);
				source1.at<cv::Vec3b>(i, j)[1] = (uchar)(255 * temp[i][j][1] / tempmax);
				source1.at<cv::Vec3b>(i, j)[2] = (uchar)(255 * temp[i][j][2] / tempmax);
			}
		}

		tempmax = 0;
		for (i = 0; i < dispa2.rows; i++) {
			for (j = 0; j < dispa2.cols; j++) {
				temp[i][j][0] = source2.at<cv::Vec3b>(i, j)[0] * tan(dispa2.at<cv::Vec3b>(i, j)[0] / 2);
				if (temp[i][j][0] > tempmax)
					tempmax = temp[i][j][0];
				temp[i][j][1] = source2.at<cv::Vec3b>(i, j)[1] * tan(dispa2.at<cv::Vec3b>(i, j)[1] / 2);
				if (temp[i][j][1] > tempmax)
					tempmax = temp[i][j][1];
				temp[i][j][2] = source2.at<cv::Vec3b>(i, j)[2] * tan(dispa2.at<cv::Vec3b>(i, j)[2] / 2);
				if (temp[i][j][2] > tempmax)
					tempmax = temp[i][j][2];
			}
		}
		for (i = 0; i < dispa2.rows; i++) {
			for (j = 0; j < dispa2.cols; j++) {
				source2.at<cv::Vec3b>(i, j)[0] = (uchar)(255 * temp[i][j][0] / tempmax);
				source2.at<cv::Vec3b>(i, j)[1] = (uchar)(255 * temp[i][j][1] / tempmax);
				source2.at<cv::Vec3b>(i, j)[2] = (uchar)(255 * temp[i][j][2] / tempmax);
			}
		}

		tempmax = 0;
		for (i = 0; i < dispa3.rows; i++) {
			for (j = 0; j < dispa3.cols; j++) {
				temp[i][j][0] = source3.at<cv::Vec3b>(i, j)[0] * tan(dispa3.at<cv::Vec3b>(i, j)[0] / 2);
				if (temp[i][j][0] > tempmax)
					tempmax = temp[i][j][0];
				temp[i][j][1] = source3.at<cv::Vec3b>(i, j)[1] * tan(dispa3.at<cv::Vec3b>(i, j)[1] / 2);
				if (temp[i][j][1] > tempmax)
					tempmax = temp[i][j][1];
				temp[i][j][2] = source3.at<cv::Vec3b>(i, j)[2] * tan(dispa3.at<cv::Vec3b>(i, j)[2] / 2);
				if (temp[i][j][2] > tempmax)
					tempmax = temp[i][j][2];
			}
		}
		for (i = 0; i < dispa3.rows; i++) {
			for (j = 0; j < dispa3.cols; j++) {
				source3.at<cv::Vec3b>(i, j)[0] = (uchar)(255 * temp[i][j][0] / tempmax);
				source3.at<cv::Vec3b>(i, j)[1] = (uchar)(255 * temp[i][j][1] / tempmax);
				source3.at<cv::Vec3b>(i, j)[2] = (uchar)(255 * temp[i][j][2] / tempmax);
			}
		}

		pyrUp(source1, source1, Size(source1.cols * 2, source1.rows * 2));
		//pyrUp(source2, source2, Size(source2.cols * 4, source2.rows * 4));
		//pyrUp(source3, source3, Size(source3.cols * 8, source3.rows * 8));
		
		for (i = 0; i < source1.rows; i++) {
			for (j = 0; j < source1.cols; j++) {
				if (source1.at<cv::Vec3b>(i, j)[0] > 100)
					source1.at<cv::Vec3b>(i, j)[0] = source1.at<cv::Vec3b>(i, j)[0] / 10;
				src1.at<cv::Vec3b>(i, j)[0] = src1.at<cv::Vec3b>(i, j)[0] + source1.at<cv::Vec3b>(i, j)[0];
				src.at<cv::Vec3b>(i, j)[0] = src1.at<cv::Vec3b>(i, j)[0] - source1.at<cv::Vec3b>(i, j)[0];
				if (source1.at<cv::Vec3b>(i, j)[1] > 100)
					source1.at<cv::Vec3b>(i, j)[1] = source1.at<cv::Vec3b>(i, j)[1] / 10;
				src1.at<cv::Vec3b>(i, j)[1] = src1.at<cv::Vec3b>(i, j)[1] + source1.at<cv::Vec3b>(i, j)[1];
				src.at<cv::Vec3b>(i, j)[1] = src1.at<cv::Vec3b>(i, j)[1] - source1.at<cv::Vec3b>(i, j)[1];
				if (source1.at<cv::Vec3b>(i, j)[2] > 100)
					source1.at<cv::Vec3b>(i, j)[2] = source1.at<cv::Vec3b>(i, j)[2] / 10;
				src1.at<cv::Vec3b>(i, j)[2] = src1.at<cv::Vec3b>(i, j)[2] + source1.at<cv::Vec3b>(i, j)[2];
				src.at<cv::Vec3b>(i, j)[2] = src1.at<cv::Vec3b>(i, j)[2] - source1.at<cv::Vec3b>(i, j)[2];
			}
		}
		imshow("1", src1);
		imshow("2", src);
		waitKey(0);
		for (i = 0; i < src1.rows;  i++) {
			for (j = 0; j < src1.cols; j++) {
				src.at<cv::Vec3b>(i, j)[0] = (src.at<cv::Vec3b>(i, j)[0] + src1.at<cv::Vec3b>(i, j)[0]) / 2;
				src.at<cv::Vec3b>(i, j)[1] = (src.at<cv::Vec3b>(i, j)[1] + src1.at<cv::Vec3b>(i, j)[1]) / 2;
				src.at<cv::Vec3b>(i, j)[2] = (src.at<cv::Vec3b>(i, j)[2] + src1.at<cv::Vec3b>(i, j)[2]) / 2;
			}
		}
		imshow("3", src);
		waitKey(0);
	}
	else if('2'==input) {
		Mat left = imread(filename1);
		Mat right = imread(filename2);
		Mat disparity(375, 450, CV_8U, cv::Scalar::all(0));
		int i, j, k,index;
		int num,nummax;
		uchar l[450][375];
		uchar r[450][375];
		for (i = 0; i < 375; i++) {
			for (j = 0; j < 450; j++) {
				l[i][j] = (left.at<cv::Vec3b>(i, j)[0] + left.at<cv::Vec3b>(i, j)[1] + left.at<cv::Vec3b>(i, j)[2]) / 3;
				r[i][j] = (right.at<cv::Vec3b>(i, j)[0] + right.at<cv::Vec3b>(i, j)[1] + right.at<cv::Vec3b>(i, j)[2]) / 3;
			}
		}
		for (i = 0; i < 375; i++) {
			for (j = 0; j < 450; j++) {
				nummax = 0;
				index = 0;
				for (k = 0; k < 450; k++) {
					num = 0;
					if (i < 3) {
						if (j < 3) {
							if ((l[i][j] - l[i][j + 1])*(r[i][k] - r[i][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i][j + 2])*(r[i][k] - r[i][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i][j + 3])*(r[i][k] - r[i][k + 3]) > 0)
								num++;
							if ((l[i][j] - l[i + 1][j + 1])*(r[i][k] - r[i + 1][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i + 1][j + 2])*(r[i][k] - r[i + 1][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i + 1][j + 3])*(r[i][k] - r[i + 1][k + 3]) > 0)
								num++;
							if ((l[i][j] - l[i + 2][j + 1])*(r[i][k] - r[i + 2][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i + 2][j + 2])*(r[i][k] - r[i + 2][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i + 2][j + 3])*(r[i][k] - r[i + 2][k + 3]) > 0)
								num++;
							if ((l[i][j] - l[i + 3][j + 1])*(r[i][k] - r[i + 3][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i + 3][j + 2])*(r[i][k] - r[i + 3][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i + 3][j + 3])*(r[i][k] - r[i + 3][k + 3]) > 0)
								num++;
						}
						else if (j > 446) {
							if ((l[i][j] - l[i][j - 1])*(r[i][k] - r[i][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i][j - 2])*(r[i][k] - r[i][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i][j - 3])*(r[i][k] - r[i][k - 3]) > 0)
								num++;
							if ((l[i][j] - l[i + 1][j - 1])*(r[i][k] - r[i + 1][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i + 1][j - 2])*(r[i][k] - r[i + 1][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i + 1][j - 3])*(r[i][k] - r[i + 1][k - 3]) > 0)
								num++;
							if ((l[i][j] - l[i + 2][j - 1])*(r[i][k] - r[i + 2][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i + 2][j - 2])*(r[i][k] - r[i + 2][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i + 2][j - 3])*(r[i][k] - r[i + 2][k - 3]) > 0)
								num++;
							if ((l[i][j] - l[i + 3][j - 1])*(r[i][k] - r[i + 3][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i + 3][j - 2])*(r[i][k] - r[i + 3][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i + 3][j - 3])*(r[i][k] - r[i + 3][k - 3]) > 0)
								num++;
						}
						else {
							if ((l[i][j] - l[i][j + 1])*(r[i][k] - r[i][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i][j + 2])*(r[i][k] - r[i][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i][j + 3])*(r[i][k] - r[i][k + 3]) > 0)
								num++;
							if ((l[i][j] - l[i + 1][j + 1])*(r[i][k] - r[i + 1][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i + 1][j + 2])*(r[i][k] - r[i + 1][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i + 1][j + 3])*(r[i][k] - r[i + 1][k + 3]) > 0)
								num++;
							if ((l[i][j] - l[i + 2][j + 1])*(r[i][k] - r[i + 2][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i + 2][j + 2])*(r[i][k] - r[i + 2][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i + 2][j + 3])*(r[i][k] - r[i + 2][k + 3]) > 0)
								num++;
							if ((l[i][j] - l[i + 3][j + 1])*(r[i][k] - r[i + 3][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i + 3][j + 2])*(r[i][k] - r[i + 3][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i + 3][j + 3])*(r[i][k] - r[i + 3][k + 3]) > 0)
								num++;
							if ((l[i][j] - l[i][j - 1])*(r[i][k] - r[i][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i][j - 2])*(r[i][k] - r[i][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i][j - 3])*(r[i][k] - r[i][k - 3]) > 0)
								num++;
							if ((l[i][j] - l[i + 1][j - 1])*(r[i][k] - r[i + 1][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i + 1][j - 2])*(r[i][k] - r[i + 1][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i + 1][j - 3])*(r[i][k] - r[i + 1][k - 3]) > 0)
								num++;
							if ((l[i][j] - l[i + 2][j - 1])*(r[i][k] - r[i + 2][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i + 2][j - 2])*(r[i][k] - r[i + 2][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i + 2][j - 3])*(r[i][k] - r[i + 2][k - 3]) > 0)
								num++;
							if ((l[i][j] - l[i + 3][j - 1])*(r[i][k] - r[i + 3][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i + 3][j - 2])*(r[i][k] - r[i + 3][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i + 3][j - 3])*(r[i][k] - r[i + 3][k - 3]) > 0)
								num++;
						}
					}
					else if (i > 371) {
						if (j < 3) {
							if ((l[i][j] - l[i][j + 1])*(r[i][k] - r[i][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i][j + 2])*(r[i][k] - r[i][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i][j + 3])*(r[i][k] - r[i][k + 3]) > 0)
								num++;
							if ((l[i][j] - l[i - 1][j + 1])*(r[i][k] - r[i - 1][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i - 1][j + 2])*(r[i][k] - r[i - 1][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i - 1][j + 3])*(r[i][k] - r[i - 1][k + 3]) > 0)
								num++;
							if ((l[i][j] - l[i - 2][j + 1])*(r[i][k] - r[i - 2][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i - 2][j + 2])*(r[i][k] - r[i - 2][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i - 2][j + 3])*(r[i][k] - r[i - 2][k + 3]) > 0)
								num++;
							if ((l[i][j] - l[i - 3][j + 1])*(r[i][k] - r[i - 3][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i - 3][j + 2])*(r[i][k] - r[i - 3][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i - 3][j + 3])*(r[i][k] - r[i - 3][k + 3]) > 0)
								num++;
						}
						else if (j > 446) {
							if ((l[i][j] - l[i][j - 1])*(r[i][k] - r[i][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i][j - 2])*(r[i][k] - r[i][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i][j - 3])*(r[i][k] - r[i][k - 3]) > 0)
								num++;
							if ((l[i][j] - l[i - 1][j - 1])*(r[i][k] - r[i - 1][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i - 1][j - 2])*(r[i][k] - r[i - 1][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i - 1][j - 3])*(r[i][k] - r[i - 1][k - 3]) > 0)
								num++;
							if ((l[i][j] - l[i - 2][j - 1])*(r[i][k] - r[i - 2][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i - 2][j - 2])*(r[i][k] - r[i - 2][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i - 2][j - 3])*(r[i][k] - r[i - 2][k - 3]) > 0)
								num++;
							if ((l[i][j] - l[i - 3][j - 1])*(r[i][k] - r[i - 3][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i - 3][j - 2])*(r[i][k] - r[i - 3][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i - 3][j - 3])*(r[i][k] - r[i - 3][k - 3]) > 0)
								num++;
						}
						else {
							if ((l[i][j] - l[i][j + 1])*(r[i][k] - r[i][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i][j + 2])*(r[i][k] - r[i][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i][j + 3])*(r[i][k] - r[i][k + 3]) > 0)
								num++;
							if ((l[i][j] - l[i - 1][j + 1])*(r[i][k] - r[i - 1][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i - 1][j + 2])*(r[i][k] - r[i - 1][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i - 1][j + 3])*(r[i][k] - r[i - 1][k + 3]) > 0)
								num++;
							if ((l[i][j] - l[i - 2][j + 1])*(r[i][k] - r[i - 2][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i - 2][j + 2])*(r[i][k] - r[i - 2][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i - 2][j + 3])*(r[i][k] - r[i - 2][k + 3]) > 0)
								num++;
							if ((l[i][j] - l[i - 3][j + 1])*(r[i][k] - r[i - 3][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i - 3][j + 2])*(r[i][k] - r[i - 3][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i - 3][j + 3])*(r[i][k] - r[i - 3][k + 3]) > 0)
								num++;
							if ((l[i][j] - l[i][j - 1])*(r[i][k] - r[i][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i][j - 2])*(r[i][k] - r[i][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i][j - 3])*(r[i][k] - r[i][k - 3]) > 0)
								num++;
							if ((l[i][j] - l[i - 1][j - 1])*(r[i][k] - r[i - 1][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i - 1][j - 2])*(r[i][k] - r[i - 1][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i - 1][j - 3])*(r[i][k] - r[i - 1][k - 3]) > 0)
								num++;
							if ((l[i][j] - l[i - 2][j - 1])*(r[i][k] - r[i - 2][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i - 2][j - 2])*(r[i][k] - r[i - 2][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i - 2][j - 3])*(r[i][k] - r[i - 2][k - 3]) > 0)
								num++;
							if ((l[i][j] - l[i - 3][j - 1])*(r[i][k] - r[i - 3][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i - 3][j - 2])*(r[i][k] - r[i - 3][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i - 3][j - 3])*(r[i][k] - r[i - 3][k - 3]) > 0)
								num++;
						}
					}
					else {
						if (j < 3) {
							if ((l[i][j] - l[i][j + 1])*(r[i][k] - r[i][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i][j + 2])*(r[i][k] - r[i][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i][j + 3])*(r[i][k] - r[i][k + 3]) > 0)
								num++;
							if ((l[i][j] - l[i + 1][j + 1])*(r[i][k] - r[i + 1][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i + 1][j + 2])*(r[i][k] - r[i + 1][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i + 1][j + 3])*(r[i][k] - r[i + 1][k + 3]) > 0)
								num++;
							if ((l[i][j] - l[i + 2][j + 1])*(r[i][k] - r[i + 2][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i + 2][j + 2])*(r[i][k] - r[i + 2][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i + 2][j + 3])*(r[i][k] - r[i + 2][k + 3]) > 0)
								num++;
							if ((l[i][j] - l[i + 3][j + 1])*(r[i][k] - r[i + 3][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i + 3][j + 2])*(r[i][k] - r[i + 3][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i + 3][j + 3])*(r[i][k] - r[i + 3][k + 3]) > 0)
								num++;
							if ((l[i][j] - l[i - 1][j + 1])*(r[i][k] - r[i - 1][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i - 1][j + 2])*(r[i][k] - r[i - 1][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i - 1][j + 3])*(r[i][k] - r[i - 1][k + 3]) > 0)
								num++;
							if ((l[i][j] - l[i - 2][j + 1])*(r[i][k] - r[i - 2][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i - 2][j + 2])*(r[i][k] - r[i - 2][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i - 2][j + 3])*(r[i][k] - r[i - 2][k + 3]) > 0)
								num++;
							if ((l[i][j] - l[i - 3][j + 1])*(r[i][k] - r[i - 3][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i - 3][j + 2])*(r[i][k] - r[i - 3][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i - 3][j + 3])*(r[i][k] - r[i - 3][k + 3]) > 0)
								num++;
						}
						else if (j > 446) {
							if ((l[i][j] - l[i][j - 1])*(r[i][k] - r[i][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i][j - 2])*(r[i][k] - r[i][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i][j - 3])*(r[i][k] - r[i][k - 3]) > 0)
								num++;
							if ((l[i][j] - l[i + 1][j - 1])*(r[i][k] - r[i + 1][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i + 1][j - 2])*(r[i][k] - r[i + 1][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i + 1][j - 3])*(r[i][k] - r[i + 1][k - 3]) > 0)
								num++;
							if ((l[i][j] - l[i + 2][j - 1])*(r[i][k] - r[i + 2][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i + 2][j - 2])*(r[i][k] - r[i + 2][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i + 2][j - 3])*(r[i][k] - r[i + 2][k - 3]) > 0)
								num++;
							if ((l[i][j] - l[i + 3][j - 1])*(r[i][k] - r[i + 3][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i + 3][j - 2])*(r[i][k] - r[i + 3][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i + 3][j - 3])*(r[i][k] - r[i + 3][k - 3]) > 0)
								num++;
							if ((l[i][j] - l[i - 1][j - 1])*(r[i][k] - r[i - 1][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i - 1][j - 2])*(r[i][k] - r[i - 1][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i - 1][j - 3])*(r[i][k] - r[i - 1][k - 3]) > 0)
								num++;
							if ((l[i][j] - l[i - 2][j - 1])*(r[i][k] - r[i - 2][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i - 2][j - 2])*(r[i][k] - r[i - 2][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i - 2][j - 3])*(r[i][k] - r[i - 2][k - 3]) > 0)
								num++;
							if ((l[i][j] - l[i - 3][j - 1])*(r[i][k] - r[i - 3][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i - 3][j - 2])*(r[i][k] - r[i - 3][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i - 3][j - 3])*(r[i][k] - r[i - 3][k - 3]) > 0)
								num++;
						}
						else {
							if ((l[i][j] - l[i][j + 1])*(r[i][k] - r[i][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i][j + 2])*(r[i][k] - r[i][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i][j + 3])*(r[i][k] - r[i][k + 3]) > 0)
								num++;
							if ((l[i][j] - l[i + 1][j + 1])*(r[i][k] - r[i + 1][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i + 1][j + 2])*(r[i][k] - r[i + 1][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i + 1][j + 3])*(r[i][k] - r[i + 1][k + 3]) > 0)
								num++;
							if ((l[i][j] - l[i + 2][j + 1])*(r[i][k] - r[i + 2][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i + 2][j + 2])*(r[i][k] - r[i + 2][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i + 2][j + 3])*(r[i][k] - r[i + 2][k + 3]) > 0)
								num++;
							if ((l[i][j] - l[i + 3][j + 1])*(r[i][k] - r[i + 3][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i + 3][j + 2])*(r[i][k] - r[i + 3][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i + 3][j + 3])*(r[i][k] - r[i + 3][k + 3]) > 0)
								num++;
							if ((l[i][j] - l[i - 1][j + 1])*(r[i][k] - r[i - 1][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i - 1][j + 2])*(r[i][k] - r[i - 1][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i - 1][j + 3])*(r[i][k] - r[i - 1][k + 3]) > 0)
								num++;
							if ((l[i][j] - l[i - 2][j + 1])*(r[i][k] - r[i - 2][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i - 2][j + 2])*(r[i][k] - r[i - 2][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i - 2][j + 3])*(r[i][k] - r[i - 2][k + 3]) > 0)
								num++;
							if ((l[i][j] - l[i - 3][j + 1])*(r[i][k] - r[i - 3][k + 1]) > 0)
								num++;
							if ((l[i][j] - l[i - 3][j + 2])*(r[i][k] - r[i - 3][k + 2]) > 0)
								num++;
							if ((l[i][j] - l[i - 3][j + 3])*(r[i][k] - r[i - 3][k + 3]) > 0)
								num++;
							if ((l[i][j] - l[i][j - 1])*(r[i][k] - r[i][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i][j - 2])*(r[i][k] - r[i][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i][j - 3])*(r[i][k] - r[i][k - 3]) > 0)
								num++;
							if ((l[i][j] - l[i + 1][j - 1])*(r[i][k] - r[i + 1][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i + 1][j - 2])*(r[i][k] - r[i + 1][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i + 1][j - 3])*(r[i][k] - r[i + 1][k - 3]) > 0)
								num++;
							if ((l[i][j] - l[i + 2][j - 1])*(r[i][k] - r[i + 2][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i + 2][j - 2])*(r[i][k] - r[i + 2][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i + 2][j - 3])*(r[i][k] - r[i + 2][k - 3]) > 0)
								num++;
							if ((l[i][j] - l[i + 3][j - 1])*(r[i][k] - r[i + 3][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i + 3][j - 2])*(r[i][k] - r[i + 3][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i + 3][j - 3])*(r[i][k] - r[i + 3][k - 3]) > 0)
								num++;
							if ((l[i][j] - l[i - 1][j - 1])*(r[i][k] - r[i - 1][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i - 1][j - 2])*(r[i][k] - r[i - 1][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i - 1][j - 3])*(r[i][k] - r[i - 1][k - 3]) > 0)
								num++;
							if ((l[i][j] - l[i - 2][j - 1])*(r[i][k] - r[i - 2][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i - 2][j - 2])*(r[i][k] - r[i - 2][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i - 2][j - 3])*(r[i][k] - r[i - 2][k - 3]) > 0)
								num++;
							if ((l[i][j] - l[i - 3][j - 1])*(r[i][k] - r[i - 3][k - 1]) > 0)
								num++;
							if ((l[i][j] - l[i - 3][j - 2])*(r[i][k] - r[i - 3][k - 2]) > 0)
								num++;
							if ((l[i][j] - l[i - 3][j - 3])*(r[i][k] - r[i - 3][k - 3]) > 0)
								num++;
						}
					}
					if (num > nummax) {
						nummax = num;
						index = k;
					}
				}
				if (fabs(j - index) > 255)
					disparity.at<uchar>(i, j) = 255;
				else
					disparity.at<uchar>(i, j) = fabs(j - index);
			}
		}
		imshow("left", left);
		imshow("right", right);
		imshow("disparity", disparity);
		waitKey(0);
	}
	return 0;
}