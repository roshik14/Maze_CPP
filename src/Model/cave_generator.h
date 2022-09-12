#ifndef SRC_MODEL_CAVE_GENERATOR_H_
#define SRC_MODEL_CAVE_GENERATOR_H_

#include <vector>

namespace s21 {
class CaveGenerator {
public:
    using DoubleVector = std::vector<std::vector<int>>;
    using Vector = std::vector<int>;
    explicit CaveGenerator(const int& birth = 3, const int& death = 2, const int& width = 4,
                           const int& height = 4)
        : birth_limit_(birth), death_limit_(death), width_(width), height_(height), aliveChance_(0) {}
    ~CaveGenerator() {}

    void setBirthLimit(int birth_limit) { birth_limit_ = birth_limit; }
    void setDeathLimit(int death_limit) { death_limit_ = death_limit; }
    void setWidth(int width) { width_ = width; }
    void setHeight(int height) { height_ = height; }
    void setAliveChance(unsigned aliveChance) { this->aliveChance_ = aliveChance; }
    void Generate();
    void StepIteration();
    void LoadCave(DoubleVector&& cave) noexcept;

    DoubleVector cave() const noexcept;
    int width() const noexcept;
    int height() const noexcept;
    int birthLimit() const noexcept;
    int deathLimit() const noexcept;
    unsigned aliveChance() const noexcept;

private:
    int count_neighboors(const int&, const int&) const;

private:
    DoubleVector matrix_;
    int birth_limit_;
    int death_limit_;
    int width_;
    int height_;
    unsigned aliveChance_;
};
};  // namespace s21

#endif  // SRC_MODEL_CAVE_GENERATOR_H_
