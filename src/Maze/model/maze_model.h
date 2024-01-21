#ifndef A1_MAZE_1_MAZE_MODEL_H
#define A1_MAZE_1_MAZE_MODEL_H

#include <fstream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {

class MazeModel {
 public:
  using Matrix = std::vector<std::vector<int>>;

  MazeModel(int n, int m);
  MazeModel() = default;
  ~MazeModel() = default;

  void loadMaze(std::ifstream& in);
  const Matrix& getHorizontalWalls() const;
  const Matrix& getVerticalWalls() const;

  int getRows() const;
  int getCols() const;
  void setRows(int n);
  void setCols(int m);

 private:
  int n_, m_;
  Matrix horizontalWalls;
  Matrix verticalWalls;
  Matrix cellSets;

  void generateMaze();
  void fillEmptyValue();
  void createUniqueCellSets(int row);
  void unionSet(int row, int index, int element);
  void createVerticalWalls(int row);
  void createHorizontalWalls(int row);
  int countUniqueElementsInRow(int row, int element);
  void updateHorizontalWallsBasedOnCount(int row);
  int countHorizontalWallsForRowElement(int row, int element);
  void initializeNewLine(int row);
  void createEndLine();
  bool getRandomBoolean();
  void checkEndLine();
};

}  // namespace s21

#endif  // A1_MAZE_1_MAZE_MODEL_H
