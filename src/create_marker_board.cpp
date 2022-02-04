#include "opencv2/opencv.hpp"
#include <opencv2/videoio.hpp>
#include <opencv2/aruco.hpp>
#include <iostream>
#include <memory>
#include <fmt/core.h>

using namespace std;
using namespace cv;

int main(){

  cv::Mat cameraMatrix = ( Mat_<double>(3,3)<< 4.8325697765087983e+02, 0., 3.2249123845863045e+02, 0.,
       4.8318579181728722e+02, 2.3958406604380093e+02, 0., 0., 1. );
  fmt::print("{} {} {} \n{} {} {}\n {} {} {}",
  cameraMatrix.at<double>(0,0), cameraMatrix.at<double>(0,1),cameraMatrix.at<double>(0,2),
  cameraMatrix.at<double>(1,0),cameraMatrix.at<double>(1,1),cameraMatrix.at<double>(1,2),
  cameraMatrix.at<double>(2,0),cameraMatrix.at<double>(2,1),cameraMatrix.at<double>(2,2));

  std::string home {std::getenv("HOME")}, imsave_path = home + "/markergrid";
  cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
  // cv::Mat markerImage;
  // cv::aruco::drawMarker(dictionary, 23, 200, markerImage, 1);
  // cv::imshow("marker", markerImage);

  cv::Mat final_file;

  for(int i{0}; i < 4 ; ++i){
    cv::Ptr<cv::aruco::GridBoard> board = cv::aruco::GridBoard::create(1, 2, 0.04, 0.01, dictionary, 2*i);
    cv::Mat boardImage;
    board->draw(cv::Size(250,500), boardImage, 10, 1);
    cv::imshow("marker", boardImage);
    char c=(char)waitKey(0);

    std::string filename = fmt::format("{}/markergrid_{}_{}.png", imsave_path, i, i+1);
    std::cout << filename << std::endl;
    // fmt::print("save image as {}", filename);
    if (final_file.empty())
      final_file = boardImage;
    else
      cv::hconcat(final_file, boardImage, final_file);
    // cv::imwrite(filename, boardImage);
  }
  // Press  ESC on keyboard to exit

    cv::imshow("marker", final_file);
    char c=(char)waitKey(0);
    // cv::imwrite("/home/jay/test.png", final_file);


	
  return 0;
}