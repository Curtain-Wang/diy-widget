#include "tnewbattery.h"
#include <QPainter>
#include <QFontMetrics>
#include <QBrush>
#include <QLinearGradient>

TNewBattery::TNewBattery(QWidget *parent)
    : QWidget(parent), m_chargeLevel(70),m_batteryWidth(150), m_batteryHeight(80) { // 初始化电量为50%
    setMinimumSize(200, 140); // 增加最小宽度
}
int TNewBattery::batteryWidth() const {
    return m_batteryWidth;
}

void TNewBattery::setBatteryWidth(int width) {
    if (width != m_batteryWidth) {
        m_batteryWidth = width;
        emit batteryWidthChanged(width);
        update();
    }
}

int TNewBattery::batteryHeight() const {
    return m_batteryHeight;
}

void TNewBattery::setBatteryHeight(int height) {
    if (height != m_batteryHeight) {
        m_batteryHeight = height;
        emit batteryHeightChanged(height);
        update();
    }
}
int TNewBattery::chargeLevel() const {
    return m_chargeLevel;
}

void TNewBattery::setChargeLevel(int level) {
    if (level != m_chargeLevel) {
        m_chargeLevel = level;
        emit chargeLevelChanged(level);
        update();
    }
}

void TNewBattery::drawBatteryBody(QPainter &painter, const QRect &batteryRect, const QRect &blueRect) {
    // 深蓝色长方形
    painter.setBrush(Qt::darkBlue);
    painter.drawRect(blueRect);

    // 渐变效果
    QLinearGradient gradient(batteryRect.topLeft(), batteryRect.bottomLeft());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter.setBrush(gradient);
    painter.drawRect(batteryRect);
}

void TNewBattery::drawElectrodes(QPainter &painter, const QRect &batteryRect) {
    int electrodeWidth = batteryRect.width() / 10;
    int electrodeHeight = batteryRect.height() / 5; // 电极高度为电池高度的1/5
    int extension = electrodeWidth; // 向上延伸一个电极宽度
    QRect leftElectrode(batteryRect.left() + electrodeWidth * 0.5, batteryRect.top() - electrodeHeight - extension*0.7, electrodeWidth, electrodeHeight);
    QRect rightElectrode(batteryRect.right() - electrodeWidth * 1.5, batteryRect.top() - electrodeHeight - extension*0.7, electrodeWidth, electrodeHeight);
    painter.setBrush(Qt::black);
    painter.drawRect(leftElectrode);
    painter.drawRect(rightElectrode);
}

void TNewBattery::drawTrapezoid(QPainter &painter, const QRect &blueRect, int borderSize, int trapezoidHeight) {
    // 上部灰色梯形（上小下大）
    QPointF upperPoints[4] = {
        QPointF(blueRect.left() - borderSize / 2, blueRect.top() - trapezoidHeight), // 左上
        QPointF(blueRect.right() + borderSize / 2, blueRect.top() - trapezoidHeight), // 右上
        QPointF(blueRect.right(), blueRect.top()), // 右下
        QPointF(blueRect.left(), blueRect.top()) // 左下
    };
    painter.setBrush(Qt::gray);
    painter.drawPolygon(upperPoints, 4);
}

void TNewBattery::drawBase(QPainter &painter, const QRect &blueRect, int borderSize, int trapezoidHeight) {
    // 灰色底座
    QPointF lowerPoints[6] = {
        QPointF(blueRect.left(), blueRect.bottom()), // 左上
        QPointF(blueRect.right(), blueRect.bottom()), // 右上
        QPointF(blueRect.right() + borderSize / 2, blueRect.bottom() + trapezoidHeight), // 右中
        QPointF(blueRect.right() + borderSize / 2, blueRect.bottom() + trapezoidHeight * 1.5), // 右下
        QPointF(blueRect.left() - borderSize / 2, blueRect.bottom() + trapezoidHeight * 1.5), // 左下
        QPointF(blueRect.left() - borderSize / 2, blueRect.bottom() + trapezoidHeight) // 左中
    };
    painter.setBrush(Qt::gray);
    painter.drawPolygon(lowerPoints, 6);
}

void TNewBattery::drawChargeLevel(QPainter &painter, const QRect &batteryRect) {
    // 电池充电百分比
    int chargeHeight = static_cast<int>((batteryRect.height() - 2) * (m_chargeLevel / 100.0));
    QRect chargeRect(batteryRect.left() + 1, batteryRect.bottom() - chargeHeight, batteryRect.width() - 2, chargeHeight);
    painter.setBrush(Qt::green);
    painter.drawRect(chargeRect);

    // 显示电量百分比
    QString chargeText = QString("%1%").arg(m_chargeLevel);
    QFontMetrics fm = painter.fontMetrics();
    int textWidth = fm.horizontalAdvance(chargeText);
    int textHeight = fm.height();
    painter.setPen(Qt::black);
    painter.drawText(batteryRect.left() + (batteryRect.width() - textWidth) / 2,
                     batteryRect.top() + (batteryRect.height() + textHeight) / 2 - fm.descent(),
                     chargeText);
}

void TNewBattery::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 设置字体大小
    QFont font = painter.font();
    font.setPointSize(width() / 20);
    painter.setFont(font);

    // 电池主体
    QRect batteryRect(width() * 2 / 10, height() * 2 / 10, m_batteryWidth, m_batteryHeight);

    // 深蓝色长方形
    int borderSize = batteryRect.width() / 20;
    QRect blueRect(batteryRect.left() - borderSize, batteryRect.top() - borderSize, batteryRect.width() + borderSize * 2, batteryRect.height() + borderSize * 2);

    // 绘制电极
    drawElectrodes(painter, batteryRect);
    // 绘制电池主体和梯形
    drawBatteryBody(painter, batteryRect, blueRect);
    drawTrapezoid(painter, blueRect, borderSize, batteryRect.height() / 10);
    drawBase(painter, blueRect, borderSize, batteryRect.height() / 10);

    // 绘制充电百分比
    drawChargeLevel(painter, batteryRect);
}
