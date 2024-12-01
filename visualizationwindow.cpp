#include "visualizationwindow.h"
#include "ui_visualizationwindow.h"

VisualizationWindow::VisualizationWindow(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::VisualizationWindow),
    chart(new QChart)
{
    ui->setupUi(this);

    // Ініціалізація графіків
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);

    // Підключення кнопок
    connect(ui->btnBarChart, &QPushButton::clicked, this, &VisualizationWindow::createBarChart);
    connect(ui->btnPieChart, &QPushButton::clicked, this, &VisualizationWindow::createPieChart);
}

VisualizationWindow::~VisualizationWindow()
{
    delete ui;
}

void VisualizationWindow::setSimulationResults(const QList<QString> &results)
{
    simulationResults = results;
}

void VisualizationWindow::createBarChart()
{
    chart->removeAllSeries();
    chart->setTitle("Гістограма результатів");

    QBarSeries *series = new QBarSeries();
    QMap<QString, int> frequencies;

    // Підрахунок частот
    for (const QString &result : simulationResults) {
        frequencies[result]++;
    }

    QBarSet *set = new QBarSet("Події");
    QStringList categories;

    for (auto it = frequencies.begin(); it != frequencies.end(); ++it) {
        *set << it.value();
        categories << it.key();
    }

    series->append(set);
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addSeries(series);
}

void VisualizationWindow::createPieChart()
{
    chart->removeAllSeries();
    chart->setTitle("Кругова діаграма результатів");

    QPieSeries *series = new QPieSeries();
    QMap<QString, int> frequencies;

    for (const QString &result : simulationResults) {
        frequencies[result]++;
    }

    for (auto it = frequencies.begin(); it != frequencies.end(); ++it) {
        series->append(it.key(), it.value());
    }

    chart->addSeries(series);
}
