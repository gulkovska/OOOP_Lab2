#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , eventInputWindow(new EventInputWindow(this))
    , simulationWindow(new SimulationWindow(this))
    , visualizationWindow(new VisualizationWindow(this))
{
    ui->setupUi(this);

    connect(eventInputWindow, &EventInputWindow::eventsReady,
                     simulationWindow, &SimulationWindow::setEventsAndProbabilities);
    connect(simulationWindow, &SimulationWindow::resultsReady,
            visualizationWindow, &VisualizationWindow::setSimulationResults);

    // Кнопки для переходу між вікнами
    connect(ui->btnEventInput, &QPushButton::clicked, this, &MainWindow::openEventInput);
    connect(ui->btnSimulation, &QPushButton::clicked, this, &MainWindow::openSimulation);
    connect(ui->btnVisualization, &QPushButton::clicked, this, &MainWindow::openVisualization);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openEventInput() {
    eventInputWindow->show();
}

void MainWindow::openSimulation() {
    simulationWindow->show();
}

void MainWindow::openVisualization() {
    visualizationWindow->show();
}
