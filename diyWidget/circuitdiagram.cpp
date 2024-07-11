#include "circuitdiagram.h"
#include <QPainter>
#include <QPen>
#include <QPaintEvent>

CircuitDiagram::CircuitDiagram(QWidget *parent) :
    QWidget(parent)
{
}

void CircuitDiagram::setPowerLevel(int pow)
{
    //设置当前电量值
    if (m_powerLevel != pow) {
        m_powerLevel = pow;
        emit powerLevelChanged(pow); //发射信号
        update();
    }
}

int CircuitDiagram::powerLevel()
{
    //返回当前电量值
    return m_powerLevel;
}

void CircuitDiagram::setWarnLevel(int warn)
{
    //设置电量低阈值
    if (m_warnLevel != warn) {
        m_warnLevel = warn;
        update();
    }
}

int CircuitDiagram::warnLevel()
{
    //返回电量低阈值
    return m_warnLevel;
}

// QSize CircuitDiagram::sizeHint() const
// {
//     //设置组件的合适大小
//     return QSize(250, 500);
// }

void CircuitDiagram::paintEvent(QPaintEvent *event)
{
    //绘制界面组件
    QPainter painter(this);
    QRect rect(0, 0, width(), height()); //视口矩形区
    painter.setViewport(rect); //设置视口
    painter.setWindow(0, 0, 250, 500); // 设置窗口大小，逻辑坐标，改成竖直方向
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    //绘制电池边框
    paintBattery(painter, rect);
    event->accept();
}

void CircuitDiagram::paintBattery(QPainter &painter, QRect &rect)
{
    QPen pen(colorBorder); //边框线条颜色
    pen.setWidth(2);
    painter.setPen(pen);

    QBrush brush(colorBack); //画刷颜色
    painter.setBrush(brush);

    int offset = 80; // 移动电池位置的偏移量

    // 绘制电池边框
    rect.setRect(1, 10 + offset, 48, 109); // 竖直方向的电池边框，从 y=10 开始
    painter.drawRect(rect); //绘制电池边框

    // 绘制电池正极头
    brush.setColor(colorBorder);
    painter.setBrush(brush);
    rect.setRect(15, offset, 20, 10); // 竖直方向的电池正极头，在顶部
    painter.drawRect(rect); //画电池正极头

    //设置电量柱的颜色
    if (m_powerLevel > m_warnLevel) {
        brush.setColor(colorPower);
        pen.setColor(colorPower);
    } else {
        brush.setColor(colorWarning);
        pen.setColor(colorWarning);
    }

    painter.setBrush(brush);
    painter.setPen(pen);

    if (m_powerLevel > 0) {
        int powerHeight = m_powerLevel; // 电量柱的高度
        int offset_y = 3; // 偏移量
        rect.setRect(5, 119 - powerHeight + offset_y + offset, 40, powerHeight - offset_y); // 竖直方向的电量柱，底部抬高3个单位
        painter.drawRect(rect); // 画电量柱
    }

    //绘制电量百分比文字
    QFontMetrics textSize(this->font());
    QString powStr = QString::asprintf("%d%%", m_powerLevel);
    QRect textRect = textSize.boundingRect(powStr); //得到字符串的矩形区
    painter.setFont(this->font());
    pen.setColor(colorBorder);
    painter.setPen(pen);
    painter.drawText(25 - textRect.width() / 2, 60 + textRect.height() / 2 + offset, powStr); // 在电池中间绘制电量百分比文字
}
