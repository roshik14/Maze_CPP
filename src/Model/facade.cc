#include "facade.h"

using s21::Facade;
using s21::LabyrinthDrawer;

Facade::Facade(QWidget* labyrinthDrawer, QWidget* caveDrawer)
    : labyrinthDrawer_(InitDrawer<LabyrinthDrawer>(labyrinthDrawer)),
      caveDrawer_(InitDrawer<CaveDrawer>(caveDrawer)),
      fileManager_(std::make_unique<FileManager>()),
      mazeGenerator_(std::make_unique<EllerAlgorithm>()),
      caveGenerator_(std::make_unique<CaveGenerator>()) {}

void Facade::GenerateMaze(int width, int height) {
    mazeGenerator_->setHeight(height);
    mazeGenerator_->setWidth(width);
    mazeGenerator_->generateLabyrinth();
    UpdateDrawerStateForMaze(mazeGenerator_->GetLabyrinth(), mazeGenerator_->GetWidth(),
                             mazeGenerator_->GetHeight());
}

void Facade::GenerateCave(const CaveData& caveData) {
    UpdateCaveGeneratorState(caveData);
    caveGenerator_->Generate();
    UpdateDrawerStateForCave(caveGenerator_->cave(), caveGenerator_->width(), caveGenerator_->height());
}

void Facade::CaveIterationStep(int birthLimit, int deathLimit) {
    caveGenerator_->setBirthLimit(birthLimit);
    caveGenerator_->setDeathLimit(deathLimit);
    caveGenerator_->StepIteration();
    UpdateDrawerStateForCave(caveGenerator_->cave(), caveGenerator_->width(), caveGenerator_->height());
}

void Facade::ReadLabyrinthFromFile(const std::string& fileName) {
    fileManager_->readLabyrinthFile(fileName);
    UpdateDrawerStateForMaze(fileManager_->walls(), fileManager_->width(), fileManager_->height());
}

void Facade::ReadCaveFromFile(const std::string& fileName) {
    fileManager_->readCaveFile(fileName);
    CaveData caveData{fileManager_->width(), fileManager_->height(), 0, 0, 50};
    UpdateCaveGeneratorState(caveData);
    caveGenerator_->LoadCave(fileManager_->cave());
    UpdateDrawerStateForCave(caveGenerator_->cave(), caveData.width, caveData.height);
}

void Facade::SaveLabyrinthFile(const std::string& fileName) {
    UpdateFileManagerState(labyrinthDrawer_->width(), labyrinthDrawer_->height());
    fileManager_->setWalls(labyrinthDrawer_->walls());
    fileManager_->writeLabyrinthFile(fileName);
}

void Facade::SaveCaveFile(const std::string& fileName) {
    UpdateFileManagerState(caveDrawer_->width(), caveDrawer_->height());
    fileManager_->setCave(caveDrawer_->cave());
    fileManager_->writeCaveFile(fileName);
}

void Facade::SearchWay(const CoordinatePoints& coordinate) {
    auto walls = labyrinthDrawer_->walls();
    auto points = std::make_unique<WaveAlgorithm>(walls, coordinate)->Execute();
    labyrinthDrawer_->SetPath(std::move(points));
    labyrinthDrawer_->EnableDrawerCase(Maze | Path);
}

void Facade::UpdateDrawerStateForMaze(TripleVector&& walls, int width, int height) noexcept {
    labyrinthDrawer_->EnableDrawerCase(Maze);
    labyrinthDrawer_->SetWalls(std::move(walls));
    labyrinthDrawer_->UpdateState(width, height);
}

void Facade::UpdateDrawerStateForCave(DoubleVector&& cave, int width, int height) noexcept {
    caveDrawer_->EnableDrawerCase(Cave);
    caveDrawer_->SetCave(std::move(cave));
    caveDrawer_->UpdateState(width, height);
}

void Facade::UpdateCaveGeneratorState(const CaveData& caveData) {
    caveGenerator_->setWidth(caveData.width);
    caveGenerator_->setHeight(caveData.height);
    caveGenerator_->setBirthLimit(caveData.birthLimit);
    caveGenerator_->setDeathLimit(caveData.deathLimit);
    caveGenerator_->setAliveChance(caveData.aliveChance);
}

inline void Facade::UpdateFileManagerState(int width, int height) {
    fileManager_->setWidth(width);
    fileManager_->setHeight(height);
}
