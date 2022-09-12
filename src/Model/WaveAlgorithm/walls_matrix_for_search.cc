#include "walls_matrix_for_search.h"

using s21::WallsMatrixForSearch;

s21::WallsMatrixForSearch::WallsMatrixForSearch(const TripleVector &labyrinthBorders) {
    if (labyrinthBorders.size() && labyrinthBorders[0].size()) {
        int width = labyrinthBorders[0].size();
        int height = labyrinthBorders[0][0].size();
        InitMatrix(width, height);
        FillMatrixValues(labyrinthBorders);
    }
}

void WallsMatrixForSearch::InitMatrix(int width, int height) {
    for (int i = 0; i != width; ++i) {
        auto innerVector = WallsVector(height);
        matrix_.push_back(std::move(innerVector));
    }
}

void WallsMatrixForSearch::FillMatrixValues(const TripleVector &labyrinthBorders) {
    for (int i = 0, rows = matrix_.size(); i != rows; ++i) {
        for (int j = 0, cols = matrix_[i].size(); j != cols; ++j) {
            matrix_[i][j] = GetWallValueForMatrix(labyrinthBorders, i, j);
        }
    }
}

inline typename WallsMatrixForSearch::Wall WallsMatrixForSearch::GetWallValueForMatrix(
    const TripleVector &labyrinthMatrix, int i, int j) const {
    auto rightWallValue = labyrinthMatrix[0][i][j];
    auto downWallValue = labyrinthMatrix[1][i][j];
    return EvaluateWallValue(rightWallValue, downWallValue);
}

inline typename WallsMatrixForSearch::Wall WallsMatrixForSearch::EvaluateWallValue(int rightWall,
                                                                                   int downWall) const {
    if (IsEmptyWallInLabyrinth(rightWall, downWall)) return Wall::kNone;
    if (IsRightWallInLabyrinth(rightWall, downWall)) return Wall::kRight;
    if (IsDownWallInLabyrinth(rightWall, downWall)) return Wall::kDown;
    return Wall::kRightAndDown;
}

inline bool WallsMatrixForSearch::IsEmptyWallInLabyrinth(int rightWall, int downWall) const {
    return !rightWall && !downWall;
}

inline bool WallsMatrixForSearch::IsRightWallInLabyrinth(int rightWall, int downWall) const {
    return rightWall && !downWall;
}

inline bool WallsMatrixForSearch::IsDownWallInLabyrinth(int rightWall, int downWall) const {
    return !rightWall && downWall;
}

bool WallsMatrixForSearch::IsRightWall(int i, int j) const {
    return matrix_[i][j] == Wall::kRight || matrix_[i][j] == Wall::kRightAndDown;
}

bool WallsMatrixForSearch::IsLeftWall(int i, int j) const {
    return matrix_[i][j - 1] == Wall::kRight || matrix_[i][j - 1] == Wall::kRightAndDown;
}

bool WallsMatrixForSearch::IsUpWall(int i, int j) const {
    return matrix_[i - 1][j] == Wall::kDown || matrix_[i - 1][j] == Wall::kRightAndDown;
}

bool WallsMatrixForSearch::IsDownWall(int i, int j) const {
    return matrix_[i][j] == Wall::kDown || matrix_[i][j] == Wall::kRightAndDown;
}

int WallsMatrixForSearch::Rows() const { return matrix_.size(); }

int WallsMatrixForSearch::Cols(int row) const { return matrix_[row].size(); }
