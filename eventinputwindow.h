#ifndef EVENTINPUTWINDOW_H
#define EVENTINPUTWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QMessageBox>
#include <QList>
#include <QString>

namespace Ui {
class EventInputWindow;
}

class EventInputWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EventInputWindow(QMainWindow *parent = nullptr);
    ~EventInputWindow();

signals:
    void eventsReady(const QList<QString> &events, const QList<double> &probabilities);

private slots:
    void addEvent();
    void removeEvent();
    void saveEvents();

private:
    Ui::EventInputWindow *ui;
    QList<QString> events;
    QList<double> probabilities;
};

#endif // EVENTINPUTWINDOW_H
