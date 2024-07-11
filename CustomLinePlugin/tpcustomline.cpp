#include "tpcustomline.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>

TPCustomLine::TPCustomLine(QWidget *parent)
    : QWidget(parent), m_x1(10), m_y1(50), m_x2(50), m_y2(50), m_lineColor(Qt::black), m_radius(0), m_line2Length(40), m_angleBetweenLines(345), m_startCircleRadius(0), m_penWidth(3), m_rotationAngle(0)
{
    setMinimumSize(100, 50);  // 可以根据需要设置最小尺寸
}

TPCustomLine::~TPCustomLine()
{
}

int TPCustomLine::x1() const
{
    return m_x1;
}

void TPCustomLine::setX1(int x1)
{
    if (m_x1 != x1) {
        m_x1 = x1;
        emit x1Changed(x1);
        update();
    }
}

int TPCustomLine::y1() const
{
    return m_y1;
}

void TPCustomLine::setY1(int y1)
{
    if (m_y1 != y1) {
        m_y1 = y1;
        emit y1Changed(y1);
        update();
    }
}

int TPCustomLine::x2() const
{
    return m_x2;
}

void TPCustomLine::setX2(int x2)
{
    if (m_x2 != x2) {
        m_x2 = x2;
        emit x2Changed(x2);
        update();
    }
}

int TPCustomLine::y2() const
{
    return m_y2;
}

void TPCustomLine::setY2(int y2)
{
    if (m_y2 != y2) {
        m_y2 = y2;
        emit y2Changed(y2);
        update();
    }
}

QColor TPCustomLine::lineColor() const
{
    return m_lineColor;
}

void TPCustomLine::setLineColor(const QColor &color)
{
    if (m_lineColor != color) {
        m_lineColor = color;
        emit lineColorChanged(color);
        update();
    }
}

int TPCustomLine::radius() const
{
    return m_radius;
}

void TPCustomLine::setRadius(int radius)
{
    if (m_radius != radius) {
        m_radius = radius;
        emit radiusChanged(radius);
        update();
    }
}

int TPCustomLine::line2Length() const
{
    return m_line2Length;
}

void TPCustomLine::setLine2Length(int length)
{
    if (m_line2Length != length) {
        m_line2Length = length;
        emit line2LengthChanged(length);
        update();
    }
}

double TPCustomLine::angleBetweenLines() const
{
    return m_angleBetweenLines;
}

void TPCustomLine::setAngleBetweenLines(double angle)
{
    if (m_angleBetweenLines != angle) {
        m_angleBetweenLines = angle;
        emit angleBetweenLinesChanged(angle);
        update();
    }
}

int TPCustomLine::startCircleRadius() const
{
    return m_startCircleRadius;
}

void TPCustomLine::setStartCircleRadius(int radius)
{
    if (m_startCircleRadius != radius) {
        m_startCircleRadius = radius;
        emit startCircleRadiusChanged(radius);
        update();
    }
}

int TPCustomLine::penWidth() const
{
    return m_penWidth;
}

void TPCustomLine::setPenWidth(int width)
{
    if (m_penWidth != width) {
        m_penWidth = width;
        emit penWidthChanged(width);
        update();
    }
}

double TPCustomLine::rotationAngle() const
{
    return m_rotationAngle;
}

void TPCustomLine::setRotationAngle(double angle)
{
    if (m_rotationAngle != angle) {
        m_rotationAngle = angle;
        emit rotationAngleChanged(angle);
        update();
    }
}

void TPCustomLine::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    if (m_rotationAngle != 0) {
        QPointF center(width() / 2.0, height() / 2.0);
        painter.translate(center);
        painter.rotate(m_rotationAngle);
        painter.translate(-center);
    }

    QPen pen(m_lineColor);
    pen.setWidth(m_penWidth);
    painter.setPen(pen);

    if (m_startCircleRadius > 0) {
        double angle = qAtan2(m_y2 - m_y1, m_x2 - m_x1);
        double offsetX = m_startCircleRadius * qCos(angle);
        double offsetY = m_startCircleRadius * qSin(angle);
        QPointF startCircleCenter(m_x1 - offsetX, m_y1 - offsetY);

        QPen circlePen(m_lineColor);
        circlePen.setWidth(m_penWidth);
        painter.setPen(circlePen);
        painter.drawEllipse(startCircleCenter, m_startCircleRadius, m_startCircleRadius);

        m_x1 = startCircleCenter.x() + offsetX;
        m_y1 = startCircleCenter.y() + offsetY;
    }

    painter.drawLine(m_x1, m_y1, m_x2, m_y2);

    if (m_radius > 0) {
        double angle = qAtan2(m_y2 - m_y1, m_x2 - m_x1);
        double offsetX = m_radius * qCos(angle);
        double offsetY = m_radius * qSin(angle);
        QPointF circleCenter(m_x2 + offsetX, m_y2 + offsetY);

        QPen circlePen(m_lineColor);
        circlePen.setWidth(m_penWidth);
        painter.setPen(circlePen);
        painter.drawEllipse(circleCenter, m_radius, m_radius);

        if (m_line2Length > 0) {
            // Adjust angle for second line
            double adjustedAngle = angle + qDegreesToRadians(m_angleBetweenLines);
            double startX = circleCenter.x() + m_radius * qCos(angle - M_PI / 2);
            double startY = circleCenter.y() + m_radius * qSin(angle - M_PI / 2);
            double endX = startX + m_line2Length * qCos(adjustedAngle);
            double endY = startY + m_line2Length * qSin(adjustedAngle);

            painter.setPen(pen);
            painter.drawLine(startX, startY, endX, endY);
        }
    }
}
