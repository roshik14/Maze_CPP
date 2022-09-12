#include "searcher.h"

using s21::WaveAlgorithm;

WaveAlgorithm::PathCreator::PathCreator(const WallsMatrixForSearch& wallsMatrix)
    : wallsMatrix_(wallsMatrix), path_(InitPathMatrix()) {}

WaveAlgorithm::PathCreator::Matrix WaveAlgorithm::PathCreator::Create(const CoordinatePoints& coordinate) {
    path_ = InitPathMatrix();
    int wave = 1;
    auto start = coordinate.Start();
    auto end = coordinate.End();
    path_[start.second][start.first] = wave;
    while (IsLessThanSize(wave) && ElementCheckerForSearch::EndPointNotFound(path_, end)) {
        FillPathValues(wave);
        ++wave;
    }
    return path_;
}

typename WaveAlgorithm::PathCreator::Matrix WaveAlgorithm::PathCreator::InitPathMatrix() {
    Matrix pathMatrix;
    for (size_t i = 0, iSize = wallsMatrix_.Rows(); i != iSize; ++i) {
        pathMatrix.push_back(Vector(wallsMatrix_.Cols(i), 0));
    }
    return pathMatrix;
}

inline bool WaveAlgorithm::PathCreator::IsLessThanSize(int value) const {
    int sz = path_.size() * path_[0].size();
    return value < sz;
}

void WaveAlgorithm::PathCreator::FillPathValues(int value) {
    for (int i = 0, rows = path_.size(); i != rows; ++i) {
        for (int j = 0, cols = path_[i].size(); j != cols; ++j) {
            if (path_[i][j] == value) {
                UpdateNeighborsValues(i, j, rows, cols, value + 1);
            }
        }
    }
}

void WaveAlgorithm::PathCreator::UpdateNeighborsValues(int i, int j, int rows, int cols, int value) {
    if (ElementCheckerForSearch::IsNotLastELement(i, rows)) UpdateDownNeighborValue(i, j, value);

    if (ElementCheckerForSearch::IsNotFirstElement(j)) UpdateLeftNeighborValue(i, j, value);

    if (ElementCheckerForSearch::IsNotFirstElement(i)) UpdateUpNeighborValue(i, j, value);

    if (ElementCheckerForSearch::IsNotLastELement(j, cols)) UpdateRightNeighborValue(i, j, value);
}

void WaveAlgorithm::PathCreator::UpdateDownNeighborValue(int i, int j, int value) {
    int& downValueRef = path_[i + 1][j];
    if (ShouldUpdateCell(downValueRef, i, j, &WallsMatrixForSearch::IsDownWall)) downValueRef = value;
}

void WaveAlgorithm::PathCreator::UpdateUpNeighborValue(int i, int j, int value) {
    int& upValueRef = path_[i - 1][j];
    if (ShouldUpdateCell(upValueRef, i, j, &WallsMatrixForSearch::IsUpWall)) upValueRef = value;
}

void WaveAlgorithm::PathCreator::UpdateLeftNeighborValue(int i, int j, int value) {
    int& leftValueRef = path_[i][j - 1];
    if (ShouldUpdateCell(leftValueRef, i, j, &WallsMatrixForSearch::IsLeftWall)) leftValueRef = value;
}

void WaveAlgorithm::PathCreator::UpdateRightNeighborValue(int i, int j, int value) {
    int& rightValueRef = path_[i][j + 1];
    if (ShouldUpdateCell(rightValueRef, i, j, &WallsMatrixForSearch::IsRightWall)) rightValueRef = value;
}

inline bool WaveAlgorithm::PathCreator::ShouldUpdateCell(int elementValue, int i, int j,
                                                         const WallChecker isWall) const {
    return !((wallsMatrix_.*isWall)(i, j)) && ElementNotMarked(elementValue);
}

inline bool WaveAlgorithm::PathCreator::ElementNotMarked(int value) const { return !value; }
