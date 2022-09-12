#include "cave_generator.h"

#include <random>

namespace s21 {
CaveGenerator::DoubleVector CaveGenerator::cave() const noexcept { return matrix_; }

int CaveGenerator::width() const noexcept { return width_; }

int CaveGenerator::height() const noexcept { return height_; }

int CaveGenerator::birthLimit() const noexcept { return birth_limit_; }

int CaveGenerator::deathLimit() const noexcept { return death_limit_; }

unsigned CaveGenerator::aliveChance() const noexcept { return this->aliveChance_; }

void CaveGenerator::Generate() {
    DoubleVector temp = DoubleVector(height_);
    std::random_device rd;
    for (int i = 0; i < height_; ++i) {
        temp[i] = Vector(width_);
        for (int j = 0; j < width_; ++j) {
            if (rd() % 101 > this->aliveChance_) {
                temp[i][j] = 1;
            } else {
                temp[i][j] = 0;
            }
        }
    }
    matrix_ = std::move(temp);
}

void CaveGenerator::StepIteration() {
    DoubleVector temp = DoubleVector(height_);
    for (int i = 0; i < height_; ++i) {
        temp[i] = Vector(width_);
        for (int j = 0; j < width_; ++j) {
            temp[i][j] = matrix_[i][j];
            int alive = count_neighboors(i, j);
            if (matrix_[i][j] && alive < death_limit_) {
                temp[i][j] = 0;
            } else if (!matrix_[i][j] && alive > birth_limit_) {
                temp[i][j] = 1;
            }
        }
    }
    matrix_ = std::move(temp);
}

void CaveGenerator::LoadCave(DoubleVector&& cave) noexcept { matrix_ = std::move(cave); }

int CaveGenerator::count_neighboors(const int& row, const int& col) const {
    int res = 0;
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            if (i || j) {
                res += matrix_[(row + i + height_) % height_][(col + j + width_) % width_];
            }
        }
    }
    return res;
}
};  // namespace s21
