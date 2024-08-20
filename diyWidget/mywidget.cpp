#include "MyWidget.h"
#include <QPainter>
#include <QPainterPath>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent), offset(0)
{
    // 初始化定时器，每隔100毫秒触发一次updatePosition槽函数
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MyWidget::updatePosition);
    timer->start(100);  // 100毫秒的时间间隔
}

void MyWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // 使用新方法绘制带有动态填充效果的水平折线
    drawHorZigzagLine(painter, 10, 10, 200, 10, Qt::red, Qt::green);

    // 使用新方法绘制带有动态填充效果的垂直折线
    drawVerZigzagLine(painter, 200, 10, 200, 200, Qt::red, Qt::green);
}

void MyWidget::drawHorZigzagLine(QPainter &painter, int startX, int startY, int endX, int endY, const QColor &lineColor, const QColor &fillColor)
{
    // 设置线条颜色
    QPen pen(lineColor);
    pen.setWidth(5);
    painter.setPen(pen);

    // 画一条水平线
    painter.drawLine(startX, startY, endX, endY);

    // 设置折线颜色
    QPen stripePen(fillColor);
    stripePen.setWidth(1);
    painter.setPen(stripePen);

    // 定义折线间隔和高度
    int stripeHeight = 4; // 折线条纹的高度
    int stripeSpacing = 10; // 折线间距
    int currentStartX = startX + offset; // 根据偏移量更新起点X坐标

    // 循环绘制多组折线
    for (int i = 0; currentStartX + i * 2 * stripeSpacing < endX + offset; i++)
    {
        // 计算每组折线的起点
        int baseX = currentStartX + i * 2 * stripeSpacing;

        // 检查折线是否会超出红线的范围
        if (baseX + stripeSpacing + stripeHeight > endX)
            break; // 如果超出边界，停止绘制

        // 第一条折线的点
        QPoint points1[3] = {
            QPoint(baseX, startY - 2),
            QPoint(baseX + stripeHeight, startY),
            QPoint(baseX, startY + 3)
        };
        painter.drawPolyline(points1, 3);

        // 第二条折线的点
        QPoint points2[3] = {
            QPoint(baseX + stripeSpacing, startY - 2),
            QPoint(baseX + stripeSpacing + stripeHeight, startY),
            QPoint(baseX + stripeSpacing, startY + 3)
        };
        painter.drawPolyline(points2, 3);

        // 使用 QPainterPath 创建填充区域，精确匹配两条折线的边界
        QPainterPath fillPath;
        fillPath.moveTo(points1[0]); // 第一条折线的起点
        fillPath.lineTo(points1[1]); // 第一条折线的中点
        fillPath.lineTo(points1[2]); // 第一条折线的终点
        fillPath.lineTo(points2[2]); // 第二条折线的终点
        fillPath.lineTo(points2[1]); // 第二条折线的中点
        fillPath.lineTo(points2[0]); // 第二条折线的起点
        fillPath.closeSubpath();     // 关闭路径

        // 填充颜色为指定的填充颜色
        painter.fillPath(fillPath, fillColor);

        // 再次绘制折线条纹以确保线条清晰可见
        painter.drawPolyline(points1, 3);
        painter.drawPolyline(points2, 3);
    }
}

void MyWidget::drawVerZigzagLine(QPainter &painter, int startX, int startY, int endX, int endY, const QColor &lineColor, const QColor &fillColor)
{
    // 设置线条颜色
    QPen pen(lineColor);
    pen.setWidth(5);
    painter.setPen(pen);

    // 画一条垂直线
    painter.drawLine(startX, startY, endX, endY);

    // 设置折线颜色
    QPen stripePen(fillColor);
    stripePen.setWidth(1);
    painter.setPen(stripePen);

    // 定义折线间隔和高度
    int stripeHeight = 4; // 折线条纹的宽度（这里表现为水平宽度）
    int stripeSpacing = 10; // 折线间距
    int currentStartY = startY + offset; // 根据偏移量更新起点Y坐标

    // 循环绘制多组折线
    for (int i = 0; currentStartY + i * 2 * stripeSpacing < endY + offset; i++)
    {
        // 计算每组折线的起点
        int baseY = currentStartY + i * 2 * stripeSpacing;

        // 检查折线是否会超出蓝线的范围
        if (baseY + stripeSpacing + stripeHeight > endY)
            break; // 如果超出边界，停止绘制

        // 第一条折线的点
        QPoint points1[3] = {
            QPoint(startX - 2, baseY),
            QPoint(startX, baseY + stripeHeight),
            QPoint(startX + 3, baseY)
        };
        painter.drawPolyline(points1, 3);

        // 第二条折线的点
        QPoint points2[3] = {
            QPoint(startX - 2, baseY + stripeSpacing),
            QPoint(startX, baseY + stripeSpacing + stripeHeight),
            QPoint(startX + 3, baseY + stripeSpacing)
        };
        painter.drawPolyline(points2, 3);

        // 使用 QPainterPath 创建填充区域，精确匹配两条折线的边界
        QPainterPath fillPath;
        fillPath.moveTo(points1[0]); // 第一条折线的起点
        fillPath.lineTo(points1[1]); // 第一条折线的中点
        fillPath.lineTo(points1[2]); // 第一条折线的终点
        fillPath.lineTo(points2[2]); // 第二条折线的终点
        fillPath.lineTo(points2[1]); // 第二条折线的中点
        fillPath.lineTo(points2[0]); // 第二条折线的起点
        fillPath.closeSubpath();     // 关闭路径

        // 填充颜色为指定的填充颜色
        painter.fillPath(fillPath, fillColor);

        // 再次绘制折线条纹以确保线条清晰可见
        painter.drawPolyline(points1, 3);
        painter.drawPolyline(points2, 3);
    }
}

void MyWidget::updatePosition()
{
    // 每次调用时偏移量增加，模拟向右移动的效果
    offset += 2;
    if (offset >= 20)  // 当偏移量达到一个周期长度后重置
    {
        offset = 0;
    }

    update();  // 触发重绘
}
