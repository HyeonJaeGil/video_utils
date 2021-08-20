#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem> //c++17
#include <set>
 

using namespace cv;
using namespace std;
using std::filesystem::directory_iterator;
 

int main(){

    string rootpath = "/home/hj/Dropbox/dataset/warehouse/210624/rgb/";

    //Transformation Matrix 구하기
    Mat trans= (Mat_<double>(3,3) << 
     -0.3476959396049488, -1.732151228600956, 809.7010384438785,
     -0.01599468240306646, -1.957173567632461, 734.35159533766,
     -2.665780400511097e-05, -0.002898450547413246, 1
    );

    // for (auto : rootpath)
    std::set<std::filesystem::path> sorted;
    for (const auto & file : directory_iterator(rootpath))
        sorted.insert(file);

    for (const auto & sortedFile : sorted)
    {
        Mat img = imread(sortedFile.c_str());
        Mat warpImg = cv::Mat(img.size(), CV_8UC3, cv::Scalar(0, 0, 0));

        //Warping
        warpPerspective(img, warpImg, trans, warpImg.size());
       
        imshow("warpedImage", warpImg);
        imshow("Image", img);

        waitKey(10);
    }
    return 0;
};