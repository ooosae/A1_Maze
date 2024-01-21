#include "cave_model.h"

#include <iostream>
#include <random>

namespace s21 {

CaveModel::CaveModel(int n, int m, double lifeChance)
    : cave_height_(n), cave_width_(m) {
  Cave = Matrix(n + 2, std::vector<int>(m + 2, 1));
  GenerateCave(lifeChance);
}

void CaveModel::GenerateCave(double chance) {
  for (int i = 1; i <= cave_height_; ++i) {
    for (int j = 1; j <= cave_width_; ++j) {
      Cave[i][j] = GenerateCell(chance);
    }
  }
}

int CaveModel::GenerateCell(double chance) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, 1.0);

  return (dis(gen) < chance) ? 1 : 0;
}

int CaveModel::getRows() const { return cave_height_; }

int CaveModel::getCols() const { return cave_width_; }

int CaveModel::getCaveDeathLimit() const { return cave_death_limit_; }

int CaveModel::getCaveLifeLimit() const { return cave_life_limit_; }

void CaveModel::setRows(int n) { cave_height_ = n; }

void CaveModel::setCols(int m) { cave_width_ = m; }

void CaveModel::setDeathLimit(int limit) { cave_death_limit_ = limit; }

void CaveModel::setLifeLimit(int limit) { cave_life_limit_ = limit; }

void CaveModel::performCellularAutomatonStep() {
  Matrix newCave = Cave;

  for (int i = 1; i <= cave_height_; ++i) {
    for (int j = 1; j <= cave_width_; ++j) {
      int aliveNeighbors = countAliveNeighbors(i, j);

      if (Cave[i][j] == 1) {
        if (aliveNeighbors < cave_death_limit_) {
          newCave[i][j] = 0;
        }
      } else {
        if (aliveNeighbors > cave_life_limit_) {
          newCave[i][j] = 1;
        }
      }
    }
  }

  Cave = newCave;
}

int CaveModel::countAliveNeighbors(int x, int y) const {
  int aliveNeighbors = 0;

  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      if (i == 0 && j == 0) continue;
      int neighborX = x + i;
      int neighborY = y + j;

      aliveNeighbors += Cave[neighborX][neighborY];
    }
  }

  return aliveNeighbors;
}

void CaveModel::loadCave(std::ifstream& in) {
  Cave.clear();
  std::string line;
  std::getline(in, line);
  std::istringstream iss(line);
  iss >> cave_height_ >> cave_width_;
  Cave.push_back(std::vector<int>(cave_width_ + 2, 1));
  for (int i = 1; i < cave_height_ + 1; ++i) {
    std::getline(in, line);
    std::istringstream iss(line);
    Cave.push_back(std::vector<int>());
    Cave[i].push_back(1);
    for (int j = 0; j < cave_width_; ++j) {
      int num;
      iss >> num;
      Cave[i].push_back(num);
    }
    Cave[i].push_back(1);
  }
  Cave.push_back(std::vector<int>(cave_width_ + 2, 1));
}

}  // namespace s21
