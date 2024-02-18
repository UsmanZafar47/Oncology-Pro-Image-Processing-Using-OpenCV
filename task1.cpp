#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


//					##########	#########	########	#	#       ##
//						#		#		#	#			#  #	   ###
//						#		#########	########	# #	 ----	 #
//						#		#		#		   #	#  #	     #
//						#		#		#	########	#   #	   #####



int check2(int x, int y)
{
	int arr[3] = { x,y };
	int min = 99999;
	for (int i = 0; i < 2; i++)
	{
		if (min > arr[i] && arr[i] != 0)
			min = arr[i];

	}
	//if(min!=0)
	return min;

}


int check3(int x, int y, int z)
{
	int arr[3] = { x,y,z };
	int min = 99999;
	for (int i = 0; i < 3; i++)
	{
		if (min > arr[i] && arr[i] != 0)
			min = arr[i];

	}
	//if(min!=0)
	return min;

}


int check4(int w, int x, int y, int z)
{
	int arr[4] = { w,x,y,z };
	int min = 99999;
	for (int i = 0; i < 4; i++)
	{
		if (min > arr[i] && arr[i] != 0)
			min = arr[i];

	}
	//if(min!=0)
	return min;

}






int main()
{
	Mat image;
	image = imread("D:\\Fall 2022\\DS\\a1\\Segmented Outputs\\mIMD019.bmp",0);
	namedWindow("First OpenCV Application", WINDOW_AUTOSIZE);
    imshow("First OpenCV Application", image);
    moveWindow("First OpenCV Application", 0, 45);
    waitKey(0);
    destroyAllWindows();
   
	int cols = image.cols;//*image.channels();
	int rows = image.rows;
	int** arr = new int*[image.rows];

	for (int i = 0; i < image.rows; i++)
	arr[i] = new int[cols];

	int** label = new int* [image.rows];
	for (int i = 0; i < image.rows; i++)
		label[i] = new int[cols];

	for (int i = 0; i < image.rows; i++)
		for (int j = 0; j < cols; j++)
			 arr[i][j]= image.at<uchar>(i, j);

	for (int i = 0; i < image.rows; i++)
		for (int j = 0; j < cols; j++)
			if (arr[i][j] == 255)
				arr[i][j] = 1;

	for (int i = 0; i < image.rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
				label[i][j] = 0;
		}
	}



	
	

	//	int arr[5][5] = { {0,0,0,0,1},{0,1,0,0,0},{1,0,0,1,1},{0,0,0,1,0},{0,0,0,1,0} };
		// 0 0 0 0 1 
		// 0 1 0 0 0
		// 1 0 0 1 1
		// 0 0 0 1 0 
		// 0 0 0 1 0


		int component = 1;

		for (int i = 0; i < image.rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				//  if(arr[6][6]==0)
				  //	break;
				
				if (arr[i][j] == 0)
					continue;

				if (i == 0 && j > 0)
				{
					if (arr[i][j-1] == 0 )
					{
	
						
						label[i][j] = component;
						component++;
					}
				}
				if (i  > 0 && j  > 0) {
					if ((arr[i][j - 1] == 0 && arr[i - 1][j] == 0 && arr[i - 1][j - 1] == 0 && arr[i - 1][j + 1] == 0))
					{
						if (label[i][j - 1] != 0 || label[i - 1][j] != 0 && label[i - 1][j - 1] != 0 || label[i - 1][j + 1] != 0)
							component = check4(label[i][j - 1], label[i - 1][j], label[i - 1][j - 1], label[i - 1][j + 1]);

						label[i][j] = component;
						component++;
					}
					if ((arr[i][j - 1] != 0 || arr[i - 1][j] != 0 || arr[i - 1][j - 1] != 0 || arr[i - 1][j + 1] != 0))
					{
						if (label[i][j - 1] != 0 || label[i - 1][j] != 0 || label[i - 1][j - 1] != 0 || label[i - 1][j + 1] != 0)
							component = check4(label[i][j - 1], label[i - 1][j], label[i - 1][j - 1], label[i - 1][j + 1]);
						

						label[i][j] = component;
						//	component++;

					}

				}

				if (i >= 0 && j == 0)
				{
					if ((arr[i - 1][j] == 0 && arr[i - 1][j + 1] == 0))
					{
						if (label[i - 1][j] != 0 || label[i - 1][j + 1] != 0)
							component = check2(label[i - 1][j], label[i - 1][j + 1]);

						label[i][j] = component;
						component++;

					}
					if ((arr[i - 1][j] != 0 || arr[i - 1][j + 1] != 0))
					{
						if (label[i - 1][j] != 0 || label[i - 1][j + 1] != 0)
							component = check2(label[i - 1][j], label[i - 1][j + 1]);

						label[i][j] = component;
						//component++;
					}


					if (i > 0 && j == cols - 1)
					{
						if ((arr[i][j - 1] == 0 && arr[i - 1][j] == 0 && arr[i - 1][j - 1] == 0))
						{

							if (label[i - 1][j] != 0 || label[i - 1][j - 1] != 0 || label[i][j - 1] != 0)
								component = check3(label[i - 1][j], label[i - 1][j - 1], label[i][j - 1]);

							label[i][j] = component;
							component++;

						}
						if ((arr[i][j - 1] != 0 || arr[i - 1][j] != 0 || arr[i - 1][j - 1] != 0))
						{
							if (label[i - 1][j] != 0 || label[i - 1][j - 1] != 0 || label[i][j - 1] != 0)
								component = check3(label[i - 1][j], label[i - 1][j - 1], label[i][j - 1]);

							label[i][j] = component;
						//	component++;

						}


					}



				}
			}
		}



	






	int i, j, k=0, count = 0, num;
	int x, y;
	int freq[5000]{ 0 };
	
	//for (int i = 0; i < 5000; i++) {
	//	for (int j = 0; j < image.rows; j++) {
	//		for (int k = 0; k < cols; k++) {
	//			if (i+1==label[j][k]) {
	//				count++;
	//				freq[k] = count;
	//				
	//			}
	//		}
	//	
	//	}
	//	count = 0;
	//}
	bool** check = new bool*[image.rows];
	for( i =0;i<image.rows;i++)
	check[i]=new bool[cols];

	for (i = 0; i < image.rows; i++)
		for (j = 0; j < cols; j++)
			check[i][j] = 0;

	for (i = 0; i < image.rows; i++) {
		for (j = 0; j < cols; j++) {
			count = 1;
			num = label[i][j];
			if (check[i][j] != 1) {
				for (x = 0; x < image.rows; x++) {
					for (y = 0; y < cols; y++) {
						if ((i == x) && (j == y)) {
							continue;
						}
						if (label[i][j] == label[x][y]) {
							check[x][y] = 1;
							count++;
						}
					}
				}
				cout << " frequency of element " << num << " is :" << count << endl;
				freq[num] = count;
			}
		}
	}
	
	int max = 0;
	int n1 = 0;
	for (int k = 1; k < image.cols; k++)
	{
	//	for (i = 0; i < image.cols; i++) {
			if (freq[k] != 0) {
				if (max < freq[k]) {

					max = freq[k];
					n1 = k;
				}
			}
		//}

	}
	
	cout << "max freq is element " << n1 << " is: " << max << endl;
	
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < cols; j++) 
		{
			if (label[i][j] != n1)
			{
				label[i][j] = 0;
				//cout <<"label[" << i << "][" << j << "]  :   " << label[i][j] << endl;
			}

			if (label[i][j] == n1)
			{
				label[i][j] = 255;
				//cout << "label[" << i << "][" << j << "]  :   " << label[i][j] << endl;
			}
		}
	}

	
    for (int i = 0; i < image.rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			//if(label[i][j]==255)
			//cout << label[i][j];
		}
	}
	
	for (int i = 0; i < image.rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			image.at<uchar>(i,j)= label[i][j];
		}
	}


	//Mat img(image.rows, cols, CV_64F, label);
	imwrite("name1.bmp", image);
	image = imread("C:\\Users\\Usman's PC\\source\\repos\\AS1\\AS1\\name1.bmp",0);
	//image = imread("D:\\Fall 2022\\DS\\a1\\Segmented Outputs\\mIMD019.bmp", 0);
	namedWindow("First OpenCV Application", WINDOW_AUTOSIZE);
	imshow("First OpenCV Application", image);
	moveWindow("First OpenCV Application", 0, 45);
	waitKey(0);
	destroyAllWindows();	system("pause");
	/*int x;
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			 x = image.at<uchar>(i, j);
			cout << x;
		}
		cout << endl;
	}*/


	return 0;
}


