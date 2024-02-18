#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include"Header.h"
#include <iostream>

using namespace std;
using namespace cv;



int main()
{
	Mat img;
	img = imread("D:\\Fall 2022\\DS\\a1\\Segmented Outputs\\mIMD002.bmp", 0);
	namedWindow("First OpenCV Application", WINDOW_AUTOSIZE);
	imshow("First OpenCV Application", img);
	moveWindow("First OpenCV Application", 0, 45);
	waitKey(0);
	destroyAllWindows();

	LinkedList l;

	int cols = img.cols;
	int rows = img.rows;
	int** arr = new int* [rows];

	for (int i = 0; i < rows; i++)
		arr[i] = new int[cols];

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			arr[i][j] = img.at<uchar>(i, j);

	int start = 0, end = 0;
	node* head= NULL;
	int temp = 0;
	bool flag=false;

	for (int i = 0; i < rows; i++)
	{
		//start = 0;
		//end = 0;

		for (int j = 0; j < cols; j++)
		{
			
			if (arr[i][j] == 0)
			{
				
				start = j;
				if(j==cols-1)
				{
					end = j;
					j--;
				}
				l.insertatend(start);
				//if (j == cols - 1)
					//end = j;
				j++;
				
			}


			while (arr[i][j] != 255 )
			{
				
				end = j;

				if (arr[i][j+1] == 255)
				{
					flag = true;
					l.insertatend(end);
				}
				//l.insertatend(end);
				if (j == cols - 1)
				{
					l.insertatend(end);
				 l.insertatend(-1);
				
				 break;
				}
				j++;
			}			
			


			//cout << i << " : start: " << start << " end : " << end << endl;
			//if(start!=0)
		}

		//l.insertatend(start);
		//l.insertatend(start);
		
		//l.insertatend(end);

		
		l.printList();


		//if (flag)
		//{

		//	l.insertatend(end);
		//	//	l.insertatend(end);
		//}
			//l.insertatend(start);
		
		//	l.insertatend(end);  
			
			
		}

			//l.printList();

	}


