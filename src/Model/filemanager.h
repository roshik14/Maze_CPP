#ifndef SRC_MODEL_FILEMANAGER_H_
#define SRC_MODEL_FILEMANAGER_H_

#include <fstream>
#include <vector>

namespace s21 {
class FileManager;
}

class s21::FileManager {
public:
    using TripleVector = std::vector<std::vector<std::vector<int>>>;
    using DoubleVector = std::vector<std::vector<int>>;
    using Vector = std::vector<int>;

    FileManager();
    void writeLabyrinthFile(const std::string &filename);
    void readLabyrinthFile(const std::string &filename);

    void writeCaveFile(const std::string &filename);
    void readCaveFile(const std::string &filename);

    // Setters
    void setWidth(int value);
    void setHeight(int value);
    void setWalls(TripleVector &&value) noexcept;
    void setCave(DoubleVector &&value) noexcept;

    // Getters
    int width();
    int height();
    TripleVector walls();
    DoubleVector cave();

private:
    void initMazeVectors();
    void initCaveVectors();
    void clearParameters();

    int width_, height_;

    std::ifstream inputFile;
    std::ofstream outputFile;

    TripleVector walls_;
    DoubleVector cave_;
};

#endif  // SRC_MODEL_FILEMANAGER_H_
