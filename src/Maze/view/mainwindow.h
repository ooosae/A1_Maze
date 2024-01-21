#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QStandardPaths>
#include <QTimer>

#include "controller.h"
#include "my_widget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pushButton_3_clicked();
  void on_pushButton_4_clicked();
  void on_pushButton_2_clicked();
  void on_pushButton_5_clicked();
  void on_pushButton_clicked();
  void on_actionLoad_triggered();
  void on_actionLoad_2_triggered();

  void on_spinBox_5_valueChanged(int arg1);

  void on_spinBox_6_valueChanged(int arg1);

  void on_pushButton_6_clicked();

 private:
  bool STOP;
  QTimer *delayTimer;
  void DrawMaze();
  void DrawCave();
  void DrawPath();
  Ui::MainWindow *ui;
  Controller controller_;
  MyMazeWidget *myMazeWidget;
  MyCaveWidget *myCaveWidget;
};
#endif  // MAINWINDOW_H
