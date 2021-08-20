#include <iostream>
#include <opencv2/opencv.hpp>

 

using namespace cv;
using namespace std;

 

int main(){

string rootpath = "/home/hj/Dropbox/dataset/warehouse/210701/rgb/";
Mat img=imread("/home/hj/Dropbox/dataset/warehouse/210624/rgb/1624516958.683195.png");

 
//Warping 전의 이미지 상의 좌표 

vector<Point2f> corners(4);
corners[0]=Point2f(592, 395);
corners[1]=Point2f(728, 394);
corners[2]=Point2f(405, 616);
corners[3]=Point2f(1087, 616);

// cv::rectangle(img, cv::Rect(corners[0], corners[3]), cv::Scalar(0,255,0));
// imshow("ROI", img);
// cv::waitKey(0);
// return 0;

vector<Point2f> warpCorners(4);
warpCorners[0]=Point2f(500 , 300);
warpCorners[1]=Point2f(780 , 300);
warpCorners[2]=Point2f(500 , 600);
warpCorners[3]=Point2f(780 , 600);
 

//Transformation Matrix 구하기
Mat trans=getPerspectiveTransform(corners, warpCorners);
cout << trans << endl;
// [-0.6129670664619388, -1.805644999388346, 1035.165120414411;
//  -0.0007742461171348405, -2.36365838251441, 974.5024411629976;
//  -2.150683658707119e-06, -0.002789276964930653, 1]

cv::Mat warpImg = cv::Mat(img.size(), CV_8UC3, cv::Scalar(0, 0, 0));

//Warping

warpPerspective(img, warpImg, trans, warpImg.size());
imshow("warpImg", warpImg);

 
for(int i=0; i<corners.size(); i++)
circle(img, corners[i], 3, Scalar(0, 255, 0), 3);

imshow("Image", img);

waitKey(0);

};