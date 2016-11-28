/**
 * Copyright (C) 2016 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#pragma once

#include <QtGlobal>
#include <QModelIndex>
#include <QSize>
#include <QPoint>
#include <QRect>
#include <QMargins>
#include <QDebug>

#include "../../global/coorinate.h"

class QFrame;
class CanvasViewHelper;

class CanvasViewPrivate
{
private:
    inline void updateCellMargins(const QSize &szItem, const QSize &szCell)
    {
        auto horizontalMargin = (szCell.width() - szItem.width());
        auto verticalMargin = (szCell.height() - szItem.height());
        auto leftMargin = horizontalMargin / 2;
        auto rightMargin = horizontalMargin - leftMargin;
        auto topMargin = verticalMargin / 2;
        auto bottom = verticalMargin - topMargin;

        cellMargins = QMargins(leftMargin, topMargin, rightMargin, bottom);
    }

public:
    CanvasViewPrivate();

    void updateCanvasSize(const QSize &szCanvas, const QMargins &geometryMargins, const QSize &szItem)
    {
        QMargins miniMargin(3, 3, 3, 3);
        auto miniCellWidth = szItem.width() + miniMargin.left() + miniMargin.right();
        colCount = szCanvas.width() / miniCellWidth;
        cellWidth = szCanvas.width() / colCount;

        auto miniCellHeigh = szItem.height() + miniMargin.top() + miniMargin.bottom();
        rowCount = szCanvas.height() / miniCellHeigh;
        cellHeight = szCanvas.height() / rowCount;

        updateCellMargins(szItem, QSize(cellWidth, cellHeight));

        auto horizontalMargin = (szCanvas.width() - cellWidth * colCount);
        auto verticalMargin = (szCanvas.height() - cellHeight * rowCount);
        auto leftMargin = horizontalMargin / 2;
        auto rightMargin = horizontalMargin - leftMargin;
        auto topMargin = verticalMargin / 2;
        auto bottom = verticalMargin - topMargin;

        viewMargins = geometryMargins + QMargins(leftMargin, topMargin, rightMargin, bottom);
    }

    Coordinate indexCoordinate(int index)
    {
        return Coordinate(index / rowCount, index % rowCount);
    }

    int coordinateIndex(Coordinate coord)
    {
        return coord.position().x() * rowCount + coord.position().y();
    }

    bool isVaildCoordinate(Coordinate coord)
    {
        return (coord.position().x() >= 0 && coord.position().x() < colCount)
               && (coord.position().y() >= 0 && coord.position().y() < rowCount);
    }
public:

    QMargins viewMargins;
    QMargins cellMargins;

    int rowCount;
    int colCount;
    int cellWidth;
    int cellHeight;

    QModelIndex         dragMoveHoverIndex;
    QModelIndex         lastCursorIndex;

    QPoint              lastPos;
    QFrame              *selectFrame = nullptr;
    QRect               selectRect;

    bool                mousePressed;

    QRect               canvasRect;
    CanvasViewHelper    *fileViewHelper = nullptr;
};