// DashboardWidget.cpp
#include "DashboardWidget.h"
#include <QPainter>
#include <QPen>
#include <QBrush>

DashboardWidget::DashboardWidget(QWidget *parent)
    : QWidget(parent), m_speed(0), m_fuelLevel(0)
{
}

void DashboardWidget::setSpeed(int speed)
{
    m_speed = speed;
    update();
}

void DashboardWidget::setFuelLevel(int fuelLevel)
{
    m_fuelLevel = fuelLevel;
    update();
}

void DashboardWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int side = qMin(width(), height());
    painter.setViewport((width() - side) / 2, (height() - side) / 2, side, side);
    painter.setWindow(-50, -50, 100, 100);

    // 画速度表
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.drawEllipse(-40, -40, 80, 80);

    painter.setPen(Qt::white);
    for (int i = 0; i <= 180; i += 20) {
        painter.save();
        painter.rotate(i - 90);
        painter.drawLine(30, 0, 40, 0);
        painter.drawText(QRect(-40, -10, 20, 20), Qt::AlignCenter, QString::number(i));
        painter.restore();
    }

    painter.rotate(m_speed - 90);
    painter.setPen(Qt::red);
    painter.drawLine(0, 0, 30, 0);
    painter.restore();

    // 画燃油表
    painter.save();
    painter.translate(0, 60);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.drawEllipse(-20, -20, 40, 40);

    painter.setPen(Qt::white);
    for (int i = 0; i <= 100; i += 25) {
        painter.save();
        painter.rotate(i - 50);
        painter.drawLine(10, 0, 20, 0);
        painter.drawText(QRect(-25, -10, 20, 20), Qt::AlignCenter, QString::number(i));
        painter.restore();
    }

    painter.rotate(m_fuelLevel - 50);
    painter.setPen(Qt::yellow);
    painter.drawLine(0, 0, 10, 0);
    painter.restore();
}
