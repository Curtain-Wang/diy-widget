#include "TScale.h"
#include <QResizeEvent>

TScale::TScale(QWidget *parent)
    : QWidget(parent)
{
    updateLabels();
    setMinimumSize(50, 100); // 设置最小尺寸，宽高比为1:2
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

int TScale::level() const
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

int TScale::warnLevelLow() const
{
    return m_warnLevelLow;
}

void TScale::setWarnLevelLow(int warnLevelLow)
{
    m_warnLevelLow = warnLevelLow;
    update();
}

int TScale::warnLevelHigh() const
{
    return m_warnLevelHigh;
}

void TScale::setWarnLevelHigh(int warnLevelHigh)
{
    m_warnLevelHigh = warnLevelHigh;
    update();
}

int TScale::highest() const
{
    return m_highest;
}

void TScale::setHighest(int highest)
{
    m_highest = highest;
    updateLabels();
    update();
}

int TScale::lowest() const
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

int TScale::widgetWidth() const
{
    return m_widgetWidth;
}

void TScale::setWidgetWidth(int widgetWidth)
{
    if (m_widgetWidth != widgetWidth)
    {
        m_widgetWidth = widgetWidth;
        update();
    }
}

int TScale::widgetHeight() const
{
    return m_widgetHeight;
}

void TScale::setWidgetHeight(int widgetHeight)
{
    if (m_widgetHeight != widgetHeight)
    {
        m_widgetHeight = widgetHeight;
        update();
    }
}

QSize TScale::sizeHint() const
{
    return QSize(m_widgetWidth, m_widgetHeight);
}

QSize TScale::minimumSizeHint() const
{
    return QSize(m_widgetWidth, m_widgetHeight);
}

void TScale::resizeEvent(QResizeEvent *event)
{
    int newWidth = event->size().width();
    int newHeight = newWidth * 2;
    setFixedSize(newWidth, newHeight);
}

void TScale::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect rect(0, 0, width(), height());
    painter.setViewport(rect);
    painter.setWindow(0, 0, m_widgetWidth, m_widgetHeight); // 将窗口坐标系设置为1:2比例

    // 绘制边框
    QPen pen(Qt::blue);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawRoundedRect(1, 1, m_widgetWidth-2, m_widgetHeight-2, 5, 5);

    // 长刻度线长度
    int longLength = m_widgetWidth / 2; // 原来的1/2长度
    int midLength = longLength * 2 / 5; // 中刻度线长度
    int shortLength = longLength * 1 / 5; // 短刻度线长度
    // 绘制背景颜色
    int warnLowY = m_widgetHeight / 10 + (m_highest - m_warnLevelLow) * m_widgetHeight * 8 / 10 / (m_highest - m_lowest);
    int warnHighY = m_widgetHeight / 10 + (m_highest - m_warnLevelHigh) * m_widgetHeight * 8 / 10 / (m_highest - m_lowest);

    // 绘制危险区间 (上方区域)
    painter.setBrush(QColor(255, 165, 0, 170)); // 橙色，半透明
    painter.drawRect(m_widgetWidth / 10 + longLength/10, m_widgetHeight / 10, longLength*8/10, warnHighY - m_widgetHeight / 10);

    // 绘制安全区间
    painter.setBrush(QColor(0, 255, 0, 170)); // 绿色，半透明
    painter.drawRect(m_widgetWidth / 10 + longLength/10, warnHighY, longLength*8/10, warnLowY - warnHighY);

    // 绘制危险区间 (下方区域)
    painter.setBrush(QColor(255, 165, 0, 170)); // 橙色，半透明
    painter.drawRect(m_widgetWidth / 10 + longLength/10, warnLowY, longLength*8/10, m_widgetHeight * 9 / 10 - warnLowY);

    // 绘制刻度线中心的黑色线段
    // pen.setColor(Qt::black);
    // pen.setWidth(1);
    // painter.setPen(pen);
    // painter.drawLine(m_widgetWidth/10 + longLength / 2, m_widgetHeight/10, m_widgetWidth/10 + longLength / 2, m_widgetHeight*9/10);

    // 绘制长刻度线
    pen.setColor(Qt::gray);
    pen.setWidth(2);
    painter.setPen(pen);
    int longStep = m_widgetHeight*8/10 / m_division;
    for (int i = 0; i <= m_division; ++i)
    {
        int y = m_widgetHeight/10 + i * longStep;
        painter.drawLine(m_widgetWidth/10, y, m_widgetWidth/10 + longLength, y);
    }

    // 绘制中刻度线和短刻度线
    pen.setWidth(1);
    painter.setPen(pen);
    int shortStep = longStep / 4;
    for (int i = 0; i < m_division; ++i)
    {
        int baseY = m_widgetHeight/10 + i * longStep;
        for (int j = 1; j <= 3; ++j)
        {
            int y = baseY + j * shortStep;
            if (j == 2) // 中刻度线
            {
                painter.drawLine(m_widgetWidth/10 + longLength / 2 - midLength / 2, y, m_widgetWidth/10 + longLength / 2 + midLength / 2, y);
            }
            else // 短刻度线
            {
                painter.drawLine(m_widgetWidth/10 + longLength / 2 - shortLength / 2, y, m_widgetWidth/10 + longLength / 2 + shortLength / 2, y);
            }
        }
    }

    // 绘制标签
    pen.setColor(Qt::blue);
    painter.setPen(pen);
    painter.setFont(QFont("Arial", m_widgetHeight/25)); // 字体缩小一倍
    for (int i = 0; i <= m_division; ++i)
    {
        int y = m_widgetHeight/10 + i * longStep - m_widgetHeight/40;
        painter.drawText(m_widgetWidth/10*2 + longLength, y, m_widgetWidth*4/10, m_widgetWidth/10, Qt::AlignLeft, m_labels[m_division - i]); // 自上而下递减，标签位置调整
    }

    // 绘制当前值水平线段
    pen.setColor(Qt::red);
    pen.setWidth(2);
    painter.setPen(pen);
    int currentY = m_widgetHeight/10 + (m_highest - m_level) * m_widgetHeight*8/10 / (m_highest - m_lowest);
    painter.drawLine(m_widgetWidth/10+longLength*2/10, currentY, m_widgetWidth/10 + longLength*8/10, currentY);

    // 绘制三角箭头
    QPolygon arrow;
    arrow << QPoint(m_widgetWidth/10, currentY) << QPoint(m_widgetWidth/20, currentY - 5) << QPoint(m_widgetWidth/20, currentY + 5);
    painter.setBrush(Qt::red);
    painter.drawPolygon(arrow);
}
