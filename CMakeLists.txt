cmake_minimum_required(VERSION 3.10)
PROJECT(display_video)

set(CMAKE_CXX_STANDARD 17)

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

#message(${OpenCV_INCLUDE_DIRS})

ADD_EXECUTABLE(display_video src/display_video.cpp)
TARGET_LINK_LIBRARIES(display_video ${OpenCV_LIBS})

ADD_EXECUTABLE(save_video src/save_video.cpp)
TARGET_LINK_LIBRARIES(save_video ${OpenCV_LIBS})

# ADD_EXECUTABLE(detect_marker src/detect_marker.cpp)
# TARGET_LINK_LIBRARIES(detect_marker ${OpenCV_LIBS})

ADD_EXECUTABLE(create_single_marker src/create_single_marker.cpp)
TARGET_LINK_LIBRARIES(create_single_marker ${OpenCV_LIBS})

ADD_EXECUTABLE(create_marker_board src/create_marker_board.cpp)
TARGET_LINK_LIBRARIES(create_marker_board ${OpenCV_LIBS} fmt::fmt)

ADD_EXECUTABLE(optical_flow src/optical_flow.cpp)
TARGET_LINK_LIBRARIES(optical_flow ${OpenCV_LIBS})

ADD_EXECUTABLE(warp_image src/warp_image.cpp)
TARGET_LINK_LIBRARIES(warp_image ${OpenCV_LIBS})

ADD_EXECUTABLE(warp_video src/warp_video.cpp)
TARGET_LINK_LIBRARIES(warp_video ${OpenCV_LIBS})

ADD_EXECUTABLE(undistort_image src/undistort_image.cpp)
TARGET_LINK_LIBRARIES(undistort_image ${OpenCV_LIBS})

add_executable( display_image src/display_image.cpp )
target_link_libraries( display_image ${OpenCV_LIBS} )

add_executable(calibration src/calibration.cpp)
target_link_libraries(calibration ${OpenCV_LIBS})

add_executable(camera_calibration src/camera_calibration/camera_calibration.cpp)
target_link_libraries(camera_calibration ${OpenCV_LIBS})