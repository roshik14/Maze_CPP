#include "drawer.h"

using s21::LabyrinthDrawer;

LabyrinthDrawer::LabyrinthDrawer(QWidget *parent) : QWidget{parent}, width_(1), height_(1) {
    cellWidth_ = NormalizeSize(width_);
    cellHeight_ = NormalizeSize(height_);
}

void LabyrinthDrawer::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    InitPainter(&painter);
    DrawMaze(&painter);
    DrawStartPoint(&painter);
    DrawPath(&painter);
}

void LabyrinthDrawer::DrawMaze(QPainter *painter) {
    if (drawMazeFlag) {
        if (!walls_.empty()) {
            for (int i = 0; i < height_; ++i) {
                for (int j = 0; j < width_; ++j) {
                    if (walls_[0][i][j]) DrawVerticalWall(painter, j, i);
                    if (walls_[1][i][j]) DrawHorizontalWall(painter, j, i);
                }
            }
        }
    }
}

void LabyrinthDrawer::DrawVerticalWall(QPainter *painter, int x, int y) {
    painter->drawLine(x * cellWidth_ + cellWidth_, y * cellHeight_, x * cellWidth_ + cellWidth_,
                      y * cellHeight_ + cellHeight_);
}

void LabyrinthDrawer::DrawHorizontalWall(QPainter *painter, int x, int y) {
    painter->drawLine(x * cellWidth_, y * cellHeight_ + cellHeight_, x * cellWidth_ + cellWidth_,
                      y * cellHeight_ + cellHeight_);
}

void LabyrinthDrawer::DrawStartPoint(QPainter *painter) {
    SetPenColorToPainer(painter, Qt::red);
    if (coordinate.Count() && drawPointsFlag) {
        painter->drawEllipse(coordinate.Start().first * cellWidth_ + cellWidth_ / 2 - 1,
                             coordinate.Start().second * cellHeight_ + cellHeight_ / 2 - 1, 2, 2);
    }
}

void LabyrinthDrawer::DrawPathLine(QPainter *painter, std::pair<int, int> first, std::pair<int, int> second) {
    painter->drawLine(first.second * cellWidth_ + cellWidth_ / 2, first.first * cellHeight_ + cellHeight_ / 2,
                      second.second * cellWidth_ + cellWidth_ / 2,
                      second.first * cellHeight_ + cellHeight_ / 2);
}

void LabyrinthDrawer::DrawPath(QPainter *painter) {
    SetPenColorToPainer(painter, Qt::red);
    if (drawPathFlag) {
        if (!mazePath_.empty()) {
            auto prevCell = mazePath_.begin();
            for (auto curCell = mazePath_.begin(); curCell != mazePath_.end(); ++curCell) {
                DrawPathLine(painter, *prevCell, *curCell);
                prevCell = curCell;
            }
        }
    }
}

void LabyrinthDrawer::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        auto pos = event->position().toPoint();
        int cellWidth = NormalizeSize(width_);
        int cellHeight = NormalizeSize(height_);

        int x = pos.x() / cellWidth;
        int y = pos.y() / cellHeight;

        coordinate.Push({x, y});
        EnableDrawerCase(Points | Maze);
        if (coordinate.Count() == 2) {
            emit findPath(coordinate);
        }
    }
    update();
}

void LabyrinthDrawer::SetWidth(int value) {
    width_ = value;
    cellWidth_ = NormalizeSize(width_);
}

void LabyrinthDrawer::SetHeight(int value) {
    height_ = value;
    cellHeight_ = NormalizeSize(height_);
}

void LabyrinthDrawer::SetWalls(TripleVector &&walls) noexcept { walls_ = std::move(walls); }

void LabyrinthDrawer::SetPath(PointContainer &&path) noexcept { mazePath_ = std::move(path); }

void LabyrinthDrawer::EnableDrawerCase(char key) {
    drawMazeFlag = key & Maze;
    drawPathFlag = key & Path;
    drawPointsFlag = key & Points;
}

void LabyrinthDrawer::UpdateState(int width, int height) {
    SetWidth(width);
    SetHeight(height);
    update();
}

s21::LabyrinthDrawer::TripleVector LabyrinthDrawer::walls() const noexcept { return walls_; }

int LabyrinthDrawer::width() const noexcept { return width_; }

int LabyrinthDrawer::height() const noexcept { return height_; }
