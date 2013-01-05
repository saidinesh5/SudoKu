#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHeaderView>
#include <sudokudelegate.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(0)
{
    ui->setupUi(this);
    connect(ui->resetButton,SIGNAL(clicked()),this, SLOT(resetGame()) );

    resetGame();

    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setResizeMode(QHeaderView::Stretch);
    //ui->tableView->setItemDelegate(new SudokuDelegate);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetGame()
{
    if(!model)
        delete model;
    model = new SudoKuModel();
    ui->tableView->setModel(model);
    connect(ui->solveButton,SIGNAL(clicked()),model,SLOT(solve()));
}
