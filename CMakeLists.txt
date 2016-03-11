cmake_minimum_required (VERSION 2.6)
project (time-conv-wx)
add_definitions ( -Wall )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
FIND_PACKAGE(wxWidgets REQUIRED html adv core base net aui xrc qa richtext )
INCLUDE(${wxWidgets_USE_FILE})

set (HDRS
    mainwindow.h
    res/res.h
)
set (SRCS
    main.cpp
    res/res.cpp
)
add_executable(time-conv-wx ${HDRS} ${SRCS})
TARGET_LINK_LIBRARIES(time-conv-wx ${wxWidgets_LIBRARIES})
