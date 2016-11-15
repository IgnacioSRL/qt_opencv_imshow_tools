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



#include "roi_selector.h"
#include "ui_roi_selector.h"

Roi_selector::Roi_selector(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Roi_selector)
{
    ui->setupUi(this);
    this->press=false;
    this->x=0;
    this->y=0;
    this->width=0;
    this->height=0;
}

Roi_selector::~Roi_selector()
{
    delete ui;
}

void Roi_selector::show_image(std::string title, cv::Mat image){
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
    image_c.copyTo(this->image);
    QPixmap pixmap = QPixmap::fromImage(img);
    ui->image->setAlignment(Qt::AlignCenter);
    ui->image->setPixmap(pixmap);
    this->layout()->setSizeConstraint( QLayout::SetFixedSize);
}

void Roi_selector::get_roi(cv::Rect &roi){
    roi=this->roi;
}

void Roi_selector::manage_event(QMouseEvent * event){
    if(!this->press){
        this->roi.x=0;
        this->roi.y=0;
        this->width=0;
        this->height=0;
        this->x=0;
        this->y=0;
        this->width=0;
        this->height=0;
        this->x=event->x();
        this->y=event->y();
        this->press=true;
    }
    else{
        this->width=event->x()-this->x;
        this->height=event->y()-this->y;
    }
    cv::Mat image;
    this->image.copyTo(image);
    if(this->width<0){
        this->roi.x=this->x+this->width;
        this->roi.width=-this->width;
    }
    else{
        this->roi.x=this->x;
        this->roi.width=this->width;
    }
    if(this->height<0){
        this->roi.y=this->y+this->height;
        this->roi.height=-this->height;
    }
    else{
        this->roi.y=this->y;
        this->roi.height=this->height;
    }
    if(this->roi.x<0)
        this->roi.x=0;
    else if(this->roi.x>this->image.cols)
        this->roi.x=this->image.cols;
    if(this->roi.y<0)
        this->roi.y=0;
    else if(this->roi.y>this->image.rows)
        this->roi.y=this->image.cols;
    if(this->roi.x+this->roi.width>this->image.cols)
        this->roi.width=this->image.cols-this->roi.x;
    if(this->roi.y+this->roi.height>this->image.rows)
        this->roi.height=this->image.rows-this->roi.y;

    cv::rectangle(image,this->roi,cv::Scalar(255,0,0),3);
    QImage img((uchar*)image.data, image.cols, image.rows, QImage::Format_RGB888);
    QPixmap pixmap = QPixmap::fromImage(img);
    ui->image->setAlignment(Qt::AlignCenter);
    ui->image->setPixmap(pixmap);
    this->layout()->setSizeConstraint( QLayout::SetFixedSize);
}

void Roi_selector::mouseMoveEvent (QMouseEvent * event){
    manage_event(event);
}

void Roi_selector::mouseReleaseEvent (QMouseEvent * event){
    manage_event(event);
    this->press=false;
}
