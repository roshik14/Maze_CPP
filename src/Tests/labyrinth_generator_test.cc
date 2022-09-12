#include <gtest/gtest.h>
#include "../Model/elleralgorithm.h"
#include <memory>

using Matrix = std::vector<std::vector<int>>;
using TripleVector = std::vector<Matrix>;
using s21::EllerAlgorithm;

bool isElement(int a) {
    return a == 1 || a == 0;
}

void TestLabyrinthMatrix(const TripleVector& labyrinthMatrix) {
    for (int i = 0, sz = labyrinthMatrix.size(); i != sz; ++i) {
        for (int j = 0, rows = labyrinthMatrix[i].size(); j != rows; ++j) {
            for (int k = 0, cols = labyrinthMatrix[i][j].size(); k != cols; ++k) {
                ASSERT_PRED1(isElement, labyrinthMatrix[i][j][k]);
            }
        }
    }
}

TEST(LabyrinthGeneratorTest, test1) {
    auto generator = std::make_unique<EllerAlgorithm>();
    auto width = 4;
    auto height = 4;
    generator->setWidth(width);
    generator->setHeight(height);
    generator->generateLabyrinth();
    auto labyrinthMatrix = generator->GetLabyrinth();
    TestLabyrinthMatrix(labyrinthMatrix);
    ASSERT_EQ(labyrinthMatrix[0].size(), height);
    ASSERT_EQ(labyrinthMatrix[1].size(), height);
    ASSERT_EQ(labyrinthMatrix[0][0].size(), width);
    ASSERT_EQ(labyrinthMatrix[1][0].size(), width);
}

TEST(LabyrinthGeneratorTest, test2) {
    auto generator = std::make_unique<EllerAlgorithm>();
    auto width = 50;
    auto height = 50;
    generator->setWidth(width);
    generator->setHeight(height);
    generator->generateLabyrinth();
    auto labyrinthMatrix = generator->GetLabyrinth();
    TestLabyrinthMatrix(labyrinthMatrix);
    ASSERT_EQ(labyrinthMatrix[0].size(), height);
    ASSERT_EQ(labyrinthMatrix[1].size(), height);
    ASSERT_EQ(labyrinthMatrix[0][0].size(), width);
    ASSERT_EQ(labyrinthMatrix[1][0].size(), width);
}

TEST(LabyrinthGeneratorTest, test3) {
    auto generator = std::make_unique<EllerAlgorithm>();
    auto width = 35;
    auto height = 15;
    generator->setWidth(width);
    generator->setHeight(height);
    generator->generateLabyrinth();
    auto labyrinthMatrix = generator->GetLabyrinth();
    TestLabyrinthMatrix(labyrinthMatrix);
    ASSERT_EQ(labyrinthMatrix[0].size(), height);
    ASSERT_EQ(labyrinthMatrix[1].size(), height);
    ASSERT_EQ(labyrinthMatrix[0][0].size(), width);
    ASSERT_EQ(labyrinthMatrix[1][0].size(), width);
}

TEST(LabyrinthGeneratorTest, test4) {
    auto generator = std::make_unique<EllerAlgorithm>();
    auto width = 28;
    auto height = 49;
    generator->setWidth(width);
    generator->setHeight(height);
    generator->generateLabyrinth();
    auto labyrinthMatrix = generator->GetLabyrinth();
    TestLabyrinthMatrix(labyrinthMatrix);
    ASSERT_EQ(labyrinthMatrix[0].size(), height);
    ASSERT_EQ(labyrinthMatrix[1].size(), height);
    ASSERT_EQ(labyrinthMatrix[0][0].size(), width);
    ASSERT_EQ(labyrinthMatrix[1][0].size(), width);
}

TEST(LabyrinthGeneratorTest, test5) {
    auto generator = std::make_unique<EllerAlgorithm>();
    auto width = 1;
    auto height = 1;
    generator->setWidth(width);
    generator->setHeight(height);
    generator->generateLabyrinth();
    auto labyrinthMatrix = generator->GetLabyrinth();
    TestLabyrinthMatrix(labyrinthMatrix);
    ASSERT_EQ(labyrinthMatrix[0].size(), height);
    ASSERT_EQ(labyrinthMatrix[1].size(), height);
    ASSERT_EQ(labyrinthMatrix[0][0].size(), width);
    ASSERT_EQ(labyrinthMatrix[1][0].size(), width);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
