#ifndef VISUALIZATIONWINDOW_H
#define VISUALIZATIONWINDOW_H

#include <QMainWindow>
#include <QtCharts>

namespace Ui {
class VisualizationWindow;
}

class VisualizationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit VisualizationWindow(QMainWindow *parent = nullptr);
    ~VisualizationWindow();

public slots:
    void setSimulationResults(const QList<QString> &simulationResults);

private:
    Ui::VisualizationWindow *ui;
    QChart *chart;

    void createBarChart();
    void createPieChart();

    QList<QString> simulationResults;
};

#endif // VISUALIZATIONWINDOW_H
