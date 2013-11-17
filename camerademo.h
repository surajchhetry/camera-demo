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

#ifndef CAMERADEMO_H
#define CAMERADEMO_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>

#include <v4l2.h>

namespace Ui {
    class CameraDemo;
}

class CameraDemo : public QMainWindow {
    Q_OBJECT
    
public:
    explicit CameraDemo(QWidget *parent = 0);
    ~CameraDemo();
    
private slots:
    void startCapture();
    void stopCapture();
    void quit();

protected:
    void timerEvent(QTimerEvent* timerEvent);

private:
    Ui::CameraDemo *ui;

    int timerId;
    bool capturing;

    v4l2_device_t* device;

    int width, height;
    unsigned char *frame;
    unsigned char *rgbFrame;

    void displayImage(int width, int height, unsigned char *data);
};

#endif // CAMERADEMO_H
