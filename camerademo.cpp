/*
    Copyright (c) 2013 James McLean

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

#include "camerademo.h"
#include "ui_camerademo.h"

#include <QDebug>

#include "ccvt.h"
#include "utils.h"

CameraDemo::CameraDemo(QWidget *parent) : QMainWindow(parent), ui(new Ui::CameraDemo) {
    ui->setupUi(this);

    capturing = false;

    device = v4l2_create_device("/dev/video1");

    v4l2_open_device(device);

    v4l2_format_t format;

    v4l2_get_format(device, &format);

    width = format.width;
    height = format.height;

    qDebug() << "Width: " << width << " " << " Height: " << height;

    frame = new unsigned char[v4l2_get_buffer_size(device)];
    rgbFrame = new unsigned char[width * height * 3];

    connect(ui->actionStart_Capture, SIGNAL(triggered(bool)), this, SLOT(startCapture()));
    connect(ui->actionStop_Capture, SIGNAL(triggered(bool)), this, SLOT(stopCapture()));
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(quit()));
}

CameraDemo::~CameraDemo() {
    if (capturing)
        stopCapture();

    if (device != NULL) {
        v4l2_close_device(device);
        v4l2_destroy_device(device);
    }

    delete ui;
}

void CameraDemo::startCapture() {
    if (!capturing) {
        v4l2_start_capture(device);
        timerId = startTimer(0);
        capturing = true;
    }
}

void CameraDemo::stopCapture() {
    if (capturing) {
        killTimer(timerId);
        capturing = false;
        v4l2_stop_capture(device);
    }
}

void CameraDemo::quit() {
    stopCapture();
    QCoreApplication::quit();
}

void CameraDemo::timerEvent(QTimerEvent*) {
    if (capturing) {
        v4l2_grab_frame(device);
        v4l2_copy_frame(device, frame);
        ccvt_yuyv_rgb24(width, height, frame, rgbFrame);
        displayImage(width, height, rgbFrame);
    }
}

void CameraDemo::displayImage(int width, int height, unsigned char* data) {
    QImage qImage = colorToQImage(width, height, data);
    ui->videoImage->setPixmap(QPixmap::fromImage(qImage));
}
