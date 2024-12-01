#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QVector>
#include <QString>

namespace Ui {
class SimulationWindow;
}

class SimulationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SimulationWindow(QMainWindow *parent = nullptr);
    ~SimulationWindow();

signals:
    void resultsReady(const QList<QString> &simulationResults);

public slots:
    void setEventsAndProbabilities(const QList<QString> &events, const QList<double> &probabilities);

private slots:
    void startSimulation();

private:
    Ui::SimulationWindow *ui;

    // Логіка симуляцій
    QList<QString> events; // Список подій
    QList<double> probabilities; // Ймовірності подій
    QList<QString> results;

    void simulateEvents(int simulationCount);
};

#endif // SIMULATIONWINDOW_H
