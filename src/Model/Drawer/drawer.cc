#include "drawer.h"

using s21::Drawer;

void Drawer::InitPainter(QPainter* painter) {
    SetPenColorToPainer(painter, Qt::black);
    auto maxSizeForPainter = kMaxSize - 1;
    painter->drawLine(1, 1, 1, maxSizeForPainter);
    painter->drawLine(1, 1, maxSizeForPainter, 1);
    painter->drawLine(maxSizeForPainter, 1, maxSizeForPainter, maxSizeForPainter);
    painter->drawLine(1, maxSizeForPainter, maxSizeForPainter, maxSizeForPainter);
}

int Drawer::NormalizeSize(int value) { return kMaxSize / value; }

void Drawer::SetPenColorToPainer(QPainter* painter, const QBrush& brush) {
    painter->setPen(QPen(brush, 2, Qt::SolidLine, Qt::FlatCap));
}
