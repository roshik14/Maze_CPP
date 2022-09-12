#include "searcher.h"

#include <iostream>

using s21::ElementCheckerForSearch;
using s21::WaveAlgorithm;

WaveAlgorithm::WaveAlgorithm(const TripleVector& labyrinthMatrix, const CoordinatePoints& coordinate)
    : wallsMatrix_(WallsMatrixForSearch(labyrinthMatrix)), coordinate_(coordinate) {}

WaveAlgorithm::PointContainer WaveAlgorithm::Execute() {
    if (wallsMatrix_.Rows() && PointsInRange()) {
        auto path = PathCreator(wallsMatrix_).Create(coordinate_);
        return PathRestorer(std::move(wallsMatrix_)).Restore(path, coordinate_);
    }
    return PointContainer{};
}

inline bool WaveAlgorithm::PointsInRange() {
    auto start = coordinate_.Start();
    auto end = coordinate_.End();
    return start.second < wallsMatrix_.Rows() && start.first < wallsMatrix_.Cols(0) &&
           end.second < wallsMatrix_.Rows() && end.first < wallsMatrix_.Cols(0);
}

bool ElementCheckerForSearch::IsNotLastELement(int index, int sz) { return index < sz - 1; }

bool ElementCheckerForSearch::IsNotFirstElement(int index) { return index > 0; }

bool ElementCheckerForSearch::EndPointNotFound(const std::vector<std::vector<int>>& matrix,
                                               std::pair<int, int> point) {
    return !matrix[point.second][point.first];
}
