#include "tpscale.h"
#include <QResizeEvent>

TPScale::TPScale(QWidget *parent)
    : QWidget(parent)
{
    updateLabels();
    setMinimumSize(100, 200); // 设置最小尺寸，宽高比为1:2
}

void TPScale::updateLabels()
{
    m_labels.clear();
    double step = static_cast<double>(m_highest - m_lowest) / m_division;
    for (int i = 0; i <= m_division; ++i)
    {
        m_labels.append(QString::number(m_lowest + i * step));
    }
}

int TPScale::level() const
{
    return m_level;
}

void TPScale::setLevel(int level)
{
    if (m_level != level)
    {
        m_level = level;
        emit levelChanged(m_level);
        update();
    }
}

int TPScale::warnLevelLow() const
{
    return m_warnLevelLow;
}

void TPScale::setWarnLevelLow(int warnLevelLow)
{
    m_warnLevelLow = warnLevelLow;
    update();
}

int TPScale::warnLevelHigh() const
{
    return m_warnLevelHigh;
}

void TPScale::setWarnLevelHigh(int warnLevelHigh)
{
    m_warnLevelHigh = warnLevelHigh;
    update();
}

int TPScale::highest() const
{
    return m_highest;
}

void TPScale::setHighest(int highest)
{
    m_highest = highest;
    updateLabels();
    update();
}

int TPScale::lowest() const
{
    return m_lowest;
}

void TPScale::setLowest(int lowest)
{
    m_lowest = lowest;
    updateLabels();
    update();
}

int TPScale::division() const
{
    return m_division;
}

void TPScale::setDivision(int division)
{
    m_division = division;
    updateLabels();
    update();
}

// int TPScale::widgetWidth() const
// {
//     return width();
// }

// void TPScale::setWidgetWidth(int widgetWidth)
// {
//     if (width() != widgetWidth)
//     {
//         width() = widgetWidth;
//         update();
//     }
// }

// int TPScale::widgetHeight() const
// {
//     return height();
// }

// void TPScale::setWidgetHeight(int widgetHeight)
// {
//     if (height() != widgetHeight)
//     {
//         height() = widgetHeight;
//         update();
//     }
// }

QSize TPScale::sizeHint() const
{
    return QSize(width(), height());
}

QSize TPScale::minimumSizeHint() const
{
    return QSize(width(), height());
}

void TPScale::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}

void TPScale::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect rect(0, 0, width(), height());
    painter.setViewport(rect);
    painter.setWindow(0, 0, width(), height()); // 将窗口坐标系设置为1:2比例

    // 绘制边框
    QPen pen(Qt::blue);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawRoundedRect(1, 1, width()-2, height()-2, 5, 5);

    // 长刻度线长度
    int longLength = width() / 2; // 原来的1/2长度
    int midLength = longLength * 2 / 5; // 中刻度线长度
    int shortLength = longLength * 1 / 5; // 短刻度线长度
    // 绘制背景颜色
    int warnLowY = height() / 10 + (m_highest - m_warnLevelLow) * height() * 8 / 10 / (m_highest - m_lowest);
    int warnHighY = height() / 10 + (m_highest - m_warnLevelHigh) * height() * 8 / 10 / (m_highest - m_lowest);

    // 绘制危险区间 (上方区域)
    painter.setBrush(QColor(255, 165, 0, 170)); // 橙色，半透明
    painter.drawRect(width() / 10 + longLength/10, height() / 10, longLength*8/10, warnHighY - height() / 10);

    // 绘制安全区间
    painter.setBrush(QColor(0, 255, 0, 170)); // 绿色，半透明
    painter.drawRect(width() / 10 + longLength/10, warnHighY, longLength*8/10, warnLowY - warnHighY);

    // 绘制危险区间 (下方区域)
    painter.setBrush(QColor(255, 165, 0, 170)); // 橙色，半透明
    painter.drawRect(width() / 10 + longLength/10, warnLowY, longLength*8/10, height() * 9 / 10 - warnLowY);

    // 绘制刻度线中心的黑色线段
    // pen.setColor(Qt::black);
    // pen.setWidth(1);
    // painter.setPen(pen);
    // painter.drawLine(width()/10 + longLength / 2, height()/10, width()/10 + longLength / 2, height()*9/10);

    // 绘制长刻度线
    pen.setColor(Qt::gray);
    pen.setWidth(2);
    painter.setPen(pen);
    int longStep = height()*8/10 / m_division;
    for (int i = 0; i <= m_division; ++i)
    {
        int y = height()/10 + i * longStep;
        painter.drawLine(width()/10, y, width()/10 + longLength, y);
    }

    // 绘制中刻度线和短刻度线
    pen.setWidth(1);
    painter.setPen(pen);
    int shortStep = longStep / 4;
    for (int i = 0; i < m_division; ++i)
    {
        int baseY = height()/10 + i * longStep;
        for (int j = 1; j <= 3; ++j)
        {
            int y = baseY + j * shortStep;
            if (j == 2) // 中刻度线
            {
                painter.drawLine(width()/10 + longLength / 2 - midLength / 2, y, width()/10 + longLength / 2 + midLength / 2, y);
            }
            else // 短刻度线
            {
                painter.drawLine(width()/10 + longLength / 2 - shortLength / 2, y, width()/10 + longLength / 2 + shortLength / 2, y);
            }
        }
    }

    // 绘制标签
    pen.setColor(Qt::blue);
    painter.setPen(pen);
    painter.setFont(QFont("Arial", height()/25)); // 字体缩小一倍
    for (int i = 0; i <= m_division; ++i)
    {
        int y = height()/10 + i * longStep - height()/40;
        painter.drawText(width()/10*2 + longLength, y, width()*4/10, width()/10, Qt::AlignLeft, m_labels[m_division - i]); // 自上而下递减，标签位置调整
    }

    // 绘制当前值水平线段
    pen.setColor(Qt::red);
    pen.setWidth(2);
    painter.setPen(pen);
    int currentY = height()/10 + (m_highest - m_level) * height()*8/10 / (m_highest - m_lowest);
    painter.drawLine(width()/10+longLength*2/10, currentY, width()/10 + longLength*8/10, currentY);

    // 绘制三角箭头
    QPolygon arrow;
    arrow << QPoint(width()/10, currentY) << QPoint(width()/20, currentY - 5) << QPoint(width()/20, currentY + 5);
    painter.setBrush(Qt::red);
    painter.drawPolygon(arrow);
}
