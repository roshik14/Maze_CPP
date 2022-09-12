#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

namespace s21 {
class Controller;
}

#include <QWidget>

#include "../Model/facade.h"
#include "../coordinatepoints.h"
#include "../useful_structs.h"

class s21::Controller {
    using TripleVector = std::vector<std::vector<std::vector<int>>>;

public:
    explicit Controller(QWidget *labyrinthDrawer, QWidget *caveDrawer);
    void GenerateMaze(int width, int height);
    void GenerateCave(const CaveData &caveData);
    void SearchWay(const CoordinatePoints &coordinate);
    void ReadLabyrinthFromFile(const std::string &fileName);
    void ReadCaveFromFile(const std::string &fileName);
    void CaveIterationStep(int birthLimit, int deathLimit);
    void SaveLabyrinthFile(const std::string &fileName);
    void SaveCaveFile(const std::string &fileName);

private:
    std::unique_ptr<Facade> facade_;
};

#endif  // SRC_CONTROLLER_CONTROLLER_H_
