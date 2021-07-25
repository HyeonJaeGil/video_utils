#include "opencv2/opencv.hpp"
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <memory>
#include <chrono>

using namespace std;
using namespace cv;

int main(){

  // Create a VideoCapture object
  VideoCapture cap;

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
  // cap.set(cv::CAP_PROP_MONOCHROME, true);

  cv::Mat cameraMatrix = ( Mat_<double>(3,3)<< 4.8325697765087983e+02, 0., 3.2249123845863045e+02, 0.,
       4.8318579181728722e+02, 2.3958406604380093e+02, 0., 0., 1. );
  cv::Mat distCoeffs  = (Mat_<double>(5,1) << -4.5624292545288403e-01, 3.2720310258928254e-01,
       7.5246312212940537e-05, 6.5448087382331561e-04,
       -1.8906774851318395e-01 );


  auto current_time = std::chrono::steady_clock::now();


  vector<Scalar> colors;
  RNG rng;
  for(int i = 0; i < 100; i++)
  {
      int r = rng.uniform(0, 256);
      int g = rng.uniform(0, 256);
      int b = rng.uniform(0, 256);
      colors.push_back(Scalar(r,g,b));
  }

  vector<Point2f> p0, p1;

  while (cap.grab()){

    static int count = 0;

    std::shared_ptr<cv::Mat> frame_ptr = std::make_shared<cv::Mat>();
    static cv::Mat old_frame;


    // Capture frame-by-frame
    cap >> *frame_ptr;
    auto prev_time = current_time;
    current_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> dur = current_time - prev_time;
    double time_diff = dur.count();
    // cout << time_diff <<endl;


   cvtColor(*frame_ptr, *frame_ptr, COLOR_BGR2GRAY);
    goodFeaturesToTrack(*frame_ptr, p0, 100, 0.3, 7, Mat(), 7, false, 0.04);
    Mat mask = Mat::zeros(frame_ptr->size(), frame_ptr->type());

    if(count < 1){
      count ++;
      old_frame = *frame_ptr;
      continue;
    
    }

    // calculate optical flow
    vector<uchar> status;
    vector<float> err;
    TermCriteria criteria = TermCriteria((TermCriteria::COUNT) + (TermCriteria::EPS), 10, 0.03);
    calcOpticalFlowPyrLK(*frame_ptr, old_frame, p0, p1, status, err, Size(15,15), 2, criteria);

    vector<Point2f> good_new;
    for(uint i = 0; i < p0.size(); i++)
    {
        // Select good points
        if(status[i] == 1) {
            good_new.push_back(p1[i]);
            // draw the tracks
            line(mask,p1[i], p0[i], colors[i], 2);
            circle(*frame_ptr, p1[i], 5, colors[i], -1);
        }
    }

    cv::Mat added;
    add(*frame_ptr, mask, added);


    // // If the frame is empty, break immediately
    // if (frame_ptr->empty())
    //   break;

    // Display the resulting frame
    imshow( "Optical Flow", added );

    // Press  ESC on keyboard to exit
    char c=(char)waitKey(25);
    if(c==27)
      break;

    // check fps of the video
    // double fps = cap.get(CAP_PROP_FPS);
    // cout << "fps of the video : " << fps << endl;

    //check frame size
    // cv::Size frame_size = frame_ptr->size();
    // std::cout << "width : " << frame_size.width << ", height : "<< frame_size.height <<std::endl;

    double distance_x = 0;
    double distance_y = 0;
    for (int i = 0; i < p1.size(); ++i){
      distance_x += (p0[i].x - p1[i].x) / p1.size();
      distance_y += (p0[i].y - p1[i].y) / p1.size();
      
    }

    cout << "norm x distance: "<< distance_x << " norm y distance" << distance_y << endl;
    // cout << "vel x : "  << distance_x/time_diff << " vel y : " << distance_y/time_diff <<endl;
   
    old_frame = frame_ptr->clone();
    p0 = good_new;
    count++;
  }
 
  // When everything done, release the video capture object
  cap.release();

  // Closes all the frames
  destroyAllWindows();
	
  return 0;
}