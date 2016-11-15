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


#ifndef DRAW_PATH_H
#define DRAW_PATH_H

#include <QMainWindow>
#include <QMouseEvent>
#include <opencv2/opencv.hpp>

namespace Ui {
class Draw_path;
}

class Draw_path : public QMainWindow
{
    Q_OBJECT

public:
    explicit Draw_path(QWidget *parent = 0);
    ~Draw_path();

    void show_image(std::string title, cv::Mat image);
    void get_path(std::vector<cv::Point2i> &path);

private:
    Ui::Draw_path *ui;
    void mouseMoveEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
    cv::Mat image;
    std::vector<cv::Point2i> path;

    int radius;
};

#endif // DRAW_PATH_H
