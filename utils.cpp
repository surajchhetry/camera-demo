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

#include "utils.h"

QImage colorToQImage(int width, int height, unsigned char* data) {
    QImage qImage(data, width, height, QImage::Format_RGB888);
    return qImage;
}

QImage grayscaleToQImage(int width, int height, unsigned char* data) {
    QImage qImage(data, width, height, QImage::Format_Indexed8);

    QVector<QRgb> colorTable;

    for (int i = 0; i < 256; i++) {
        colorTable.push_back(qRgb(i, i, i));
    }

    qImage.setColorTable(colorTable);

    return qImage;
}
