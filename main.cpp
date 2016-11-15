/*
*
* Copyright 2016 Ignacio San Roman Lana
*
* This file is part of Camera_Reader
*
* qt_opencv_imshow_tools is free software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* qt_opencv_imshow_tools is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with qt_opencv_imshow_tools. If not, see http://www.gnu.org/licenses/.
*
* For those usages not covered by this license please contact with
* isanromanlana@gmail.com
*/


#include "qt_imshow.h"
#include "roi_selector.h"
#include "draw_image.h"
#include "draw_path.h"
#include <QApplication>
#include <opencv2/opencv.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    cv::Mat image=cv::imread("image.png");

    Roi_selector roi_selector;
    roi_selector.show_image("Roi Selector", image);
    roi_selector.show();

    a.exec();

    cv::Rect roi;
    roi_selector.get_roi(roi);
    std::cout<<"ROI="<<roi<<std::endl;

    Draw_image draw_image;
    draw_image.show_image("Draw Image", image);
    draw_image.show();

    a.exec();

    cv::Mat mask;
    draw_image.get_mask(mask);
    Qt_imshow imshow;
    imshow.show_image("Mask", mask);
    imshow.show();

    a.exec();

    Draw_path draw_path;
    draw_path.show_image("Draw Path",image);
    draw_path.show();

    a.exec();

    std::vector<cv::Point2i> path;
    draw_path.get_path(path);

    std::cout<<"Path=";
    for(uint i=0; i<path.size(); i++){
        std::cout<<path[i]<<",";
    }
    std::cout<<std::endl;

    return 0;
}
