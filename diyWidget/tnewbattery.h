#ifndef TNEWBATTERY_H
#define TNEWBATTERY_H

#include <QWidget>

class TNewBattery : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int batteryWidth READ batteryWidth WRITE setBatteryWidth NOTIFY batteryWidthChanged)
    Q_PROPERTY(int batteryHeight READ batteryHeight WRITE setBatteryHeight NOTIFY batteryHeightChanged)

public:
    explicit TNewBattery(QWidget *parent = nullptr);

    int chargeLevel() const;
    void setChargeLevel(int level);

    int batteryWidth() const;
    void setBatteryWidth(int width);

    int batteryHeight() const;
    void setBatteryHeight(int height);

signals:
    void chargeLevelChanged(int level);
    void batteryWidthChanged(int width);
    void batteryHeightChanged(int height);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_chargeLevel;
    int m_batteryWidth;
    int m_batteryHeight;

    void drawBatteryBody(QPainter &painter, const QRect &batteryRect, const QRect &blueRect);
    void drawElectrodes(QPainter &painter, const QRect &batteryRect);
    void drawTrapezoid(QPainter &painter, const QRect &blueRect, int borderSize, int trapezoidHeight);
    void drawBase(QPainter &painter, const QRect &blueRect, int borderSize, int trapezoidHeight);
    void drawChargeLevel(QPainter &painter, const QRect &batteryRect);
};

#endif // TNEWBATTERY_H
