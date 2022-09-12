#include "searcher.h"

using s21::WaveAlgorithm;

WaveAlgorithm::PathRestorer::PathRestorer(WallsMatrixForSearch&& wallsMatrix) noexcept
    : wallsMatrix_(std::move(wallsMatrix)) {}

WaveAlgorithm::PathRestorer::CheckCellData::CheckCellData(const Matrix& path, int i, int j, int rows,
                                                          int cols, int current)
    : path(path), i(i), j(j), rows(rows), cols(cols), current(current) {}

typename WaveAlgorithm::PathRestorer::PointContainer WaveAlgorithm::PathRestorer::Restore(
    const Matrix& path, const CoordinatePoints& coordinate) {
    auto start = coordinate.Start();
    auto end = coordinate.End();
    if (!ElementCheckerForSearch::EndPointNotFound(path, end)) {
        AddPointsToContainer(path, start, end);
    }
    AppendPoint(start.second, start.first);
    return points_;
}

void WaveAlgorithm::PathRestorer::AddPointsToContainer(const Matrix& path, Point start, Point end) {
    auto i = end.second;
    auto j = end.first;
    while (IsNotEqualStartPoint(path, i, j, start)) {
        CheckCellData checkData(path, i, j, path.size(), path[i].size(), path[i][j] - 1);
        if (IsThereWayToDownCell(checkData)) {
            AppendPoint(i, j);
            ++i;
        }
        if (IsThereWayToUpCell(checkData)) {
            AppendPoint(i, j);
            --i;
        }
        if (IsThereWayToLeftCell(checkData)) {
            AppendPoint(i, j);
            --j;
        }
        if (IsThereWayToRightCell(checkData)) {
            AppendPoint(i, j);
            ++j;
        }
    }
}

inline bool WaveAlgorithm::PathRestorer::IsThereWayToDownCell(const CheckCellData& data) const {
    return ElementCheckerForSearch::IsNotLastELement(data.i, data.rows) &&
           !wallsMatrix_.IsDownWall(data.i, data.j) &&
           CurrentEqualsNeighbor(data.path[data.i + 1][data.j], data.current);
}

inline bool WaveAlgorithm::PathRestorer::IsThereWayToUpCell(const CheckCellData& data) const {
    return ElementCheckerForSearch::IsNotFirstElement(data.i) && !wallsMatrix_.IsUpWall(data.i, data.j) &&
           CurrentEqualsNeighbor(data.path[data.i - 1][data.j], data.current);
}

inline bool WaveAlgorithm::PathRestorer::IsThereWayToLeftCell(const CheckCellData& data) const {
    return ElementCheckerForSearch::IsNotFirstElement(data.j) && !wallsMatrix_.IsLeftWall(data.i, data.j) &&
           CurrentEqualsNeighbor(data.path[data.i][data.j - 1], data.current);
}

inline bool WaveAlgorithm::PathRestorer::IsThereWayToRightCell(const CheckCellData& data) const {
    return ElementCheckerForSearch::IsNotLastELement(data.j, data.cols) &&
           !wallsMatrix_.IsRightWall(data.i, data.j) &&
           CurrentEqualsNeighbor(data.path[data.i][data.j + 1], data.current);
}

inline bool WaveAlgorithm::PathRestorer::IsNotEqualStartPoint(const Matrix& path, int i, int j,
                                                              Point start) const {
    return path[i][j] != path[start.second][start.first];
}

inline bool WaveAlgorithm::PathRestorer::CurrentEqualsNeighbor(int neighbor, int current) const {
    return neighbor == current;
}

void WaveAlgorithm::PathRestorer::AppendPoint(int first, int second) {
    points_.push_back(Point(first, second));
}
