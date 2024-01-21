#include "maze_solver.h"

namespace s21 {

bool Point::operator==(const Point& other) const {
  return x == other.x && y == other.y;
}

bool Point::operator!=(const Point& other) const { return !(*this == other); }

MazeSolver::PointsVector MazeSolver::findPath(Point start, Point end) {
  if (start == end) {
    return {start};
  }

  std::queue<Point> pointsQueue;
  std::unordered_map<int, Point> prev;
  std::vector<std::vector<bool>> visited(
      maze_.getRows(), std::vector<bool>(maze_.getCols(), false));

  pointsQueue.push(start);
  visited[start.x][start.y] = true;

  while (!pointsQueue.empty()) {
    Point current = pointsQueue.front();
    pointsQueue.pop();

    if (current == end) {
      return buildPathFromEnd(start, end, prev);
    }

    for (const Point& neighbor : getNeighbors(current)) {
      if (!visited[neighbor.x][neighbor.y]) {
        pointsQueue.push(neighbor);
        visited[neighbor.x][neighbor.y] = true;
        prev[neighbor.x * maze_.getCols() + neighbor.y] = current;
      }
    }
  }

  return std::vector<Point>({Point(-1, -1)});
}

MazeSolver::PointsVector MazeSolver::getNeighbors(const Point& point) {
  std::vector<Point> neighbors;
  const auto& horizontalWalls = maze_.getHorizontalWalls();
  const auto& verticalWalls = maze_.getVerticalWalls();

  if (point.x > 0 && horizontalWalls[point.x - 1][point.y] == 0) {
    neighbors.push_back(Point(point.x - 1, point.y));
  }

  if (point.x < maze_.getRows() - 1 && horizontalWalls[point.x][point.y] == 0) {
    neighbors.push_back(Point(point.x + 1, point.y));
  }

  if (point.y > 0 && verticalWalls[point.x][point.y - 1] == 0) {
    neighbors.push_back(Point(point.x, point.y - 1));
  }

  if (point.y < maze_.getCols() - 1 && verticalWalls[point.x][point.y] == 0) {
    neighbors.push_back(Point(point.x, point.y + 1));
  }

  return neighbors;
}

MazeSolver::PointsVector MazeSolver::buildPathFromEnd(
    Point start, Point end, const std::unordered_map<int, Point>& prev) {
  std::vector<Point> path;
  for (Point at = end; at != start;
       at = prev.at(at.x * maze_.getCols() + at.y)) {
    path.push_back(at);
  }
  path.push_back(start);
  std::reverse(path.begin(), path.end());
  return path;
}

}  // namespace s21
