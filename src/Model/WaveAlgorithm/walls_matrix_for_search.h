#ifndef SRC_MODEL_WAVEALGORITHM_WALLS_MATRIX_FOR_SEARCH_H_
#define SRC_MODEL_WAVEALGORITHM_WALLS_MATRIX_FOR_SEARCH_H_

#include <cstddef>
#include <vector>

namespace s21 {
class WallsMatrixForSearch;
}

class s21::WallsMatrixForSearch final {
    using Vector = std::vector<int>;
    using Matrix = std::vector<Vector>;
    using TripleVector = std::vector<Matrix>;
    enum class Wall {
        kNone,
        kRight,
        kDown,
        kRightAndDown,
    };
    using WallsVector = std::vector<Wall>;
    using WallsMatrix = std::vector<WallsVector>;

public:
    explicit WallsMatrixForSearch(const TripleVector &labyrinthBorders);
    bool IsRightWall(int i, int j) const;
    bool IsLeftWall(int i, int j) const;
    bool IsUpWall(int i, int j) const;
    bool IsDownWall(int i, int j) const;
    int Rows() const;
    int Cols(int row) const;

private:
    void InitMatrix(int width, int height);
    void FillMatrixValues(const TripleVector &labyrinthBorders);
    Wall GetWallValueForMatrix(const TripleVector &labyrinthBorders, int i, int j) const;
    Wall EvaluateWallValue(int rightWall, int downWall) const;
    bool IsEmptyWallInLabyrinth(int rightWall, int downWall) const;
    bool IsRightWallInLabyrinth(int rightWall, int downWall) const;
    bool IsDownWallInLabyrinth(int rightWall, int downWall) const;

private:
    std::vector<std::vector<Wall>> matrix_;
};

#endif  // SRC_MODEL_WAVEALGORITHM_WALLS_MATRIX_FOR_SEARCH_H_
