#include "BatteryCircuitWidget.h"
#include <QPainter>

BatteryCircuitWidget::BatteryCircuitWidget(QWidget *parent) :
    QWidget(parent)
{
}

void BatteryCircuitWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 设置视口和窗口
    QRect rect(0, 0, width(), height());
    painter.setViewport(rect);
    painter.setWindow(0, 0, 200, 200); // 根据实际情况调整大小

    drawBattery(painter);
    drawCircuit(painter);
    drawContactors(painter);
}

void BatteryCircuitWidget::drawBattery(QPainter &painter)
{
    QPen pen(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);

    // 绘制电池
    painter.setBrush(Qt::white);
    painter.drawRect(10, 40, 20, 80); // 电池主体
    painter.setBrush(Qt::green);
    painter.drawRect(10, 80, 20, 40); // 电池电量

    // 绘制电池正极头
    painter.setBrush(Qt::yellow);
    painter.drawRect(15, 30, 10, 10); // 电池正极头
}

void BatteryCircuitWidget::drawCircuit(QPainter &painter)
{
    QPen pen(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);

    // 绘制电路部分
    painter.drawLine(30, 50, 70, 50);  // 电池正极到接触器
    painter.drawLine(70, 50, 70, 100); // 竖线
    painter.drawLine(70, 100, 100, 100); // 接触器到电路
    painter.drawLine(100, 100, 100, 150); // 竖线
    painter.drawLine(100, 150, 20, 150); // 左下横线
    painter.drawLine(20, 150, 20, 140); // 竖线

    // 绘制电路控制部分
    painter.drawLine(20, 140, 60, 140); // 下横线
    painter.drawLine(60, 140, 60, 130); // 竖线
    painter.drawLine(60, 130, 40, 130); // 中横线
    painter.drawLine(40, 130, 40, 120); // 竖线
    painter.drawLine(40, 120, 70, 120); // 上横线
    painter.drawLine(70, 120, 70, 100); // 竖线
    painter.drawLine(70, 100, 50, 100); // 横线回到电池
}

void BatteryCircuitWidget::drawContactors(QPainter &painter)
{
    QPen pen(Qt::red);
    pen.setWidth(2);
    painter.setPen(pen);

    // 绘制接触器和电路连接
    painter.drawLine(30, 40, 130, 40); // 接触器到正极
    painter.drawLine(130, 40, 130, 70); // 竖线

    // 绘制BUS+和BUS-
    painter.drawLine(130, 40, 170, 40); // BUS+
    painter.drawLine(130, 150, 170, 150); // BUS-
}
