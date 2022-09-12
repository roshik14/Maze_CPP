#ifndef SRC_COORDINATEPOINTS_H_
#define SRC_COORDINATEPOINTS_H_

#include <vector>

namespace s21 {
class CoordinatePoints;
}

class s21::CoordinatePoints {
    using Point = std::pair<int, int>;

public:
    CoordinatePoints() {}
    Point Start() const noexcept { return mazePath_[0]; }
    Point End() const noexcept { return mazePath_[1]; }
    int Count() const noexcept { return mazePath_.size(); }
    void Push(Point coordinate) {
        if (mazePath_.size() == 2) mazePath_.clear();
        mazePath_.push_back(coordinate);
    }

private:
    std::vector<Point> mazePath_;
};

#endif  // SRC_COORDINATEPOINTS_H_
