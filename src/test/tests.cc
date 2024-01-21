#include <gtest/gtest.h>

#include <queue>

#include "../Maze/model/cave_model.h"
#include "../Maze/model/maze_model.h"
#include "../Maze/model/maze_solver.h"

bool isPath(s21::MazeModel &maze, int i1, int j1, int i2, int j2) {
  if (std::abs(i1 - i2) + std::abs(j1 - j2) != 1) {
    return false;
  }

  if (i1 == i2) {
    if (j1 < j2) {
      return maze.getVerticalWalls()[i1][j1] == 0;
    } else {
      return maze.getVerticalWalls()[i1][j2] == 0;
    }
  } else {
    if (i1 < i2) {
      return maze.getHorizontalWalls()[i1][j1] == 0;
    } else {
      return maze.getHorizontalWalls()[i2][j1] == 0;
    }
  }
}

bool dfs(s21::MazeModel &maze, int x, int y,
         std::vector<std::vector<bool>> &visited, int px, int py) {
  if (visited[x][y]) return true;

  visited[x][y] = true;
  std::vector<std::pair<int, int>> directions = {
      {0, 1}, {0, -1}, {1, 0}, {-1, 0}};

  for (const auto &dir : directions) {
    int nx = x + dir.first, ny = y + dir.second;

    if (nx >= 0 && nx < maze.getRows() && ny >= 0 && ny < maze.getCols() &&
        !(nx == px && ny == py) && isPath(maze, x, y, nx, ny)) {
      if (dfs(maze, nx, ny, visited, x, y)) return true;
    }
  }

  return false;
}

bool bfs(s21::MazeModel &maze, int startX, int startY) {
  std::queue<std::pair<int, int>> q;
  std::vector<std::vector<bool>> visited(
      maze.getRows(), std::vector<bool>(maze.getCols(), false));

  q.push({startX, startY});
  visited[startX][startY] = true;

  while (!q.empty()) {
    int x = q.front().first, y = q.front().second;
    q.pop();

    std::vector<std::pair<int, int>> directions = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    for (const auto &dir : directions) {
      int nx = x + dir.first, ny = y + dir.second;

      if (nx >= 0 && nx < maze.getRows() && ny >= 0 && ny < maze.getCols() &&
          !visited[nx][ny] && isPath(maze, x, y, nx, ny)) {
        visited[nx][ny] = true;
        q.push({nx, ny});
      }
    }
  }

  for (int i = 0; i < maze.getRows(); ++i) {
    for (int j = 0; j < maze.getCols(); ++j) {
      if (!visited[i][j]) return false;
    }
  }

  return true;
}

TEST(MazeModelTest, UniquePathsSquareMaze) {
  s21::MazeModel maze(10, 10);
  EXPECT_TRUE(bfs(maze, 0, 0));
}

TEST(MazeModelTest, UniquePathsNoSquareMaze) {
  s21::MazeModel maze(3, 6);
  EXPECT_TRUE(bfs(maze, 0, 0));
}

TEST(MazeModelTest, UniquePathsLargeSquareMaze) {
  s21::MazeModel maze(20, 20);
  EXPECT_TRUE(bfs(maze, 0, 0));
}

TEST(MazeModelTest, UniquePathsLargeNoSquareMaze) {
  s21::MazeModel maze(23, 20);
  EXPECT_TRUE(bfs(maze, 0, 0));
}

TEST(MazeModelTest, NoCyclesSquareMaze) {
  s21::MazeModel maze(10, 10);
  std::vector<std::vector<bool>> visited(10, std::vector<bool>(10, false));

  EXPECT_FALSE(dfs(maze, 0, 0, visited, -1, -1));
}

TEST(MazeModelTest, NoCyclesNoSquareMaze) {
  s21::MazeModel maze(4, 5);
  std::vector<std::vector<bool>> visited(10, std::vector<bool>(10, false));

  EXPECT_FALSE(dfs(maze, 0, 0, visited, -1, -1));
}

TEST(MazeModelTest, NoCyclesNoSquareLargeMaze) {
  s21::MazeModel maze(20, 20);
  std::vector<std::vector<bool>> visited(20, std::vector<bool>(20, false));

  EXPECT_FALSE(dfs(maze, 0, 0, visited, -1, -1));
}

TEST(MazeSolverTest, PathInMaze) {
  s21::MazeModel maze(10, 10);
  s21::MazeSolver solver(maze);
  auto path = solver.findPath({0, 0}, {9, 9});
  ASSERT_FALSE(path.empty());
  ASSERT_NE(path[0], s21::Point(-1, -1));
}

TEST(MazeSolverTest, PathInSmallMaze) {
  s21::MazeModel maze(2, 2);
  s21::MazeSolver solver(maze);
  auto path = solver.findPath({0, 0}, {1, 1});
  ASSERT_FALSE(path.empty());
  ASSERT_NE(path[0], s21::Point(-1, -1));
}

TEST(MazeSolverTest, PathInNoSquareMaze) {
  s21::MazeModel maze(10, 5);
  s21::MazeSolver solver(maze);
  auto path = solver.findPath({0, 0}, {1, 1});
  ASSERT_FALSE(path.empty());
  ASSERT_NE(path[0], s21::Point(-1, -1));
}

TEST(MazeSolverTest, PathInLargeManyVal) {
  s21::MazeModel maze(100, 100);
  s21::MazeSolver solver(maze);
  auto path = solver.findPath({0, 0}, {99, 99});
  ASSERT_FALSE(path.empty());
  ASSERT_NE(path[0], s21::Point(-1, -1));
}

TEST(MazeSolverTest, PathInMazeError) {
  s21::MazeModel maze(10, 10);
  s21::MazeSolver solver(maze);
  auto path = solver.findPath({0, 0}, {20, 9});
  ASSERT_EQ(path.size(), 1);
  ASSERT_EQ(path[0], s21::Point(-1, -1));
}

TEST(CaveModelTest, CountAliveNeighbors) {
  s21::CaveModel caveModel;

  std::ifstream inputFile("./data/cave_data.txt");
  if (inputFile.is_open()) {
    caveModel.loadCave(inputFile);
    inputFile.close();
  }

  EXPECT_EQ(caveModel.countAliveNeighbors(1, 1), 7);
  EXPECT_EQ(caveModel.countAliveNeighbors(2, 2), 3);
  EXPECT_EQ(caveModel.countAliveNeighbors(3, 3), 4);
}

TEST(CaveModelTest, PerformCellularAutomatonStep) {
  s21::CaveModel caveModel;

  std::ifstream inputFile("./data/cave_data.txt");
  if (inputFile.is_open()) {
    caveModel.loadCave(inputFile);
    inputFile.close();
  }

  std::vector<std::vector<int>> originalCave = caveModel.getCave();

  caveModel.performCellularAutomatonStep();

  EXPECT_NE(caveModel.getCave(), originalCave);

  for (int i = 1; i <= caveModel.getRows(); ++i) {
    for (int j = 1; j <= caveModel.getCols(); ++j) {
      int aliveNeighbors = caveModel.countAliveNeighbors(i, j);
      int cellValue = originalCave[i][j];

      if (cellValue == 1) {
        if (aliveNeighbors < caveModel.getCaveDeathLimit()) {
          EXPECT_EQ(caveModel.getCave()[i][j], 0);
        } else {
          EXPECT_EQ(caveModel.getCave()[i][j], 1);
        }
      } else {
        if (aliveNeighbors > caveModel.getCaveLifeLimit()) {
          EXPECT_EQ(caveModel.getCave()[i][j], 1);
        } else {
          EXPECT_EQ(caveModel.getCave()[i][j], 0);
        }
      }
    }
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
