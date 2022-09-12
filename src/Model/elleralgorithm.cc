#include "elleralgorithm.h"

#include <random>

using s21::EllerAlgorithm;

EllerAlgorithm::EllerAlgorithm() : width(0), height(0) {}

void EllerAlgorithm::generateLabyrinth() {
    InitLabyrinthData();
    FillLabyrinthMatrixData();
}

void EllerAlgorithm::InitLabyrinthData() {
    row = std::vector<int>(width, 0);
    labyrinthMatrix_ = TripleVector(2);
    for (int i = 0; i < 2; ++i) {
        labyrinthMatrix_[i] = DoubleVector(height);
        for (int j = 0; j < height; ++j) {
            labyrinthMatrix_[i][j] = Vector(width);
        }
    }
}

void EllerAlgorithm::FillLabyrinthMatrixData() {
    int setNumber = 1;
    for (int i = 0; i < height; ++i) {
        AssignNewSet(&setNumber);
        CreateVerticalWallsInRow(i);
        if (i != height - 1) {
            CreateHorizontalWallsInRow(i);
        }
    }
    FinishLastRow();
}

void EllerAlgorithm::AssignNewSet(int *setNumber) {
    for (int j = 0; j < width; ++j) {
        if (row[j] == 0) {
            row[j] = *setNumber;
            *setNumber += 1;
        }
    }
}

void EllerAlgorithm::CreateVerticalWallsInRow(int index) {
    for (int j = 0; j < width - 1; ++j) {
        if (ThrowCoin() || row[j] == row[j + 1]) {
            labyrinthMatrix_[Right][index][j] = 1;
        } else {
            UniteSets(row[j], row[j + 1]);
        }
    }
    labyrinthMatrix_[Right][index][width - 1] = 1;
}

void EllerAlgorithm::CreateHorizontalWallsInRow(int index) {
    for (int j = 0; j < width; ++j) {
        if (ThrowCoin() && UniqueSetCount(row[j]) != 1) {
            labyrinthMatrix_[Lower][index][j] = 1;
            row[j] = 0;
        }
    }
}

void EllerAlgorithm::FinishLastRow() {
    for (int j = 0; j < width; ++j) {
        labyrinthMatrix_[Lower][height - 1][j] = 1;
        if (row[j] != row[j + 1]) {
            labyrinthMatrix_[Right][height - 1][j] = 0;
        }
        UniteSets(row[j], row[j + 1]);
    }
    labyrinthMatrix_[Right][height - 1][width - 1] = 1;
}

bool EllerAlgorithm::ThrowCoin() {
    std::random_device rd;
    return rd() % 2;
}

int EllerAlgorithm::UniqueSetCount(int number) {
    int count = 0;
    for (int i = 0; i < width; ++i) {
        if (row[i] == number) count++;
    }
    return count;
}

void EllerAlgorithm::UniteSets(int a, int b) {
    for (int i = 0; i < width; ++i) {
        if (row[i] == b) row[i] = a;
    }
}

void EllerAlgorithm::setWidth(int value) { width = value; }
void EllerAlgorithm::setHeight(int value) { height = value; }

s21::EllerAlgorithm::TripleVector EllerAlgorithm::GetLabyrinth() const noexcept { return labyrinthMatrix_; }

int EllerAlgorithm::GetWidth() const noexcept { return width; }

int EllerAlgorithm::GetHeight() const noexcept { return height; }
