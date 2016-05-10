#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QtCore>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked() //Quit 按鍵
{
    close();
}

void MainWindow::on_pushButton_clicked() //開始遊戲 按鍵
{
    openNewWindow(); //遊戲畫面
    close();
}

void MainWindow::openNewWindow()
{
   mMyNewWindow = new newwindow();
   mMyNewWindow->setWindowTitle("Game");
   mMyNewWindow->show();
}
