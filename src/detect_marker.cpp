#include "opencv2/opencv.hpp"
#include <opencv2/videoio.hpp>
#include <opencv2/aruco.hpp>
#include <iostream>
#include <memory>

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

  while (cap.grab()){

    std::shared_ptr<cv::Mat> frame_ptr = std::make_shared<cv::Mat>();

    // Capture frame-by-frame
    cap >> *frame_ptr;
 
    // // If the frame is empty, break immediately
    // if (frame_ptr->empty())
    //   break;

    // Display the resulting frame
    // imshow( "Frame", *frame_ptr );


    std::vector<int> markerIds;
    std::vector<std::vector<cv::Point2f>> markerCorners, rejectedCandidates;
    cv::Ptr<cv::aruco::DetectorParameters> parameters = cv::aruco::DetectorParameters::create();
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
    cv::aruco::detectMarkers(*frame_ptr, dictionary, markerCorners, markerIds, parameters, rejectedCandidates);

    cv::Mat copy_frame = frame_ptr->clone();

    if (markerIds.size() > 0)
    {  
      cv::aruco::drawDetectedMarkers(copy_frame, markerCorners, markerIds);

      std::vector<cv::Vec3d> rvecs, tvecs;
      cv::aruco::estimatePoseSingleMarkers(markerCorners, 0.1, cameraMatrix, distCoeffs, rvecs, tvecs);
      // draw axis for each marker
      for(int i=0; i<markerIds.size(); i++)
          cv::aruco::drawAxis(copy_frame, cameraMatrix, distCoeffs, rvecs[i], tvecs[i], 0.1);

    }    
    cv::imshow("out", copy_frame);

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


  }
 
  // When everything done, release the video capture object
  cap.release();

  // Closes all the frames
  destroyAllWindows();
	
  return 0;
}