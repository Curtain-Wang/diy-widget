#include "VerticalLineDrawer.h"
#include <QPainter>
#include <QPainterPath>

VerticalLineDrawer::VerticalLineDrawer(QWidget *parent)
    : QWidget(parent)
{
    // 构造函数
}

void VerticalLineDrawer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // 设置线条颜色
    QPen pen(Qt::red);
    pen.setWidth(5);
    painter.setPen(pen);
    // 画一条水平线
    painter.drawLine(10, 10, 200, 10);
    painter.drawLine(200, 10, 200, 200);
    //画能量块
    drawGradientLineSegment(100, 10, 120, 10, Qt::red, painter);
    drawGradientPolylineSegment(195, 10, 200, 10, 200, 25, Qt::red, painter);
}

void VerticalLineDrawer::drawGradientLineSegment(int x1, int y1, int x2, int y2, Qt::GlobalColor edgeColor, QPainter &painter, double color2At)
{
    //绘制能量块覆盖的部分
    QLinearGradient gradient(x1, y1, x2, y2);
    if(color2At != 0)
    {
        gradient.setColorAt(0, edgeColor);
    }
    gradient.setColorAt(color2At, Qt::white);
    gradient.setColorAt(1, edgeColor);
    QPen pen = painter.pen();
    pen.setBrush(gradient);
    painter.setPen(pen);
    painter.drawLine(x1, y1, x2, y2);
    //绘制能量块之后的部分
    pen.setColor(edgeColor); // 恢复原始颜色
    painter.setPen(pen);
}
void VerticalLineDrawer::drawGradientPolylineSegment(int x1, int y1, int x2, int y2, int x3, int y3, Qt::GlobalColor edgeColor, QPainter &painter)
{
    // 计算渐变起点和终点，跨越垂直和水平部分
    QLinearGradient gradient(x1, y1, x3, y3);
    gradient.setColorAt(0, edgeColor);
    gradient.setColorAt(0.5, Qt::white);
    gradient.setColorAt(1, edgeColor);
    QPen pen = painter.pen();
    pen.setBrush(gradient);
    painter.setPen(pen);

    // 绘制能量块在垂直部分和水平部分的电线
    QPainterPath path;
    path.moveTo(x1, y1);
    path.lineTo(x2, y2);
    path.lineTo(x3, y3);
    painter.drawPath(path);
    pen.setColor(edgeColor); // 恢复原始颜色
    painter.setPen(pen);
}
