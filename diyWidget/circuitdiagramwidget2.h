#ifndef CIRCUITDIAGRAMWIDGET2_H
#define CIRCUITDIAGRAMWIDGET2_H

#include <QWidget>

class CircuitDiagramWidget2 : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int chargeLevel READ chargeLevel WRITE setChargeLevel NOTIFY chargeLevelChanged)
    Q_PROPERTY(int warningLevel READ warningLevel WRITE setWarningLevel NOTIFY warningLevelChanged)
    Q_PROPERTY(int systemVoltage READ systemVoltage WRITE setSystemVoltage NOTIFY systemVoltageChanged)
    Q_PROPERTY(bool mainContactorClosed READ mainContactorClosed WRITE setMainContactorClosed NOTIFY mainContactorClosedChanged)
    Q_PROPERTY(bool dischargeContactorClosed READ dischargeContactorClosed WRITE setDischargeContactorClosed NOTIFY dischargeContactorClosedChanged)
    Q_PROPERTY(bool chargeContactorClosed READ chargeContactorClosed WRITE setChargeContactorClosed NOTIFY chargeContactorClosedChanged)
    Q_PROPERTY(bool heaterFaultContactorClosed READ heaterFaultContactorClosed WRITE setHeaterFaultContactorClosed NOTIFY heaterFaultContactorClosedChanged)
    Q_PROPERTY(bool isHeating READ isHeating WRITE setIsHeating NOTIFY isHeatingChanged)
    Q_PROPERTY(bool heaterContactorClosed READ heaterContactorClosed WRITE setHeaterContactorClosed NOTIFY heaterContactorClosedChanged)
    Q_PROPERTY(bool limitedContactorClosed READ limitedContactorClosed WRITE setLimitedContactorClosed NOTIFY limitedContactorClosedChanged)

public:
    explicit CircuitDiagramWidget2(QWidget *parent = nullptr);

    int chargeLevel() const;
    void setChargeLevel(int level);

    int warningLevel() const;
    void setWarningLevel(int level);

    int systemVoltage() const;
    void setSystemVoltage(int voltage);

    bool mainContactorClosed() const;
    void setMainContactorClosed(bool closed);

    bool dischargeContactorClosed() const;
    void setDischargeContactorClosed(bool closed);

    bool chargeContactorClosed() const;
    void setChargeContactorClosed(bool closed);

    bool heaterFaultContactorClosed() const;
    void setHeaterFaultContactorClosed(bool closed);

    bool isHeating() const;
    void setIsHeating(bool heating);

    bool heaterContactorClosed() const;
    void setHeaterContactorClosed(bool closed);

    bool limitedContactorClosed() const;
    void setLimitedContactorClosed(bool closed);

    void drawWireToMainContactor(QPainter &painter, int batteryX, int batteryY, int batteryWidth, int batteryHeight);
    void drawMainContactor(QPainter &painter, int x, int y, int batteryWidth);
    void drawWireToSystemVoltage(QPainter &painter, int mainContactorX, int mainContactorY, int batteryWidth);
    void drawSystemVoltage(QPainter &painter, int startX, int startY);
    void drawWireToDischargeContactor(QPainter &painter, int startX, int startY);
    void drawDischargeContactor(QPainter &painter, int x, int y, int batteryWidth);
    void drawWireToChargeContactor(QPainter &painter, int startX, int startY, int batteryWidth);
    void drawChargeContactor(QPainter &painter, int x, int y, int batteryWidth);
    void drawWireFromNegativeElectrode(QPainter &painter, int batteryX, int batteryY, int batteryWidth, int batteryHeight);
    // TNewBattery 的绘制方法
    void drawBatteryBody(QPainter &painter, const QRect &batteryRect, const QRect &blueRect);
    void drawElectrodes(QPainter &painter, const QRect &batteryRect);
    void drawTrapezoid(QPainter &painter, const QRect &blueRect, int borderSize, int trapezoidHeight);
    void drawBase(QPainter &painter, const QRect &blueRect, int borderSize, int trapezoidHeight);
    void drawChargeLevel(QPainter &painter, const QRect &batteryRect);
    void drawWireToHeaterFaultContactor(QPainter &painter, int mainContactorX, int mainContactorY, int batteryWidth);
    void drawHeaterFaultContactor(QPainter &painter, int x, int y, int batteryWidth);
    void drawWireToHeater(QPainter &painter, int heaterFaultContactorX, int heaterFaultContactorY, int batteryWidth);
    void drawHeater(QPainter &painter, int x, int y, int side);
    void drawWireToHeaterContactor(QPainter &painter, int heaterX, int heaterY, int heaterWidth);
    void drawHeaterContactor(QPainter &painter, int x, int y);
    void drawWireToLimitedContactor(QPainter &painter, int dischargeContactorX, int dischargeContactorY, int chargeContactorX);
    void drawLimitedContactor(QPainter &painter, int x, int y);
signals:
    void chargeLevelChanged(int level);
    void warningLevelChanged(int level);
    void systemVoltageChanged(int voltage);
    void mainContactorClosedChanged(bool closed);
    void dischargeContactorClosedChanged(bool closed);
    void chargeContactorClosedChanged(bool closed);
    void heaterFaultContactorClosedChanged(bool closed);
    void isHeatingChanged(bool heating);
    void heaterContactorClosedChanged(bool closed);
    void limitedContactorClosedChanged(bool closed);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_chargeLevel;
    int m_warningLevel;
    int m_systemVoltage;
    bool m_mainContactorClosed;
    bool m_dischargeContactorClosed;
    bool m_chargeContactorClosed;
    bool m_heaterFaultContactorClosed;
    bool m_isHeating;
    bool m_heaterContactorClosed;
    bool m_limitedContactorClosed;
private:
    int chargeContactorEndx;
};

#endif // CIRCUITDIAGRAMWIDGET2_H
