#include "maze_model.h"

#include <iostream>

namespace s21 {

MazeModel::MazeModel(int n, int m) : n_(n), m_(m) {
  cellSets = Matrix(n, std::vector<int>(m, -1));
  horizontalWalls = Matrix(n, std::vector<int>(m, 1));
  verticalWalls = Matrix(n, std::vector<int>(m, 1));
  generateMaze();
}

const MazeModel::Matrix& MazeModel::getHorizontalWalls() const {
  return horizontalWalls;
}

const MazeModel::Matrix& MazeModel::getVerticalWalls() const {
  return verticalWalls;
}

int MazeModel::getRows() const { return n_; }

int MazeModel::getCols() const { return m_; }

void MazeModel::setRows(int n) { n_ = n; }

void MazeModel::setCols(int m) { m_ = m; }

void MazeModel::loadMaze(std::ifstream& in) {
  std::string line;
  std::getline(in, line);
  std::istringstream iss(line);
  iss >> n_ >> m_;

  horizontalWalls.clear();
  verticalWalls.clear();

  for (int i = 0; i < n_; ++i) {
    std::getline(in, line);
    std::istringstream is(line);
    verticalWalls.push_back(std::vector<int>());
    for (int j = 0; j < m_; ++j) {
      int num;

      is >> num;
      verticalWalls[i].push_back(num);
    }
  }
  std::getline(in, line);
  for (int i = 0; i < n_; ++i) {
    std::getline(in, line);
    std::istringstream is(line);
    horizontalWalls.push_back(std::vector<int>());
    for (int j = 0; j < m_; ++j) {
      int num;
      is >> num;
      horizontalWalls[i].push_back(num);
    }
  }
}

void MazeModel::generateMaze() {
  fillEmptyValue();
  for (int j = 0; j < n_ - 1; j++) {
    createUniqueCellSets(j);
    createVerticalWalls(j);
    createHorizontalWalls(j);
    updateHorizontalWallsBasedOnCount(j);
    initializeNewLine(j);
  }
  createEndLine();
}

void MazeModel::fillEmptyValue() {
  for (int i = 0; i < n_; i++) {
    std::fill(horizontalWalls[i].begin(), horizontalWalls[i].end(), 0);
  }

  for (int i = 0; i < n_; i++) {
    std::fill(verticalWalls[i].begin(), verticalWalls[i].end(), 0);
  }

  for (int i = 0; i < n_; i++) {
    std::fill(cellSets[i].begin(), cellSets[i].end(), -1);
  }
}

void MazeModel::createUniqueCellSets(int row) {
  static int setID = 0;
  for (int j = 0; j < m_; j++) {
    if (cellSets[row][j] == -1) {
      cellSets[row][j] = setID++;
    }
  }
}

void MazeModel::createVerticalWalls(int row) {
  for (int i = 0; i < m_ - 1; i++) {
    bool shouldAddWalls = getRandomBoolean();

    if (shouldAddWalls || cellSets[row][i] == cellSets[row][i + 1]) {
      verticalWalls[row][i] = 1;
    } else {
      unionSet(row, i, cellSets[row][i]);
    }
  }
  verticalWalls[row][m_ - 1] = 1;
}

void MazeModel::unionSet(int row, int index, int element) {
  int mutableSet = cellSets[row][index + 1];
  for (int j = 0; j < m_; j++) {
    if (cellSets[row][j] == mutableSet) {
      cellSets[row][j] = element;
    }
  }
}

void MazeModel::createHorizontalWalls(int row) {
  for (int j = 0; j < m_; j++) {
    bool shouldAddWalls = getRandomBoolean();

    if (countUniqueElementsInRow(row, cellSets[row][j]) > 1 && shouldAddWalls) {
      horizontalWalls[row][j] = 1;
    }
  }
}

int MazeModel::countUniqueElementsInRow(int row, int element) {
  int countUniqSet = 0;
  for (int j = 0; j < m_; j++) {
    if (cellSets[row][j] == element) {
      countUniqSet++;
    }
  }
  return countUniqSet;
}

void MazeModel::updateHorizontalWallsBasedOnCount(int row) {
  for (int j = 0; j < m_; j++) {
    if (countHorizontalWallsForRowElement(row, cellSets[row][j]) == 0) {
      horizontalWalls[row][j] = 0;
    }
  }
}

int MazeModel::countHorizontalWallsForRowElement(int row, int element) {
  int countHorizontalWalls = 0;
  for (int j = 0; j < m_; j++) {
    if (cellSets[row][j] == element && horizontalWalls[row][j] == 0) {
      countHorizontalWalls++;
    }
  }
  return countHorizontalWalls;
}

void MazeModel::initializeNewLine(int row) {
  for (int j = 0; j < m_; j++) {
    if (horizontalWalls[row][j] == 1) {
      cellSets[row + 1][j] = -1;
    } else {
      cellSets[row + 1][j] = cellSets[row][j];
    }

    verticalWalls[row + 1][j] = 0;
    horizontalWalls[row + 1][j] = 0;
  }
}

void MazeModel::createEndLine() {
  createUniqueCellSets(n_ - 1);
  createVerticalWalls(n_ - 1);
  checkEndLine();
}

void MazeModel::checkEndLine() {
  int lastRow = n_ - 1;
  for (int j = 0; j < m_ - 1; j++) {
    if (cellSets[lastRow][j] != cellSets[lastRow][j + 1]) {
      verticalWalls[lastRow][j] = 0;
      unionSet(lastRow, j, cellSets[lastRow][j]);
    }
  }

  for (int j = 0; j < m_; j++) {
    horizontalWalls[lastRow][j] = 1;
  }
}

bool MazeModel::getRandomBoolean() {
  static std::random_device rd;
  static std::mt19937 generator(rd());
  static std::uniform_int_distribution<> distribution(0, 1);

  return distribution(generator) == 1;
}

}  // namespace s21
