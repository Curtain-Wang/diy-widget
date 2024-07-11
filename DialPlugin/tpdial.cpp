#include "tpdial.h"
#include <QPainter>
#include <QLinearGradient>
#include <QRadialGradient>
#include <QConicalGradient>
#include <QFontMetricsF>
#include <cmath>

TPDial::TPDial(QWidget *parent)
    : QWidget(parent),
    m_background(Qt::black),
    m_foreground(Qt::white),
    m_maxValue(60),
    m_minValue(0),
    m_startAngle(60),
    m_endAngle(60),
    m_scaleMajor(6),
    m_scaleMinor(10),
    m_value(33),
    m_precision(0),
    m_units("L/min"),
    m_title("Water flow"),
    m_targetFlag(true),
    m_targetValue(37)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

TPDial::~TPDial() {}

void TPDial::drawCrown(QPainter *painter)
{
    painter->save();
    int radius = 100;
    QLinearGradient lg1(0, -radius, 0, radius);

    lg1.setColorAt(0, Qt::white);
    lg1.setColorAt(1, Qt::gray);

    painter->setBrush(lg1);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(-radius, -radius, radius << 1, radius << 1);
    painter->setBrush(m_background);
    painter->drawEllipse(-92, -92, 184, 184);
    painter->restore();
}

void TPDial::drawScaleNum(QPainter *painter)
{
    painter->save();
    painter->setPen(m_foreground);
    double startRad = (270 - m_startAngle) * (M_PI / 180);
    double deltaRad = (360 - m_startAngle - m_endAngle) * (M_PI / 180) / m_scaleMajor;
    double sina, cosa;
    int x, y;
    QFontMetricsF fm(this->font());
    double w, h, tmpVal;
    QString str;

    for (int i = 0; i <= m_scaleMajor; i++)
    {
        sina = sin(startRad - i * deltaRad);
        cosa = cos(startRad - i * deltaRad);
        tmpVal = 1.0 * i * ((m_maxValue - m_minValue) / m_scaleMajor) + m_minValue;
        str = QString("%1").arg(tmpVal);
        w = fm.size(Qt::TextSingleLine, str).width();
        h = fm.size(Qt::TextSingleLine, str).height();
        x = 82 * cosa - w / 2;
        y = -82 * sina + h / 4;
        painter->drawText(x, y, str);
    }

    // Draw the target value if targetFlag is set
    if (m_targetFlag) {
        double targetRad = startRad - ((m_targetValue - m_minValue) * deltaRad) / ((m_maxValue - m_minValue) / m_scaleMajor);
        sina = sin(targetRad);
        cosa = cos(targetRad);
        str = QString("%1").arg(m_targetValue);
        w = fm.size(Qt::TextSingleLine, str).width();
        h = fm.size(Qt::TextSingleLine, str).height();
        x = 82 * cosa - w / 2;
        y = -82 * sina + h / 4;
        painter->setPen(Qt::red);
        painter->drawText(x, y, str);
    }

    painter->restore();
}

void TPDial::drawScale(QPainter *painter)
{
    painter->save();
    painter->rotate(m_startAngle);
    int steps = (m_scaleMajor * m_scaleMinor);
    double angleStep = (360.0 - m_startAngle - m_endAngle) / steps;

    QPen pen;
    pen.setColor(Qt::green);
    for (int i = 0; i <= steps; i++)
    {
        if (i % m_scaleMinor == 0)
        {
            pen.setWidth(1);
            painter->setPen(pen);
            painter->drawLine(0, 62, 0, 72);
        }
        else
        {
            pen.setWidth(0);
            painter->setPen(pen);
            painter->drawLine(0, 67, 0, 72);
        }
        painter->rotate(angleStep);
    }

    // Draw the target scale line if targetFlag is set
    if (m_targetFlag) {
        // Reset the rotation back to the initial state
        painter->rotate(-angleStep * steps - angleStep);

        // Calculate the target angle
        double targetAngle = (360.0 - m_startAngle - m_endAngle) * (m_targetValue - m_minValue) / (m_maxValue - m_minValue);

        // Rotate to the target angle
        painter->rotate(targetAngle);
        pen.setColor(Qt::red);
        pen.setWidth(2);
        painter->setPen(pen);
        painter->drawLine(0, 62, 0, 72);
    }

    painter->restore();
}

void TPDial::drawTitle(QPainter *painter)
{
    painter->save();
    painter->setPen(m_foreground);
    QString str(m_title);
    QFontMetricsF fm(this->font());
    double w = fm.size(Qt::TextSingleLine, str).width();
    painter->drawText(-w / 2, 70, str);  // 调整y坐标值到合适的位置
    painter->restore();
}

void TPDial::drawNumericValue(QPainter *painter)
{
    QString str = QString("%1 %2").arg(m_value, 0, 'f', m_precision).arg(m_units);
    QFontMetricsF fm(font());
    double w = fm.size(Qt::TextSingleLine, str).width();
    painter->setPen(m_foreground);
    painter->drawText(-w / 2, 42, str);
}

void TPDial::UpdateAngle()
{
    update();
}

void TPDial::drawIndicator(QPainter *painter)
{
    painter->save();
    QPolygon pts;
    pts.setPoints(3, -2, 0, 2, 0, 0, 60);

    painter->rotate(m_startAngle);
    double degRotate = (360.0 - m_startAngle - m_endAngle) / (m_maxValue - m_minValue) * (m_value - m_minValue);

    painter->rotate(degRotate);
    QRadialGradient haloGradient(0, 0, 60, 0, 0);
    haloGradient.setColorAt(0, QColor(60, 60, 60));
    haloGradient.setColorAt(1, QColor(160, 160, 160));
    painter->setPen(Qt::white);
    painter->setBrush(haloGradient);
    painter->drawConvexPolygon(pts);
    painter->restore();

    QColor niceBlue(150, 150, 200);
    QConicalGradient coneGradient(0, 0, -90.0);
    coneGradient.setColorAt(0.0, Qt::darkGray);
    coneGradient.setColorAt(0.2, niceBlue);
    coneGradient.setColorAt(0.5, Qt::white);
    coneGradient.setColorAt(1.0, Qt::darkGray);
    painter->setPen(Qt::NoPen);
    painter->setBrush(coneGradient);
    painter->drawEllipse(-5, -5, 10, 10);
}

void TPDial::paintEvent(QPaintEvent *event)
{
    int width = this->width();
    int height = this->height();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width / 2, height / 2);
    int side = qMin(width, height);
    painter.scale(side / 200.0, side / 200.0);

    drawCrown(&painter);
    drawScaleNum(&painter);
    drawScale(&painter);
    drawTitle(&painter);
    drawNumericValue(&painter);
    drawIndicator(&painter);
}
