#ifndef A1_MAZE_1_CAVE_MODEL_H
#define A1_MAZE_1_CAVE_MODEL_H

#include <fstream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {

class CaveModel {
 public:
  using Matrix = std::vector<std::vector<int>>;

  CaveModel(int n, int m, double lifeChance);
  CaveModel() = default;
  ~CaveModel() = default;

  void loadCave(std::ifstream& in);

  int getRows() const;
  int getCols() const;
  int getCaveDeathLimit() const;
  int getCaveLifeLimit() const;
  void setRows(int n);
  void setCols(int m);
  void setDeathLimit(int limit);
  void setLifeLimit(int limit);

  const Matrix& getCave() const { return Cave; }

  void performCellularAutomatonStep();

  int countAliveNeighbors(int x, int y) const;

 private:
  Matrix Cave;
  int cave_width_;
  int cave_height_;
  int cave_death_limit_;
  int cave_life_limit_;

  void GenerateCave(double chance);
  int GenerateCell(double chance);
};

}  // namespace s21

#endif  // A1_MAZE_1_CAVE_MODEL_H
