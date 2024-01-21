#ifndef A1_MAZE_1_MAZE_SOLVER_H
#define A1_MAZE_1_MAZE_SOLVER_H

#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

#include "maze_model.h"

namespace s21 {

struct Point {
  int x, y;
  Point() : x(0), y(0) {}
  Point(int x, int y) : x(x), y(y) {}

  bool operator==(const Point& other) const;
  bool operator!=(const Point& other) const;
};

class MazeSolver {
 public:
  using PointsVector = std::vector<Point>;

  MazeSolver(const MazeModel& maze) : maze_(maze) {}
  PointsVector findPath(Point start, Point end);

 private:
  const MazeModel& maze_;
  PointsVector getNeighbors(const Point& point);
  PointsVector buildPathFromEnd(Point start, Point end,
                                const std::unordered_map<int, Point>& prev);
};

}  // namespace s21

#endif  // A1_MAZE_1_MAZE_SOLVER_H
