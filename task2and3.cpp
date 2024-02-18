#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include<iostream>
//#include "leslist.h"

using namespace cv;
using namespace std;

int average(int size, int arr[])
{
	int sum = 0, avg = 0;

	
		for (int i = 0; i < size; i++)
			sum += arr[i];

		avg = sum / size;
		return avg;

}

int main()
{
	//------------------------read image and show in window
	//Mat image;		//reading image
	Mat image;
	image = imread("D:\\Fall 2022\\DS\\a1\\Original Images\\IMD002.bmp", 0);
	namedWindow("First OpenCV Application", WINDOW_AUTOSIZE);
	imshow("First OpenCV Application", image);
	moveWindow("First OpenCV Application", 0, 45);
	waitKey(0);
	destroyAllWindows();

//	srand(time(0));
	int k1 = 0, k2 = 0;
	int rows = image.rows;
	int cols = image.cols;
	
	int mean[4] = { 0 };
	int index_mean = 0;

	int** arr = new int* [rows];
	for (int i = 0; i < rows; i++)
		arr[i] = new int[cols];

	int diff1 = 0, diff2 = 0;
	int low_index = 0;
	int upper_index = 0;
	int c1[50000];

	int c2[50000];

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			arr[i][j] = image.at<uchar>(i, j);


	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
		{


			k1 = rand() % 50;
			k2 = rand() % 133;

			diff1 = (k1 - arr[i][j]);
			diff2 = (k2 - arr[i][j]);

			if (diff1 < 0)
				diff1 *= -1;
			if (diff2 < 0)
				diff2 *= -1;

			if (diff1 > diff2)
			{
				c1[low_index] = arr[i][j];
				low_index++;
			}
			if (diff1 < diff2)
			{
				c2[upper_index] = arr[i][j];
				upper_index++;
			}
			if (diff1 == diff2)
				break;


		}


		mean[index_mean] = average(low_index, c1);
		index_mean++;
		mean[index_mean] = average(upper_index, c2);


		if (index_mean == 1)
		{
			k1 = rand() % 50;
			k2 = rand() % 133;

		}
		if (index_mean == 3)
		{
			k1 = rand() % 50;
			k2 = rand() % 133;
			index_mean=0;

		}

		
		if ((mean[0] == mean[2]) && (mean[1] == mean[3]))
			break;
		else
			continue;

	}

	if (mean[0] == mean[2])
		cout << mean[0] << mean[2] << endl;

	if (mean[1] == mean[3])
		cout << mean[1] << mean[3];

	//cout << "mean1 and 3 : " << mean1 << "== " << mean3<<endl;
	//cout << "mean2 and 4 : " << mean2 << "== " << mean4 << endl;
	//system("pause");

	int** arr2 = new int* [rows];
	for (int i = 0; i < rows; i++)
		arr2[i] = new int[cols];
		
		for (int i = 0; i < rows; i++) 
			for (int j = 0; j < cols; j++)
				arr2[i][j] =255;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
		{
			for (int k = 0; k < low_index; k++) {
				if (arr[i][j] == c1[k])
				{
					arr2[i][j] = 255;
				}
				//else if(arr[i][j]==c2[k])
					//arr2[i][j] = 255;
			}

		}
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
		{
			for (int k = 0; k < upper_index; k++)
			{
				if (arr[i][j] == c2[k])
				{
					arr2[i][j] = 0;
				}
				//if (arr[i][j] == c1[k])
			//	{
				//	arr2[i][j] = 255;
				//}


			}
		}
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			image.at<uchar>(i, j) = arr2[i][j];
		}
	}

	imwrite("task2.bmp", image);
	image = imread("C:\\Users\\Usman's PC\\source\\repos\\AS1\\AS1\\task2.bmp");
	//image = imread("D:\\Fall 2022\\DS\\a1\\Segmented Outputs\\mIMD019.bmp", 0);
	namedWindow("First OpenCV Application", WINDOW_AUTOSIZE);
	imshow("First OpenCV Application", image);
	moveWindow("First OpenCV Application", 0, 45);
	waitKey(0);
	destroyAllWindows();

	Mat imge;
	imge = imread("D:\\Fall 2022\\DS\\a1\\Ground Truths\\IMD002_lesion.bmp", 0);
	namedWindow("First OpenCV Application", WINDOW_AUTOSIZE);
	imshow("First OpenCV Application", imge);
	moveWindow("First OpenCV Application", 0, 45);
	waitKey(0);
	destroyAllWindows();

	int TP[30000] = { 0 };
	int FP[30000] = { 0 };
	int FN[30000] = { 0 };

	int cols2 = imge.cols;//*image.channels();
	int rows2 = imge.rows;
	int** arr3 = new int*[imge.rows];

	for (int i = 0; i < imge.rows; i++)
	arr3[i] = new int[cols2];

	
	for (int i = 0; i < imge.rows; i++)
		for (int j = 0; j < cols2; j++)
			 arr3[i][j]= imge.at<uchar>(i, j);

	for (int i = 0; i < imge.rows; i++)
		for (int j = 0; j < cols2; j++)
			for(int k =0;k<30000;k++)
				if (arr3[i][j] == 255 && arr2[i][j] == 0)
					TP[k] = arr3[i][j];

	for (int i = 0; i < imge.rows; i++)
		for (int j = 0; j < cols2; j++)
			for (int k = 0; k < 30000; k++)
				if ((arr3[i][j] == 255 || arr2[i][j] == 0))
					FP[k] = arr3[i][j];


	float *Dice=new float[cols] { 0 };
	for (int i = 0; i < imge.cols; i++,FN[i]+=1)
		 Dice[i] = 2 * TP[i] / (FN[i] + (2 * TP[i]) + FP[i]);

	for (int i = 0; i < imge.cols; i++)
		cout << Dice[i] << "";
}