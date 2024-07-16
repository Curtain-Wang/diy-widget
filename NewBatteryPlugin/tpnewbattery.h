#ifndef TPNEWBATTERY_H
#define TPNEWBATTERY_H
#include <QtUiPlugin/QDesignerExportWidget>
#include <QWidget>

class QDESIGNER_WIDGET_EXPORT TPNewBattery : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int warningLevel READ warningLevel WRITE setWarningLevel NOTIFY warningLevelChanged)
    Q_PROPERTY(int chargeLevel READ chargeLevel WRITE setChargeLevel NOTIFY chargeLevelChanged)

public:
    explicit TPNewBattery(QWidget *parent = nullptr);

    int chargeLevel() const;
    void setChargeLevel(int level);

    int warningLevel() const;
    void setWarningLevel(int level);

signals:
    void chargeLevelChanged(int level);
    void warningLevelChanged(int level);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_chargeLevel;
    int m_warningLevel;

    void drawBatteryBody(QPainter &painter, const QRect &batteryRect, const QRect &blueRect);
    void drawElectrodes(QPainter &painter, const QRect &batteryRect);
    void drawTrapezoid(QPainter &painter, const QRect &blueRect, int borderSize, int trapezoidHeight);
    void drawBase(QPainter &painter, const QRect &blueRect, int borderSize, int trapezoidHeight);
    void drawChargeLevel(QPainter &painter, const QRect &batteryRect);
};


#endif // TPNEWBATTERY_H
