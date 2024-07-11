#ifndef BATTERYCIRCUITWIDGET_H
#define BATTERYCIRCUITWIDGET_H

#include <QWidget>

class BatteryCircuitWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BatteryCircuitWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void drawBattery(QPainter &painter);
    void drawCircuit(QPainter &painter);
    void drawContactors(QPainter &painter);
};

#endif // BATTERYCIRCUITWIDGET_H
