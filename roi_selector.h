/*
*
* Copyright 2016 Ignacio San Roman Lana
*
* This file is part of qt_opencv_imshow_tools
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



#ifndef ROI_SELECTOR_H
#define ROI_SELECTOR_H

#include <QMainWindow>
#include <QMouseEvent>
#include <opencv2/opencv.hpp>

namespace Ui {
class Roi_selector;
}

class Roi_selector : public QMainWindow
{
    Q_OBJECT

public:
    explicit Roi_selector(QWidget *parent = 0);
    ~Roi_selector();

    void show_image(std::string title, cv::Mat image);
    void get_roi(cv::Rect &roi);

private:
    Ui::Roi_selector *ui;
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void manage_event(QMouseEvent * event);

    cv::Mat image;
    int x,y,width,height;
    cv::Rect roi;
    bool press;
};


#endif // ROI_SELECTOR_H
