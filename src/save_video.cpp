#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
#include <memory>

using namespace std;
using namespace cv;

int main(){

  // Create a VideoCapture object
  VideoCapture cap;

  // file saving directory
  string save_path = "/home/hj/webcam_test/save/";

  // open exiting video file
  // string file_name = "/home/hj/testing3.mp4";
  // cap(file_name); 

  // open webcam device
  int deviceID = 6;
  int apiID = cv::CAP_V4L2;
  cap.open(deviceID, apiID);


  //check backend api name
  std::cout << cap.getBackendName() << std::endl;

  // Check if camera opened successfully
  if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
    return -1;
  }

  //set parameters of the camera
  cap.set(cv::CAP_PROP_BUFFERSIZE, 2);
  cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
  cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
  cap.set(cv::CAP_PROP_FPS, 30);
  // cap.set(cv::CAP_PROP_MONOCHROME, true);


  while(1){

    static int frame_count = 0;

    if (frame_count < 5)
    {
      frame_count ++;
      continue;
    }

    std::unique_ptr<cv::Mat> frame_ptr = std::make_unique<cv::Mat>();
    // Capture frame-by-frame
    cap >> *frame_ptr;

    // If the frame is empty, break immediately
    if (frame_ptr->empty())
      break;

    // cout << save_path + to_string(frame_count) + ".png" << endl;
    cv::imwrite (save_path + to_string(frame_count) + ".png", *frame_ptr);

    // Press  ESC on keyboard to exit
    char c=(char)waitKey(25);
    if(c==27)
      break;

    frame_count++;

    //check fps of the video
    double fps = cap.get(CAP_PROP_FPS);
    cout << "fps of the video : " << fps << endl;

    //check frame size
    cv::Size frame_size = frame_ptr->size();
    std::cout << "width : " << frame_size.width << ", height : "<< frame_size.height <<std::endl;
  }
 
  // When everything done, release the video capture object
  cap.release();

  // Closes all the frames
  destroyAllWindows();
	
  return 0;
}