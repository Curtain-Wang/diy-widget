#include "heater.h"
#include <QPainter>
#include <QPainterPath>

Heater::Heater(QWidget *parent) :
    QWidget(parent)
{
}
void Heater::setHeating(bool heating)
{
    if (m_isHeating != heating) {
        m_isHeating = heating;
        emit heatingChanged(m_isHeating);
        update();  // 触发重绘
    }
}

void Heater::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 设置正方形边框画笔颜色和宽度
    QPen squarePen(Qt::black);
    int penWidth = 3;
    squarePen.setWidth(penWidth);
    painter.setPen(squarePen);
    painter.setBrush(Qt::NoBrush); // 设置为无填充

    // 绘制一个空心正方形，调整位置以避免边缘被裁剪
    int side = qMin(width(), height() - 120) - penWidth;  // 减去更多高度以腾出空间给波浪线
    int x = (width() - side) / 2 + penWidth / 2;
    int y = (height() - side) / 2 + penWidth / 2 + 70;  // 下移正方形以腾出更多空间给波浪线
    painter.drawRect(x, y, side - penWidth, side - penWidth);

    int lineCount = 3;
    int waveHeight = 10;  // 波浪线高度
    int waveFrequency = 20; // 波浪线频率，每次移动的距离

    // 绘制三条竖线
    for (int i = 1; i <= lineCount; ++i)
    {
        int lineX = x + (side / (lineCount + 1)) * i;
        int startY = y;
        int endY = y + side - penWidth;
        int waveStartY = startY + 0.2 * side;
        int waveEndY = startY + 0.8 * side;

        // 设置竖线的画笔颜色为黑色
        QPen linePen(Qt::black);
        linePen.setWidth(2);
        painter.setPen(linePen);

        // 绘制竖线的上部分
        painter.drawLine(lineX, startY, lineX, waveStartY);

        // 设置波浪线的画笔颜色
        QPen wavePen(m_isHeating ? Qt::red : Qt::black);
        wavePen.setWidth(2);
        painter.setPen(wavePen);

        // 绘制波浪线
        QPainterPath path;
        path.moveTo(lineX, waveStartY);
        for (int posY = waveStartY; posY < waveEndY; posY += waveFrequency)
        {
            int nextY = posY + waveFrequency;
            if (nextY > waveEndY) nextY = waveEndY;
            path.cubicTo(lineX - waveHeight / 2, posY + waveFrequency / 2,
                         lineX + waveHeight / 2, posY + waveFrequency / 2,
                         lineX, nextY);
        }
        painter.drawPath(path);

        // 设置竖线的画笔颜色为黑色
        painter.setPen(linePen);

        // 绘制竖线的下部分
        painter.drawLine(lineX, waveEndY, lineX, endY);
    }

    if (m_isHeating) {
        // 绘制正方形上方的波浪线（冒烟效果）
        int smokeCount = 4;
        int smokeHeight = side / 2;  // 增加波浪线高度
        int smokeFrequency = 20;
        int smokeWidth = side / (smokeCount + 1);

        QPen smokePen(Qt::gray);
        smokePen.setWidth(2);
        painter.setPen(smokePen);

        for (int i = 1; i <= smokeCount; ++i)
        {
            int smokeX = x + smokeWidth * i;
            int smokeStartY = y - penWidth / 2 - 10;  // 上移波浪线起点，使其更靠近正方形
            int smokeEndY = smokeStartY - smokeHeight;

            QPainterPath smokePath;
            smokePath.moveTo(smokeX, smokeStartY);
            bool direction = true;
            for (int posY = smokeStartY; posY > smokeEndY; posY -= smokeFrequency)
            {
                int nextY = posY - smokeFrequency;
                if (nextY < smokeEndY) nextY = smokeEndY;
                int offsetX = direction ? smokeWidth / 4 : -smokeWidth / 4;
                smokePath.cubicTo(smokeX + offsetX, posY - smokeFrequency / 2,
                                  smokeX - offsetX, posY - smokeFrequency / 2,
                                  smokeX, nextY);
                direction = !direction;
            }
            painter.drawPath(smokePath);
        }
    }
}
