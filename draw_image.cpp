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


#include "draw_image.h"
#include "ui_draw_image.h"

Draw_image::Draw_image(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Draw_image)
{
    ui->setupUi(this);
    qApp->installEventFilter(this);
    this->radius=50;
}

Draw_image::~Draw_image()
{
    delete ui;
}

void Draw_image::show_image(std::string title, cv::Mat image){
    cv::Mat image_c;
    image.copyTo(image_c);
    this->mask=cv::Mat::ones(image_c.rows,image_c.cols,CV_8UC1)*255;
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

void Draw_image::get_mask(cv::Mat &mask){
    this->mask.copyTo(mask);
}

void Draw_image::mouseMoveEvent (QMouseEvent *event){
    cv::circle(this->image,cv::Point(event->x(),event->y()),this->radius,cv::Scalar(0,0,0),-1);
    cv::circle(this->mask,cv::Point(event->x(),event->y()),this->radius,cv::Scalar(0,0,0),-1);
    QImage img((uchar*)this->image.data, this->image.cols, this->image.rows, QImage::Format_RGB888);
    QPixmap pixmap = QPixmap::fromImage(img);
    ui->image->setAlignment(Qt::AlignCenter);
    ui->image->setPixmap(pixmap);
    this->layout()->setSizeConstraint( QLayout::SetFixedSize);
}

void Draw_image::wheelEvent(QWheelEvent *event){
    this->radius=this->radius+(event->delta()/(8*15));
    if(this->radius<1)
        this->radius=1;
    else if(this->radius>500)
        this->radius=500;
    cv::Mat img_show;
    this->image.copyTo(img_show);
    QPoint pos=QWidget::mapFromGlobal(QCursor::pos());
    cv::circle(img_show,cv::Point(pos.x(),pos.y()),this->radius,cv::Scalar(0,0,0),2);
    QImage img((uchar*)img_show.data, img_show.cols, img_show.rows, QImage::Format_RGB888);
    QPixmap pixmap = QPixmap::fromImage(img);
    ui->image->setAlignment(Qt::AlignCenter);
    ui->image->setPixmap(pixmap);
    this->layout()->setSizeConstraint( QLayout::SetFixedSize);
}

bool Draw_image::eventFilter(QObject *obj, QEvent *event){
    if (event->type() == QEvent::MouseMove){
        cv::Mat img_show;
        this->image.copyTo(img_show);
        QPoint pos=QWidget::mapFromGlobal(QCursor::pos());
        cv::circle(img_show,cv::Point(pos.x(),pos.y()),this->radius,cv::Scalar(0,0,0),2);
        QImage img((uchar*)img_show.data, img_show.cols, img_show.rows, QImage::Format_RGB888);
        QPixmap pixmap = QPixmap::fromImage(img);
        ui->image->setAlignment(Qt::AlignCenter);
        ui->image->setPixmap(pixmap);
        this->layout()->setSizeConstraint( QLayout::SetFixedSize);
    }
    return false;
}
