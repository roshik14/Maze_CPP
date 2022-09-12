#include "drawer.h"

using s21::CaveDrawer;

CaveDrawer::CaveDrawer(QWidget *parent) : QWidget{parent}, width_(1), height_(1) {
    cellWidth_ = NormalizeSize(width_);
    cellHeight_ = NormalizeSize(height_);
}

void CaveDrawer::DrawCave(QPainter *painter) {
    if (drawCaveFlag) {
        if (!cave_.empty()) {
            for (int i = 0; i < height_; ++i) {
                for (int j = 0; j < width_; ++j) {
                    if (cave_[i][j]) {
                        painter->fillRect(j * cellWidth_, i * cellHeight_, cellWidth_, cellHeight_,
                                          Qt::black);
                    }
                }
            }
        }
    }
}

void CaveDrawer::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    InitPainter(&painter);
    DrawCave(&painter);
}

void CaveDrawer::SetCave(DoubleVector &&value) { cave_ = std::move(value); }

void CaveDrawer::SetWidth(int value) {
    width_ = value;
    cellWidth_ = NormalizeSize(width_);
}

void CaveDrawer::SetHeight(int value) {
    height_ = value;
    cellHeight_ = NormalizeSize(height_);
}

void CaveDrawer::EnableDrawerCase(char key) { drawCaveFlag = key & Cave; }

void CaveDrawer::UpdateState(int width, int height) {
    SetWidth(width);
    SetHeight(height);
    update();
}

s21::CaveDrawer::DoubleVector CaveDrawer::cave() const noexcept { return cave_; }

int CaveDrawer::width() const noexcept { return width_; }

int CaveDrawer::height() const noexcept { return height_; }
