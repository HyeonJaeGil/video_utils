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

ADD_EXECUTABLE(detect_marker src/detect_marker.cpp)
TARGET_LINK_LIBRARIES(detect_marker ${OpenCV_LIBS})

ADD_EXECUTABLE(create_marker src/create_marker.cpp)
TARGET_LINK_LIBRARIES(create_marker ${OpenCV_LIBS})

ADD_EXECUTABLE(optical_flow src/optical_flow.cpp)
TARGET_LINK_LIBRARIES(optical_flow ${OpenCV_LIBS})