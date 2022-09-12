#ifndef SRC_MODEL_FACADE_H_
#define SRC_MODEL_FACADE_H_

#include <QWidget>
#include <memory>

#include "../coordinatepoints.h"
#include "../useful_structs.h"
#include "Drawer/drawer.h"
#include "WaveAlgorithm/searcher.h"
#include "cave_generator.h"
#include "elleralgorithm.h"
#include "filemanager.h"

namespace s21 {
class Facade;
}

class s21::Facade {
public:
    using TripleVector = std::vector<std::vector<std::vector<int>>>;
    using DoubleVector = std::vector<std::vector<int>>;

    explicit Facade(QWidget* labyrinthDrawer, QWidget* caveDrawer);
    void GenerateMaze(int widht, int height);
    void GenerateCave(const CaveData& caveData);
    void CaveIterationStep(int birthLimit, int deathLimit);
    void ReadLabyrinthFromFile(const std::string& fileName);
    void ReadCaveFromFile(const std::string& fileName);
    void SaveLabyrinthFile(const std::string& fileName);
    void SaveCaveFile(const std::string& fileName);
    void SearchWay(const CoordinatePoints& coordinate);

private:
    template <typename T>
    T* InitDrawer(QWidget* drawer);
    void UpdateDrawerStateForMaze(TripleVector&& walls, int width, int height) noexcept;
    void UpdateDrawerStateForCave(DoubleVector&& cave, int width, int height) noexcept;
    void UpdateCaveGeneratorState(const CaveData& caveData);
    void UpdateFileManagerState(int width, int height);

private:
    LabyrinthDrawer* labyrinthDrawer_;
    CaveDrawer* caveDrawer_;
    std::unique_ptr<FileManager> fileManager_;
    std::unique_ptr<EllerAlgorithm> mazeGenerator_;
    std::unique_ptr<CaveGenerator> caveGenerator_;
};

template <typename T>
T* s21::Facade::InitDrawer(QWidget* drawer) {
    return static_cast<T*>(drawer);
}

#endif  // SRC_MODEL_FACADE_H_
