#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include "opencv2/opencv.hpp"


#include <iostream>

int main()
{

    cv::Mat original = cv::imread("/home/hj/Data/500.png");
    cv::Mat cameraMatrix = (cv::Mat_<double>(3,3) 
        <<  2.8950781760224106e+02, 0., 4.2350000000000000e+02, 0.,
    2.9143151929932071e+02, 3.9950000000000000e+02, 0., 0., 1.
           );    
    // cv::Mat cameraMatrix = (cv::Mat_<double>(3,3) 
    //     <<  286.764, 0., 419.229, 0.,
    // 286.904, 388.059, 0., 0., 1.
    //        );
    cv::Mat distCoeffs = (cv::Mat_<double>(4,1) << -3.3306769566869890e-04, 2.5578518565356045e-02,
    -2.0000817234451157e-02, 0.);    
    // cv::Mat distCoeffs = (cv::Mat_<double>(4,1) << -0.0104742, 0.0472432, -0.0452336, 0.00871225, 0.0);
    cv::Size imageSize = original.size();


    cv::Mat newCameraMatrix;
    cv::fisheye::estimateNewCameraMatrixForUndistortRectify
            (cameraMatrix, distCoeffs, imageSize, cv::Matx33d::eye(), newCameraMatrix);
    
    std::cout << newCameraMatrix << std::endl;

    cv::Mat output;
    cv::fisheye::undistortImage(original, output, cameraMatrix, distCoeffs, cameraMatrix, cv::Size(1200, 1200));

    cv::imshow("output", output);
    cv::imshow("original", original);
    cv::waitKey(0);

    return 0;
    
}