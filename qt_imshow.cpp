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



#include "qt_imshow.h"
#include "ui_qt_imshow.h"

Qt_imshow::Qt_imshow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Qt_imshow)
{
    ui->setupUi(this);
}

Qt_imshow::~Qt_imshow()
{
    delete ui;
}

void Qt_imshow::show_image(std::string title, cv::Mat image){
    cv::Mat image_c;
    image.copyTo(image_c);
    this->setWindowTitle(QString::fromStdString(title));
    QImage img;
    if(image_c.channels()>1){
        cv::cvtColor(image_c,image_c,CV_BGR2RGB);
        img=QImage((uchar*)image_c.data, image_c.cols, image_c.rows, QImage::Format_RGB888);
    }
    else
        img=QImage((uchar*)image_c.data, image_c.cols, image_c.rows, QImage::Format_Indexed8);
    this->image_size=image_c.size();
    QPixmap pixmap = QPixmap::fromImage(img);
    ui->image->setAlignment(Qt::AlignCenter);
    ui->image->setScaledContents(true);
    ui->image->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->image->setPixmap(pixmap);
    this->resize(pixmap.size());
}

void Qt_imshow::mousePressEvent(QMouseEvent *event){
    this->resize(QSize(this->image_size.width,this->image_size.height));
}
