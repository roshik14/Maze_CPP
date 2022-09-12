#ifndef SRC_MODEL_DRAWER_DRAWER_H_
#define SRC_MODEL_DRAWER_DRAWER_H_

#include <QMouseEvent>
#include <QPainter>
#include <QWidget>
#include <fstream>
#include <vector>

#include "../../coordinatepoints.h"

namespace s21 {

enum DrawerCase { Maze = 1, Path = 2, Cave = 4, Points = 8 };

class Drawer {
public:
    virtual void SetWidth(int value) = 0;
    virtual void SetHeight(int value) = 0;
    virtual void EnableDrawerCase(char key) = 0;
    virtual void UpdateState(int width, int height) = 0;
    virtual int width() const noexcept = 0;
    virtual int height() const noexcept = 0;
    virtual ~Drawer() {}

protected:
    void InitPainter(QPainter *painter);
    int NormalizeSize(int value);
    void SetPenColorToPainer(QPainter *painter, const QBrush &brush);
    int cellWidth_, cellHeight_;

private:
    const int kMaxSize = 500;
};

class LabyrinthDrawer final : public QWidget, public Drawer {
    Q_OBJECT
    using Vector = std::vector<int>;
    using DoubleVector = std::vector<Vector>;
    using TripleVector = std::vector<DoubleVector>;
    using Point = std::pair<int, int>;
    using PointContainer = std::vector<Point>;

public:
    explicit LabyrinthDrawer(QWidget *parent = nullptr);
    void SetWidth(int value) override;
    void SetHeight(int value) override;
    void SetWalls(TripleVector &&value) noexcept;
    void SetPath(PointContainer &&path) noexcept;
    void EnableDrawerCase(char key) override;
    void UpdateState(int width, int height) override;

    TripleVector walls() const noexcept;
    int width() const noexcept override;
    int height() const noexcept override;

private:
    void DrawMaze(QPainter *painter);
    void DrawPath(QPainter *painter);
    void DrawStartPoint(QPainter *painter);
    void DrawVerticalWall(QPainter *painter, int x, int y);
    void DrawHorizontalWall(QPainter *painter, int x, int y);
    void DrawPathLine(QPainter *painter, std::pair<int, int> first, std::pair<int, int> second);
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void findPath(const CoordinatePoints &coordinate);

private:
    bool drawPathFlag = false, drawMazeFlag = false, drawPointsFlag = false;
    int width_, height_;
    PointContainer mazePath_;
    CoordinatePoints coordinate;
    TripleVector walls_;
};

class CaveDrawer final : public QWidget, public Drawer {
    Q_OBJECT
    using DoubleVector = std::vector<std::vector<int>>;

public:
    explicit CaveDrawer(QWidget *parent = nullptr);
    void SetWidth(int value) override;
    void SetHeight(int value) override;
    void EnableDrawerCase(char key) override;
    void UpdateState(int width, int height) override;
    void SetCave(DoubleVector &&value);

    DoubleVector cave() const noexcept;
    int width() const noexcept override;
    int height() const noexcept override;

private:
    void DrawCave(QPainter *painter);
    void paintEvent(QPaintEvent *event) override;

private:
    int width_, height_;
    bool drawCaveFlag = false;
    DoubleVector cave_;
};

}  // namespace s21

#endif  // SRC_MODEL_DRAWER_DRAWER_H_
