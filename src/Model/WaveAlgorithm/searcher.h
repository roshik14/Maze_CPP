#ifndef SRC_MODEL_WAVEALGORITHM_SEARCHER_H_
#define SRC_MODEL_WAVEALGORITHM_SEARCHER_H_
#include <vector>

#include "../../coordinatepoints.h"
#include "walls_matrix_for_search.h"

namespace s21 {
class Searcher;
class WaveAlgorithm;
struct ElementCheckerForSearch;
}  // namespace s21

class s21::Searcher {
    using Point = std::pair<int, int>;
    using PointContainer = std::vector<Point>;

public:
    virtual PointContainer Execute() = 0;
};

class s21::WaveAlgorithm final : public Searcher {
    using Point = std::pair<int, int>;
    using PointContainer = std::vector<Point>;
    using Vector = std::vector<int>;
    using Matrix = std::vector<Vector>;
    using TripleVector = std::vector<Matrix>;

public:
    WaveAlgorithm(const TripleVector& labyrinthMatrix, const CoordinatePoints& coordinate);
    PointContainer Execute() override;

private:
    void AddPointToPath(PointContainer* points, int row, int col);
    bool PointsInRange();

private:
    class PathCreator;
    class PathRestorer;
    WallsMatrixForSearch wallsMatrix_;
    Matrix pathMatrix_;
    CoordinatePoints coordinate_;
};

class s21::WaveAlgorithm::PathCreator final {
    using Vector = std::vector<int>;
    using Matrix = std::vector<Vector>;
    using WallChecker = bool (WallsMatrixForSearch::*)(int, int) const;

public:
    explicit PathCreator(const WallsMatrixForSearch& wallsMatrix);
    Matrix Create(const CoordinatePoints& coordinate);

private:
    Matrix InitPathMatrix();
    bool IsLessThanSize(int value) const;
    void FillPathValues(int value);
    bool ElementNotMarked(int value) const;
    void UpdateNeighborsValues(int i, int j, int rows, int cols, int value);
    void UpdateDownNeighborValue(int i, int j, int value);
    void UpdateLeftNeighborValue(int i, int j, int value);
    void UpdateUpNeighborValue(int i, int j, int value);
    void UpdateRightNeighborValue(int i, int j, int value);
    bool ShouldUpdateCell(int elementValue, int i, int j, const WallChecker isWall) const;

private:
    const WallsMatrixForSearch wallsMatrix_;
    Matrix path_;
};

class s21::WaveAlgorithm::PathRestorer final {
    using Vector = std::vector<int>;
    using Matrix = std::vector<Vector>;
    using Point = std::pair<int, int>;
    using PointContainer = std::vector<Point>;
    struct CheckCellData {
        CheckCellData(const Matrix& path, int i, int j, int rows, int cols, int current);
        const Matrix& path;
        int i;
        int j;
        int rows;
        int cols;
        int current;
    };

public:
    explicit PathRestorer(WallsMatrixForSearch&& wallsMatrix) noexcept;
    PointContainer Restore(const Matrix& path, const CoordinatePoints& coordinate);

private:
    void AddPointsToContainer(const Matrix& path, Point start, Point end);
    void AppendPoint(int first, int second);
    bool IsNotEqualStartPoint(const Matrix& path, int i, int j, Point start) const;
    bool CurrentEqualsNeighbor(int neighbor, int current) const;
    bool IsThereWayToDownCell(const CheckCellData& data) const;
    bool IsThereWayToUpCell(const CheckCellData& data) const;
    bool IsThereWayToLeftCell(const CheckCellData& data) const;
    bool IsThereWayToRightCell(const CheckCellData& data) const;

private:
    WallsMatrixForSearch wallsMatrix_;
    PointContainer points_;
};

struct s21::ElementCheckerForSearch {
    static bool IsNotLastELement(int index, int sz);
    static bool IsNotFirstElement(int index);
    static bool EndPointNotFound(const std::vector<std::vector<int>>& matrix, std::pair<int, int> point);
};

#endif  // SRC_MODEL_WAVEALGORITHM_SEARCHER_H_
