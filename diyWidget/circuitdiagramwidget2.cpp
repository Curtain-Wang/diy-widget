#include "CircuitDiagramWidget2.h"
#include <QPainter>
#include <QFontMetrics>
#include <QBrush>
#include <QLinearGradient>
#include  <QPainterPath>
#include <QResizeEvent>
#include <QTimer>
CircuitDiagramWidget2::CircuitDiagramWidget2(QWidget *parent)
    : QWidget(parent), m_chargeLevel(0), m_warningLevel(20)
    , timer(new QTimer(this))
    , m_mainContactorClosed(true)
    , m_systemVoltage(0)
    , m_dischargeContactorClosed(true)
    , m_chargeContactorClosed(true)
    , m_heaterFaultContactorClosed(true)
    , m_isHeating(true)
    , m_heaterContactorClosed(true)
    , m_limitedContactorClosed(false)
    , m_discharged(true),
    m_packColor1(Qt::gray),  // 初始化为灰色
    m_packColor2(Qt::gray),  // 初始化为灰色
    m_packColor3(Qt::gray),  // 初始化为灰色
    m_packColor4(Qt::gray),  // 初始化为灰色
    m_packColor5(Qt::gray),  // 初始化为灰色
    m_packColor6(Qt::gray),   // 初始化为灰色
    m_language(2) //默认中文
{
    energyColor = Qt::white;
    setMinimumSize(200, 140);
    timer->setInterval(50);
    connect(timer, &QTimer::timeout, this, &CircuitDiagramWidget2::on_timer_timeout);
    if(m_discharged)
    {
        m_energyFlowPosition = DISCHARGE_START;
    }else
    {
        m_energyFlowPosition = CHARGE_START;
    }
    //有闭合回路才开启定时器
    if(ifCloseLoop())
    {
        timer->start();
    }
}

int CircuitDiagramWidget2::chargeLevel() const {
    return m_chargeLevel;
}

void CircuitDiagramWidget2::setChargeLevel(int level) {
    if (level != m_chargeLevel) {
        m_chargeLevel = level;
        emit chargeLevelChanged(level);
        update();
    }
}

int CircuitDiagramWidget2::warningLevel() const {
    return m_warningLevel;
}

void CircuitDiagramWidget2::setWarningLevel(int level) {
    if (level != m_warningLevel) {
        m_warningLevel = level;
        emit warningLevelChanged(level);
        update();
    }
}

double CircuitDiagramWidget2::systemVoltage() const {
    return m_systemVoltage;
}

void CircuitDiagramWidget2::setSystemVoltage(double voltage) {
    if (voltage != m_systemVoltage) {
        m_systemVoltage = voltage;
        emit systemVoltageChanged(voltage);
        update();
    }
}

bool CircuitDiagramWidget2::mainContactorClosed() const {
    return m_mainContactorClosed;
}

void CircuitDiagramWidget2::setMainContactorClosed(bool closed) {
    if (closed != m_mainContactorClosed) {
        m_mainContactorClosed = closed;
        emit mainContactorClosedChanged(closed);
        update();
    }
}

bool CircuitDiagramWidget2::dischargeContactorClosed() const {
    return m_dischargeContactorClosed;
}

void CircuitDiagramWidget2::setDischargeContactorClosed(bool closed) {
    if (closed != m_dischargeContactorClosed) {
        m_dischargeContactorClosed = closed;
        emit dischargeContactorClosedChanged(closed);
        timerAndEnergyAdjust();
        update();

    }
}

bool CircuitDiagramWidget2::chargeContactorClosed() const {
    return m_chargeContactorClosed;
}

void CircuitDiagramWidget2::setChargeContactorClosed(bool closed) {
    if (closed != m_chargeContactorClosed) {
        m_chargeContactorClosed = closed;
        emit chargeContactorClosedChanged(closed);
        timerAndEnergyAdjust();
        update();
    }
}

bool CircuitDiagramWidget2::heaterFaultContactorClosed() const {
    return m_heaterFaultContactorClosed;
}

void CircuitDiagramWidget2::setHeaterFaultContactorClosed(bool closed) {
    if (closed != m_heaterFaultContactorClosed) {
        m_heaterFaultContactorClosed = closed;
        emit heaterFaultContactorClosedChanged(closed);
        update();
    }
}

bool CircuitDiagramWidget2::isHeating() const {
    return m_isHeating;
}

void CircuitDiagramWidget2::setIsHeating(bool heating) {
    if (heating != m_isHeating) {
        m_isHeating = heating;
        emit isHeatingChanged(heating);
        update();
    }
}

bool CircuitDiagramWidget2::heaterContactorClosed() const {
    return m_heaterContactorClosed;
}

void CircuitDiagramWidget2::setHeaterContactorClosed(bool closed) {
    if (closed != m_heaterContactorClosed) {
        m_heaterContactorClosed = closed;
        emit heaterContactorClosedChanged(closed);
        update();
    }
}

bool CircuitDiagramWidget2::limitedContactorClosed() const {
    return m_limitedContactorClosed;
}

void CircuitDiagramWidget2::setLimitedContactorClosed(bool closed) {
    if (closed != m_limitedContactorClosed) {
        m_limitedContactorClosed = closed;
        emit limitedContactorClosedChanged(closed);
        timerAndEnergyAdjust();
        update();
    }
}

QColor CircuitDiagramWidget2::packColor1() const {
    return m_packColor1;
}

void CircuitDiagramWidget2::setPackColor1(const QColor &color) {
    if (color != m_packColor1) {
        m_packColor1 = color;
        emit packColor1Changed(color);
        update();
    }
}

QColor CircuitDiagramWidget2::packColor2() const {
    return m_packColor2;
}

void CircuitDiagramWidget2::setPackColor2(const QColor &color) {
    if (color != m_packColor2) {
        m_packColor2 = color;
        emit packColor2Changed(color);
        update();
    }
}

QColor CircuitDiagramWidget2::packColor3() const {
    return m_packColor3;
}

void CircuitDiagramWidget2::setPackColor3(const QColor &color) {
    if (color != m_packColor3) {
        m_packColor3 = color;
        emit packColor3Changed(color);
        update();
    }
}

QColor CircuitDiagramWidget2::packColor4() const {
    return m_packColor4;
}

void CircuitDiagramWidget2::setPackColor4(const QColor &color) {
    if (color != m_packColor4) {
        m_packColor4 = color;
        emit packColor4Changed(color);
        update();
    }
}

QColor CircuitDiagramWidget2::packColor5() const {
    return m_packColor5;
}

void CircuitDiagramWidget2::setPackColor5(const QColor &color) {
    if (color != m_packColor5) {
        m_packColor5 = color;
        emit packColor5Changed(color);
        update();
    }
}

QColor CircuitDiagramWidget2::packColor6() const {
    return m_packColor6;
}

void CircuitDiagramWidget2::setPackColor6(const QColor &color) {
    if (color != m_packColor6) {
        m_packColor6 = color;
        emit packColor6Changed(color);
        update();
    }
}

quint8 CircuitDiagramWidget2::language() const {
    return m_language;
}

void CircuitDiagramWidget2::setLanguage(const quint8 &language) {
    if (m_language != language) {
        m_language = language;
        emit languageChanged(m_language);
        update(); // 更新界面以反映语言更改
    }
}

bool CircuitDiagramWidget2::discharged() const
{
    return m_discharged;
}

void CircuitDiagramWidget2::setDischarged(const bool &discharged)
{
    if(m_discharged != discharged)
    {
        m_discharged = discharged;
        emit dischargedChanged(discharged);
        update();
        if(discharged)
        {
            m_energyFlowPosition = DISCHARGE_START;
        }else
        {
            m_energyFlowPosition = CHARGE_START;
        }
    }
}

void CircuitDiagramWidget2::drawBatteryBody(QPainter &painter, const QRect &batteryRect, const QRect &blueRect) {
    painter.setBrush(Qt::darkBlue);
    painter.drawRect(blueRect);

    QLinearGradient gradient(batteryRect.topLeft(), batteryRect.bottomLeft());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter.setBrush(gradient);
    painter.drawRect(batteryRect);
}

void CircuitDiagramWidget2::drawElectrodes(QPainter &painter, const QRect &batteryRect) {
    int electrodeWidth = batteryRect.width() / 10;
    int electrodeHeight = batteryRect.height() / 5;
    int extension = electrodeWidth;
    QRect leftElectrode(batteryRect.left() + electrodeWidth * 0.5, batteryRect.top() - electrodeHeight - extension * 0.7, electrodeWidth, electrodeHeight);
    QRect rightElectrode(batteryRect.right() - electrodeWidth * 1.5, batteryRect.top() - electrodeHeight - extension * 0.7, electrodeWidth, electrodeHeight);
    painter.setBrush(Qt::black);
    painter.drawRect(leftElectrode);
    painter.drawRect(rightElectrode);
}

void CircuitDiagramWidget2::drawTrapezoid(QPainter &painter, const QRect &blueRect, int borderSize, int trapezoidHeight) {
    QPointF upperPoints[4] = {
        QPointF(blueRect.left() - borderSize / 2, blueRect.top() - trapezoidHeight),
        QPointF(blueRect.right() + borderSize / 2, blueRect.top() - trapezoidHeight),
        QPointF(blueRect.right(), blueRect.top()),
        QPointF(blueRect.left(), blueRect.top())
    };
    painter.setBrush(Qt::gray);
    painter.drawPolygon(upperPoints, 4);
}

void CircuitDiagramWidget2::drawBase(QPainter &painter, const QRect &blueRect, int borderSize, int trapezoidHeight) {
    QPointF lowerPoints[6] = {
        QPointF(blueRect.left(), blueRect.bottom()),
        QPointF(blueRect.right(), blueRect.bottom()),
        QPointF(blueRect.right() + borderSize / 2, blueRect.bottom() + trapezoidHeight),
        QPointF(blueRect.right() + borderSize / 2, blueRect.bottom() + trapezoidHeight * 1.5),
        QPointF(blueRect.left() - borderSize / 2, blueRect.bottom() + trapezoidHeight * 1.5),
        QPointF(blueRect.left() - borderSize / 2, blueRect.bottom() + trapezoidHeight)
    };
    painter.setBrush(Qt::gray);
    painter.drawPolygon(lowerPoints, 6);
}

void CircuitDiagramWidget2::drawChargeLevel(QPainter &painter, const QRect &batteryRect) {
    int chargeHeight = static_cast<int>((batteryRect.height() - 2) * (m_chargeLevel / 100.0));
    QRect chargeRect(batteryRect.left() + 1, batteryRect.bottom() - chargeHeight, batteryRect.width() - 2, chargeHeight);

    if (m_chargeLevel < m_warningLevel) {
        painter.setBrush(Qt::yellow);
    } else {
        painter.setBrush(Qt::green);
    }
    painter.drawRect(chargeRect);

    QFont font = painter.font();
    font.setPointSize(font.pointSize() * 1.5); // 调整字体大小（这里放大 1.5 倍）
    painter.setFont(font);

    QString chargeText = QString("%1%").arg(m_chargeLevel);
    QFontMetrics fm = painter.fontMetrics();
    int textWidth = fm.horizontalAdvance(chargeText);
    int textHeight = fm.height();
    painter.setPen(Qt::black);
    painter.drawText(batteryRect.left() + (batteryRect.width() - textWidth) / 2,
                     batteryRect.top() + (batteryRect.height() + textHeight) / 2 - fm.descent(),
                     chargeText);

    font = painter.font();
    font.setPointSize(font.pointSize() / 1.5); // 还原字体大小
    painter.setFont(font);
}

/**
 * 放电起点 0
 * 长度 width() / 4 - width() / 24 + width() / 40
 * @brief CircuitDiagramWidget2::drawWireToMainContactor
 * @param painter
 * @param batteryX
 * @param batteryY
 * @param batteryWidth
 * @param batteryHeight
 */
void CircuitDiagramWidget2::drawWireToMainContactor(QPainter &painter, int batteryX, int batteryY, int batteryWidth, int batteryHeight)
{
    // 还原视口和窗口设置，以绘制其他部分
    painter.setViewport(0, 0, width(), height());
    painter.setWindow(0, 0, width(), height());

    int penWidth = 5;
    // 电池左侧电极的坐标
    int electrodeWidth = batteryWidth / 10;
    int electrodeHeight = batteryHeight / 5;
    int extension = electrodeWidth;
    QRect leftElectrode(batteryX + electrodeWidth * 0.5, batteryY - electrodeHeight - extension * 0.7, electrodeWidth, electrodeHeight);

    int batteryPosX = leftElectrode.center().x(); // 使用电极的中心x坐标
    int batteryPosY = leftElectrode.top() - batteryHeight / 50; // 使用电极的顶部y坐标

    // 垂直线长度为电池高度的1/4
    int verticalLineLength = batteryHeight / 4;

    // 主接触器的位置 (相对电池)
    int horizontalLineLength = width() / 4 - width() / 24; // 连接到主接触器的水平线长度
    int centerDistance = batteryWidth / 4; // 主接触器两个圆心之间的距离

    int mainContactorX = batteryPosX - horizontalLineLength - centerDistance; // 向左延伸以连接到右侧圆的圆弧
    mianContactorStartX = mainContactorX;
    int mainContactorY = batteryPosY - verticalLineLength;

    // 判断并绘制从电池正极到主接触器的线
    QPen pen(Qt::red);
    pen.setWidth(penWidth);
    painter.setPen(pen);

    if (m_energyFlowPosition <= verticalLineLength && m_energyFlowPosition > 0) {
        // 绘制垂直部分电线
        if (m_energyFlowPosition > 0) {
            // 绘制能量块之前的电线部分
            painter.drawLine(batteryPosX, batteryPosY, batteryPosX, batteryPosY - m_energyFlowPosition);
        }
        if (m_energyFlowPosition + energyBlockWidth <= verticalLineLength) {
            // 绘制能量块完全在垂直部分
            drawGradientLineSegment(batteryPosX, batteryPosY - m_energyFlowPosition - energyBlockWidth,
                                    batteryPosX, batteryPosY - m_energyFlowPosition, Qt::red, painter);

            // 绘制能量块之后的垂直部分电线
            painter.drawLine(batteryPosX, batteryPosY - m_energyFlowPosition - energyBlockWidth, batteryPosX, batteryPosY - verticalLineLength);

            // 绘制水平部分电线
            painter.drawLine(batteryPosX, batteryPosY - verticalLineLength, mainContactorX + centerDistance, batteryPosY - verticalLineLength);

        } else {
            // 能量块部分在垂直部分，部分在水平部分
            int remainingLength = verticalLineLength - m_energyFlowPosition;

            // 计算渐变起点和终点，跨越垂直和水平部分
            drawGradientPolylineSegment(batteryPosX, batteryPosY - m_energyFlowPosition, batteryPosX, batteryPosY - verticalLineLength
                                        ,batteryPosX - (energyBlockWidth - remainingLength), batteryPosY - verticalLineLength
                                        ,Qt::red, painter);
            // 绘制能量块之后的水平部分电线
            painter.drawLine(batteryPosX - (energyBlockWidth - remainingLength), batteryPosY - verticalLineLength, mainContactorX + centerDistance, batteryPosY - verticalLineLength);
        }

    } else if(m_energyFlowPosition > verticalLineLength && m_energyFlowPosition + energyBlockWidth < width() * 7 / 30){
        // 绘制垂直部分电线（能量块已经通过此段）
        painter.drawLine(batteryPosX, batteryPosY, batteryPosX, batteryPosY - verticalLineLength);

        // 水平部分电线的绘制
        int horizontalPosition = m_energyFlowPosition - verticalLineLength;

        if (horizontalPosition > 0) {
            // 绘制能量块之前的电线部分
            painter.drawLine(batteryPosX, batteryPosY - verticalLineLength, batteryPosX - horizontalLineLength, batteryPosY - verticalLineLength);
        }

        // 绘制能量块对应的电线部分
        drawGradientLineSegment(batteryPosX - horizontalPosition, batteryPosY - verticalLineLength,
                                batteryPosX - horizontalPosition - energyBlockWidth, batteryPosY - verticalLineLength,
                                Qt::red, painter);
        // 绘制能量块之后的水平部分电线
        painter.setPen(pen);
        painter.drawLine(batteryPosX - horizontalPosition - energyBlockWidth, batteryPosY - verticalLineLength, mainContactorX + centerDistance, batteryPosY - verticalLineLength);
    }else{
        pen.setColor(Qt::red); // 恢复原始颜色
        painter.setPen(pen);
        //垂直
        painter.drawLine(batteryPosX, batteryPosY, batteryPosX, batteryPosY - verticalLineLength);
        //水平
        painter.drawLine(batteryPosX, batteryPosY - verticalLineLength, batteryPosX - horizontalLineLength, batteryPosY - verticalLineLength);
    }

    // 绘制主接触器
    drawMainContactor(painter, mainContactorX, mainContactorY, batteryWidth);

    // 绘制从主接触器到系统电压的导线
    drawWireToSystemVoltage(painter, mainContactorX, mainContactorY, batteryWidth);
}


void CircuitDiagramWidget2::on_timer_timeout()
{
    bool flag = !m_chargeContactorClosed && m_limitedContactorClosed;
    if(m_discharged)
    {
        m_energyFlowPosition += 5; // 调整速度
        if (!flag && m_energyFlowPosition + energyBlockWidth > horizontalEndX - chargeContactorEndx + width() * 11 / 12 + height() * 19 / 12 + 28) {
            m_energyFlowPosition = 0; // 循环能量块的位置
        }
        if(flag && m_energyFlowPosition + energyBlockWidth > width() * 37/40 + height() * 23/12 + horizontalEndX - chargeContactorEndx + 28){
            m_energyFlowPosition = 0; // 循环能量块的位置
        }
    }else
    {
        //充电
        m_energyFlowPosition -= 5;
        m_chargeHeatEnergyFlowPosition += 5;
        if(m_energyFlowPosition < 0)
        {
            if(flag)
            {
                m_energyFlowPosition = width() * 37/40 + height() * 23/12 + horizontalEndX - chargeContactorEndx;
            }else
            {
                m_energyFlowPosition = horizontalEndX - chargeContactorEndx + width() * 11 / 12 + height() * 19 / 12;
            }
        }
        if(m_energyFlowPosition - (width()*9/40+height()*1/3+16) + energyBlockWidth > height() / 2 - 8 - width() * 1 / 40)
        {
            m_energyFlowPosition = 0;
            wireToDischHeadflag = false;
        }
    }
    update(); // 重新绘制界面
}

void CircuitDiagramWidget2::drawMainContactor(QPainter &painter, int x, int y, int batteryWidth)
{
    int radius = 4;
    int centerDistance = batteryWidth / 4; // 调整为电池宽度的1/4

    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制两个圆
    QPen pen(Qt::red); // 圆和线的颜色
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(Qt::white);
    painter.drawEllipse(x - radius, y - radius, radius * 2, radius * 2);
    painter.drawEllipse(x + centerDistance - radius, y - radius, radius * 2, radius * 2);

    // 绘制开关线
    QLineF line;
    QPointF startPoint(x, y - radius); // 从圆弧位置开始
    if (m_mainContactorClosed) // 假设有一个bool类型变量 mainContactorClosed 来表示接触器状态
    {
        // 闭合状态：水平线
        QPointF endPoint(x + centerDistance, y - radius);
        line.setP1(startPoint);
        line.setP2(endPoint);
    }
    else
    {
        // 打开状态：与水平夹角345度，斜向右上
        double angle = 15.0; // 与水平线的夹角是345度，即360-15度
        double length = centerDistance;
        QPointF endPoint(x + length * cos(qDegreesToRadians(angle)), y - radius - length * sin(qDegreesToRadians(angle)));
        line.setP1(startPoint);
        line.setP2(endPoint);
    }
    painter.drawLine(line);
}

/**
 *
 * 放电起点  width() * 7 / 30 + width() * 0.2 / 4 + 8 = width() * 17 / 60 + 8
 * 长度 width() * 3 / 10
 * @brief CircuitDiagramWidget2::drawWireToSystemVoltage
 * @param painter
 * @param mainContactorX
 * @param mainContactorY
 * @param batteryWidth
 */
void CircuitDiagramWidget2::drawWireToSystemVoltage(QPainter &painter, int mainContactorX, int mainContactorY, int batteryWidth)
{
    double startLength = width() * 17 / 60 + 8;
    // 还原视口和窗口设置，以绘制其他部分
    painter.setViewport(0, 0, width(), height());
    painter.setWindow(0, 0, width(), height());

    QPen pen(Qt::red); // 导线颜色
    pen.setWidth(5);
    painter.setPen(pen);

    // 水平线的起点是主接触器左侧圆弧,-2是因为线太粗了
    int startX = mainContactorX - 4 - 2;
    int startY = mainContactorY;

    // 计算水平线的终点位置
    int horizontalLineLength = width() / 3 - width() / 30;
    int endX = startX - horizontalLineLength;

    if(m_energyFlowPosition > startLength && m_energyFlowPosition + energyBlockWidth < width() * 7 / 12 + 8)
    {
        int horizontalPosition = m_energyFlowPosition - startLength;
        //绘制能量块之前的水平线
        painter.drawLine(startX, startY, startX - horizontalPosition, startY);
        // 绘制能量块对应的电线部分
        drawGradientLineSegment(startX - horizontalPosition, startY,
                                startX - horizontalPosition - energyBlockWidth, startY,
                                Qt::red, painter);
        // 绘制能量块之后的水平部分电线
        painter.drawLine(startX - horizontalPosition - energyBlockWidth, startY, endX, startY);
    }else
    {
        painter.drawLine(startX, startY, startX - horizontalLineLength, startY);
    }

    // 绘制垂直线
    int verticalLineLength = height() / 3;
    pen.setWidth(2);
    pen.setStyle(Qt::DashLine);
    painter.setPen(pen);
    painter.drawLine(endX, startY, endX, startY + verticalLineLength);
    pen.setStyle(Qt::SolidLine);
    // 绘制系统电压
    drawSystemVoltage(painter, endX, startY + verticalLineLength);

    //连向绘制加热故障开关的线
    drawWireToHeaterFaultContactor(painter, mainContactorX, mainContactorY, batteryWidth);
}

/**
 * 放电起点 width() * 59 / 120 + 8
 * 长度 height() / 12
 * 充电起点 width() * 11 / 120
 * @brief CircuitDiagramWidget2::drawWireToHeaterFaultContactor
 * @param painter
 * @param mainContactorX
 * @param mainContactorY
 * @param batteryWidth
 */
void CircuitDiagramWidget2::drawWireToHeaterFaultContactor(QPainter &painter, int mainContactorX, int mainContactorY, int batteryWidth)
{
    double startLength = width() * 59 / 120 + 8;
    // 还原视口和窗口设置，以绘制其他部分
    painter.setViewport(0, 0, width(), height());
    painter.setWindow(0, 0, width(), height());

    QPen pen(Qt::red); // 导线颜色
    pen.setWidth(5);
    painter.setPen(pen);

    // 水平线的起点是主接触器左侧圆弧
    int startX = mainContactorX - width() * 13 / 48 + width() / 12 - width() / 48;
    int startY = mainContactorY;

    // 绘制垂直线
    int verticalLineLength = height() / 12;
    int verticalEndY = startY + verticalLineLength;
    //放电情况
    if(m_discharged && m_heaterFaultContactorClosed && m_heaterContactorClosed && m_energyFlowPosition >= startLength && m_energyFlowPosition + energyBlockWidth < startLength + verticalLineLength)
    {
        //能量块之前的部分
        painter.drawLine(startX, startY, startX, startY + m_energyFlowPosition - startLength);
        //能量块所代表的电线
        drawGradientLineSegment(startX, startY + m_energyFlowPosition - startLength,
                                startX, startY + m_energyFlowPosition - startLength + energyBlockWidth,
                                Qt::red, painter);
    }else if(!m_discharged && m_heaterFaultContactorClosed && m_heaterContactorClosed && m_chargeHeatEnergyFlowPosition >= width() * 11 / 120 && m_chargeHeatEnergyFlowPosition - width() * 11 / 120 + energyBlockWidth <=  verticalLineLength)
    {
        int positionInLine = m_chargeHeatEnergyFlowPosition - width() * 11 / 120;
        //绘制能量块之前的电线
        painter.drawLine(startX, startY, startX, startY + positionInLine);
        //绘制能量块覆盖的电线
        drawGradientLineSegment(startX, startY + positionInLine, startX, startY + positionInLine + energyBlockWidth, Qt::red, painter);
        //绘制能量块之后的电线
        painter.drawLine(startX, startY + positionInLine + energyBlockWidth, startX, verticalEndY);
    }else{
        painter.drawLine(startX, startY, startX, verticalEndY);
    }
    // 绘制加热故障接触器
    drawHeaterFaultContactor(painter, startX, verticalEndY, batteryWidth);
}

void CircuitDiagramWidget2::drawHeaterFaultContactor(QPainter &painter, int x, int y, int batteryWidth)
{
    int radius = 4;
    int centerDistance = batteryWidth / 4; // 调整为电池宽度的1/4

    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制两个圆
    QPen pen(Qt::red); // 圆和线的颜色
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(Qt::white);
    painter.drawEllipse(x - radius, y - radius, radius * 2, radius * 2);
    painter.drawEllipse(x - radius, y + centerDistance - radius, radius * 2, radius * 2);

    // 绘制开关线
    QLineF line;
    QPointF startPoint(x + radius, y); // 从上圆的右侧开始
    if (m_heaterFaultContactorClosed) // 假设有一个bool类型变量 m_heaterFaultContactorClosed 来表示接触器状态
    {
        // 闭合状态：竖直线
        QPointF endPoint(x + radius, y + centerDistance);
        line.setP1(startPoint);
        line.setP2(endPoint);
    }
    else
    {
        // 打开状态：向右下方延伸
        double angle = 75.0;//与垂直线的夹角是75度
        double length = centerDistance;
        QPointF endPoint(x + radius + length * cos(qDegreesToRadians(angle)), y + length + sin(qDegreesToRadians(angle)));
        line.setP1(startPoint);
        line.setP2(endPoint);
    }
    painter.drawLine(line);

    //绘制连接加热器的线
    drawWireToHeater(painter, x, y + centerDistance + 4, batteryWidth);
}

/**
 * 放电起点： width() * 59 / 120 + 8 + width() * 0.2 / 4 + 8 = width() * 13 / 24 + 16
 * 长度： height() / 6 + width() / 30
 * 充电起点：width() * 17 / 120 + height() / 12 + 8
 * @brief CircuitDiagramWidget2::drawWireToHeater
 * @param painter
 * @param heaterFaultContactorX
 * @param heaterFaultContactorY
 * @param batteryWidth
 */
void CircuitDiagramWidget2::drawWireToHeater(QPainter &painter, int heaterFaultContactorX, int heaterFaultContactorY, int batteryWidth)
{
    double startLength = width() * 13 / 24 + 16; // 这个值是能量块进入该部分的开始位置

    // 还原视口和窗口设置，以绘制其他部分
    painter.setViewport(0, 0, width(), height());
    painter.setWindow(0, 0, width(), height());

    QPen pen(Qt::red); // 导线颜色
    pen.setWidth(5);
    painter.setPen(pen);

    // 垂直线的起点是加热故障接触器下侧圆弧, +2是因为电线太粗了
    int startX = heaterFaultContactorX;
    int startY = heaterFaultContactorY + 2;

    // 计算垂直线的终点位置
    int verticalLineLength = height() / 6;
    int verticalEndY = startY + verticalLineLength;

    int length = width() / 30; // 加热器的水平位置可以调整

    // 判断能量块是否已经进入到此部分
    double positionInLine = 0.0;
    if (m_discharged && m_heaterContactorClosed && m_heaterFaultContactorClosed && m_energyFlowPosition >= startLength && m_energyFlowPosition + energyBlockWidth < startLength + height() / 6 + width() / 30) {
         positionInLine = m_energyFlowPosition - startLength;
    }
    if(!m_discharged && m_heaterContactorClosed && m_heaterFaultContactorClosed
        && m_chargeHeatEnergyFlowPosition >= width() * 17 / 120 + height() / 12 + 8
        && m_chargeHeatEnergyFlowPosition - (width() * 17 / 120 + height() / 12 + 8) + energyBlockWidth <= (height() / 6 + width() / 30))
    {
        positionInLine = m_chargeHeatEnergyFlowPosition - (width() * 17 / 120 + height() / 12 + 8);
    }

    if (positionInLine > 0) {
        if (positionInLine <= verticalLineLength) {
            // 能量块在垂直线段内之前的部分
            if (positionInLine > 0) {
                // 绘制能量块之前的电线部分
                painter.drawLine(startX, startY, startX, startY + positionInLine);
            }
            //能量块完全在垂直线段内
            if(positionInLine + energyBlockWidth < verticalLineLength){
                // 绘制能量块完全在垂直部分
                drawGradientLineSegment(startX, startY + positionInLine,
                                        startX, startY + positionInLine + energyBlockWidth,
                                        Qt::red, painter);
                // 绘制能量块之后的垂直部分电线
                painter.drawLine(startX, startY + positionInLine + energyBlockWidth, startX, verticalEndY);
                // 绘制水平部分电线
                painter.drawLine(startX, verticalEndY, startX + length - 2, verticalEndY);
            }else
            {
                // 能量块部分在垂直部分，部分在水平部分
                int remainingLength = verticalLineLength - positionInLine;

                // 计算渐变起点和终点，跨越垂直和水平部分
                drawGradientPolylineSegment(startX, startY + positionInLine,
                                            startX, verticalEndY,
                                            startX + (energyBlockWidth - remainingLength), verticalEndY,
                                            Qt::red, painter);
                // 绘制能量块之后的水平部分电线
                painter.drawLine(startX + (energyBlockWidth - remainingLength), verticalEndY, startX + length - 2, verticalEndY);
            }
        } else {
            // 能量块完全在水平部分之后
            painter.drawLine(startX, startY, startX, verticalEndY);
            //绘制能量块之前的水平线
            positionInLine -= verticalLineLength;
            painter.drawLine(startX, verticalEndY, startX + positionInLine, verticalEndY);
            //绘制能量块部分的水平线
            drawGradientLineSegment(startX + positionInLine, verticalEndY,
                                    startX + positionInLine + energyBlockWidth, verticalEndY,
                                    Qt::red, painter);
            //绘制能量块之后的水平线
            painter.drawLine(startX + positionInLine + energyBlockWidth, verticalEndY, startX + length - 2, verticalEndY);
        }
    } else {
        // 绘制不包含能量块的完整电线
        painter.drawLine(startX, startY, startX, verticalEndY);
        //-2是电线太粗了
        painter.drawLine(startX, verticalEndY, startX + length - 2, verticalEndY);
    }

    // 绘制加热器
    drawHeater(painter, startX + length, verticalEndY - batteryWidth / 4, batteryWidth / 2);
}


void CircuitDiagramWidget2::drawHeater(QPainter &painter, int x, int y, int side)
{
    // 设置正方形边框画笔颜色和宽度
    QPen squarePen(Qt::black);
    int penWidth = 3;
    squarePen.setWidth(penWidth);
    painter.setPen(squarePen);
    painter.setBrush(Qt::NoBrush); // 设置为无填充

    // 绘制一个空心正方形，调整位置以避免边缘被裁剪
    int actualSide = side - penWidth;  // 减去更多高度以腾出空间给波浪线
    painter.drawRect(x, y, actualSide, actualSide);

    int lineCount = 3;
    int waveHeight = 10;  // 波浪线高度
    int waveFrequency = 20; // 波浪线频率，每次移动的距离

    // 绘制三条竖线
    for (int i = 1; i <= lineCount; ++i)
    {
        int lineX = x + (actualSide / (lineCount + 1)) * i;
        int startY = y;
        int endY = y + actualSide;
        int waveStartY = startY + 0.2 * actualSide;
        int waveEndY = startY + 0.8 * actualSide;

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
        int smokeHeight = actualSide / 2;  // 增加波浪线高度
        int smokeFrequency = 20;
        int smokeWidth = actualSide / (smokeCount + 1);

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
    drawWireToHeaterContactor(painter, x, y, side);
}

/**
 * 放电起点：width() * 23 / 40 + height() / 6 + 16
 * 长度：height() / 12
 * 充电起点：width() * 7 / 40 + height() / 4 + 8
 * @brief CircuitDiagramWidget2::drawWireToHeaterContactor
 * @param painter
 * @param heaterX
 * @param heaterY
 * @param heaterWidth
 */
void CircuitDiagramWidget2::drawWireToHeaterContactor(QPainter &painter, int heaterX, int heaterY, int heaterWidth)
{

    // 还原视口和窗口设置，以绘制其他部分
    painter.setViewport(0, 0, width(), height());
    painter.setWindow(0, 0, width(), height());

    QPen pen(Qt::black); // 导线颜色
    pen.setWidth(5);
    painter.setPen(pen);

    // 垂直线的起点是加热器底部
    int startX = heaterX + heaterWidth / 2;
    int startY = heaterY + heaterWidth;

    // 计算垂直线的终点位置
    int verticalLineLength = height() / 12;
    int verticalEndY = startY + verticalLineLength;

    int positionInLine = -1;
    if(m_discharged && m_heaterContactorClosed && m_heaterFaultContactorClosed && m_energyFlowPosition >= width() * 23 / 40 + height() / 6 + 16 && m_energyFlowPosition + energyBlockWidth <= width() * 23 / 40 + height() / 6 + 16 + verticalLineLength)
    {
        int startLength = width() * 23 / 40 + height() / 6 + 16;
        positionInLine = m_energyFlowPosition - startLength;
    }
    if(!m_discharged && m_heaterContactorClosed && m_heaterFaultContactorClosed
        && m_chargeHeatEnergyFlowPosition >= width() * 7 / 40 + height() / 4 + 8
        && m_chargeHeatEnergyFlowPosition - (width() * 7 / 40 + height() / 4 + 8) + energyBlockWidth <= height() / 12)
    {
        positionInLine = m_chargeHeatEnergyFlowPosition - (width() * 7 / 40 + height() / 4 + 8);
    }

    //能量块在此垂直线段
    if(positionInLine >= 0)
    {

        if(positionInLine > 0)
        {
            //绘制能量块之前的部分
           painter.drawLine(startX, startY, startX, startY + positionInLine);
        }
        //绘制能量块部分
        drawGradientLineSegment(startX, startY + positionInLine,
                                startX, startY + positionInLine + energyBlockWidth,
                                Qt::black, painter);
        //绘制能量块之后的部分
        painter.drawLine(startX, startY + positionInLine + energyBlockWidth, startX, verticalEndY);
    }
    else
    {
        // 绘制垂直线
        painter.drawLine(startX, startY, startX, verticalEndY);
    }
    // 在垂直线末端绘制加热接触器
    drawHeaterContactor(painter, startX, verticalEndY);
}

/**
 * 放电起点（加热开关下方位置）: width() * 5 / 8 + height() / 4 + 24
 * （加热开关下方那条线长度: height() / 2 - 8 - width() * 3 / 20
 * 充电起点： width()∗9/40+height()∗1/3+16；
 * @brief CircuitDiagramWidget2::drawHeaterContactor
 * @param painter
 * @param x
 * @param y
 */
void CircuitDiagramWidget2::drawHeaterContactor(QPainter &painter, int x, int y)
{
    int radius = 4;
    int centerDistance = width() / 20; // 调整为电池宽度的1/4

    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制两个圆
    QPen pen(Qt::black); // 圆和线的颜色
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(Qt::white);
    painter.drawEllipse(x - radius, y - radius, radius * 2, radius * 2);
    painter.drawEllipse(x - radius, y + centerDistance - radius, radius * 2, radius * 2);

    // 绘制开关线
    QLineF line;
    QPointF startPoint(x + radius, y); // 从上圆的右侧开始
    if (m_heaterContactorClosed) // 假设有一个bool类型变量 m_heaterContactorClosed 来表示接触器状态
    {
        // 闭合状态：竖直线
        QPointF endPoint(x + radius, y + centerDistance);
        line.setP1(startPoint);
        line.setP2(endPoint);
    }
    else
    {
        // 打开状态：向右下方延伸
        double angle = 75.0; // 与垂直线的夹角是15度
        double length = centerDistance;
        QPointF endPoint(x + radius + length * cos(qDegreesToRadians(angle)), y + length * sin(qDegreesToRadians(angle)));
        line.setP1(startPoint);
        line.setP2(endPoint);
    }
    painter.drawLine(line);

    pen.setWidth(5);
    painter.setPen(pen);
    //绘制垂直向下的电线
    int startX = x;
    //+2是因为线太粗了
    int startY = y + centerDistance + 4 + 2;
    //-4是因为线太粗了
    int length = height() / 2 - 8 - width() * 3 / 20 - 4;



    //能量块逻辑
    int positionInLine = -1;
    if(m_discharged && m_heaterContactorClosed && m_heaterFaultContactorClosed && m_energyFlowPosition -  (width() * 5 / 8 + height() / 4 + 24) >= 0 && m_energyFlowPosition -  (width() * 5 / 8 + height() / 4 + 24) + energyBlockWidth <= length)
    {
        positionInLine = m_energyFlowPosition -  (width() * 5 / 8 + height() / 4 + 24);
    }
    if(!m_discharged && m_heaterContactorClosed && m_heaterFaultContactorClosed
        && m_energyFlowPosition >= width()*9/40+height()*1/3+16
        && m_energyFlowPosition - (width()*9/40+height()*1/3+16) + energyBlockWidth <= height() / 2 - 8 - width() * 1 / 40)
    {
        positionInLine = m_energyFlowPosition - (width()*9/40+height()*1/3+16);
    }
    if(positionInLine >= 0)
    {
        //垂直线段有能量
        if(positionInLine <= length)
        {
            if(positionInLine > 0)
            {
                //绘制能量块之前的电线
                painter.drawLine(startX, startY, x, startY + positionInLine);
            }
            //能量完全覆盖在垂直线段
            if(positionInLine + energyBlockWidth <= length)
            {
                //绘制能量块所覆盖的电线
                drawGradientLineSegment(startX, startY + positionInLine,
                                        startX, startY + positionInLine + energyBlockWidth,
                                        Qt::black, painter);
                //绘制能量块之后的电线
                painter.drawLine(startX, startY + positionInLine + energyBlockWidth, startX, startY + length);
            }else{
                //能量部分覆盖在垂直线段
                //只考虑充电的情况
                if(!m_discharged)
                {
                    //需要画连向外部电源的线段
                    wireToDischHeadflag = true;
                    //绘制能量块所覆盖的电线
                    int energyHorLength = positionInLine + energyBlockWidth - length;
                    drawGradientPolylineSegment(startX, startY + positionInLine, startX, startY + length, startX - energyHorLength, startY + length, Qt::black, painter);
                    //绘制连向外部电源的线段
                    painter.drawLine(startX - energyHorLength, startY + length, startX - width() * 7 / 40, startY + length);
                }else
                {
                   painter.drawLine(startX, startY + positionInLine, startX, startY + length);
                }
            }
        }else
        {
            //充电情况，能量完全在连向外部电源的线段
            painter.drawLine(startX, startY, startX, startY + length);
            positionInLine -= length;
            painter.drawLine(startX, startY + length, startX - positionInLine, startY + length);
            drawGradientLineSegment(startX - positionInLine, startY + length, startX - positionInLine - energyBlockWidth, startY + length, Qt::black, painter);
            painter.drawLine(startX - positionInLine - energyBlockWidth, startY + length, startX - width() * 7 / 40, startY + length);
        }
    }else
    {
        painter.drawLine(startX, startY, startX, startY + length);
    }
}

void CircuitDiagramWidget2::drawSystemVoltage(QPainter &painter, int startX, int startY)
{
    // 还原视口和窗口设置，以绘制其他部分
    painter.setViewport(0, 0, width(), height());
    painter.setWindow(0, 0, width(), height());

    int radius = height() / 12; // 圆的半径为画布高度的1/10

    // 计算圆的中心坐标
    int centerX = startX;
    int centerY = startY + radius;

    // 绘制圆
    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(Qt::white);
    painter.drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);

    // 绘制系统电压值
    QString voltageText = QString("%1V").arg(m_systemVoltage);
    QFontMetrics metrics(painter.font());
    int textWidth = metrics.horizontalAdvance(voltageText);
    int textHeight = metrics.height();
    painter.drawText(centerX - textWidth / 2, centerY + textHeight / 4, voltageText);

    // 绘制从系统电压下方的导线
    drawWireToDischargeContactor(painter, startX, centerY + radius);
}

/**
 * 放电起点: width() * 7 / 30 + height() * 3 / 4 + 10
 *
 * @brief CircuitDiagramWidget2::drawWireToDischargeContactor
 * @param painter
 * @param startX
 * @param startY
 */
void CircuitDiagramWidget2::drawWireToDischargeContactor(QPainter &painter, int startX, int startY)
{
    // 设置画笔颜色
    QPen pen(Qt::black);
    pen.setStyle(Qt::DashLine);
    pen.setWidth(2);
    painter.setPen(pen);

    // 垂直线的终点
    int verticalEndY = startY + height() / 3;

    // 水平线的终点
    int horizontalEndX = mianContactorStartX;

    // 绘制从系统电压下方圆弧垂直向下的线
    painter.drawLine(startX, startY, startX, verticalEndY);

    // 绘制水平向右的线
    pen.setWidth(5);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    int startLength = width() * 3 / 10 + height() * 3 / 4 + 10;
    int positionInLine = m_energyFlowPosition - startLength;
    if(positionInLine >= 0 && positionInLine + energyBlockWidth <= (mianContactorStartX - startX))
    {
        //绘制能量块之前的部分
        if(positionInLine > 0)
        {
            painter.drawLine(startX, verticalEndY, startX + positionInLine, verticalEndY);
        }
        //绘制能量块覆盖的部分
        drawGradientLineSegment(startX + positionInLine, verticalEndY,
                                startX + positionInLine + energyBlockWidth, verticalEndY,
                                Qt::black, painter);
        //绘制能量块之后的部分
        painter.drawLine(startX + positionInLine + energyBlockWidth, verticalEndY, horizontalEndX, verticalEndY);
    }else
    {
        if(wireToDischHeadflag)
        {
            painter.drawLine(startX + width() * 7 / 40, verticalEndY, horizontalEndX, verticalEndY);
        }else
        {
           painter.drawLine(startX, verticalEndY, horizontalEndX, verticalEndY);
        }
    }
    // 绘制放电接触器
    drawDischargeContactor(painter, horizontalEndX, verticalEndY, width() / 5);
}

void CircuitDiagramWidget2::drawDischargeContactor(QPainter &painter, int x, int y, int batteryWidth)
{
    int radius = 4;
    int centerDistance = batteryWidth / 4; // 这里的距离设为电池宽度的1/4

    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制两个圆
    QPen pen(Qt::black); // 圆和线的颜色
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(Qt::white);
    painter.drawEllipse(x - radius, y - radius, radius * 2, radius * 2);
    painter.drawEllipse(x + centerDistance - radius, y - radius, radius * 2, radius * 2);

    // 绘制开关线
    QLineF line;
    QPointF startPoint(x, y - radius); // 从圆弧位置开始
    if (m_dischargeContactorClosed) // 假设有一个bool类型变量 m_dischargeContactorClosed 来表示接触器状态
    {
        // 闭合状态：水平线
        QPointF endPoint(x + centerDistance, y - radius);
        line.setP1(startPoint);
        line.setP2(endPoint);
    }
    else
    {
        // 打开状态：与水平夹角345度，斜向右上
        double angle = 15.0; // 与水平线的夹角是345度，即360-15度
        double length = centerDistance;
        QPointF endPoint(x + length * cos(qDegreesToRadians(angle)), y - radius - length * sin(qDegreesToRadians(angle)));
        line.setP1(startPoint);
        line.setP2(endPoint);
    }
    painter.drawLine(line);

    // 绘制从放电接触器到充电接触器的导线
    drawWireToChargeContactor(painter, x + centerDistance + radius, y, batteryWidth);

    //绘制连接limited接触器的电线
    int startX = x + centerDistance + radius;
    drawWireToLimitedContactor(painter, startX, y, startX + width() / 8 + width() / 24);
}

/**
 * 放电起点：width() * 7 / 12 + height() * 3 / 4 + 20
 * 长度：width() / 6 + height() / 6
 * @brief CircuitDiagramWidget2::drawWireToLimitedContactor
 * @param painter
 * @param dischargeContactorX
 * @param dischargeContactorY
 * @param chargeContactorX
 */
void CircuitDiagramWidget2::drawWireToLimitedContactor(QPainter &painter, int dischargeContactorX, int dischargeContactorY, int chargeContactorX)
{
    // 还原视口和窗口设置，以绘制其他部分
    painter.setViewport(0, 0, width(), height());
    painter.setWindow(0, 0, width(), height());

    QPen pen(Qt::black); // 导线颜色
    pen.setWidth(5);
    painter.setPen(pen);

    // 获取连接放电接触器和充电接触器的线的中点坐标
    int midX = (dischargeContactorX + chargeContactorX) / 2;
    int midY = dischargeContactorY;
    // 垂直线的终点位置
    int verticalLineLength = height() / 6;
    int verticalEndY = midY - verticalLineLength;

    //充电开关断开，限流开关开启，那么从放电出来那一段是由限流来画
    if(!m_chargeContactorClosed && m_limitedContactorClosed){
        int positionInLine = m_energyFlowPosition - (width() * 7 / 12 + height() * 3 / 4 + 20);
        //能量块在此段
        if(positionInLine >= 0 && positionInLine + energyBlockWidth <= (height() / 6 + (chargeContactorX - dischargeContactorX))){
            //第一段水平线有能量块
            if(positionInLine <= (midX - dischargeContactorX)){
                //绘制能量块之前的水平线+2是线太粗了
                painter.drawLine(dischargeContactorX + 2, midY, dischargeContactorX + positionInLine, midY);

                int energyVerLength = 0;
                //能量块完全在第一段水平电线
                if(positionInLine + energyBlockWidth <= (midX - dischargeContactorX)){
                    //绘制能量块覆盖的电线
                    drawGradientLineSegment(dischargeContactorX + positionInLine, midY, dischargeContactorX + positionInLine + energyBlockWidth, midY, Qt::black, painter);
                    //绘制能量块之后的水平线
                    painter.drawLine(dischargeContactorX + positionInLine + energyBlockWidth, midY, midX, midY);
                }else //能量部分在水平线，部分在垂直线
                {
                    energyVerLength = positionInLine + energyBlockWidth - (midX - dischargeContactorX);
                    //绘制能量块覆盖的电线
                    drawGradientPolylineSegment(dischargeContactorX + positionInLine, midY, midX, midY, midX, midY - energyVerLength, Qt::black, painter);
                }
                //绘制剩余的电线
                //绘制垂直向上的线
                painter.drawLine(midX, midY - energyVerLength, midX, verticalEndY);
                //绘制最后一段水平向右的线
                painter.drawLine(midX, verticalEndY, chargeContactorX, verticalEndY);
            }else{
                positionInLine -= (midX - dischargeContactorX);
                //能量不再第一段水平线上，直接画+2是线太粗了
                painter.drawLine(dischargeContactorX + 2, midY, midX, midY);
                //垂直线上有能量
                if(positionInLine <= (midY - verticalEndY)){
                    //绘制能量块之前的线段
                    painter.drawLine(midX, midY, midX, midY - positionInLine);
                    int energyHorLength = 0;
                    //能量块完全在垂直线段内
                    if(positionInLine + energyBlockWidth <= (midY - verticalEndY)){
                        drawGradientLineSegment(midX, midY - positionInLine, midX, midY - positionInLine - energyBlockWidth, Qt::black, painter);
                        //绘制能量块之后的垂直线段
                        painter.drawLine(midX, midY - positionInLine - energyBlockWidth, midX, verticalEndY);
                    }else{//能量块部分在垂直线段上，部分在水平线段上
                        energyHorLength = positionInLine + energyBlockWidth - (midY - verticalEndY);
                        drawGradientPolylineSegment(midX, midY - positionInLine, midX, verticalEndY, midX + energyHorLength, verticalEndY, Qt::black, painter);
                    }
                    //绘制最后剩余的水平线段
                    painter.drawLine(midX + energyHorLength, verticalEndY, chargeContactorX, verticalEndY);
                }else{ //能量块完全落在最后一段
                    //第一段水平线+2是线太粗了
                    painter.drawLine(dischargeContactorX + 2, midY, midX, midY);
                    //第二段垂直线
                    painter.drawLine(midX, midY, midX, verticalEndY);
                    positionInLine -= (midY - verticalEndY);
                    //绘制能量块之前的水平线
                    painter.drawLine(midX, verticalEndY, midX + positionInLine, verticalEndY);
                    //绘制能量块覆盖的水平线
                    drawGradientLineSegment(midX + positionInLine, verticalEndY, midX + positionInLine + energyBlockWidth, verticalEndY, Qt::black, painter);
                    //绘制能量块之后的水平线
                    painter.drawLine(midX + positionInLine + energyBlockWidth, verticalEndY, chargeContactorX, verticalEndY);
                }
            }
        }else{
            //能量块不在此段
            //绘制放电开关到中点的线,+2是线太粗了
            painter.drawLine(dischargeContactorX + 2, midY, midX, midY);
            // 绘制从中点到垂直向上的线
            painter.drawLine(midX, midY, midX, verticalEndY);
            // 绘制水平向右的线，直到充电接触器的x坐标
            painter.drawLine(midX, verticalEndY, chargeContactorX, verticalEndY);
        }
    }else{
        //电流不会经过这里
        // 绘制从中点到垂直向上的线
        painter.drawLine(midX, midY, midX, verticalEndY);
        // 绘制水平向右的线，直到充电接触器的x坐标
        painter.drawLine(midX, verticalEndY, chargeContactorX, verticalEndY);
    }
    //绘制limited接触器
    drawLimitedContactor(painter, chargeContactorX, verticalEndY);
}

/**
 * 放电起点（开关结束侧）: width()∗4/5+height()∗11/12+28
 * 长度：width() / 6 + height() / 6
 * @brief CircuitDiagramWidget2::drawLimitedContactor
 * @param painter
 * @param x
 * @param y
 */
void CircuitDiagramWidget2::drawLimitedContactor(QPainter &painter, int x, int y)
{
    int radius = 4;
    int centerDistance = width() / 20; // 调整为电池宽度的1/4

    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制两个圆
    QPen pen(Qt::black); // 圆和线的颜色
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(Qt::white);
    painter.drawEllipse(x - radius, y - radius, radius * 2, radius * 2);
    painter.drawEllipse(x + centerDistance - radius, y - radius, radius * 2, radius * 2);

    // 绘制开关线
    QLineF line;
    QPointF startPoint(x, y - radius); // 从左侧圆的顶部开始
    if (m_limitedContactorClosed)
    {
        // 闭合状态：水平线
        QPointF endPoint(x + centerDistance, y - radius);
        line.setP1(startPoint);
        line.setP2(endPoint);
    }
    else
    {
        // 打开状态：与水平线夹角为345度，斜向右下
        double angle = 15.0; // 与水平线的夹角是15度
        double length = centerDistance;
        QPointF endPoint(x + length * cos(qDegreesToRadians(angle)), y - radius - length * sin(qDegreesToRadians(angle)));
        line.setP1(startPoint);
        line.setP2(endPoint);
    }
    painter.drawLine(line);

    int startX = x + centerDistance + radius;
    //绘制电阻 +2是线太粗了
    QRect rect(startX + width() / 24, y - width() / 96, width() / 12, width() / 48);
    painter.drawRect(rect);
    //绘制电线
    pen.setWidth(5);
    painter.setPen(pen);

    //充电开关断开，限流开关闭合，那么要考虑能量的情况，且要画垂直之后的水平线
    if(!m_chargeContactorClosed && m_limitedContactorClosed)
    {
        int positionInLine = m_energyFlowPosition - (width() * 4/5+height() * 11/12+28);
        //说明能量到达
        if(positionInLine >= -energyBlockWidth / 2 && positionInLine <= (width() / 6 + height() / 6))
        {
            //能量块冒个头
            if(positionInLine <= 0){
                double colorAt = (positionInLine + energyBlockWidth / 2.0) / energyBlockWidth;
                //绘制能量块所覆盖的电线
                drawGradientLineSegment(startX, y, startX + positionInLine + energyBlockWidth, y, Qt::black, painter, colorAt);
                //绘制开关之后水平向右的线
                painter.drawLine(startX + positionInLine + energyBlockWidth, y, startX + width() / 24 - 2, y);
                //绘制电阻之后的水平线，+2是线太粗了
                painter.drawLine(startX + width() / 8 + 2, y, startX + width() / 6, y);
                //绘制垂直向下的线
                painter.drawLine(startX + width() / 6, y, startX + width() / 6, y + height() / 6);
                //最后的一段水平线，只要画能量宽度就好
                painter.drawLine(startX + width() / 6, y + height() / 6, startX + width() / 6 + energyBlockWidth, y + height() / 6);
            }else if(positionInLine <= width() / 24 - 2)
            {   //能量块在第一段水平线中
                //绘制能量块之前的线
                painter.drawLine(startX + 2, y, startX + positionInLine, y);
                //能量完全在水平线中
                if(positionInLine <= width() / 24 - energyBlockWidth - 4)
                {
                    //绘制能量块
                    drawGradientLineSegment(startX + positionInLine, y, startX + positionInLine + energyBlockWidth, y, Qt::black, painter);
                    //绘制能量块之后的水平线
                    painter.drawLine(startX + positionInLine + energyBlockWidth, y, startX + width() / 24 - 2, y);
                }else if(positionInLine <= width() / 24 - energyBlockWidth / 2 - 4)
                {
                    //能量部分在水平线中
                    //绘制能量块
                    double colorAt = energyBlockWidth/ 2.0 / (width() / 24.0 - positionInLine);
                    drawGradientLineSegment(startX + positionInLine, y, startX + width() / 24 - 2, y, Qt::black, painter, colorAt);
                }else{
                    //能量在电阻中
                    painter.drawLine(startX + positionInLine, y, startX + width() / 24 - 2, y);
                }
                //绘制电阻之后的水平线，+2是线太粗了
                painter.drawLine(startX + width() / 8 + 2, y, startX + width() / 6 - 4, y);
                //绘制垂直向下的线
                painter.drawLine(startX + width() / 6, y, startX + width() / 6, y + height() / 6);
                //最后的一段水平线，只要画能量宽度就好
                painter.drawLine(startX + width() / 6, y + height() / 6, startX + width() / 6 + energyBlockWidth, y + height() / 6);
            }else
            {
                //第一段不存在能量，直接画
                painter.drawLine(startX + 2, y, startX + width() / 24 - 2, y);
                positionInLine -= (width() / 24 + width() / 12);
                //能量块还在电阻里，正常画各段
                if(positionInLine < -energyBlockWidth / 2)
                {
                    //绘制电阻之后的水平线，+2是线太粗了
                    painter.drawLine(startX + width() / 8 + 2, y, startX + width() / 6, y);
                    //绘制垂直向下的线
                    painter.drawLine(startX + width() / 6, y, startX + width() / 6, y + height() / 6);
                    //最后的一段水平线，只要画能量宽度就好
                    painter.drawLine(startX + width() / 6, y + height() / 6, startX + width() / 6 + energyBlockWidth, y + height() / 6);
                }else if(positionInLine <= 0)
                {
                    //能量块部分在电阻里
                    double colorAt = energyBlockWidth / 2.0 / (positionInLine + energyBlockWidth);
                    drawGradientLineSegment(startX + width() / 8 + 2, y, startX + width() / 8 + positionInLine + energyBlockWidth, y, Qt::black, painter, colorAt);
                    //绘制能量块后面的水平线
                    painter.drawLine(startX + width() / 8 + positionInLine + energyBlockWidth, y, startX + width() / 6, y);
                    //绘制垂直向下的线
                    painter.drawLine(startX + width() / 6, y, startX + width() / 6, y + height() / 6);
                    //最后的一段水平线，只要画能量宽度就好
                    painter.drawLine(startX + width() / 6, y + height() / 6, startX + width() / 6 + energyBlockWidth, y + height() / 6);
                }else if(positionInLine <= (width() / 6 - width() / 8))
                {
                    //能量块在电阻后的水平线
                    //绘制能量块之前的水平线
                    painter.drawLine(startX + width() / 8 + 2, y, startX + width() / 8 + positionInLine, y);
                    int energyVerLength = 0;
                    if(positionInLine+ energyBlockWidth <= (width() / 6 - width() / 8 - 2))
                    {
                        //能量块完全在水平线上
                        //绘制能量块覆盖的水平线
                        drawGradientLineSegment(startX + width() / 8 + positionInLine, y, startX + width() / 8 + positionInLine + energyBlockWidth, y, Qt::black, painter);
                        //绘制能量块之后的水平线
                        painter.drawLine(startX + width() / 8 + positionInLine + energyBlockWidth, y, startX + width() / 6, y);
                    }else{
                        //能量块部分在水平线上
                        energyVerLength = positionInLine + energyBlockWidth - (width() / 6 - width() / 8);
                        drawGradientPolylineSegment(startX + width() / 8 + positionInLine, y, startX + width() / 6, y, startX + width() / 6, y + energyVerLength, Qt::black, painter);
                    }

                    //绘制垂直向下的线
                    painter.drawLine(startX + width() / 6, y + energyVerLength, startX + width() / 6, y + height() / 6);
                    //最后的一段水平线，只要画能量宽度就好
                    painter.drawLine(startX + width() / 6, y + height() / 6, startX + width() / 6 + energyBlockWidth, y + height() / 6);
                }else{
                    //能量块在垂直线段
                    positionInLine -= width() / 24;
                    //绘制电阻之后的水平线，+2是线太粗了
                    painter.drawLine(startX + width() / 8 + 2, y, startX + width() / 6, y);
                    //绘制能量块之前的垂直线段
                    painter.drawLine(startX + width() / 6, y, startX + width() / 6, y + positionInLine);
                    int energyHorLength = 0;
                    //能量块完全在垂直线段内
                    if(positionInLine + energyBlockWidth <= height() / 6)
                    {
                        //绘制能量块覆盖的线段
                        drawGradientLineSegment(startX + width() / 6, y + positionInLine, startX + width() / 6, y + positionInLine + energyBlockWidth, Qt::black, painter);
                        //绘制能量块之后的垂直线段
                        painter.drawLine(startX + width() / 6, y + positionInLine + energyBlockWidth, startX + width() / 6, y + height() / 6);
                    }else
                    {
                        //能量块部分在垂直线段内
                        energyHorLength = positionInLine + energyBlockWidth - height() / 6;
                        drawGradientPolylineSegment(startX + width() / 6, y + positionInLine, startX + width() / 6, y + height() / 6, startX + width() / 6 + energyHorLength, y + height() / 6, Qt::black, painter);
                    }
                    //绘制最后的水平线段
                     painter.drawLine(startX + width() / 6 + energyHorLength, y + height() / 6, startX + width() / 6 + energyBlockWidth, y + height() / 6);
                }
            }
        }else
        {
            //能量还没到达/已经过去
            //绘制电阻之后的水平线，+2是线太粗了
            painter.drawLine(startX + width() / 8 + 2, y, startX + width() / 6, y);
            //绘制开关之后水平向右的线,+-2是因为线太粗了
            painter.drawLine(startX + 2, y, startX + width() / 24 - 2, y);
            //绘制垂直向下的线
            painter.drawLine(startX + width() / 6, y, startX + width() / 6, y + height() / 6);
            //最后的一段水平线，在能量未过去之前都是这里画
            if(positionInLine < -energyBlockWidth / 2)
            {
                painter.drawLine(startX + width() / 6, y + height() / 6, startX + width() / 6 + energyBlockWidth, y + height() / 6);
            }
        }

    }else
    {
        //不考虑能量的情况,且不用画垂直后的水平线
        //绘制电阻之后的水平线，+2是线太粗了
        painter.drawLine(startX + width() / 8 + 2, y, startX + width() / 6, y);
        //绘制开关之后水平向右的线,+-2是因为线太粗了
        painter.drawLine(startX + 2, y, startX + width() / 24 - 2, y);
        //绘制垂直向下的线
        painter.drawLine(startX + width() / 6, y, startX + width() / 6, y + height() / 6);
    }
}

void CircuitDiagramWidget2::drawGradientLineSegment(int x1, int y1, int x2, int y2, Qt::GlobalColor edgeColor, QPainter &painter, double color2At)
{
    //绘制能量块覆盖的部分
    QLinearGradient gradient(x1, y1, x2, y2);
    if(color2At != 0)
    {
        gradient.setColorAt(0, edgeColor);
    }
    gradient.setColorAt(color2At, energyColor);
    gradient.setColorAt(1, edgeColor);
    QPen pen = painter.pen();
    pen.setBrush(gradient);
    painter.setPen(pen);
    painter.drawLine(x1, y1, x2, y2);
    //绘制能量块之后的部分
    pen.setColor(edgeColor); // 恢复原始颜色
    painter.setPen(pen);
}

void CircuitDiagramWidget2::drawGradientPolylineSegment(int x1, int y1, int x2, int y2, int x3, int y3, Qt::GlobalColor edgeColor, QPainter &painter)
{
    // 计算渐变起点和终点，跨越垂直和水平部分
    QLinearGradient gradient(x1, y1, x3, y3);
    gradient.setColorAt(0, edgeColor);
    gradient.setColorAt(0.5, energyColor);
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

bool CircuitDiagramWidget2::ifCloseLoop()
{
    return m_mainContactorClosed && m_dischargeContactorClosed && (m_chargeContactorClosed || m_limitedContactorClosed);
}

void CircuitDiagramWidget2::timerAndEnergyAdjust()
{
    //电路闭合,但是定时器已经停止
    if(ifCloseLoop() && !timer->isActive())
    {
        timer->start();
    }
    //电路断开，但是定时器正在运行
    if(!ifCloseLoop() && timer->isActive())
    {
        timer->stop();
        //将能量位置归为0
        m_energyFlowPosition = 0;
    }
}


/**
 * 充电起点：width() * 7 / 12 + height() * 3 / 4 + 20
 * 长度：width() / 8 + width() / 24
 * @brief CircuitDiagramWidget2::drawWireToChargeContactor
 * @param painter
 * @param startX
 * @param startY
 * @param batteryWidth
 */
void CircuitDiagramWidget2::drawWireToChargeContactor(QPainter &painter, int startX, int startY, int batteryWidth)
{
    // 设置画笔颜色
    QPen pen(Qt::black); // 导线颜色
    pen.setWidth(5);
    painter.setPen(pen);

    // 水平线长度为画布宽度的1/20
    int horizontalLineLength = width() / 8 + width() / 24;

    // 计算水平线的终点坐标
    //+2是因为线太粗了
    startX += 2;
    int horizontalLineEndX = startX + horizontalLineLength;
    int horizontalLineEndY = startY;

    // 绘制水平线
    int positionInLine = m_energyFlowPosition - (width() * 7 / 12 + height() * 3 / 4 + 20);

    //如果限流开关闭合且充电开关断开，放电开关出来那段由限流去画,这里只画后半段
    if(m_limitedContactorClosed && !m_chargeContactorClosed){
        //+2是因为线太粗了
        painter.drawLine(startX + horizontalLineLength / 2 + 2, startY, horizontalLineEndX, horizontalLineEndY);
    }else if(m_chargeContactorClosed && positionInLine >= 0 && positionInLine + energyBlockWidth <= horizontalLineLength){
        //绘制能量块之前的部分
        if(positionInLine > 0)
        {
            painter.drawLine(startX, startY, startX + positionInLine, horizontalLineEndY);
        }
        //绘制能量块所覆盖的那部分
        drawGradientLineSegment(startX + positionInLine, startY,
                                startX + positionInLine + energyBlockWidth, startY,
                                Qt::black, painter);
        //绘制能量块之后的部分
        painter.drawLine(startX + positionInLine + energyBlockWidth, startY, horizontalLineEndX, horizontalLineEndY);

    }else
    {
       painter.drawLine(startX, startY, horizontalLineEndX, horizontalLineEndY);
    }
    // 放电接触器的位置 (相对电池)
    int chargeContactorX = horizontalLineEndX;
    int chargeContactorY = horizontalLineEndY;

    // 绘制充电接触器
    drawChargeContactor(painter, chargeContactorX, chargeContactorY, batteryWidth);
}

void CircuitDiagramWidget2::drawChargeContactor(QPainter &painter, int x, int y, int batteryWidth)
{
    int radius = 4;
    int centerDistance = batteryWidth / 4; // 调整为电池宽度的1/4

    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制两个圆
    QPen pen(Qt::black); // 圆和线的颜色
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(Qt::white);
    painter.drawEllipse(x - radius, y - radius, radius * 2, radius * 2);
    painter.drawEllipse(x + centerDistance - radius, y - radius, radius * 2, radius * 2);

    // 绘制开关线
    QLineF line;
    QPointF startPoint(x, y - radius); // 从圆弧位置开始
    if (m_chargeContactorClosed) // 假设有一个bool类型变量 m_chargeContactorClosed 来表示接触器状态
    {
        // 闭合状态：水平线
        QPointF endPoint(x + centerDistance, y - radius);
        line.setP1(startPoint);
        line.setP2(endPoint);
    }
    else
    {
        // 打开状态：与水平夹角345度，斜向右上
        double angle = 15.0; // 与水平线的夹角是345度，即360-15度
        double length = centerDistance;
        QPointF endPoint(x + length * cos(qDegreesToRadians(angle)), y - radius - length * sin(qDegreesToRadians(angle)));
        line.setP1(startPoint);
        line.setP2(endPoint);
    }
    painter.drawLine(line);
    chargeContactorEndx = x + centerDistance + radius;
}

/**
 * 充电起点：width()*19/24 + height() * 3/4 + 28
 * 长度: horizontalEndX−chargeContactorEndx+height()*5/6+width() / 8
 * @brief CircuitDiagramWidget2::drawWireFromNegativeElectrode
 * @param painter
 * @param batteryX
 * @param batteryY
 * @param batteryWidth
 * @param batteryHeight
 */
void CircuitDiagramWidget2::drawWireFromNegativeElectrode(QPainter &painter, int batteryX, int batteryY, int batteryWidth, int batteryHeight)
{
    // 还原视口和窗口设置，以绘制其他部分
    painter.setViewport(0, 0, width(), height());
    painter.setWindow(0, 0, width(), height());

    QPen pen(Qt::black); // 导线颜色
    pen.setWidth(5);
    painter.setPen(pen);

    // 电池右侧电极的坐标
    int electrodeWidth = batteryWidth / 10;
    int electrodeHeight = batteryHeight / 5;
    int extension = electrodeWidth;
    QRect rightElectrode(batteryX + batteryWidth - electrodeWidth * 1.5, batteryY - electrodeHeight - extension * 0.7, electrodeWidth, electrodeHeight);

    int batteryNegPosX = rightElectrode.center().x(); // 使用电极的中心x坐标
    int batteryNegPosY = rightElectrode.top() - batteryHeight / 50; // 与电池正极电线起点的y坐标对齐

    // 垂直线长度为电池高度的1/4
    int verticalLineLength = batteryHeight / 4;
    // 水平向右的部分，长度为画布宽度的1/20
    int horizontalLineLength = width() / 10;
    horizontalEndX = batteryNegPosX + horizontalLineLength;
    // 垂直向下的部分，长度为画布高度的5/6
    int verticalEndY = batteryNegPosY - verticalLineLength + height() * 5 / 6 - 2;
    int positionInLine = m_energyFlowPosition - (width()*19/24 + height() * 3/4 + 28);

    //充电开关断开，限流开关闭合
    bool flag = !m_chargeContactorClosed && limitedContactorClosed();
    if(flag)
    {
        //只考虑limit线路流动到水平线段开始
        positionInLine = m_energyFlowPosition - (width()*29/30+height()*13/12+28);
    }
    //能量块未进入
    if(positionInLine < 0)
    {
        // 绘制从电池负极向上垂直线
        painter.drawLine(batteryNegPosX, batteryNegPosY, batteryNegPosX, batteryNegPosY - verticalLineLength);
        // 水平向右的部分，长度为画布宽度的1/20
        painter.drawLine(batteryNegPosX, batteryNegPosY - verticalLineLength, horizontalEndX, batteryNegPosY - verticalLineLength);
        // 垂直向下的部分，长度为画布高度的5/6
        painter.drawLine(horizontalEndX, batteryNegPosY - verticalLineLength, horizontalEndX, verticalEndY);
        if(flag)
        {
            //这个时候，有一段需要limit那里来画，-5是limit出来那条线的宽度是5，这部分也去掉
            int length = width() / 6 - 5;
            painter.drawLine(chargeContactorEndx + 2, verticalEndY, chargeContactorEndx + length, verticalEndY);
            painter.drawLine(chargeContactorEndx + length + 2 + energyBlockWidth, verticalEndY, horizontalEndX, verticalEndY);
        }else
        {
            //绘制与充电接触器相连的电线, +2是因为线太粗了
            painter.drawLine(horizontalEndX, verticalEndY, chargeContactorEndx + 2, verticalEndY);
        }

    }
    //能量块进入,可能是从充电开关过来的，也有可能是限流开关过来的
    if(positionInLine >= 0)
    {
        //如果从限流开关过来
        if(flag)
        {
            positionInLine += width() / 6;
        }
        //水平线段有能量
        if(positionInLine <= (horizontalEndX - chargeContactorEndx))
        {
            int energyVerLength = 0;
            //绘制水平线段能量之前的电线 +1是因为线太粗了
            painter.drawLine(chargeContactorEndx + 1, verticalEndY, chargeContactorEndx + positionInLine, verticalEndY);
            //能量完全在水平线段之内
            if(positionInLine + energyBlockWidth <= (horizontalEndX - chargeContactorEndx - 2))
            {
                //绘制能量覆盖的那段
                drawGradientLineSegment(chargeContactorEndx + positionInLine, verticalEndY,
                                        chargeContactorEndx + positionInLine + energyBlockWidth, verticalEndY,
                                        Qt::black, painter);
                //绘制能量块之后的正常线段
                painter.drawLine(chargeContactorEndx + positionInLine + energyBlockWidth, verticalEndY,
                                 horizontalEndX, verticalEndY);
            }else
            {
                //能量部分在水平线段，部分在垂直线段
                int remainingLength = horizontalEndX - chargeContactorEndx - positionInLine;
                energyVerLength = energyBlockWidth - remainingLength;
                // 计算渐变起点和终点，跨越垂直和水平部分
                drawGradientPolylineSegment(chargeContactorEndx + positionInLine, verticalEndY,
                                            horizontalEndX, verticalEndY,
                                            horizontalEndX, verticalEndY - energyVerLength,
                                            Qt::black, painter);
            }
            //绘制能量块之后的垂直线段到电池负极
            // 垂直向上的部分，长度为画布高度的5/6
            painter.drawLine(horizontalEndX, verticalEndY - energyVerLength, horizontalEndX, batteryNegPosY - verticalLineLength);
            // 绘制从电池负极向上垂直线
            painter.drawLine(batteryNegPosX, batteryNegPosY, batteryNegPosX, batteryNegPosY - verticalLineLength);
            // 水平向右的部分，长度为画布宽度的1/20
            painter.drawLine(batteryNegPosX, batteryNegPosY - verticalLineLength, horizontalEndX, batteryNegPosY - verticalLineLength);
        }else
        {
            //水平线段没能量先把水平线段画了+2是因为线太粗了
            painter.drawLine(horizontalEndX, verticalEndY, chargeContactorEndx + 2, verticalEndY);
            positionInLine -= (horizontalEndX - chargeContactorEndx);
            //垂直线段有能量
            if(positionInLine <= verticalEndY - (batteryNegPosY - verticalLineLength)){
                int energyHoriLength = 0;
                //绘制能量块前的垂直线
                painter.drawLine(horizontalEndX, verticalEndY, horizontalEndX, verticalEndY - positionInLine);

                //能量块完全在垂直线段内
                if(positionInLine + energyBlockWidth <= verticalEndY - (batteryNegPosY - verticalLineLength))
                {
                    //绘制能量覆盖的那段
                    drawGradientLineSegment(horizontalEndX, verticalEndY - positionInLine,
                                            horizontalEndX, verticalEndY - positionInLine - energyBlockWidth,
                                            Qt::black, painter);
                    //绘制能量块之后的正常线段
                    painter.drawLine(horizontalEndX, verticalEndY - positionInLine - energyBlockWidth,
                                     horizontalEndX, batteryNegPosY - verticalLineLength);
                }else
                {
                    //能量块部分在垂直线段内
                    int remainingLength = verticalEndY - (batteryNegPosY - verticalLineLength) - positionInLine;
                    energyHoriLength = energyBlockWidth - remainingLength;
                    // 计算渐变起点和终点，跨越垂直和水平部分
                    drawGradientPolylineSegment(horizontalEndX, verticalEndY - positionInLine,
                                                horizontalEndX, batteryNegPosY - verticalLineLength,
                                                horizontalEndX - energyHoriLength, batteryNegPosY - verticalLineLength,
                                                Qt::black, painter);
                }
                //绘制剩余的连接到负电极的电线
                pen.setColor(Qt::black); // 恢复原始颜色
                painter.setPen(pen);
                // 绘制从电池负极向上垂直线
                painter.drawLine(batteryNegPosX, batteryNegPosY, batteryNegPosX, batteryNegPosY - verticalLineLength);
                // 水平向右的部分，长度为画布宽度的1/20
                painter.drawLine(batteryNegPosX, batteryNegPosY - verticalLineLength, horizontalEndX - energyHoriLength, batteryNegPosY - verticalLineLength);
            }else
            {
                //能量至少到了最后那段水平线段，可以线绘制第一个水平和垂直线段
                painter.drawLine(horizontalEndX, batteryNegPosY - verticalLineLength, horizontalEndX, verticalEndY);
                //绘制与充电接触器相连的电线+2是因为线太粗了
                painter.drawLine(horizontalEndX, verticalEndY, chargeContactorEndx + 2, verticalEndY);
                positionInLine -= (verticalEndY - (batteryNegPosY - verticalLineLength));
                //最后那段水平线段有能量
                if(positionInLine <= (horizontalEndX - batteryNegPosX))
                {
                    int energyVerLength = 0;
                    //先绘制能量前的
                    painter.drawLine(horizontalEndX, batteryNegPosY - verticalLineLength, horizontalEndX - positionInLine, batteryNegPosY - verticalLineLength);
                    //能量完全在水平线段内
                    if(positionInLine + energyBlockWidth <= (horizontalEndX - batteryNegPosX))
                    {
                        //绘制能量覆盖的那段
                        drawGradientLineSegment(horizontalEndX - positionInLine, batteryNegPosY - verticalLineLength,
                                                horizontalEndX - positionInLine - energyBlockWidth, batteryNegPosY - verticalLineLength,
                                                Qt::black, painter);
                        //绘制能量块之后的正常线段
                        painter.drawLine(horizontalEndX - positionInLine - energyBlockWidth, batteryNegPosY - verticalLineLength,
                                         batteryNegPosX, batteryNegPosY - verticalLineLength);
                    }else
                    {
                        //能量部分在水平线段内
                        int remainingLength = horizontalEndX - batteryNegPosX - positionInLine;
                        energyVerLength = energyBlockWidth - remainingLength;
                        // 计算渐变起点和终点，跨越垂直和水平部分
                        drawGradientPolylineSegment(horizontalEndX - positionInLine, batteryNegPosY - verticalLineLength,
                                                    batteryNegPosX, batteryNegPosY - verticalLineLength,
                                                    batteryNegPosX, batteryNegPosY - verticalLineLength + energyVerLength,
                                                    Qt::black, painter);
                    }
                    //绘制最后连向负电极的电线
                    painter.drawLine(batteryNegPosX, batteryNegPosY, batteryNegPosX, batteryNegPosY - verticalLineLength + energyVerLength);
                }else
                {
                    //能量在最后的垂直线段
                    positionInLine -= (horizontalEndX - batteryNegPosX);
                    //只考虑完全在垂直线段内
                    if(positionInLine >= 0 && positionInLine <= verticalLineLength)
                    {
                        //绘制能量块之前的垂线
                        painter.drawLine(batteryNegPosX, batteryNegPosY - verticalLineLength, batteryNegPosX, batteryNegPosY - verticalLineLength + positionInLine);
                        //绘制能量覆盖的那段
                        drawGradientLineSegment(batteryNegPosX, batteryNegPosY - verticalLineLength + positionInLine,
                                                batteryNegPosX, batteryNegPosY - verticalLineLength + positionInLine + energyBlockWidth,
                                                Qt::black, painter);
                        //绘制能量块之后的正常线段
                        painter.drawLine(batteryNegPosX, batteryNegPosY - verticalLineLength + positionInLine + energyBlockWidth,
                                         batteryNegPosX, batteryNegPosY);
                        // 水平向右的部分，长度为画布宽度的1/20
                        int horizontalLineLength = width() / 10;
                        int horizontalEndX = batteryNegPosX + horizontalLineLength;
                        painter.drawLine(batteryNegPosX, batteryNegPosY - verticalLineLength, horizontalEndX, batteryNegPosY - verticalLineLength);

                        // 垂直向下的部分，长度为画布高度的5/6
                        int verticalEndY = batteryNegPosY - verticalLineLength + height() * 5 / 6;
                        painter.drawLine(horizontalEndX, batteryNegPosY - verticalLineLength, horizontalEndX, verticalEndY);

                        //绘制与充电接触器相连的电线+2是因为线太粗了
                        painter.drawLine(horizontalEndX, verticalEndY, chargeContactorEndx + 2, verticalEndY);
                    }
                }
            }
        }
    }
}


void CircuitDiagramWidget2::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    offsetX = -width() * 1 / 10;
    // 绘制画布边框
    QPen borderPen(Qt::black); // 边框线条颜色
    borderPen.setWidth(2);
    painter.setPen(borderPen);
    //painter.drawRect(0, 0, width() - 1, height() - 1); // 绘制画布的黑色边框

    // 动态调整字体大小
    QFont font = painter.font();
    font.setPointSize(width() / 60);
    font.setFamilies({"Arial", "Microsoft YaHei UI"});
    painter.setFont(font);

    // 计算电池的宽度和高度，使其充满画布并保持2:1的比例
    int batteryWidth = width() * 0.2; // 占窗口宽度的20%
    int batteryHeight = batteryWidth / 2; // 保持2:1比例

    // 确保电池高度不会超过画布高度
    if (batteryHeight > height() * 0.4) { // 高度占画布的40%
        batteryHeight = height() * 0.4;
        batteryWidth = batteryHeight * 2;
    }

    // 计算电池相对于画布的间距
    int verticalMargin = height() / 4;
    int horizontalMargin = width() / 9;

    // 电池主体
    QRect batteryRect(width() - batteryWidth - horizontalMargin + offsetX, verticalMargin, batteryWidth, batteryHeight);

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

    // 绘制从电池正极到主接触器的连接线
    drawWireToMainContactor(painter, batteryRect.x(), batteryRect.y(), batteryRect.width(), batteryRect.height());

    // 绘制从电池负极出来的线
    drawWireFromNegativeElectrode(painter, batteryRect.x(), batteryRect.y(), batteryRect.width(), batteryRect.height());

    // 绘制右侧的“串电压”和方框
    painter.setPen(Qt::black);
    int textX = batteryRect.right() + width() / 15 + width() / 20; // "串电压" 文字的X位置
    int textY = batteryRect.top() - height() / 10; // "串电压" 文字的Y位置
    font.setPointSize(width() / 50);
    painter.setFont(font);
    if(m_language == 2)
    {
        painter.drawText(textX, textY, tr("串电压"));
    }else{
        painter.drawText(textX, textY, tr("pack V."));
    }

    int rectWidth = width() / 15; // 方框的宽度
    int rectHeight = height() / 10; // 方框的高度
    int rectSpacing = height() / 40; // 方框之间的间距

    QList<QColor> colors = {m_packColor1, m_packColor2, m_packColor3, m_packColor4, m_packColor5, m_packColor6};

    for (int i = 1; i <= 6; ++i) {
        painter.setPen(Qt::black);
        painter.setBrush(colors[i - 1]);
        int rectX = textX + rectWidth / 5; // 方框的X位置
        int rectY = textY + rectSpacing * 2 + (i - 1) * (rectHeight + rectSpacing); // 方框的Y位置

        // 绘制序号
        painter.drawText(rectX - rectWidth / 2, rectY + rectHeight * 3 / 5, QString("%1)").arg(i));

        // 绘制方框
        painter.drawRect(rectX, rectY, rectWidth, rectHeight);
    }
}

void CircuitDiagramWidget2::resizeEvent(QResizeEvent *event)
{
    // 目标宽高比
    const float aspectRatio = 746.0f / 305.0f;

    // 获取当前尺寸
    int currentWidth = event->size().width();
    int currentHeight = event->size().height();

    // 计算基于宽度和高度的目标尺寸
    int newHeightBasedOnWidth = static_cast<int>(currentWidth / aspectRatio);
    int newWidthBasedOnHeight = static_cast<int>(currentHeight * aspectRatio);

    int finalWidth, finalHeight;

    // 根据最小差值选择调整方式并计算最终的尺寸
    if (abs(newHeightBasedOnWidth - currentHeight) < abs(newWidthBasedOnHeight - currentWidth)) {
        finalWidth = currentWidth;
        finalHeight = newHeightBasedOnWidth;
    } else {
        finalWidth = newWidthBasedOnHeight;
        finalHeight = currentHeight;
    }

    // 获取最小和最大尺寸
    QSize minSize = minimumSize();
    QSize maxSize = maximumSize();

    // 调整最终尺寸以确保不超出最大和最小尺寸限制
    if (finalWidth < minSize.width()) {
        finalWidth = minSize.width();
        finalHeight = static_cast<int>(finalWidth / aspectRatio);
    }
    if (finalHeight < minSize.height()) {
        finalHeight = minSize.height();
        finalWidth = static_cast<int>(finalHeight * aspectRatio);
    }

    if (finalWidth > maxSize.width()) {
        finalWidth = maxSize.width();
        finalHeight = static_cast<int>(finalWidth / aspectRatio);
    }
    if (finalHeight > maxSize.height()) {
        finalHeight = maxSize.height();
        finalWidth = static_cast<int>(finalHeight * aspectRatio);
    }

    // 应用最终尺寸
    resize(finalWidth, finalHeight);

    QWidget::resizeEvent(event);
}
