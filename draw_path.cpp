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



#include "draw_path.h"
#include "ui_draw_path.h"

Draw_path::Draw_path(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Draw_path)
{
    ui->setupUi(this);
    qApp->installEventFilter(this);
    this->radius=10;
}

Draw_path::~Draw_path()
{
    delete ui;
}

void Draw_path::show_image(std::string title, cv::Mat image){
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

void Draw_path::get_path(std::vector<cv::Point2i> &path){
    path=this->path;
}

void Draw_path::mouseMoveEvent (QMouseEvent *event){
    cv::Point2i point;
    point.x=event->x();
    point.y=event->y();
    this->path.push_back(point);
    cv::circle(this->image,cv::Point(event->x(),event->y()),this->radius,cv::Scalar(0,0,0),-1);
    QImage img((uchar*)this->image.data, this->image.cols, this->image.rows, QImage::Format_RGB888);
    QPixmap pixmap = QPixmap::fromImage(img);
    ui->image->setAlignment(Qt::AlignCenter);
    ui->image->setPixmap(pixmap);
    this->layout()->setSizeConstraint( QLayout::SetFixedSize);
}

bool Draw_path::eventFilter(QObject *obj, QEvent *event){
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
