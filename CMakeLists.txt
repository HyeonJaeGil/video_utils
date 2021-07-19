cmake_minimum_required(VERSION 3.10)
PROJECT(display_video)

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

ADD_EXECUTABLE(display_video src/display_video.cpp)
TARGET_LINK_LIBRARIES(display_video ${OpenCV_LIBS})

ADD_EXECUTABLE(save_video src/save_video.cpp)
TARGET_LINK_LIBRARIES(save_video ${OpenCV_LIBS})
