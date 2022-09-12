#include <gtest/gtest.h>
#include "../Model/WaveAlgorithm/searcher.h"
#include "../Model/filemanager.h"
#include "../coordinatepoints.h"
#include <memory>

using s21::WaveAlgorithm;
using s21::FileManager;
using s21::CoordinatePoints;

bool isPointEqual(std::pair<int, int> p, int first, int second) {
    return p.first == first && p.second == second;
}

TEST(LabyrinthSearcherTest, test1) {
    auto fileManager = std::make_unique<FileManager>();
    fileManager->readLabyrinthFile("Tests/maze.txt");
    auto labyrinthMatrix = fileManager->walls();
    CoordinatePoints coordinate;
    std::pair<int, int> start {0, 0};
    std::pair<int, int> end = {3, 3};
    coordinate.Push(start);
    coordinate.Push(end);
    auto points = std::make_unique<WaveAlgorithm>(labyrinthMatrix, coordinate)->Execute();
    ASSERT_PRED3(isPointEqual, points[0], 3, 3);
    ASSERT_PRED3(isPointEqual, points[1], 3, 2);
    ASSERT_PRED3(isPointEqual, points[2], 2, 2);
    ASSERT_PRED3(isPointEqual, points[3], 2, 3);
    ASSERT_PRED3(isPointEqual, points[4], 1, 3);
    ASSERT_PRED3(isPointEqual, points[5], 0, 3);
    ASSERT_PRED3(isPointEqual, points[6], 0, 2);
    ASSERT_PRED3(isPointEqual, points[7], 0, 1);
    ASSERT_PRED3(isPointEqual, points[8], 0, 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

