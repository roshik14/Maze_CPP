#include "filemanager.h"

using s21::FileManager;

FileManager::FileManager() : width_(0), height_(0) {}

void FileManager::readLabyrinthFile(const std::string& filename) {
    inputFile.open(filename);
    if (inputFile.is_open()) {
        clearParameters();
        initMazeVectors();
        inputFile.close();
    }
}

void FileManager::initMazeVectors() {
    inputFile >> width_ >> height_;
    if (width_ > 0 && height_ > 0) {
        walls_ = TripleVector(2);
        for (int i = 0; i < 2; ++i) {
            walls_[i] = DoubleVector(height_);
            for (int j = 0; j < height_; ++j) {
                walls_[i][j] = Vector(width_);
                for (int k = 0; k < width_; ++k) {
                    inputFile >> walls_[i][j][k];
                }
            }
        }
    }
}

void FileManager::readCaveFile(const std::string& filename) {
    inputFile.open(filename);
    if (inputFile.is_open()) {
        clearParameters();
        initCaveVectors();
        inputFile.close();
    }
}

void FileManager::initCaveVectors() {
    inputFile >> height_ >> width_;
    if (width_ > 0 && height_ > 0) {
        cave_ = DoubleVector(height_);
        for (int i = 0; i < height_; ++i) {
            cave_[i] = Vector(width_);
            for (int j = 0; j < width_; ++j) {
                inputFile >> cave_[i][j];
            }
        }
    }
}

void FileManager::clearParameters() {
    width_ = height_ = 0;
    walls_.clear();
    cave_.clear();
}

void FileManager::writeLabyrinthFile(const std::string& filename) {
    outputFile.open(filename);
    if (outputFile.is_open()) {
        outputFile << width_ << " " << height_ << std::endl;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < height_; ++j) {
                for (int k = 0; k < width_; ++k) {
                    outputFile << walls_[i][j][k] << " ";
                }
                outputFile << std::endl;
            }
            outputFile << std::endl;
        }
        outputFile.close();
    }
}

void FileManager::writeCaveFile(const std::string& filename) {
    outputFile.open(filename);
    if (outputFile.is_open()) {
        outputFile << width_ << " " << height_ << std::endl << std::endl;
        for (int i = 0; i < height_; ++i) {
            for (int j = 0; j < width_; ++j) {
                outputFile << cave_[i][j] << " ";
            }
            outputFile << std::endl;
        }
        outputFile.close();
    }
}

// Setters
void FileManager::setWidth(int value) { width_ = value; }
void FileManager::setHeight(int value) { height_ = value; }
void FileManager::setWalls(TripleVector&& value) noexcept { walls_ = std::move(value); }
void FileManager::setCave(DoubleVector&& value) noexcept { cave_ = std::move(value); }

// Getters
int FileManager::width() { return width_; }
int FileManager::height() { return height_; }
FileManager::TripleVector FileManager::walls() { return walls_; }
FileManager::DoubleVector FileManager::cave() { return cave_; }
