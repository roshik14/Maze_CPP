#include "controller.h"

using s21::Controller;

Controller::Controller(QWidget *labyrinthDrawer, QWidget *caveDrawer)
    : facade_(std::make_unique<Facade>(labyrinthDrawer, caveDrawer)) {}

void Controller::GenerateMaze(int width, int height) { facade_->GenerateMaze(width, height); }

void Controller::GenerateCave(const CaveData &caveData) { facade_->GenerateCave(caveData); }

void Controller::ReadLabyrinthFromFile(const std::string &fileName) {
    facade_->ReadLabyrinthFromFile(fileName);
}

void Controller::ReadCaveFromFile(const std::string &fileName) { facade_->ReadCaveFromFile(fileName); }

void Controller::CaveIterationStep(int birthLimit, int deathLimit) {
    facade_->CaveIterationStep(birthLimit, deathLimit);
}

void Controller::SaveLabyrinthFile(const std::string &fileName) { facade_->SaveLabyrinthFile(fileName); }

void Controller::SaveCaveFile(const std::string &fileName) { facade_->SaveCaveFile(fileName); }

void Controller::SearchWay(const CoordinatePoints &coordinate) { facade_->SearchWay(coordinate); }
