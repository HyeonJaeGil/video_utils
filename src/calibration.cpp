#include <opencv2/calib3d.hpp>
#include <iostream>
#include <vector>

int main()
{

/*
    1. get checkerboard information

    2. get 2d pixel coordinate

    3. calibrate
*/


    std::cout << "Get checkerboard information" << std::endl;

    int checker_row, checker_col, checker_width;
    std::cout << "row: ";    std::cin >> checker_row;
    std::cout << "col: ";    std::cin >> checker_col;
    std::cout << "width[mm]: ";    std::cin >> checker_width;
    
    std::cout << "row: " << checker_row << " col: " << checker_col <<  " width: " << checker_width << std::endl;

    std::vector<cv::Point2d> points;

    return 0;
}