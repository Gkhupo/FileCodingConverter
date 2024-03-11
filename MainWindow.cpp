#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindowClass())
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::initSystem()
{ }

void MainWindow::initUI()
{ }

void MainWindow::initConnect()
{ }
