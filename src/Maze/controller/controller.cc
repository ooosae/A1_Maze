#include "controller.h"

void Controller::loadMaze(std::ifstream& in) { Maze.loadMaze(in); }

void Controller::loadCave(std::ifstream& in) { Cave.loadCave(in); }
