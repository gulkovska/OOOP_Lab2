#include "simulationwindow.h"
#include "ui_simulationwindow.h"
#include <QRandomGenerator>
#include <QMessageBox>

SimulationWindow::SimulationWindow(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::SimulationWindow)
{
    ui->setupUi(this);
    ui->resultsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // Підключення кнопки "Запуск симуляції"
    connect(ui->btnStartSimulation, &QPushButton::clicked, this, &SimulationWindow::startSimulation);
}

SimulationWindow::~SimulationWindow()
{
    delete ui;
}

void SimulationWindow::setEventsAndProbabilities(const QList<QString> &events, const QList<double> &probabilities)
{
    this->events = events;
    this->probabilities = probabilities;
}

void SimulationWindow::startSimulation()
{
    // Очищення попередніх результатів
    ui->resultsTable->setRowCount(0);
    results.clear();

    // Перевірка введених даних
    int simulationCount = ui->simulationCountSpinBox->value();
    if (events.isEmpty() || probabilities.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Список подій порожній або не задано ймовірностей.");
        return;
    }

    // Запуск симуляції
    simulateEvents(simulationCount);

    // Відображення результатів
    for (int i = 0; i < results.size(); ++i) {
        int row = ui->resultsTable->rowCount();
        ui->resultsTable->insertRow(row);
        ui->resultsTable->setItem(row, 0, new QTableWidgetItem(QString::number(i + 1)));
        ui->resultsTable->setItem(row, 1, new QTableWidgetItem(results[i]));
    }

    emit resultsReady(results);
}

void SimulationWindow::simulateEvents(int simulationCount)
{
    // Генерація подій на основі ймовірностей
    for (int i = 0; i < simulationCount; ++i) {
        double randomValue = QRandomGenerator::global()->generateDouble();
        double cumulativeProbability = 0.0;

        for (int j = 0; j < events.size(); ++j) {
            cumulativeProbability += probabilities[j];
            if (randomValue <= cumulativeProbability) {
                results.append(events[j]);
                break;
            }
        }
    }
}
