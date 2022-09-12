#include <gtest/gtest.h>

#include "../Model/cave_generator.h"
#include "../Model/filemanager.h"

TEST(CaveGeneratorTests, test1) {
    s21::FileManager fm;
    fm.readCaveFile("Tests/cave.txt");
    s21::CaveGenerator::DoubleVector cave = fm.cave();
    int cave_width = fm.width();
    int cave_height = fm.height();
    s21::CaveGenerator cg;
    cg.LoadCave(std::move(cave));
    cg.setWidth(cave_width);
    cg.setHeight(cave_height);
    cg.setBirthLimit(6);
    cg.setDeathLimit(1);
    ASSERT_EQ(cave_width, cg.width());
    ASSERT_EQ(cave_height, cg.height());
    ASSERT_EQ(6, cg.birthLimit());
    ASSERT_EQ(1, cg.deathLimit());
    for (int i = 0; i < 10; ++i) {
        cg.StepIteration();
    }
    fm.readCaveFile("Tests/cave_result.txt");
    s21::CaveGenerator::DoubleVector cave_result = fm.cave();
    ASSERT_EQ(cg.cave(), cave_result);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
