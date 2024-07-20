#include "TScale.h"
#include <QResizeEvent>

TScale::TScale(QWidget *parent)
    : QWidget(parent)
{
    updateLabels();
    setMinimumSize(100, 200); // 设置最小尺寸，宽高比为1:2
 // 设置最小尺寸，宽高比为1:2
    checkWarnLevel();
}

void TScale::checkWarnLevel()
{
    setWarnLevelHigh(m_warnLevelHigh);
    setWarnLevelLow(m_warnLevelLow);


}

void TScale::updateLabels()
{
    m_labels.clear();
    double step = static_cast<double>(m_highest - m_lowest) / m_division;
    for (int i = 0; i <= m_division; ++i)
    {
        m_labels.append(QString::number(m_lowest + i * step));
    }
}

double TScale::level() const
{
    return m_level;
}

void TScale::setLevel(int level)
{
    if (m_level != level)
    {
        m_level = level;
        emit levelChanged(m_level);
        update();
    }
}

double TScale::warnLevelLow() const
{
    return m_warnLevelLow;
}

void TScale::setWarnLevelLow(int warnLevelLow)
{
    if (warnLevelLow < m_lowest)
        warnLevelLow = m_lowest;
    m_warnLevelLow = warnLevelLow;
    update();
}

double TScale::warnLevelHigh() const
{
    return m_warnLevelHigh;
}

void TScale::setWarnLevelHigh(int warnLevelHigh)
{
    if (warnLevelHigh > m_highest)
        warnLevelHigh = m_highest;
    m_warnLevelHigh = warnLevelHigh;
    update();
}

double TScale::highest() const
{
    return m_highest;
}

void TScale::setHighest(int highest)
{

    m_highest = highest;
    updateLabels();
    update();
}

double TScale::lowest() const
{
    return m_lowest;
}

void TScale::setLowest(int lowest)
{
    m_lowest = lowest;
    updateLabels();
    update();
}

int TScale::division() const
{
    return m_division;
}

void TScale::setDivision(int division)
{
    m_division = division;
    updateLabels();
    update();
}

// int TScale::widgetWidth() const
// {
//     return width();
// }

// void TScale::setWidgetWidth(int widgetWidth)
// {
//     if (width() != widgetWidth)
//     {
//         width() = widgetWidth;
//         update();
//     }
// }

// int TScale::widgetHeight() const
// {
//     return height();
// }

// void TScale::setWidgetHeight(int widgetHeight)
// {
//     if (height() != widgetHeight)
//     {
//         height() = widgetHeight;
//         update();
//     }
// }

QSize TScale::sizeHint() const
{
    return QSize(width(), height());
}

QSize TScale::minimumSizeHint() const
{
    return QSize(width(), height());
}

void TScale::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}

void TScale::paintEvent(QPaintEvent *event)
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

    double warnLowY = height() / 10.0 + (m_highest - m_warnLevelLow) * height() * 8.0 / 10.0 / (m_highest - m_lowest);
    double warnHighY = height() / 10.0 + (m_highest - m_warnLevelHigh) * height() * 8.0 / 10.0 / (m_highest - m_lowest);

    // 绘制危险区间 (上方区域)
    painter.setBrush(QColor(255, 165, 0, 170)); // 橙色，半透明
    painter.drawRect(width() / 10.0 + longLength / 10.0, height() / 10.0, longLength * 8.0 / 10.0, warnHighY - height() / 10.0);

    // 绘制安全区间
    painter.setBrush(QColor(0, 255, 0, 170)); // 绿色，半透明
    painter.drawRect(width() / 10.0 + longLength / 10.0, warnHighY, longLength * 8.0 / 10.0, warnLowY - warnHighY);

    // 绘制危险区间 (下方区域)
    painter.setBrush(QColor(255, 165, 0, 170)); // 橙色，半透明
    painter.drawRect(width() / 10.0 + longLength / 10.0, warnLowY, longLength * 8.0 / 10.0, height() * 9.0 / 10.0 - warnLowY);

    // 绘制刻度线中心的黑色线段
    // pen.setColor(Qt::black);
    // pen.setWidth(1);
    // painter.setPen(pen);
    // painter.drawLine(width() / 10.0 + longLength / 2.0, height() / 10.0, width() / 10.0 + longLength / 2.0, height() * 9.0 / 10.0);

    // 绘制长刻度线
    pen.setColor(Qt::gray);
    pen.setWidth(2);
    painter.setPen(pen);
    double longStep = height() * 8.0 / 10.0 / m_division;
    for (int i = 0; i <= m_division; ++i) {
        double y = height() / 10.0 + i * longStep;
        painter.drawLine(width() / 10.0, y, width() / 10.0 + longLength, y);
    }

    // 绘制中刻度线和短刻度线
    pen.setWidth(1);
    painter.setPen(pen);
    double shortStep = longStep / 4.0;
    for (int i = 0; i < m_division; ++i) {
        double baseY = height() / 10.0 + i * longStep;

        for (int j = 1; j <= 3; ++j) {
            double y = baseY + j * shortStep;
            if (j == 2) { // 中刻度线
                painter.drawLine(width() / 10.0 + longLength / 2.0 - midLength / 2.0, y, width() / 10.0 + longLength / 2.0 + midLength / 2.0, y);
            } else { // 短刻度线
                painter.drawLine(width() / 10.0 + longLength / 2.0 - shortLength / 2.0, y, width() / 10.0 + longLength / 2.0 + shortLength / 2.0, y);
            }
        }
    }

    // 绘制标签
    pen.setColor(Qt::blue);
    painter.setPen(pen);
    painter.setFont(QFont("Arial", height() / 25)); // 字体缩小一倍
    for (int i = 0; i <= m_division; ++i) {
        double y = height() / 10.0 + i * longStep - height() / 40.0;
        painter.drawText(width() / 10.0 * 2 + longLength, y, width() * 4.0 / 10.0, height() / 10.0, Qt::AlignLeft, m_labels[m_division - i]); // 自上而下递减，标签位置调整
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
