// DashboardWidget.h
#ifndef DASHBOARDWIDGET_H
#define DASHBOARDWIDGET_H

#include <QWidget>

class DashboardWidget : public QWidget
{
    Q_OBJECT

public:
    DashboardWidget(QWidget *parent = nullptr);
    void setSpeed(int speed);
    void setFuelLevel(int fuelLevel);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_speed;
    int m_fuelLevel;
};

#endif // DASHBOARDWIDGET_H
