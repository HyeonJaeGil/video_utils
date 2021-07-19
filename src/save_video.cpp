#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>

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
  int deviceID = 4;
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


  while(1){

    static int frame_count = 0;

    Mat frame;
    // Capture frame-by-frame
    cap >> frame;
 
    // If the frame is empty, break immediately
    if (frame.empty())
      break;

    // cout << save_path + to_string(frame_count) + ".png" << endl;
    imwrite (save_path + to_string(frame_count) + ".png", frame);

    // Press  ESC on keyboard to exit
    char c=(char)waitKey(25);
    if(c==27)
      break;

    frame_count++;
  }
 
  // When everything done, release the video capture object
  cap.release();

  // Closes all the frames
  destroyAllWindows();
	
  return 0;
}