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


#ifndef DRAW_IMAGE_H
#define DRAW_IMAGE_H

#include <QMainWindow>
#include <QMouseEvent>
#include <opencv2/opencv.hpp>

namespace Ui {
class Draw_image;
}

class Draw_image : public QMainWindow
{
    Q_OBJECT

public:
    explicit Draw_image(QWidget *parent = 0);
    ~Draw_image();

    void show_image(std::string title, cv::Mat image);
    void get_mask(cv::Mat &mask);

private:
    Ui::Draw_image *ui;
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
    cv::Mat image, mask;

    int radius;
};

#endif // DRAW_IMAGE_H
