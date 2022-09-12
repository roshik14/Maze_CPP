#ifndef SRC_MODEL_ELLERALGORITHM_H_
#define SRC_MODEL_ELLERALGORITHM_H_

#include <vector>

namespace s21 {

enum WallType { Right = 0, Lower };

class EllerAlgorithm {
public:
    using Vector = std::vector<int>;
    using DoubleVector = std::vector<Vector>;
    using TripleVector = std::vector<DoubleVector>;

    EllerAlgorithm();
    void generateLabyrinth();
    void setWidth(int value);
    void setHeight(int value);

    TripleVector GetLabyrinth() const noexcept;
    int GetWidth() const noexcept;
    int GetHeight() const noexcept;

private:
    void InitLabyrinthData();
    void FillLabyrinthMatrixData();
    void AssignNewSet(int *setNumber);
    void CreateVerticalWallsInRow(int index);
    void CreateHorizontalWallsInRow(int index);
    void FinishLastRow();
    bool ThrowCoin();
    void UniteSets(int a, int b);
    int UniqueSetCount(int number);

private:
    std::vector<int> row;
    int width, height;
    TripleVector labyrinthMatrix_;
};

}  // namespace s21
#endif  // SRC_MODEL_ELLERALGORITHM_H_
