#include "tpnewbattery.h"
#include <QPainter>
#include <QFontMetrics>
#include <QBrush>
#include <QLinearGradient>
#include <QPropertyAnimation>

TPNewBattery::TPNewBattery(QWidget *parent)
    : QWidget(parent), m_chargeLevel(10), m_warningLevel(20) { // 初始化电量为10%
    setMinimumSize(200, 140); // 增加最小宽度
}

int TPNewBattery::chargeLevel() const {
    return m_chargeLevel;
}

void TPNewBattery::setChargeLevel(int level) {
    if (level != m_chargeLevel) {
        m_chargeLevel = level;
        emit chargeLevelChanged(level);
        update();
    }
}

int TPNewBattery::warningLevel() const {
    return m_warningLevel;
}

void TPNewBattery::setWarningLevel(int level) {
    if (level != m_warningLevel) {
        m_warningLevel = level;
        emit warningLevelChanged(level);
        update();
    }
}

void TPNewBattery::drawBatteryBody(QPainter &painter, const QRect &batteryRect, const QRect &blueRect) {
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

void TPNewBattery::drawElectrodes(QPainter &painter, const QRect &batteryRect) {
    int electrodeWidth = batteryRect.width() / 10;
    int electrodeHeight = batteryRect.height() / 5; // 电极高度为电池高度的1/5
    int extension = electrodeWidth; // 向上延伸一个电极宽度
    QRect leftElectrode(batteryRect.left() + electrodeWidth * 0.5, batteryRect.top() - electrodeHeight - extension * 0.7, electrodeWidth, electrodeHeight);
    QRect rightElectrode(batteryRect.right() - electrodeWidth * 1.5, batteryRect.top() - electrodeHeight - extension * 0.7, electrodeWidth, electrodeHeight);
    painter.setBrush(Qt::black);
    painter.drawRect(leftElectrode);
    painter.drawRect(rightElectrode);
}

void TPNewBattery::drawTrapezoid(QPainter &painter, const QRect &blueRect, int borderSize, int trapezoidHeight) {
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

void TPNewBattery::drawBase(QPainter &painter, const QRect &blueRect, int borderSize, int trapezoidHeight) {
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

void TPNewBattery::drawChargeLevel(QPainter &painter, const QRect &batteryRect) {
    // 电池充电百分比
    int chargeHeight = static_cast<int>((batteryRect.height() - 2) * (m_chargeLevel / 100.0));
    QRect chargeRect(batteryRect.left() + 1, batteryRect.bottom() - chargeHeight, batteryRect.width() - 2, chargeHeight);

    // 根据电量选择颜色
    if (m_chargeLevel < m_warningLevel) {
        painter.setBrush(Qt::yellow); // 电量低于警戒电量时显示黄色
    } else {
        painter.setBrush(Qt::green); // 电量正常时显示绿色
    }
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

void TPNewBattery::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 动态调整字体大小
    QFont font = painter.font();
    font.setPointSize(width() / 20);
    painter.setFont(font);

    // 计算电池的宽度和高度，使其充满画布并保持2:1的比例
    int batteryWidth = width() * 0.8; // 例如，占窗口宽度的80%
    int batteryHeight = batteryWidth / 2; // 保持2:1比例

    // 确保电池高度不会超过画布高度
    if (batteryHeight > height() * 0.8) {
        batteryHeight = height() * 0.8;
        batteryWidth = batteryHeight * 2;
    }

    // 电池主体
    QRect batteryRect((width() - batteryWidth) / 2, (height() - batteryHeight) / 2, batteryWidth, batteryHeight);

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
