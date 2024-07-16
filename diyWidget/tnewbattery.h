#ifndef TNEWBATTERY_H
#define TNEWBATTERY_H

#include <QWidget>

class TNewBattery : public QWidget
{
    Q_OBJECT

public:
    explicit TNewBattery(QWidget *parent = nullptr);

    int chargeLevel() const;
    void setChargeLevel(int level);

signals:
    void chargeLevelChanged(int level);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_chargeLevel;

    void drawBatteryBody(QPainter &painter, const QRect &batteryRect, const QRect &blueRect);
    void drawElectrodes(QPainter &painter, const QRect &batteryRect);
    void drawTrapezoid(QPainter &painter, const QRect &blueRect, int borderSize, int trapezoidHeight);
    void drawBase(QPainter &painter, const QRect &blueRect, int borderSize, int trapezoidHeight);
    void drawChargeLevel(QPainter &painter, const QRect &batteryRect);
};

#endif // TNEWBATTERY_H
