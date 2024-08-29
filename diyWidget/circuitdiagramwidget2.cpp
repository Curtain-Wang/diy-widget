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
    , m_mainContactorClosed(false)
    , m_systemVoltage(0)
    , m_dischargeContactorClosed(false)
    , m_chargeContactorClosed(false)
    , m_heaterFaultContactorClosed(false)
    , m_isHeating(false)
    , m_heaterContactorClosed(false)
    , m_limitedContactorClosed(false),
    m_packColor1(QColor("#d4d4d9")),  // 初始化为灰色
    m_packColor2(QColor("#d4d4d9")),  // 初始化为灰色
    m_packColor3(QColor("#d4d4d9")),  // 初始化为灰色
    m_packColor4(QColor("#d4d4d9")),  // 初始化为灰色
    m_packColor5(QColor("#d4d4d9")),  // 初始化为灰色
    m_packColor6(QColor("#d4d4d9")),   // 初始化为灰色
    m_language(2), //默认中文
    m_state(0)
{
    energyColor = Qt::white;
    setMinimumSize(200, 140);
    timer->setInterval(50);
    connect(timer, &QTimer::timeout, this, &CircuitDiagramWidget2::on_timer_timeout);
    //有闭合回路才开启定时器
    if(m_state == 1 || m_state == 2)
    {
        timer->start();
    }
    adjustEnergyPosition();
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
        update();
    }
}

bool CircuitDiagramWidget2::heaterFaultContactorClosed() const {
    return m_heaterFaultContactorClosed;
}

void CircuitDiagramWidget2::setHeaterFaultContactorClosed(bool closed) {
    if (closed != m_heaterFaultContactorClosed) {
        m_heaterFaultContactorClosed = closed;
        adjustEnergyPosition();
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
        adjustEnergyPosition();
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

int CircuitDiagramWidget2::customLanguage() const
{
    return m_language;
}

void CircuitDiagramWidget2::setCustomLanguage(const int language) {
    if (m_language != language) {
        m_language = language;
        emit customLanguageChanged(m_language);
        update(); // 更新界面以反映语言更改
    }
}

int CircuitDiagramWidget2::componentState() const
{
    return m_state;
}

void CircuitDiagramWidget2::setComponentState(const int state)
{
    if(m_state != state)
    {
        energyPositionList.clear();
        m_state = state;
        adjustEnergyPosition();
        emit componentStateChanged(m_state);
        update();
    }
}

void CircuitDiagramWidget2::drawBatteryBody(QPainter &painter, const QRect &batteryRect, const QRect &blueRect) {
    QPen pen = painter.pen();
    pen.setBrush(QColor("#0000ff"));
    painter.setPen(pen);
    painter.setBrush(QColor("#0000ff"));
    painter.drawRect(blueRect);

    // QLinearGradient gradient(batteryRect.topLeft(), batteryRect.bottomLeft());
    // gradient.setColorAt(0, Qt::white);
    // gradient.setColorAt(1, Qt::lightGray);
    painter.setBrush(Qt::white);
    painter.drawRect(batteryRect);
    pen.setBrush(Qt::black);
    painter.setPen(pen);

    //绘制电池状态
    QString text;
    if(m_state == 1)
    {
        text = "充电";
    }
    else if(m_state == 2)
    {
        text = "放电";
    }
    else if(m_state == 3)
    {
        text = "冷态";
    }
    else if(m_state == 4)
    {
        text = "静置";
    }
    else
    {
        text = "未知";
    }
    painter.drawText(batteryRect.center().x() - 17, batteryRect.top() - 50, text);
}

void CircuitDiagramWidget2::drawElectrodes(QPainter &painter, const QRect &batteryRect) {
    int electrodeWidth = batteryRect.width() / 12;
    int electrodeHeight = batteryRect.height() / 5;
    int extension = electrodeWidth;
    QRect leftElectrode(batteryRect.left() + electrodeWidth * 0.5 + 1, batteryRect.top() - electrodeHeight - extension * 0.7 - 2, electrodeWidth, electrodeHeight);
    QRect rightElectrode(batteryRect.right() - electrodeWidth * 1.5 - 1, batteryRect.top() - electrodeHeight - extension * 0.7 - 2, electrodeWidth, electrodeHeight);
    painter.setBrush(QColor("#d4d4d9"));
    painter.drawRect(leftElectrode);
    painter.drawRect(rightElectrode);
    // 设置字体和颜色
    QFont font = painter.font();
    int size = font.pointSize();
    font.setPointSize(electrodeHeight * 0.8); // 根据电极高度调整字体大小
    painter.setFont(font);

    // 绘制B+文本（红色）
    painter.setPen(Qt::red); // 设置画笔为红色
    painter.drawText(leftElectrode.right() + 5, leftElectrode.center().y(), "B+"); // 在左电极右边画文本

    // 绘制B-文本（默认黑色）
    painter.setPen(Qt::black); // 设置画笔为黑色
    painter.drawText(rightElectrode.left() - 20, rightElectrode.center().y(), "B-"); // 在右电极左边画文本
    //还原字体大小
    font.setPointSize(size);
    painter.setFont(font);

}

void CircuitDiagramWidget2::drawTrapezoid(QPainter &painter, const QRect &blueRect, int borderSize, int trapezoidHeight) {
    QPointF upperPoints[4] = {
        QPointF(blueRect.left() - borderSize / 2, blueRect.top() - trapezoidHeight),
        QPointF(blueRect.right() + borderSize / 2 + 1, blueRect.top() - trapezoidHeight),
        QPointF(blueRect.right() + 1, blueRect.top()),
        QPointF(blueRect.left(), blueRect.top())
    };
    QPen pen = painter.pen();
    pen.setBrush(QColor("#0000ff"));
    painter.setPen(pen);
    painter.setBrush(QColor("#0000ff"));
    painter.drawPolygon(upperPoints, 4);
    pen.setBrush(Qt::black);
    painter.setPen(pen);
    int width = blueRect.right() + borderSize / 2 + 1 - (blueRect.left() - borderSize / 2);
    painter.setBrush(Qt::gray);
    painter.drawRect(blueRect.left() - borderSize / 2, blueRect.top() - trapezoidHeight - 5, width, 5);
    painter.drawRect(blueRect.left() - borderSize / 2 + 3, blueRect.top() - trapezoidHeight - 10, width - 6, 5);
    painter.drawRect(blueRect.left() - borderSize / 2 + 43, blueRect.top() - trapezoidHeight - 11, width - 86, 6);

}

void CircuitDiagramWidget2::drawBase(QPainter &painter, const QRect &blueRect, int borderSize, int trapezoidHeight) {
    QPointF lowerPoints[6] = {
        QPointF(blueRect.left(), blueRect.bottom()),
        QPointF(blueRect.right() + 1, blueRect.bottom()),
        QPointF(blueRect.right() + borderSize / 2 + 1, blueRect.bottom() + trapezoidHeight),
        QPointF(blueRect.right() + borderSize / 2 + 1, blueRect.bottom() + trapezoidHeight * 1.5),
        QPointF(blueRect.left() - borderSize / 2, blueRect.bottom() + trapezoidHeight * 1.5),
        QPointF(blueRect.left() - borderSize / 2, blueRect.bottom() + trapezoidHeight)
    };
    painter.setBrush(Qt::gray);
    painter.drawPolygon(lowerPoints, 6);
}

void CircuitDiagramWidget2::drawChargeLevel(QPainter &painter, const QRect &batteryRect) {
    int chargeHeight = static_cast<int>((batteryRect.height() - 2) * (m_chargeLevel / 100.0));
    QRect chargeRect(batteryRect.left() + 1, batteryRect.bottom() - chargeHeight, batteryRect.width() - 2, chargeHeight);

    QPen pen = painter.pen();
    if(m_chargeLevel == 0){
        painter.setBrush(Qt::white);
        pen.setColor(Qt::white);
    }
    else if (m_chargeLevel < m_warningLevel) {
        painter.setBrush(Qt::red);
        pen.setColor(Qt::red);
    } else {
        painter.setBrush(Qt::green);
        pen.setColor(Qt::green);
    }
    painter.setPen(pen);
    painter.drawRect(chargeRect);
    pen.setColor(Qt::black);
    painter.setPen(pen);
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

    //垂直
    painter.drawLine(batteryPosX, batteryPosY - 2, batteryPosX, batteryPosY - verticalLineLength);
    //水平
    painter.drawLine(batteryPosX, batteryPosY - verticalLineLength, batteryPosX - horizontalLineLength, batteryPosY - verticalLineLength);

    //绘制能量块，如果有的话
    for(int i = 0; i < energyPositionList.size(); i++)
    {
        //该能量不在这段
        if(energyPositionList[i] >= verticalLineLength + horizontalLineLength -HALF_ENERGY_BLOCK_WIDTH || energyPositionList[i] <= -HALF_ENERGY_BLOCK_WIDTH)
        {
            continue;
        }
        //能量冒头
        if(energyPositionList[i] < 0)
        {
            double colorAt = HALF_ENERGY_BLOCK_WIDTH / (energyPositionList[i] + ENERGY_BLOCK_WIDTH);
            drawGradientLineSegment(batteryPosX, batteryPosY - energyPositionList[i] - ENERGY_BLOCK_WIDTH, batteryPosX, batteryPosY - 2, Qt::red, painter, colorAt);
        }
        //能量完全在垂直线段
        else if(energyPositionList[i] + ENERGY_BLOCK_WIDTH <= verticalLineLength)
        {
            drawGradientLineSegment(batteryPosX, batteryPosY - energyPositionList[i], batteryPosX, batteryPosY - energyPositionList[i] - ENERGY_BLOCK_WIDTH, Qt::red, painter);
        }
        //能量在折线处
        else if(energyPositionList[i] < verticalLineLength)
        {
            int length = energyPositionList[i] + ENERGY_BLOCK_WIDTH - verticalLineLength;
            drawGradientPolylineSegment(batteryPosX, batteryPosY - energyPositionList[i], batteryPosX, batteryPosY - verticalLineLength, batteryPosX - length, batteryPosY - verticalLineLength, Qt::red, painter);
        }
        //能量在水平线处
        else if(energyPositionList[i] + ENERGY_BLOCK_WIDTH <= verticalLineLength + horizontalLineLength)
        {
            int startX = batteryPosX - (energyPositionList[i] - verticalLineLength);
            drawGradientLineSegment(startX, batteryPosY - verticalLineLength, startX - ENERGY_BLOCK_WIDTH, batteryPosY - verticalLineLength, Qt::red, painter);
        }
        //能量进入开关ing
        else
        {
            int startX = batteryPosX - (energyPositionList[i] - verticalLineLength);
            double colorAt = HALF_ENERGY_BLOCK_WIDTH / (horizontalLineLength + verticalLineLength - energyPositionList[i]);
            drawGradientLineSegment(startX, batteryPosY - verticalLineLength, batteryPosX - horizontalLineLength, batteryPosY - verticalLineLength, Qt::red, painter, colorAt);
        }
    }
    // 绘制主接触器
    drawMainContactor(painter, mainContactorX, mainContactorY, batteryWidth);

    // 绘制从主接触器到系统电压的导线
    drawWireToSystemVoltage(painter, mainContactorX, mainContactorY, batteryWidth);
}


void CircuitDiagramWidget2::on_timer_timeout()
{
    bool flag = !m_chargeContactorClosed && m_limitedContactorClosed;
    count++;
    //每5S添加一个能量
    if(count == 10)
    {
        count = 0;
        if(m_state == 2)
        {
            energyPositionList.append(DISCHARGE_START);
        }else
        {
            energyPositionList.append(CHARGE_START);
            chargeHeatPositionList.append(0);
        }
    }
    //放电
    if(m_state == 2)
    {
        for(int i = 0; i < energyPositionList.size(); i++)
        {
            energyPositionList[i] += 5;
            if (!flag && energyPositionList[i] + HALF_ENERGY_BLOCK_WIDTH > horizontalEndX - chargeContactorEndx + width() * 11 / 12 + height() * 19 / 12 + 28) {
                energyPositionList.remove(i);
            }
            if(flag && energyPositionList[i] + HALF_ENERGY_BLOCK_WIDTH > width() * 37/40 + height() * 23/12 + horizontalEndX - chargeContactorEndx + 28){
                energyPositionList.remove(i);
            }
        }
    }
    //充电
    else
    {
        //不经过加热电线的能量
        bool test = false;
        for (int i = 0; i < energyPositionList.size(); ++i) {
            energyPositionList[i] -= 5;
            if(energyPositionList[i] < 0)
            {
                if(flag)
                {
                    energyPositionList[i] = width() * 37/40 + height() * 23/12 + horizontalEndX - chargeContactorEndx + 28;
                }
                else
                {
                    energyPositionList[i] = horizontalEndX - chargeContactorEndx + width() * 11 / 12 + height() * 19 / 12 + 28;
                }
            }
            //电流回到充电的地方，移除能量
            if(energyPositionList[i] > CHARGE_START && energyPositionList[i] < width() * 3 / 10 + height() * 3 / 4 + 10)
            {
                test = true;
                energyPositionList.remove(i);
            }
        }
        // qDebug() << "铺满的能量流动：";
        for (int i = 0; i < energyPositionList.size(); ++i) {
            // qDebug() << energyPositionList[i];
        }
        //经过加热电线的能量
        for (int i = 0; i < chargeHeatPositionList.size(); ++i) {
            chargeHeatPositionList[i] += 5;
            if(chargeHeatPositionList[i] > 451)
            {
                chargeHeatPositionList.remove(i);
            }
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

    painter.drawLine(startX, startY, startX - horizontalLineLength, startY);

    //绘制能量块，如果有的话
    for(int i = 0; i < energyPositionList.size(); i++)
    {
        if(energyPositionList[i]  <= startLength - HALF_ENERGY_BLOCK_WIDTH || energyPositionList[i] > startLength + horizontalLineLength - HALF_ENERGY_BLOCK_WIDTH)
        {
            continue;
        }
        //能量冒头
        if(energyPositionList[i] <= startLength)
        {
            int length = energyPositionList[i] + ENERGY_BLOCK_WIDTH - startLength;
            double colorAt = HALF_ENERGY_BLOCK_WIDTH / length;
            drawGradientLineSegment(startX - length, startY, startX, startY, Qt::red, painter, colorAt);
        }
        //能量在水平线
        else if (energyPositionList[i] + ENERGY_BLOCK_WIDTH <= startLength + horizontalLineLength)
        {
            int x = startX - (energyPositionList[i] - startLength);
            drawGradientLineSegment(x, startY, x - ENERGY_BLOCK_WIDTH, startY, Qt::red, painter);
        }
        //能量逐渐消逝
        else
        {
            int positionInLine = energyPositionList[i] - startLength;
            double colorAt = HALF_ENERGY_BLOCK_WIDTH / (horizontalLineLength - positionInLine);
            drawGradientLineSegment(startX - positionInLine, startY, endX, startY, Qt::red, painter, colorAt);
        }
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
    painter.drawLine(startX, startY + 5, startX, verticalEndY);


    //绘制能量块，如果有的话
    if(m_heaterContactorClosed && m_heaterFaultContactorClosed)
    {
        //放电情况
        if(m_state == 2)
        {
            for(int i = 0; i < energyPositionList.size(); i++)
            {

                if(energyPositionList[i] <= startLength - HALF_ENERGY_BLOCK_WIDTH || energyPositionList[i] - startLength + HALF_ENERGY_BLOCK_WIDTH >= verticalLineLength)
                {
                    continue;
                }
                //能量冒头
                if(energyPositionList[i] < startLength)
                {
                    int positionInLine = std::min<int>(energyPositionList[i] + ENERGY_BLOCK_WIDTH - startLength, height() / 12 - 5);
                    double colorAt = HALF_ENERGY_BLOCK_WIDTH / positionInLine;
                    drawGradientLineSegment(startX, startY + positionInLine, startX, startY, Qt::red, painter, colorAt);
                }
                //能量完全在垂线上
                else if (energyPositionList[i] + ENERGY_BLOCK_WIDTH - startLength <= verticalLineLength)
                {
                    drawGradientLineSegment(startX, startY + energyPositionList[i] - startLength, startX, startY + energyPositionList[i] + ENERGY_BLOCK_WIDTH - startLength, Qt::red, painter);
                }
                //能量逐渐消散
                else
                {
                    double colorAt = HALF_ENERGY_BLOCK_WIDTH / (verticalLineLength - (energyPositionList[i] -startLength));
                    drawGradientLineSegment(startX, startY + energyPositionList[i] - startLength, startX, verticalEndY, Qt::red, painter);
                }

            }
        }

        //充电情况
        if(m_state == 1)
        {
            int startLength = width() * 11 / 120;
            for(int i = 0; i < chargeHeatPositionList.size(); i++)
            {
                if(chargeHeatPositionList[i] <= startLength - HALF_ENERGY_BLOCK_WIDTH || chargeHeatPositionList[i] >= startLength + verticalLineLength - HALF_ENERGY_BLOCK_WIDTH)
                {
                    continue;
                }
                //能量冒头
                if(chargeHeatPositionList[i] < startLength)
                {
                    double colorAt = HALF_ENERGY_BLOCK_WIDTH / std::min(chargeHeatPositionList[i] + ENERGY_BLOCK_WIDTH - startLength, height() / 12 - 5);
                    drawGradientLineSegment(startX, startY + std::min(chargeHeatPositionList[i] + ENERGY_BLOCK_WIDTH - startLength, height() / 12 - 5), startX, startY, Qt::red, painter, colorAt);
                }
                //能量完全在垂线中
                else if(chargeHeatPositionList[i] + ENERGY_BLOCK_WIDTH <= startLength + verticalLineLength)
                {
                    drawGradientLineSegment(startX, startY + chargeHeatPositionList[i] - startLength, startX, startY + chargeHeatPositionList[i] - startLength + ENERGY_BLOCK_WIDTH, Qt::red, painter);
                }
                //能量进入开关
                else
                {
                    double colorAt = HALF_ENERGY_BLOCK_WIDTH / (startLength + verticalLineLength - chargeHeatPositionList[i]);
                    drawGradientLineSegment(startX, startY + chargeHeatPositionList[i] - startLength, startX, verticalEndY, Qt::red, painter, colorAt);
                }
            }
        }
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

    painter.drawLine(startX, startY, startX, verticalEndY);
    painter.drawLine(startX, verticalEndY, startX + length - 2, verticalEndY);

    //绘制能量块，如果有的话
    if(m_heaterContactorClosed && m_heaterFaultContactorClosed)
    {
        //放电
        if(m_state == 2)
        {
            for(int i = 0; i < energyPositionList.size(); i++)
            {
                if(energyPositionList[i] <= startLength - HALF_ENERGY_BLOCK_WIDTH || energyPositionList[i] + HALF_ENERGY_BLOCK_WIDTH >= startLength + height() / 6 + width() / 30)
                {
                    continue;
                }
                //能量冒头
                if(energyPositionList[i] <= startLength)
                {
                    double colorAt = HALF_ENERGY_BLOCK_WIDTH / (energyPositionList[i] + ENERGY_BLOCK_WIDTH - startLength);
                    drawGradientLineSegment(startX, startY + energyPositionList[i] + ENERGY_BLOCK_WIDTH - startLength, startX, startY, Qt::red, painter, colorAt);
                }
                //能量完全在垂直线上
                else if(energyPositionList[i] + ENERGY_BLOCK_WIDTH <= startLength + verticalLineLength)
                {
                    drawGradientLineSegment(startX, startY + energyPositionList[i] - startLength, startX, startY + energyPositionList[i] - startLength + ENERGY_BLOCK_WIDTH, Qt::red, painter);
                }
                //能量在折线中
                else if (energyPositionList[i] <= startLength + verticalLineLength)
                {
                    int tmp = std::min<int>(energyPositionList[i] + ENERGY_BLOCK_WIDTH - startLength - verticalLineLength, length - 2);
                    drawGradientPolylineSegment(startX, startY + energyPositionList[i] - startLength, startX, verticalEndY, startX + tmp, verticalEndY, Qt::red, painter);
                }
                //能量完全在水平线中
                else if(energyPositionList[i] + ENERGY_BLOCK_WIDTH <= startLength + verticalLineLength + length - 2)
                {
                    int x = startX + energyPositionList[i] - (startLength + verticalLineLength);
                    drawGradientLineSegment(x, verticalEndY, x + ENERGY_BLOCK_WIDTH, verticalEndY, Qt::red, painter);
                }
                //能量逐渐消散
                else
                {
                    double colorAt = HALF_ENERGY_BLOCK_WIDTH / (startLength + verticalLineLength + length - energyPositionList[i]);
                    int x = startX + energyPositionList[i] - (startLength + verticalLineLength);
                    drawGradientLineSegment(x, verticalEndY, startX + length - 2, verticalEndY, Qt::red, painter);
                }
            }
        }
        //充电
        if(m_state == 1)
        {
            int startLength = width() * 17 / 120 + height() / 12 + 8;
            for (int i = 0; i < chargeHeatPositionList.size(); ++i) {
                if(chargeHeatPositionList[i] <= startLength - HALF_ENERGY_BLOCK_WIDTH || chargeHeatPositionList[i] >= startLength + height() / 6 + width() / 30 - HALF_ENERGY_BLOCK_WIDTH)
                {
                    continue;
                }
                //能量冒头
                else if(chargeHeatPositionList[i] < startLength)
                {
                    double colorAt = HALF_ENERGY_BLOCK_WIDTH / (chargeHeatPositionList[i] + ENERGY_BLOCK_WIDTH - startLength);
                    drawGradientLineSegment(startX, startY + chargeHeatPositionList[i] + ENERGY_BLOCK_WIDTH - startLength, startX, startY, Qt::red, painter, colorAt);
                }
                //能量完全在垂直线中
                else if(chargeHeatPositionList[i] + ENERGY_BLOCK_WIDTH <= startLength + verticalLineLength)
                {
                    drawGradientLineSegment(startX, startY + chargeHeatPositionList[i] - startLength, startX, startY + chargeHeatPositionList[i] - startLength + ENERGY_BLOCK_WIDTH, Qt::red, painter);
                }
                //能量在折线中
                else if(chargeHeatPositionList[i] < startLength + verticalLineLength)
                {
                    drawGradientPolylineSegment(startX, startY + chargeHeatPositionList[i] - startLength, startX, verticalEndY, startX + std::min(chargeHeatPositionList[i] - startLength - verticalLineLength + ENERGY_BLOCK_WIDTH, length - 2), verticalEndY, Qt::red, painter);
                }
                //能量在水平线中
                else if(chargeHeatPositionList[i] + ENERGY_BLOCK_WIDTH <= startLength + verticalLineLength + length)
                {
                    drawGradientLineSegment(startX + chargeHeatPositionList[i] - startLength - verticalLineLength, verticalEndY, startX + chargeHeatPositionList[i] - startLength - verticalLineLength + ENERGY_BLOCK_WIDTH, verticalEndY, Qt::red, painter);
                }
                //能量进入电阻
                else
                {
                    double colorAt = HALF_ENERGY_BLOCK_WIDTH / (length - chargeHeatPositionList[i] + startLength + verticalLineLength);
                    drawGradientLineSegment(startX + chargeHeatPositionList[i] - startLength - verticalLineLength, verticalEndY, startX + length, verticalEndY, Qt::red, painter, colorAt);
                }
            }
        }
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

    // 绘制垂直线
    painter.drawLine(startX, startY, startX, verticalEndY);

    if(m_heaterContactorClosed && m_heaterFaultContactorClosed)
    {
        //放电
        if(m_state == 2)
        {
            //绘制能量块，如果有的话
            for(int i = 0; i < energyPositionList.size(); i++)
            {
                int startLength = width() * 23 / 40 + height() / 6 + 16;
                if(energyPositionList[i] <= startLength - HALF_ENERGY_BLOCK_WIDTH
                    || energyPositionList[i] >= startLength + verticalLineLength - HALF_ENERGY_BLOCK_WIDTH)
                {
                    continue;
                }
                //能量冒头
                if(energyPositionList[i] <= startLength)
                {
                    double colorAt = HALF_ENERGY_BLOCK_WIDTH / std::min(energyPositionList[i] + ENERGY_BLOCK_WIDTH - startLength, verticalLineLength);
                    drawGradientLineSegment(startX, startY + std::min(energyPositionList[i] + ENERGY_BLOCK_WIDTH - startLength, verticalLineLength), startX, startY, Qt::black, painter, colorAt);
                }
                //能量完全在垂直线中
                else if(energyPositionList[i] + ENERGY_BLOCK_WIDTH <= startLength + verticalLineLength)
                {
                    int y = startY + energyPositionList[i] - startLength;
                    drawGradientLineSegment(startX, y, startX, y + ENERGY_BLOCK_WIDTH, Qt::black, painter);
                }
                //能量逐渐消散
                else
                {
                    double colorAt = HALF_ENERGY_BLOCK_WIDTH / (startLength + verticalLineLength - energyPositionList[i]);
                    drawGradientLineSegment(startX, startY + energyPositionList[i] - startLength, startX, verticalEndY, Qt::black, painter);
                }
            }
        }
        //充电
        if(m_state == 1)
        {
            int startLength = width() * 7 / 40 + height() / 4 + 8;
            for(int i = 0; i < chargeHeatPositionList.size(); i++)
            {
                if(chargeHeatPositionList[i] <= startLength - HALF_ENERGY_BLOCK_WIDTH || chargeHeatPositionList[i] >= startLength + verticalLineLength - HALF_ENERGY_BLOCK_WIDTH)
                {
                    continue;
                }
                //能量冒头
                int positionInLine = chargeHeatPositionList[i] - startLength;
                if(chargeHeatPositionList[i] < startLength)
                {
                    double colorAt = HALF_ENERGY_BLOCK_WIDTH / std::min(positionInLine + ENERGY_BLOCK_WIDTH, verticalLineLength);
                    drawGradientLineSegment(startX, startY + std::min(positionInLine + ENERGY_BLOCK_WIDTH, verticalLineLength), startX, startY, Qt::black, painter, colorAt);
                }
                //能量完全在垂线中
                else if(positionInLine + ENERGY_BLOCK_WIDTH <= verticalLineLength)
                {
                    drawGradientLineSegment(startX, startY + positionInLine, startX, startY + positionInLine + ENERGY_BLOCK_WIDTH, Qt::black, painter);
                }
                //能量逐渐消散
                else
                {
                    double colorAt = HALF_ENERGY_BLOCK_WIDTH / (verticalLineLength - positionInLine);
                    drawGradientLineSegment(startX, startY + positionInLine, startX, startY + verticalLineLength, Qt::black, painter);
                }
            }
        }
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
    painter.drawLine(startX, startY, startX, startY + length - 4);

    if(m_heaterContactorClosed && m_heaterFaultContactorClosed)
    {
        //放电
        if(m_state == 2)
        {
            //绘制能量块，如果有的话
            for(int i = 0; i < energyPositionList.size(); i++)
            {

                int startLength = width() * 5 / 8 + height() / 4 + 24;
                if(energyPositionList[i] <= startLength - HALF_ENERGY_BLOCK_WIDTH || energyPositionList[i] >= startLength + length - HALF_ENERGY_BLOCK_WIDTH)
                {
                    continue;
                }
                //能量冒头
                if(energyPositionList[i] <= startLength)
                {
                    double colorAt = HALF_ENERGY_BLOCK_WIDTH / std::min(energyPositionList[i] + ENERGY_BLOCK_WIDTH - startLength, length - 4);
                    drawGradientLineSegment(startX, startY + std::min(energyPositionList[i] + ENERGY_BLOCK_WIDTH - startLength, length - 4), startX, startY, Qt::black, painter, colorAt);
                }
                //能量完全在垂线中
                else if(energyPositionList[i] + ENERGY_BLOCK_WIDTH <= startLength + length)
                {
                    int y = startY + energyPositionList[i] - startLength;
                    drawGradientLineSegment(startX, y, startX, y + ENERGY_BLOCK_WIDTH, Qt::black, painter);
                }
                //能量在折线中
                else
                {
                    int y = startY + energyPositionList[i] - startLength;
                    double colorAt = HALF_ENERGY_BLOCK_WIDTH / (startLength + length - energyPositionList[i]);
                    drawGradientLineSegment(startX, y, startX, startY + length, Qt::black, painter, colorAt);
                }


            }
        }
        //充电
        if(m_state == 1)
        {
            int startLength = width() * 9 / 40 + height() * 1 / 3 + 16;
            for(int i = 0; i < chargeHeatPositionList.size(); i++)
            {
                if(chargeHeatPositionList[i] <= startLength - HALF_ENERGY_BLOCK_WIDTH || chargeHeatPositionList[i] >= startLength + length)
                {
                    continue;
                }
                int positionInLine = chargeHeatPositionList[i] - startLength;
                //能量冒头
                if(chargeHeatPositionList[i] < startLength)
                {
                    double colorAt = HALF_ENERGY_BLOCK_WIDTH / std::min(positionInLine + ENERGY_BLOCK_WIDTH, length - 4);
                    drawGradientLineSegment(startX, startY + std::min(positionInLine + ENERGY_BLOCK_WIDTH, length - 4), startX, startY, Qt::black, painter, colorAt);
                }
                //能量完全在垂线中
                else if(positionInLine + ENERGY_BLOCK_WIDTH <= length)
                {
                    drawGradientLineSegment(startX, startY + positionInLine, startX, startY + positionInLine + ENERGY_BLOCK_WIDTH, Qt::black, painter);
                }
                //能量在折线中
                // else
                // {
                //     drawGradientPolylineSegment(startX, startY + positionInLine, startX, startY + length, startX - (positionInLine + ENERGY_BLOCK_WIDTH - length), startY + length, Qt::black, painter);
                // }
            }
        }
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
 * 放电起点: width() * 3 / 10 + height() * 3 / 4 + 10
 * 充电起点：width() * 3 / 40 + height() * 5 / 6 + 4
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

    painter.drawLine(startX, verticalEndY, horizontalEndX, verticalEndY);


    //绘制能量块，如果有的话
    for(int i = 0; i < energyPositionList.size(); i++)
    {
        int startLength = width() * 3 / 10 + height() * 3 / 4 + 10;
        if(energyPositionList[i] <= startLength - HALF_ENERGY_BLOCK_WIDTH || energyPositionList[i] >= startLength + horizontalEndX - startX - HALF_ENERGY_BLOCK_WIDTH)
        {
            continue;
        }
        //能量冒个头
        if(energyPositionList[i] <= startLength)
        {
            double colorAt = HALF_ENERGY_BLOCK_WIDTH / (energyPositionList[i] + ENERGY_BLOCK_WIDTH - startLength);
            drawGradientLineSegment(startX + energyPositionList[i] + ENERGY_BLOCK_WIDTH - startLength, verticalEndY, startX, verticalEndY, Qt::black, painter, colorAt);
        }
        //能量完全在水平线中
        else if(energyPositionList[i] + ENERGY_BLOCK_WIDTH <= startLength + horizontalEndX - startX)
        {
            int x = startX + energyPositionList[i] - startLength;
            drawGradientLineSegment(x, verticalEndY, x + ENERGY_BLOCK_WIDTH, verticalEndY, Qt::black, painter);
        }
        //能量逐渐消散
        else
        {
            int x = startX + energyPositionList[i] - startLength;
            double colorAt = HALF_ENERGY_BLOCK_WIDTH / (horizontalEndX - x);
            drawGradientLineSegment(x, verticalEndY, horizontalEndX, verticalEndY, Qt::black, painter, colorAt);
        }
    }
    //从充电 加热线路过来的电流
    // if(m_heaterContactorClosed && m_heaterFaultContactorClosed && m_state == 1)
    // {
    //     for(int i = 0; i < chargeHeatPositionList.size(); i++)
    //     {
    //         int startLength = width() * 3 / 40 + height() * 5 / 6 + 4;
    //         int length = width() * 9 / 40 - startX;
    //         int positionInLine = chargeHeatPositionList[i] - startLength;
    //         if(chargeHeatPositionList[i] <= startLength || chargeHeatPositionList[i] >= startLength + length - HALF_ENERGY_BLOCK_WIDTH)
    //         {
    //             continue;
    //         }
    //         //能量块完全在水平线上
    //         else if(chargeHeatPositionList[i] + ENERGY_BLOCK_WIDTH <= startLength + length)
    //         {
    //             drawGradientLineSegment(startX + length - positionInLine, verticalEndY, startX + length - positionInLine - ENERGY_BLOCK_WIDTH, verticalEndY, Qt::black, painter);
    //         }
    //         //能量逐渐消散
    //         else
    //         {
    //             double colorAt = HALF_ENERGY_BLOCK_WIDTH / (length - positionInLine);
    //             drawGradientLineSegment(startX + length - positionInLine, verticalEndY, startX, verticalEndY, Qt::black, painter, colorAt);
    //         }
    //     }
    // }
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

    // 绘制从中点到垂直向上的线
    painter.drawLine(midX, midY - 5, midX, verticalEndY);
    // 绘制水平向右的线，直到充电接触器的x坐标
    painter.drawLine(midX, verticalEndY, chargeContactorX, verticalEndY);

    if(m_limitedContactorClosed && !m_chargeContactorClosed)
    {
        //绘制能量块，如果有的话
        int startLength = width() * 7 / 12 + height() * 3 / 4 + 20;
        int length = (chargeContactorX - midX) + verticalLineLength;
        for(int i = 0; i < energyPositionList.size(); i++)
        {
            if(energyPositionList[i] <= startLength - HALF_ENERGY_BLOCK_WIDTH || energyPositionList[i] >= startLength + length - HALF_ENERGY_BLOCK_WIDTH)
            {
                continue;
            }
            //能量在折线中
            if(energyPositionList[i] <= startLength)
            {
                drawGradientPolylineSegment(midX + energyPositionList[i] - startLength, midY, midX, midY, midX, midY - (energyPositionList[i] - startLength + ENERGY_BLOCK_WIDTH), Qt::black, painter);
            }
            //能量在垂线中
            else if (energyPositionList[i] + ENERGY_BLOCK_WIDTH - startLength <= verticalLineLength)
            {
                int y = midY - (energyPositionList[i] - startLength);
                drawGradientLineSegment(midX, y, midX, y - ENERGY_BLOCK_WIDTH, Qt::black, painter);
            }
            //能量在折线中
            else if (energyPositionList[i] - startLength <= verticalLineLength)
            {
                int tmp = energyPositionList[i] - startLength;
                drawGradientPolylineSegment(midX, midY - tmp, midX, midY - verticalLineLength, midX + tmp + ENERGY_BLOCK_WIDTH - verticalLineLength, midY - verticalLineLength, Qt::black, painter);
            }
            //能量在水平线中
            else if (energyPositionList[i] + ENERGY_BLOCK_WIDTH <= startLength + verticalLineLength + chargeContactorX - midX)
            {
                int tmp = energyPositionList[i] - (startLength + verticalLineLength);
                drawGradientLineSegment(midX + tmp, midY - verticalLineLength, midX + tmp + ENERGY_BLOCK_WIDTH, midY - verticalLineLength, Qt::black, painter);
            }
            //能量逐渐消散
            else
            {
                int tmp = energyPositionList[i] - (startLength + verticalLineLength);
                double colorAt = HALF_ENERGY_BLOCK_WIDTH / (chargeContactorX - midX - tmp);
                drawGradientLineSegment(midX + tmp, midY - verticalLineLength, chargeContactorX, midY - verticalLineLength, Qt::black, painter, colorAt);
            }
        }
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

    //绘制开关之后水平向右的线,+-2是因为线太粗了
    painter.drawLine(startX + 2, y, startX + width() / 24 - 2, y);
    //绘制电阻之后的水平线，+2是线太粗了
    painter.drawLine(startX + width() / 8 + 2, y, startX + width() / 6, y);
    //绘制垂直向下的线
    painter.drawLine(startX + width() / 6, y, startX + width() / 6, y + height() / 6 - 5);

    if(!m_chargeContactorClosed && m_limitedContactorClosed)
    {
        //绘制能量块，如果有的话
        int startLength = width() * 4 / 5 + height() * 11 / 12 + 28;
        for(int i = 0; i < energyPositionList.size(); i++)
        {
            //能量块从限流开关冒头
            if(energyPositionList[i] > startLength - HALF_ENERGY_BLOCK_WIDTH && energyPositionList[i] < startLength)
            {
                double colorAt = HALF_ENERGY_BLOCK_WIDTH / std::min(energyPositionList[i] + ENERGY_BLOCK_WIDTH - startLength, width() / 24 - 2);
                drawGradientLineSegment(startX + std::min(energyPositionList[i] + ENERGY_BLOCK_WIDTH - startLength, width() / 24 - 2), y, startX + 2, y, Qt::black, painter, colorAt);
            }
            //能量从在限流开关之后的水平线
            else if (energyPositionList[i] >= startLength + 2 && energyPositionList[i] + ENERGY_BLOCK_WIDTH <= startLength + width() / 24 - 2)
            {
                int tmp = energyPositionList[i] - startLength;
                drawGradientLineSegment(startX + tmp, y, startX + tmp + ENERGY_BLOCK_WIDTH, y, Qt::black, painter);
            }
            //能量正在进入电阻
            else if (energyPositionList[i] < startLength + width() / 24 - HALF_ENERGY_BLOCK_WIDTH && energyPositionList[i] > startLength + width() / 24 - ENERGY_BLOCK_WIDTH)
            {
                int tmp = energyPositionList[i] - startLength;
                double colorAt = HALF_ENERGY_BLOCK_WIDTH / (startLength + width() / 24 - energyPositionList[i]);
                drawGradientLineSegment(startX + tmp, y, startX + width() / 24 - 2, y, Qt::black, painter, colorAt);
            }
            //能量从电阻冒头
            else if (energyPositionList[i] > startLength + width() / 8 - HALF_ENERGY_BLOCK_WIDTH && energyPositionList[i] <= startLength + width() / 8)
            {
                int tmp = std::min(energyPositionList[i] + ENERGY_BLOCK_WIDTH - startLength - width() / 8, width() / 24);
                double colorAt = HALF_ENERGY_BLOCK_WIDTH / tmp;
                int x = startX + width() / 8;
                drawGradientLineSegment(x + tmp, y, x, y, Qt::black, painter, colorAt);
            }
            //能量完全在水平线
            else if(energyPositionList[i] >= startLength + width() / 8 && energyPositionList[i] + ENERGY_BLOCK_WIDTH <= startLength + width() / 6)
            {
                int x = startX + energyPositionList[i] - startLength;
                drawGradientLineSegment(x, y, x + ENERGY_BLOCK_WIDTH, y, Qt::black, painter);
            }
            //能量在折线中
            else if (energyPositionList[i] + ENERGY_BLOCK_WIDTH >= startLength + width() / 6 && energyPositionList[i] <= startLength + width() / 6)
            {
                int x = startX + energyPositionList[i] - startLength;
                int tmp = energyPositionList[i] + ENERGY_BLOCK_WIDTH - (startLength + width() / 6);
                drawGradientPolylineSegment(x, y, startX + width() / 6, y, startX + width() / 6, y + tmp, Qt::black, painter);
            }
            //能量在垂线中
            else if(energyPositionList[i] >= startLength + width() / 6 && energyPositionList[i] + ENERGY_BLOCK_WIDTH <= startLength + width() / 6 + height() / 6)
            {
                int tmp = energyPositionList[i] - startLength - width() / 6;
                drawGradientLineSegment(startX + width() / 6, y + tmp, startX + width() / 6, y + tmp + ENERGY_BLOCK_WIDTH, Qt::black, painter);
            }
            //能量在折线中
            else if(energyPositionList[i] <= startLength + width() / 6 + height() / 6 && energyPositionList[i] + ENERGY_BLOCK_WIDTH >= startLength + width() / 6 + height() / 6)
            {
                int tmp = energyPositionList[i] - startLength - width() / 6;
                int tmp1 = tmp + ENERGY_BLOCK_WIDTH - height() / 6;
                drawGradientPolylineSegment(startX + width() / 6, y + tmp, startX + width() / 6, y + height() / 6, startX + width() / 6 + tmp1, y + height() / 6, Qt::black, painter);
            }
        }
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
    pen.setWidth(3);
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
    pen.setWidth(3);
    pen.setBrush(gradient);
    painter.setPen(pen);

    // 绘制两条直线，避免填充三角形区域
    painter.drawLine(x1, y1, x2, y2); // 绘制第一段
    painter.drawLine(x2, y2, x3, y3); // 绘制第二段

    // 恢复原始颜色的画笔
    pen.setColor(edgeColor);
    painter.setPen(pen);
}

void CircuitDiagramWidget2::buildEnergyPositionListWithLimit()
{
    energyPositionList.clear();
    energyPositionList = {
        501, 546, 596, 646, 696, 746, 796,
        846, 896, 946, 996, 1046, 1096, 1146,
        1196, 1246, 1296, 1346, 1396, 1446, 10,
        60, 110, 160, 210, 260, 310, 360, 410
    };
}

void CircuitDiagramWidget2::buildChargeHeatEnergyPositionList()
{
    chargeHeatPositionList.clear();
    chargeHeatPositionList = {
        445, 400, 350, 300, 250, 200, 150, 100, 50, 0
    };
}

void CircuitDiagramWidget2::buildEnergyPositionListWithCharge()
{
    energyPositionList.clear();
    energyPositionList = {
        473, 518, 568, 618, 668, 718, 768,
        818, 868, 918, 968, 1018, 1068, 1118,
        1168, 1218, 1268, 1318, 1368, 40, 90,
        140, 190, 240, 290, 340, 390
    };
}

void CircuitDiagramWidget2::adjustEnergyPosition()
{
    //需要初始化能量块的位置
    if(m_state == 1 || m_state == 2)
    {
        if(!timer->isActive())
        {
            timer->start();
        }
        if(!m_chargeContactorClosed && m_limitedContactorClosed)
        {
            buildEnergyPositionListWithLimit();
        }
        else
        {
            buildEnergyPositionListWithCharge();
        }
        if(m_state == 1 && m_heaterContactorClosed && m_heaterFaultContactorClosed)
        {
            buildChargeHeatEnergyPositionList();
        }
        else
        {
            chargeHeatPositionList.clear();
        }
    }
    //不需要能量块
    else
    {
        if(timer->isActive())
        {
            timer->stop();
        }
        energyPositionList.clear();
        chargeHeatPositionList.clear();
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
    painter.drawLine(startX, startY, horizontalLineEndX, horizontalLineEndY);


    //绘制能量块，如果有的话
    int startLength = width() * 7 / 12 + height() * 3 / 4 + 20;
    for(int i = 0; i < energyPositionList.size(); i++)
    {
        if(energyPositionList[i] <= startLength - HALF_ENERGY_BLOCK_WIDTH || energyPositionList[i] >= startLength + horizontalLineLength - HALF_ENERGY_BLOCK_WIDTH)
        {
            continue;
        }
        //能量冒头
        if(energyPositionList[i] <= startLength)
        {
            double colorAt = HALF_ENERGY_BLOCK_WIDTH / (energyPositionList[i] + ENERGY_BLOCK_WIDTH - startLength);
            drawGradientLineSegment(startX + energyPositionList[i] + ENERGY_BLOCK_WIDTH - startLength, startY, startX, startY, Qt::black, painter, colorAt);
        }
        //能量块完全在线中
        else if(energyPositionList[i] + ENERGY_BLOCK_WIDTH <= startLength + horizontalLineLength)
        {
            if(m_chargeContactorClosed)
            {
                drawGradientLineSegment(startX + energyPositionList[i] - startLength, startY, startX + energyPositionList[i] - startLength + ENERGY_BLOCK_WIDTH, startY, Qt::black, painter);
            }
            else
            {
                //走限流路线
                if(energyPositionList[i] + ENERGY_BLOCK_WIDTH <= startLength + horizontalLineLength / 2)
                {
                    drawGradientLineSegment(startX + energyPositionList[i] - startLength, startY, startX + energyPositionList[i] - startLength + ENERGY_BLOCK_WIDTH, startY, Qt::black, painter);
                }
            }
        }
        //能量逐渐消散
        else
        {
            if(m_chargeContactorClosed)
            {
                double colorAt = HALF_ENERGY_BLOCK_WIDTH / (startLength + horizontalLineLength - energyPositionList[i]);
                drawGradientLineSegment(startX + energyPositionList[i] - startLength, startY, horizontalLineEndX, horizontalLineEndY, Qt::black, painter, colorAt);
            }
        }
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
    // 绘制流向电源负极的线
    drawWireFromNegativeElectrode(painter, rect.x(), rect.y(), rect.width(), rect.height());
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

    // 绘制从电池负极向上垂直线
    painter.drawLine(batteryNegPosX, batteryNegPosY - 2, batteryNegPosX, batteryNegPosY - verticalLineLength);
    // 水平向右的部分，长度为画布宽度的1/20
    painter.drawLine(batteryNegPosX, batteryNegPosY - verticalLineLength, horizontalEndX, batteryNegPosY - verticalLineLength);
    // 垂直向下的部分，长度为画布高度的5/6
    painter.drawLine(horizontalEndX, batteryNegPosY - verticalLineLength, horizontalEndX, verticalEndY);
    //绘制与充电接触器相连的电线, +2是因为线太粗了
    painter.drawLine(horizontalEndX, verticalEndY, chargeContactorEndx + 2, verticalEndY);

    //绘制能量块，如果有的话
    //充电开关断开，限流开关闭合
    bool flag = !m_chargeContactorClosed && limitedContactorClosed();
    for(int i = 0; i < energyPositionList.size(); i++)
    {
        int positionInLine = energyPositionList[i] - (width()*19/24 + height() * 3/4 + 28);
        if(flag)
        {
            //只考虑limit线路流动到水平线段开始
            positionInLine = energyPositionList[i] - (width()*29/30+height()*13/12+28);
        }
        if(positionInLine <= -HALF_ENERGY_BLOCK_WIDTH || (positionInLine <= 0 && flag)){
            continue;
        }
        //能量冒头
        if(positionInLine < 0)
        {
            double colorAt = HALF_ENERGY_BLOCK_WIDTH / (positionInLine + ENERGY_BLOCK_WIDTH);
            drawGradientLineSegment(chargeContactorEndx + positionInLine + ENERGY_BLOCK_WIDTH, verticalEndY, chargeContactorEndx + 2, verticalEndY, Qt::black, painter, colorAt);
        }
        else
        {
            //从限流过来的
            if(flag)
            {
                positionInLine += width() / 6;
            }
            //能量在第一条水平线中
            if(positionInLine + ENERGY_BLOCK_WIDTH <= (horizontalEndX - chargeContactorEndx))
            {
                drawGradientLineSegment(chargeContactorEndx + positionInLine, verticalEndY, chargeContactorEndx + positionInLine + ENERGY_BLOCK_WIDTH, verticalEndY, Qt::black, painter);
            }
            //能量在折线中
            else if (positionInLine < horizontalEndX - chargeContactorEndx)
            {
                int tmp = positionInLine + ENERGY_BLOCK_WIDTH - (horizontalEndX - chargeContactorEndx);
                drawGradientPolylineSegment(chargeContactorEndx + positionInLine, verticalEndY, horizontalEndX, verticalEndY, horizontalEndX, verticalEndY - tmp, Qt::black, painter);
            }
            //能量在垂线中
            else if(positionInLine + ENERGY_BLOCK_WIDTH <= horizontalEndX - chargeContactorEndx + verticalEndY - (batteryNegPosY - verticalLineLength))
            {
                positionInLine -= (horizontalEndX - chargeContactorEndx);
                drawGradientLineSegment(horizontalEndX, verticalEndY - positionInLine, horizontalEndX, verticalEndY - positionInLine - ENERGY_BLOCK_WIDTH, Qt::black, painter);
            }
            //能量在折线中
            else if (positionInLine <= horizontalEndX - chargeContactorEndx + verticalEndY - (batteryNegPosY - verticalLineLength))
            {
                positionInLine -= (horizontalEndX - chargeContactorEndx);
                int temp = positionInLine + ENERGY_BLOCK_WIDTH - (verticalEndY - (batteryNegPosY - verticalLineLength));
                drawGradientPolylineSegment(horizontalEndX, verticalEndY - positionInLine, horizontalEndX, batteryNegPosY - verticalLineLength, horizontalEndX - temp, batteryNegPosY - verticalLineLength, Qt::black, painter);
            }
            //能量在水平线中
            else if (positionInLine + ENERGY_BLOCK_WIDTH <= horizontalEndX - chargeContactorEndx + verticalEndY - (batteryNegPosY - verticalLineLength) + horizontalLineLength)
            {
                positionInLine -= (horizontalEndX - chargeContactorEndx + verticalEndY - (batteryNegPosY - verticalLineLength));
                drawGradientLineSegment(horizontalEndX - positionInLine, batteryNegPosY - verticalLineLength, horizontalEndX - positionInLine - ENERGY_BLOCK_WIDTH, batteryNegPosY - verticalLineLength, Qt::black, painter);
            }
            //能量在折线中
            else if (positionInLine <= horizontalEndX - chargeContactorEndx + verticalEndY - (batteryNegPosY - verticalLineLength) + horizontalLineLength)
            {
                positionInLine -= (horizontalEndX - chargeContactorEndx + verticalEndY - (batteryNegPosY - verticalLineLength));
                int tmp = std::min(positionInLine + ENERGY_BLOCK_WIDTH - horizontalLineLength, verticalLineLength - 2);
                drawGradientPolylineSegment(horizontalEndX - positionInLine, batteryNegPosY - verticalLineLength, batteryNegPosX, batteryNegPosY - verticalLineLength, batteryNegPosX, batteryNegPosY - verticalLineLength + tmp > batteryNegPosY ? batteryNegPosY : batteryNegPosY - verticalLineLength + tmp, Qt::black, painter);
            }
            //能量在垂线中
            else if (positionInLine + ENERGY_BLOCK_WIDTH <= horizontalEndX - chargeContactorEndx + verticalEndY - (batteryNegPosY - verticalLineLength) + horizontalLineLength + verticalLineLength)
            {
                positionInLine -= (horizontalEndX - chargeContactorEndx + verticalEndY - (batteryNegPosY - verticalLineLength) + horizontalLineLength);
                drawGradientLineSegment(batteryNegPosX, batteryNegPosY - verticalLineLength + positionInLine, batteryNegPosX, batteryNegPosY - verticalLineLength + positionInLine + ENERGY_BLOCK_WIDTH, Qt::black, painter);
            }
            //能量逐渐消散
            else
            {
                //最后一段低于能量块宽度，直接忽略
                // positionInLine -= (horizontalEndX - chargeContactorEndx + verticalEndY - (batteryNegPosY - verticalLineLength) + horizontalLineLength + verticalLineLength);
                // double colorAt = HALF_ENERGY_BLOCK_WIDTH / (verticalLineLength - positionInLine);
                // drawGradientLineSegment(batteryNegPosX, batteryNegPosY - verticalLineLength + positionInLine, batteryNegPosX, batteryNegPosY, Qt::black, painter, colorAt);
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
    int verticalMargin = height() / 4 + 5;
    int horizontalMargin = width() / 9;

    // 电池主体
    QRect batteryRect(width() - batteryWidth - horizontalMargin + offsetX, verticalMargin, batteryWidth, batteryHeight);
    rect = batteryRect;
    // 深蓝色长方形
    int borderSize = batteryRect.width() / 40;
    QRect blueRect(batteryRect.left() - borderSize, batteryRect.top() - borderSize, batteryRect.width() + borderSize * 2, batteryRect.height() + borderSize * 2);

    // 绘制电池主体和梯形
    drawBatteryBody(painter, batteryRect, blueRect);
    drawTrapezoid(painter, blueRect, borderSize, batteryRect.height() / 20);
    drawBase(painter, blueRect, borderSize, batteryRect.height() / 10);

    // 绘制电极
    drawElectrodes(painter, batteryRect);

    // 绘制充电百分比
    drawChargeLevel(painter, batteryRect);

    // 绘制从电池正极到主接触器的连接线
    drawWireToMainContactor(painter, batteryRect.x(), batteryRect.y(), batteryRect.width(), batteryRect.height());

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

CircuitDiagramWidget2::~CircuitDiagramWidget2()
{
    if (timer->isActive()) {
        timer->stop();
    }
    delete timer;
}
