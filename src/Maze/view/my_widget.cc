#include "my_widget.h"

MyMazeWidget::MyMazeWidget(QWidget *parent) : QWidget(parent) {
  Maze = nullptr;
}

void MyMazeWidget::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);

  QPainter painter(this);
  QPen pen(QColor(211, 191, 222));
  pen.setWidth(2);
  painter.setPen(pen);
  painter.setBrush(Qt::white);

  if (Maze) {
    if (Maze->getRows() > Maze->getRows()) {
      stepX = (HEIGHT) / (Maze->getRows());
      stepY = stepX * Maze->getRows() / Maze->getRows();
    } else {
      stepY = (WIDTH) / (Maze->getRows());
      stepX = stepY * Maze->getRows() / Maze->getCols();
    }

    DrawField(painter);
    DrawMaze(painter);

    if (Path.size()) {
      QPen pen2(QColor(74, 70, 74));
      pen2.setWidth(2);
      painter.setPen(pen2);
      DrawPath(painter);
    }
  }
}

void MyMazeWidget::DrawHorizontal(QPainter &painter, int posX, int posY) {
  painter.drawLine(posX * stepX + 1, posY * stepY + 1, (posX + 1) * stepX + 1,
                   posY * stepY + 1);
}

void MyMazeWidget::DrawVertical(QPainter &painter, int posX, int posY) {
  painter.drawLine(posX * stepX + 1, posY * stepY + 1, posX * stepX + 1,
                   (posY + 1) * stepY + 1);
}

void MyMazeWidget::DrawField(QPainter &painter) {
  painter.drawRect(1, 1, WIDTH, HEIGHT);
}

void MyMazeWidget::DrawMaze(QPainter &painter) {
  for (int i = 0; i < Maze->getRows(); ++i)
    for (int j = 0; j < Maze->getCols(); ++j) {
      if (Maze->getHorizontalWalls()[i][j]) DrawHorizontal(painter, j, i + 1);

      if (Maze->getVerticalWalls()[i][j]) DrawVertical(painter, j + 1, i);
    }
}

void MyMazeWidget::DrawPath(QPainter &painter) {
  for (size_t i = 0; i < Path.size() - 1; ++i) {
    if (Path[i].x == Path[i + 1].x) {
      if (Path[i].y < Path[i + 1].y)
        painter.drawLine(
            (Path[i].y + 0.5) * stepX + 1, (Path[i].x + 0.5) * stepY + 1,
            (Path[i].y + 1.5) * stepX + 1, (Path[i].x + 0.5) * stepY + 1);
      else
        painter.drawLine(
            (Path[i].y + 0.5) * stepX + 1, (Path[i].x + 0.5) * stepY + 1,
            (Path[i].y + -0.5) * stepX + 1, (Path[i].x + 0.5) * stepY + 1);
    } else {
      if (Path[i].x < Path[i + 1].x)
        painter.drawLine(
            (Path[i].y + 0.5) * stepX + 1, (Path[i].x + 0.5) * stepY + 1,
            (Path[i].y + 0.5) * stepX + 1, (Path[i].x + 1.5) * stepY + 1);
      else
        painter.drawLine(
            (Path[i].y + 0.5) * stepX + 1, (Path[i].x + 0.5) * stepY + 1,
            (Path[i].y + 0.5) * stepX + 1, (Path[i].x + -0.5) * stepY + 1);
    }
  }
}

MyCaveWidget::MyCaveWidget(QWidget *parent) : QWidget(parent) {
  Cave = nullptr;
}

void MyCaveWidget::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  if (!Cave) return;

  QPainter painter(this);
  QPen pen(QColor(211, 191, 222));
  pen.setWidth(2);
  painter.setPen(pen);

  if (Cave->getRows() > Cave->getRows()) {
    stepX = (HEIGHT) / (Cave->getRows());
    stepY = stepX * Cave->getRows() / Cave->getRows();
  } else {
    stepY = (WIDTH) / (Cave->getRows());
    stepX = stepY * Cave->getRows() / Cave->getCols();
  }
  DrawField(painter);
  DrawCave(painter);
}

void MyCaveWidget::DrawField(QPainter &painter) {
  QRectF rectangle(0, 0, WIDTH, HEIGHT);
  painter.fillRect(rectangle, painter.brush());
}

void MyCaveWidget::DrawCave(QPainter &painter) {
  for (int i = 1; i <= Cave->getRows(); ++i)
    for (int j = 1; j <= Cave->getCols(); ++j)
      if (Cave->getCave()[i][j]) {
        QBrush brush(Qt::black);
        QRectF rectangle((j - 1) * stepX + 1, (i - 1) * stepY + 1, stepX,
                         stepY);
        painter.fillRect(rectangle, brush);
      }
}
