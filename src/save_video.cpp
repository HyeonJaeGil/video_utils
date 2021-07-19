#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

int main(){

  // Create a VideoCapture object and open the input file
  // If the input is the web camera, pass 0 instead of the video file name
  string file_name = "/home/hj/testing3.mp4";
  VideoCapture cap(file_name); 

  // file saving directory
  string save_path = "/home/hj/webcam_test/save/";

  // Check if camera opened successfully
  if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
    return -1;
  }
	
  //get fps of the video
  double fps = cap.get(CAP_PROP_FPS);
  cout << "fps of the video : " << fps << endl;

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