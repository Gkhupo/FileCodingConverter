#pragma once

#include <QMainWindow>
#include "publicFunc.h"
#include "ui_MainWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowClass; };
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private:
	void initSystem();

	void initUI();

	void initConnect();



private:
	Ui::MainWindowClass* ui;
};
