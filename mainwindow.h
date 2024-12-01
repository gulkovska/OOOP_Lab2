#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "eventinputwindow.h"
#include "simulationwindow.h"
#include "visualizationwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openEventInput();
    void openSimulation();
    void openVisualization();

private:
    Ui::MainWindow *ui;
    EventInputWindow *eventInputWindow;
    SimulationWindow *simulationWindow;
    VisualizationWindow *visualizationWindow;
};

#endif // MAINWINDOW_H
