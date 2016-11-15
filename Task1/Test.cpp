#include "opencv2\core.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"
using namespace cv;
#include <iostream>
#include <string>
#include <list>
using namespace std;
list <Mat> GetImagelist(string videofilename, int chopDistance)
{
	list <Mat> outlist;
	VideoCapture video;
	video.open(videofilename);
	Mat frame;
	int cout = 0;
	while (true)
	{
		if (!frame.data)
			break;
		if (cout == chopDistance)
		{
			video >> frame;
			outlist.push_back(frame);
		}
		else cout++;
	}
	return outlist;
}
 
list <Mat> ResizeImageList(list<Mat> inputlist, int newWidth, int newHeight)
{
	list <Mat> outlist;
	for (list <Mat>::iterator it = inputlist.begin(); it != inputlist.end(); it++)
	{
		Mat a = *it;
		resize(a, a, Size(newWidth, newHeight));
		outlist.push_back(a);
	}
	return outlist;
}
list <Mat> ImagelisttoGrayscale(list<Mat> inputlist)
{
	list <Mat> outlist;
	for (list <Mat>::iterator it = inputlist.begin(); it != inputlist.end(); it++)
	{
		Mat a = *it;
		cvtColor(a, a, COLOR_BGR2GRAY);
		outlist.push_back(a);
	}
	return outlist;
}
void SaveImageList(list<Mat> inputlist, string folderName)
{
	folderName += "\\";
	string path = "md " + folderName;
	system(path.c_str());
	int count = 0;
	for (list <Mat>::iterator it = inputlist.begin(); it != inputlist.end(); it++)
	{
		path = folderName + to_string(count++) + ".jpg";
		imwrite(path, *it);
	}
}


int main()
{
	string ipath;
	string opath;
	cout << "Input path:  ";
	getline(cin, ipath);
	cout << "Output path: ";
	getline(cin, opath);
	list <Mat> A;
	A = GetImagelist(ipath, 20);
	A = ResizeImageList(A, 500, 500);
	A = ImagelisttoGrayscale(A);
	SaveImageList(A, opath);
}