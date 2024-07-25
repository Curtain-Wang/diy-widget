#include "tpcircuitdiagram.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QPainterPath>s


TPCircuitDiagram::TPCircuitDiagram(QWidget *parent)
    : QWidget(parent),
    m_powerLevel(0),
    m_warnLevel(20),
    m_mainContactorClosed(false),
    m_heaterErrorContactorClosed(false),
    m_isHeating(false),
    m_dischargeContactorClosed(true),
    m_chargeContactorClosed(false),
    m_limitedContactorClosed(false),
    m_heaterContactorClosed(false)
{

}

// Power Level
int TPCircuitDiagram::powerLevel() const {
    return m_powerLevel;
}

void TPCircuitDiagram::setPowerLevel(int level) {
    if (m_powerLevel != level) {
        m_powerLevel = level;
        emit powerLevelChanged(m_powerLevel);
        update(); // 更新界面
    }
}

// Warn Level
int TPCircuitDiagram::warnLevel() const {
    return m_warnLevel;
}

void TPCircuitDiagram::setWarnLevel(int level) {
    if (m_warnLevel != level) {
        m_warnLevel = level;
        emit warnLevelChanged(m_warnLevel);
        update(); // 更新界面
    }
}

// Main Contactor Closed
bool TPCircuitDiagram::mainContactorClosed() const {
    return m_mainContactorClosed;
}

void TPCircuitDiagram::setMainContactorClosed(bool closed) {
    if (m_mainContactorClosed != closed) {
        m_mainContactorClosed = closed;
        emit mainContactorClosedChanged(m_mainContactorClosed);
        update(); // 更新界面
    }
}

// Heater Error Contactor Closed
bool TPCircuitDiagram::heaterErrorContactorClosed() const {
    return m_heaterErrorContactorClosed;
}

void TPCircuitDiagram::setHeaterErrorContactorClosed(bool closed) {
    if (m_heaterErrorContactorClosed != closed) {
        m_heaterErrorContactorClosed = closed;
        emit heaterErrorContactorClosedChanged(m_heaterErrorContactorClosed);
        update(); // 更新界面
    }
}

// Is Heating
bool TPCircuitDiagram::isHeating() const {
    return m_isHeating;
}

void TPCircuitDiagram::setIsHeating(bool heating) {
    if (m_isHeating != heating) {
        m_isHeating = heating;
        emit isHeatingChanged(m_isHeating);
        update(); // 更新界面
    }
}

// Discharge Contactor Closed
bool TPCircuitDiagram::dischargeContactorClosed() const {
    return m_dischargeContactorClosed;
}

void TPCircuitDiagram::setDischargeContactorClosed(bool closed) {
    if (m_dischargeContactorClosed != closed) {
        m_dischargeContactorClosed = closed;
        emit dischargeContactorClosedChanged(m_dischargeContactorClosed);
        update(); // 更新界面
    }
}

// Charge Contactor Closed
bool TPCircuitDiagram::chargeContactorClosed() const {
    return m_chargeContactorClosed;
}

void TPCircuitDiagram::setChargeContactorClosed(bool closed) {
    if (m_chargeContactorClosed != closed) {
        m_chargeContactorClosed = closed;
        emit chargeContactorClosedChanged(m_chargeContactorClosed);
        update(); // 更新界面
    }
}

// Limited Contactor Closed
bool TPCircuitDiagram::limitedContactorClosed() const {
    return m_limitedContactorClosed;
}

void TPCircuitDiagram::setLimitedContactorClosed(bool closed) {
    if (m_limitedContactorClosed != closed) {
        m_limitedContactorClosed = closed;
        emit limitedContactorClosedChanged(m_limitedContactorClosed);
        update(); // 更新界面
    }
}

// Heater Contactor Closed
bool TPCircuitDiagram::heaterContactorClosed() const {
    return m_heaterContactorClosed;
}

void TPCircuitDiagram::setHeaterContactorClosed(bool closed) {
    if (m_heaterContactorClosed != closed) {
        m_heaterContactorClosed = closed;
        emit heaterContactorClosedChanged(m_heaterContactorClosed);
        update(); // 更新界面
    }
}

void TPCircuitDiagram::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // 获取当前画布的大小
    int widgetWidth = width();
    int widgetHeight = height();

    // 绘制画布边框
    QPen borderPen(Qt::black); // 边框线条颜色
    borderPen.setWidth(2);
    painter.setPen(borderPen);
    // painter.drawRect(0, 0, widgetWidth-1, widgetHeight-1); // 绘制画布的黑色边框

    // 计算相对坐标和尺寸
    int batteryX = widgetWidth * 25 / 755;
    int batteryY = widgetHeight * 100 / 393;
    int batteryWidth = widgetWidth * 125 / 755;
    int batteryHeight = widgetHeight * 200 / 393;

    // 绘制电池
    drawBattery(painter, batteryX, batteryY, batteryWidth, batteryHeight);

    // 绘制从电池正极到主接触器的连接线
    drawWireToMainContactor(painter, batteryX, batteryY, batteryWidth, batteryHeight);

    // 从BUS+线绘制垂直线到HeaterErrorContactor
    int startX = batteryX + batteryWidth + width() / 2;
    int startY = batteryY - 2 - batteryWidth / 4;
    drawWireToHeaterErrorContactor(painter, startX, startY, batteryWidth);

    // 绘制加热器
    // 从HeaterErrorContactor到加热器的垂直线末尾位置
    int heaterY = startY + 2 * (batteryWidth / 6) + batteryWidth / 3 + 4;
    int heaterSize = batteryWidth; // 加热器的大小
    drawHeater(painter, startX - heaterSize / 2, heaterY, heaterSize);
    //绘制加热器下方的开关
    drawWireToHeaterContactor(painter, startX - heaterSize / 2, heaterY, heaterSize, batteryWidth, batteryY, batteryHeight);

    // 绘制从电池负电极到Discharge开关的导线以及charge开关等等
    drawWireToDischargeContactor(painter, batteryX, batteryY, batteryWidth, batteryHeight);
}

void TPCircuitDiagram::drawBattery(QPainter &painter, int x, int y, int width, int height)
{
    // 设置视口和窗口
    QRect batteryRect(x, y, width, height);
    painter.setViewport(batteryRect); // 设置视口
    painter.setWindow(0, 0, 50, 120); // 设置窗口大小，逻辑坐标

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    // 绘制电池边框
    QPen pen(Qt::black); // 边框线条颜色
    pen.setWidth(2);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::BevelJoin);
    painter.setPen(pen);
    QBrush brush(Qt::white); // 画刷颜色
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    QRect rect(1, 10, 48, 109); // 电池边框的矩形区域
    painter.drawRect(rect); // 绘制电池边框

    brush.setColor(Qt::black);
    painter.setBrush(brush);
    rect.setRect(15, 0, 20, 10); // 电池正极头的矩形区域
    painter.drawRect(rect); // 画电池正极头

    // 画电量柱
    if (m_powerLevel > m_warnLevel) // 正常颜色的电量柱
    {
        brush.setColor(Qt::green);
        pen.setColor(Qt::green);
    }
    else // 电量低的电量柱
    {
        brush.setColor(Qt::red);
        pen.setColor(Qt::red);
    }
    painter.setBrush(brush);
    painter.setPen(pen);
    if (m_powerLevel > 0)
    {
        int powerHeight = m_powerLevel; // 电量柱的高度
        int offset = 3; // 偏移量
        rect.setRect(5, 119 - powerHeight - offset, 40, powerHeight - offset); // 电量柱的矩形区域
        painter.drawRect(rect); // 画电量柱
    }

    // 绘制电量百分比文字
    QFontMetrics textSize(this->font());
    QString powStr = QString::asprintf("%d%%", m_powerLevel);
    QRect textRect = textSize.boundingRect(powStr); // 得到字符串的矩形区
    painter.setFont(this->font());
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.drawText(25 - textRect.width() / 2, 60 + textRect.height() / 2, powStr); // 在电池中间绘制电量百分比文字
}

void TPCircuitDiagram::drawWireToMainContactor(QPainter &painter, int batteryX, int batteryY, int batteryWidth, int batteryHeight)
{
    // 还原视口和窗口设置，以绘制其他部分
    painter.setViewport(0, 0, width(), height());
    painter.setWindow(0, 0, width(), height());

    QPen pen(Qt::red); // 导线颜色
    pen.setWidth(2);
    painter.setPen(pen);

    // 电池正极的中心点坐标
    int batteryPosX = batteryX + batteryWidth / 2;
    int batteryPosY = batteryY - 2; // 向上移动2个单位

    // 垂直线长度为电池宽度的1/4
    int verticalLineLength = batteryWidth / 4;

    // 主接触器的位置 (相对电池右上角)
    int horizontalLineLength = width() / 4; // 连接到主接触器的水平线长度
    int mainContactorX = batteryPosX + horizontalLineLength;
    int mainContactorY = batteryPosY - verticalLineLength;

    // 绘制从电池到主接触器的线
    painter.drawLine(batteryPosX, batteryPosY, batteryPosX, batteryPosY - verticalLineLength); // 垂直线
    painter.drawLine(batteryPosX, batteryPosY - verticalLineLength, mainContactorX, batteryPosY - verticalLineLength); // 水平线

    // 绘制主接触器
    drawMainContactor(painter, mainContactorX, batteryPosY - verticalLineLength, batteryWidth);

    // 在主接触器上方绘制 "Main Contactor"
    QFont font = painter.font();
    font.setFamily("Times New Roman"); // 设置字体样式
    font.setPointSize(13); // 设置字体大小
    painter.setFont(font);
    painter.drawText(mainContactorX, batteryPosY - verticalLineLength - 20, "Main Contactor");

    // 绘制主接触器右边的水平线
    int busLineLength = width() / 2; // 水平线长度为画布宽度的1/2
    int busLineStartX = mainContactorX + batteryWidth / 3 + 4; // 从圆弧开始，并加上圆的半径
    int busLineEndX = busLineStartX + busLineLength;
    painter.drawLine(busLineStartX, batteryPosY - verticalLineLength, busLineEndX, batteryPosY - verticalLineLength);

    // 在水平线末尾上方绘制 "BUS+"
    font.setPointSize(15); // 设置字体大小
    font.setWeight(QFont::Bold); // 设置字体加粗
    painter.setFont(font);
    painter.drawText(busLineEndX - (batteryWidth / 3), batteryPosY - verticalLineLength - 5, "BUS+");
}









void TPCircuitDiagram::drawMainContactor(QPainter &painter, int x, int y, int batteryWidth)
{
    int radius = 4;
    int centerDistance = batteryWidth / 3; // 调整为电池宽度的1/3

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
    if (m_mainContactorClosed)
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

void TPCircuitDiagram::drawWireToHeaterErrorContactor(QPainter &painter, int startX, int startY, int batteryWidth)
{
    // 垂直线长度为电池宽度的1/6
    int verticalLineLength = batteryWidth / 6;
    int radius = 4;

    // 绘制垂直线
    painter.drawLine(startX, startY, startX, startY + verticalLineLength);

    // 绘制HeaterErrorContactor
    drawHeaterErrorContactor(painter, startX, startY + verticalLineLength, batteryWidth);

    // 绘制HeaterErrorContactor下方的垂直线
    int lowerVerticalLineStartY = startY + verticalLineLength + batteryWidth / 3 + radius;
    int lowerVerticalLineEndY = lowerVerticalLineStartY + verticalLineLength;
    painter.drawLine(startX, lowerVerticalLineStartY, startX, lowerVerticalLineEndY);
}



void TPCircuitDiagram::drawHeaterErrorContactor(QPainter &painter, int x, int y, int batteryWidth)
{
    int radius = 4;
    int centerDistance = batteryWidth / 3; // 调整为电池宽度的1/3

    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制两个圆
    QPen pen(Qt::red); // 圆和线的颜色
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(Qt::white);
    painter.drawEllipse(x - radius, y - radius, radius * 2, radius * 2);
    painter.drawEllipse(x - radius, y + centerDistance - radius, radius * 2, radius * 2);

    // 绘制接触器线
    QLineF line;
    QPointF startPoint(x + radius, y); // 从圆弧位置开始
    if (m_heaterErrorContactorClosed)
    {
        // 闭合状态：垂直线
        QPointF endPoint(x + radius, y + centerDistance);
        line.setP1(startPoint);
        line.setP2(endPoint);
    }
    else
    {
        // 打开状态：与垂直夹角345度，斜向右下
        double angle = 75.0; // 与垂直线的夹角是75度，即90-15度
        double length = centerDistance;
        QPointF endPoint(x + radius + length * cos(qDegreesToRadians(angle)), y + length * sin(qDegreesToRadians(angle)));
        line.setP1(startPoint);
        line.setP2(endPoint);
    }
    painter.drawLine(line);
}

void TPCircuitDiagram::drawHeater(QPainter &painter, int x, int y, int side)
{
    // 设置正方形边框画笔颜色和宽度
    QPen squarePen(Qt::black);
    int penWidth = 3;
    squarePen.setWidth(penWidth);
    painter.setPen(squarePen);
    painter.setBrush(Qt::NoBrush); // 设置为无填充

    // 绘制一个空心正方形
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
        int smokeHeight = 50;  // 增加波浪线高度
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

void TPCircuitDiagram::drawWireToDischargeContactor(QPainter &painter, int batteryX, int batteryY, int batteryWidth, int batteryHeight)
{
    // 设置画笔颜色
    QPen pen(Qt::black); // 导线颜色
    pen.setWidth(2);
    painter.setPen(pen);

    // 电池负极的中心点坐标
    int batteryPosX = batteryX + batteryWidth / 2;
    int batteryPosY = batteryY + batteryHeight;

    // 绘制从电池负极到Discharge开关的垂直线
    int verticalLineLength = batteryWidth / 2;
    painter.drawLine(batteryPosX, batteryPosY, batteryPosX, batteryPosY + verticalLineLength);

    // 计算水平线的终点坐标
    int horizontalLineLength = width() / 4; // 与drawWireToMainContactor中的水平线长度一致
    int horizontalLineEndX = batteryPosX + horizontalLineLength; // 将方向改为向右

    // 绘制水平线
    painter.drawLine(batteryPosX, batteryPosY + verticalLineLength, horizontalLineEndX, batteryPosY + verticalLineLength);

    // Discharge开关的位置 (相对电池底部)
    int dischargeContactorX = horizontalLineEndX;
    int dischargeContactorY = batteryPosY + verticalLineLength;

    // 绘制Discharge开关
    drawDischargeContactor(painter, dischargeContactorX, dischargeContactorY, batteryWidth);

    //绘制chargeContactor
    drawWireToChargeContactor(painter, dischargeContactorX, dischargeContactorY, batteryWidth);
}




void TPCircuitDiagram::drawDischargeContactor(QPainter &painter, int x, int y, int batteryWidth)
{
    int radius = 4;
    int centerDistance = batteryWidth / 3; // 调整为电池宽度的1/3

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
    if (m_dischargeContactorClosed)
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

void TPCircuitDiagram::drawWireToChargeContactor(QPainter &painter, int dischargeContactorX, int dischargeContactorY, int batteryWidth)
{
    // 设置画笔颜色
    QPen pen(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);

    // 计算水平线的起点和终点坐标
    int startX = dischargeContactorX + batteryWidth / 3 + 4; // 圆的右边缘
    int startY = dischargeContactorY;
    int endX = startX + batteryWidth / 4; // 水平线的长度为 batteryWidth / 4

    // 绘制水平线
    painter.drawLine(startX, startY, endX, startY);

    // 绘制Charge开关
    drawChargeContactor(painter, endX, startY, batteryWidth);

    //绘制limit
    // 计算起始位置
    int midX = (startX + endX) / 2;
    int midY = startY;

    // 调用新方法
    drawWireToLimitedContactor(painter, midX, midY, batteryWidth);
}

void TPCircuitDiagram::drawChargeContactor(QPainter &painter, int x, int y, int batteryWidth)
{
    int radius = 4;
    int centerDistance = batteryWidth / 3;

    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制两个圆
    QPen pen(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(Qt::white);
    painter.drawEllipse(x - radius, y - radius, radius * 2, radius * 2);
    painter.drawEllipse(x + centerDistance - radius, y - radius, radius * 2, radius * 2);

    // 绘制开关线
    QLineF line;
    QPointF startPoint(x, y - radius);
    if (m_chargeContactorClosed)
    {
        QPointF endPoint(x + centerDistance, y - radius);
        line.setP1(startPoint);
        line.setP2(endPoint);
    }
    else
    {
        double angle = 15.0;
        double length = centerDistance;
        QPointF endPoint(x + length * cos(qDegreesToRadians(angle)), y - radius - length * sin(qDegreesToRadians(angle)));
        line.setP1(startPoint);
        line.setP2(endPoint);
    }
    painter.drawLine(line);


    // 调用 drawWireToBusMinus 方法绘制连接线
    int wireStartX = x + centerDistance + 4; // 从第二个圆的右边开始
    int wireStartY = y; // 水平位置与圆心一致
    drawWireToBusMinus(painter, wireStartX, wireStartY, batteryWidth);
}

void TPCircuitDiagram::drawWireToBusMinus(QPainter &painter, int startX, int startY, int batteryWidth)
{
    // 设置画笔颜色
    QPen pen(Qt::black); // 导线颜色
    pen.setWidth(2);
    painter.setPen(pen);

    // 绘制水平线
    int horizontalLineLength = width() / 2 - 8 - batteryWidth / 3 - batteryWidth / 4; // 水平线长度
    int horizontalLineEndX = startX + horizontalLineLength;
    painter.drawLine(startX, startY, horizontalLineEndX, startY);

    // 在水平线末尾上方绘制 "BUS-"
    QFont font = painter.font();
    font.setFamily("Times New Roman"); // 设置字体样式
    font.setWeight(QFont::Bold); // 设置字体加粗
    font.setPointSize(15); // 设置字体大小
    painter.setFont(font);
    painter.drawText(horizontalLineEndX - batteryWidth / 3, startY - 5, "BUS-");
}

void TPCircuitDiagram::drawWireToLimitedContactor(QPainter &painter, int midX, int midY, int batteryWidth)
{
    // 垂直线的长度
    int verticalLineLength = batteryWidth / 3;

    // 绘制垂直线
    painter.drawLine(midX, midY, midX, midY - verticalLineLength);

    // 水平线的长度
    int horizontalLineLength = batteryWidth / 8;

    // 绘制水平线
    painter.drawLine(midX, midY - verticalLineLength, midX + horizontalLineLength, midY - verticalLineLength);

    // 绘制Limited接触器
    drawLimitedContactor(painter, midX + horizontalLineLength, midY - verticalLineLength, batteryWidth);

    //绘制limited接触器右边的水平线
    int startX = midX + horizontalLineLength + 4 + batteryWidth / 3;
    int length = batteryWidth / 8;
    painter.drawLine(startX, midY - verticalLineLength, startX + length, midY - verticalLineLength);

    //绘制limited接触器右边的垂直线
    painter.drawLine(startX + length, midY - verticalLineLength, startX + length, midY);
}

void TPCircuitDiagram::drawLimitedContactor(QPainter &painter, int x, int y, int batteryWidth)
{
    int radius = 4;
    int centerDistance = batteryWidth / 3;

    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制两个圆
    QPen pen(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(Qt::white);
    painter.drawEllipse(x - radius, y - radius, radius * 2, radius * 2);
    painter.drawEllipse(x + centerDistance - radius, y - radius, radius * 2, radius * 2);

    // 绘制开关线
    QLineF line;
    QPointF startPoint(x, y - radius);
    if (m_limitedContactorClosed)
    {
        QPointF endPoint(x + centerDistance, y - radius);
        line.setP1(startPoint);
        line.setP2(endPoint);
    }
    else
    {
        double angle = 15.0;
        double length = centerDistance;
        QPointF endPoint(x + length * cos(qDegreesToRadians(angle)), y - radius - length * sin(qDegreesToRadians(angle)));
        line.setP1(startPoint);
        line.setP2(endPoint);
    }
    painter.drawLine(line);
}

void TPCircuitDiagram::drawWireToHeaterContactor(QPainter &painter, int heaterX, int heaterY, int heaterSize, int batteryWidth, int batteryY, int batteryHeight)
{
    // 垂直线的长度
    int verticalLineLength = batteryWidth / 8;

    // 绘制从加热器底部向下的垂直线
    int verticalLineStartX = heaterX + heaterSize / 2;
    int verticalLineStartY = heaterY + heaterSize;
    int verticalLineEndY = verticalLineStartY + verticalLineLength;
    painter.drawLine(verticalLineStartX, verticalLineStartY - 4, verticalLineStartX, verticalLineEndY);

    // 加热接触器的位置
    int heaterContactorX = verticalLineStartX;
    int heaterContactorY = verticalLineEndY;

    // 绘制加热接触器
    drawHeaterContactor(painter, heaterContactorX, heaterContactorY, batteryWidth, batteryY, batteryHeight);
}

void TPCircuitDiagram::drawHeaterContactor(QPainter &painter, int x, int y, int batteryWidth, int batteryY, int batteryHeight)
{
    int radius = 4;
    int centerDistance = batteryWidth / 3;

    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制两个圆
    QPen pen(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(Qt::white);
    painter.drawEllipse(x - radius, y - radius, radius * 2, radius * 2);
    painter.drawEllipse(x - radius, y + centerDistance - radius, radius * 2, radius * 2);

    // 绘制接触器线
    QLineF line;
    QPointF startPoint(x + radius, y); // 开关线的起点为圆的右侧
    if (m_heaterContactorClosed)
    {
        // 闭合状态：垂直线
        QPointF endPoint(x + radius, y + centerDistance);
        line.setP1(startPoint);
        line.setP2(endPoint);
    }
    else
    {
        // 打开状态：与垂直线夹角75度，斜向右下
        double angle = 75.0; // 与垂直线的夹角是75度
        double length = centerDistance;
        QPointF endPoint(x + radius + length * cos(qDegreesToRadians(angle)), y + length * sin(qDegreesToRadians(angle)));
        line.setP1(startPoint);
        line.setP2(endPoint);
    }
    painter.drawLine(line);

    //绘制加热器开关下面的垂直线
    painter.drawLine(x, y + centerDistance + 4, x, batteryY + batteryHeight + batteryWidth / 2);
}

