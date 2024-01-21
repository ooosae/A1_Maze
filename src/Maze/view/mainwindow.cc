#include "mainwindow.h"

#include <QTimer>

#include "my_widget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  myMazeWidget = new MyMazeWidget(this);
  QVBoxLayout *layout = new QVBoxLayout(ui->widget);
  layout->addWidget(myMazeWidget);

  myCaveWidget = new MyCaveWidget(this);
  QVBoxLayout *layout_2 = new QVBoxLayout(ui->widget_2);
  layout_2->addWidget(myCaveWidget);

  STOP = true;
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::DrawMaze() {
  myMazeWidget->Maze = &controller_.Maze;
  myMazeWidget->Path = {};
  myMazeWidget->update();
}

void MainWindow::DrawCave() {
  myCaveWidget->Cave = &controller_.Cave;
  myCaveWidget->update();
}

void MainWindow::DrawPath() {
  myMazeWidget->Path = controller_.Path;
  myMazeWidget->update();
}

void MainWindow::on_pushButton_3_clicked() {
  controller_.Maze.setRows(ui->spinBox->value());
  controller_.Maze.setCols(ui->spinBox_2->value());

  s21::MazeModel newMaze(controller_.Maze.getRows(),
                         controller_.Maze.getCols());
  controller_.Maze = newMaze;
  DrawMaze();
}

void MainWindow::on_pushButton_4_clicked() {
  s21::MazeSolver mazeSolver(controller_.Maze);
  s21::Point startP(ui->spinBox_3->value() - 1, ui->spinBox_8->value() - 1);
  s21::Point endP(ui->spinBox_4->value() - 1, ui->spinBox_9->value() - 1);
  controller_.Path = mazeSolver.findPath(startP, endP);
  if (controller_.Path[0].x < 0)
    QMessageBox::critical(this, "no path", "no path");
  else
    DrawPath();
}

void MainWindow::on_pushButton_2_clicked() {
  if (!STOP) {
    delayTimer->stop();
    delayTimer->deleteLater();
  }
  STOP = false;
  delayTimer = new QTimer(this);
  connect(delayTimer, &QTimer::timeout, this, [=]() {
    controller_.Cave.performCellularAutomatonStep();
    DrawCave();

    if (STOP) {
      delayTimer->stop();
      delayTimer->deleteLater();
    }
  });

  delayTimer->setInterval(ui->spinBox_7->value());
  delayTimer->start();
}

void MainWindow::on_pushButton_5_clicked() { STOP = true; }

void MainWindow::on_pushButton_clicked() {
  controller_.Cave.performCellularAutomatonStep();
  DrawCave();
}

void MainWindow::on_actionLoad_triggered() {
  controller_.mazeFileName = QFileDialog::getOpenFileName(
      this, "Select txt file", QDir::homePath(), "*.txt");
  if (controller_.mazeFileName.isEmpty()) {
    QMessageBox::critical(this, "cannot open file", "cannot open file");
  } else {
    std::string str = controller_.mazeFileName.toStdString();
    const char *p = str.c_str();
    std::ifstream fin(p);
    controller_.loadMaze(fin);

    ui->spinBox->setValue(controller_.Maze.getRows());
    ui->spinBox_2->setValue(controller_.Maze.getCols());
  }
  DrawMaze();
}

void MainWindow::on_actionLoad_2_triggered() {
  controller_.caveFileName = QFileDialog::getOpenFileName(
      this, "Select txt file", QDir::homePath(), "*.txt");
  if (controller_.caveFileName.isEmpty()) {
    QMessageBox::critical(this, "cannot open file", "cannot open file");
  } else {
    std::string str = controller_.caveFileName.toStdString();
    const char *p = str.c_str();
    std::ifstream fin(p);
    controller_.loadCave(fin);
  }
  controller_.Cave.setDeathLimit(ui->spinBox_5->value());
  controller_.Cave.setLifeLimit(ui->spinBox_6->value());
  DrawCave();
}

void MainWindow::on_spinBox_5_valueChanged(int arg1) {
  controller_.Cave.setDeathLimit(arg1);
}

void MainWindow::on_spinBox_6_valueChanged(int arg1) {
  controller_.Cave.setLifeLimit(arg1);
}

void MainWindow::on_pushButton_6_clicked() {
  controller_.Cave.setRows(ui->spinBox_11->value());
  controller_.Cave.setCols(ui->spinBox_10->value());
  s21::CaveModel newCave(controller_.Cave.getRows(), controller_.Cave.getCols(),
                         ui->doubleSpinBox->value());
  controller_.Cave = newCave;
  controller_.Cave.setDeathLimit(ui->spinBox_5->value());
  controller_.Cave.setLifeLimit(ui->spinBox_6->value());
  DrawCave();
}
