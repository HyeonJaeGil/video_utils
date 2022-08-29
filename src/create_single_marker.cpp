#include "opencv2/opencv.hpp"
#include <opencv2/videoio.hpp>
#include <opencv2/aruco.hpp>
#include <iostream>
#include <memory>

using namespace std;
using namespace cv;

int main(){

  cv::Mat markerImage;
  cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
  cv::aruco::drawMarker(dictionary, 23, 200, markerImage, 1);
  cv::imshow("marker", markerImage);

  // Press  ESC on keyboard to exit
  char c=(char)waitKey(25);
    

  cv::imwrite("marker23.png", markerImage);
	
  return 0;
}