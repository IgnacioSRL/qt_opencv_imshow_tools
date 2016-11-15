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


#ifndef QT_IMSHOW_H
#define QT_IMSHOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>

namespace Ui {
class Qt_imshow;
}

class Qt_imshow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Qt_imshow(QWidget *parent = 0);
    ~Qt_imshow();

    void show_image(std::string title, cv::Mat image);

private:
    Ui::Qt_imshow *ui;
    cv::Size image_size;
    void mousePressEvent(QMouseEvent *event);
};

#endif // QT_IMSHOW_H
