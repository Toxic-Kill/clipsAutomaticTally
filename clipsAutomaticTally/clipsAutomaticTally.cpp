#include <iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	cv::Mat srcMat = cv::imread("D:\\Files\\clips.png", 0);//读取图像
	cv::Mat binMat;
	cv::Mat labMat;
	cv::Mat staMat;
	cv::Mat cenMat;
	cv::Mat cloMat;
	threshold(srcMat, binMat, 100, 255, THRESH_BINARY_INV);//二值化
	cv::Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));//定义结构元素
	morphologyEx(binMat, cloMat, MORPH_OPEN, kernel);//进行开运算
	int num = connectedComponentsWithStats(cloMat, labMat, staMat, cenMat);//进行连通域标记
	int sum = 0;
	for (int i = 1; i < num; i++)//计算前景像素平均值
	{
		 sum = sum + staMat.at<int>(i, 4);
	}
	int average = sum / num;
	int clips = 0;
	for (int i = 1; i < num; i++)//计数
	{
		if (staMat.at<int>(i, 4) > average)
		{
			clips++;
		}
	}
	std::cout << "the number is:" << clips << endl;//显示物件数量
	waitKey(0);
}