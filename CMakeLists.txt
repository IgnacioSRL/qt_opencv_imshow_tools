cmake_minimum_required(VERSION 2.8.3)
project(example)

find_package(OpenCV REQUIRED)
find_package(
 Qt5Widgets REQUIRED
 Qt5Core REQUIRED
 Qt5Gui REQUIRED
)


set(CMAKE_AUTOMOC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
add_definitions(${Qt5Widgets_DEFINITIONS})

FIND_PROGRAM(QT_UIC_EXECUTABLE uic
  $ENV{QTDIR}/bin
)

IF (QT_UIC_EXECUTABLE)
  SET ( QT_WRAP_UI "YES")
ENDIF (QT_UIC_EXECUTABLE)

QT5_WRAP_UI(UIS_HDRS
    qt_imshow.ui
    draw_image.ui
    draw_path.ui
    roi_selector.ui
)

include_directories(include)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${OpenCV_INCLUDE_DIR})
include_directories(
  ${PROJECT_SOURCE_DIR}
  ${Qt5Widgets_INCLUDE_DIRS} 
  ${Qt5Core_INCLUDE_DIRS} 
  ${Qt5Gui_INCLUDE_DIRS}
)


add_library(qt_imshow qt_imshow.cpp ${UIS_HDRS})
add_library(draw_image draw_image.cpp ${UIS_HDRS})
add_library(draw_path draw_path.cpp ${UIS_HDRS})
add_library(roi_selector roi_selector.cpp ${UIS_HDRS})

add_executable(main main.cpp)

add_dependencies(main qt_imshow draw_image draw_path roi_selector)

target_link_libraries(qt_imshow
  Qt5::Core
  Qt5::Widgets 
  ${OpenCV_LIBS}
)

target_link_libraries(draw_image
  Qt5::Core
  Qt5::Widgets 
  ${OpenCV_LIBS}
)

target_link_libraries(draw_path
  Qt5::Core
  Qt5::Widgets 
  ${OpenCV_LIBS}
)

target_link_libraries(roi_selector
  Qt5::Core
  Qt5::Widgets 
  ${OpenCV_LIBS}
)

target_link_libraries(main
  qt_imshow
  draw_image
  draw_path
  roi_selector
  ${OpenCV_LIBS}
)
