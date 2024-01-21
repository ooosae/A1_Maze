#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QString>
#include <vector>

#include "cave_model.h"
#include "maze_solver.h"
#include "point.h"

class Controller {
 public:
  s21::MazeModel Maze;
  Point mazeStartPoint;
  Point mazeEndPoint;
  std::vector<s21::Point> Path;

  QString mazeFileName;
  void loadMaze(std::ifstream& in);

  s21::CaveModel Cave;

  QString caveFileName;
  void loadCave(std::ifstream& in);
};

#endif  // CONTROLLER_H
