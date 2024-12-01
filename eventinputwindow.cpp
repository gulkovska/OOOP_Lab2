#include "eventinputwindow.h"
#include "ui_eventinputwindow.h"

EventInputWindow::EventInputWindow(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::EventInputWindow)
{
    ui->setupUi(this);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // Підключення кнопок
    connect(ui->btnAddEvent, &QPushButton::clicked, this, &EventInputWindow::addEvent);
    connect(ui->btnRemoveEvent, &QPushButton::clicked, this, &EventInputWindow::removeEvent);
    connect(ui->btnSaveEvents, &QPushButton::clicked, this, &EventInputWindow::saveEvents);
}

EventInputWindow::~EventInputWindow()
{
    delete ui;
}

void EventInputWindow::addEvent()
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    // За замовчуванням додаємо порожні клітинки
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem("Подія " + QString::number(row + 1)));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem("0.0")); // Ймовірність за замовчуванням
}

void EventInputWindow::removeEvent()
{
    int row = ui->tableWidget->currentRow();
    if (row >= 0) {
        ui->tableWidget->removeRow(row);
    }
}

void EventInputWindow::saveEvents()
{
    QList<QString> events;
    QList<double> probabilities;

    // Обхід усіх рядків таблиці
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QTableWidgetItem *eventItem = ui->tableWidget->item(row, 0); // Подія
        QTableWidgetItem *probabilityItem = ui->tableWidget->item(row, 1); // Ймовірність

        if (eventItem && probabilityItem) {
            QString event = eventItem->text();
            bool ok;
            double probability = probabilityItem->text().toDouble(&ok);

            if (ok && probability >= 0.0) {
                events.append(event);
                probabilities.append(probability);
            } else {
                QMessageBox::warning(this, "Помилка", "Неправильний формат ймовірності в рядку " + QString::number(row + 1));
                return;
            }
        } else {
            QMessageBox::warning(this, "Помилка", "Порожнє значення в рядку " + QString::number(row + 1));
            return;
        }
    }

    // Перевірка, чи сума ймовірностей дорівнює 1
    double totalProbability = std::accumulate(probabilities.begin(), probabilities.end(), 0.0);
    if (std::abs(totalProbability - 1.0) > 1e-6) {
        QMessageBox::warning(this, "Помилка", "Сума ймовірностей має дорівнювати 1.");
        return;
    }

    emit eventsReady(events, probabilities);
}
