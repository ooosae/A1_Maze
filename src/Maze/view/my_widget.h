#ifndef MY_WIDGET_H
#define MY_WIDGET_H

#include <QDebug>
#include <QPainter>
#include <QWidget>
#include <cmath>

#include "cave_model.h"
#include "maze_solver.h"

#define HEIGHT 500.0
#define WIDTH 500.0

class MyMazeWidget : public QWidget {
  Q_OBJECT

 public:
  MyMazeWidget(QWidget *parent = nullptr);
  double stepX;
  double stepY;
  s21::MazeModel *Maze;
  std::vector<s21::Point> Path;

 protected:
  void paintEvent(QPaintEvent *event) override;
  void DrawField(QPainter &painter);
  void DrawMaze(QPainter &painter);
  void DrawPath(QPainter &painter);
  void DrawHorizontal(QPainter &painter, int posX, int posY);
  void DrawVertical(QPainter &painter, int posX, int posY);
};

class MyCaveWidget : public QWidget {
  Q_OBJECT

 public:
  MyCaveWidget(QWidget *parent = nullptr);
  double stepX;
  double stepY;
  s21::CaveModel *Cave;

 protected:
  void paintEvent(QPaintEvent *event) override;
  void DrawField(QPainter &painter);
  void DrawCave(QPainter &painter);
};

#endif  // MY_WIDGET_Hvv
