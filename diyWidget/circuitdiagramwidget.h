#ifndef CIRCUITDIAGRAMWIDGET_H
#define CIRCUITDIAGRAMWIDGET_H

#include <QWidget>

class CircuitDiagramWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int powerLevel READ powerLevel WRITE setPowerLevel NOTIFY powerLevelChanged)
    Q_PROPERTY(int warnLevel READ warnLevel WRITE setWarnLevel NOTIFY warnLevelChanged)
    Q_PROPERTY(bool mainContactorClosed READ mainContactorClosed WRITE setMainContactorClosed NOTIFY mainContactorClosedChanged)
    Q_PROPERTY(bool heaterErrorContactorClosed READ heaterErrorContactorClosed WRITE setHeaterErrorContactorClosed NOTIFY heaterErrorContactorClosedChanged)
    Q_PROPERTY(bool isHeating READ isHeating WRITE setIsHeating NOTIFY isHeatingChanged)
    Q_PROPERTY(bool dischargeContactorClosed READ dischargeContactorClosed WRITE setDischargeContactorClosed NOTIFY dischargeContactorClosedChanged)
    Q_PROPERTY(bool chargeContactorClosed READ chargeContactorClosed WRITE setChargeContactorClosed NOTIFY chargeContactorClosedChanged)
    Q_PROPERTY(bool limitedContactorClosed READ limitedContactorClosed WRITE setLimitedContactorClosed NOTIFY limitedContactorClosedChanged)
    Q_PROPERTY(bool heaterContactorClosed READ heaterContactorClosed WRITE setHeaterContactorClosed NOTIFY heaterContactorClosedChanged)

public:
    explicit CircuitDiagramWidget(QWidget *parent = nullptr);

    int powerLevel() const;
    void setPowerLevel(int level);

    int warnLevel() const;
    void setWarnLevel(int level);

    bool mainContactorClosed() const;
    void setMainContactorClosed(bool closed);

    bool heaterErrorContactorClosed() const;
    void setHeaterErrorContactorClosed(bool closed);

    bool isHeating() const;
    void setIsHeating(bool heating);

    bool dischargeContactorClosed() const;
    void setDischargeContactorClosed(bool closed);

    bool chargeContactorClosed() const;
    void setChargeContactorClosed(bool closed);

    bool limitedContactorClosed() const;
    void setLimitedContactorClosed(bool closed);

    bool heaterContactorClosed() const;
    void setHeaterContactorClosed(bool closed);

signals:
    void powerLevelChanged(int level);
    void warnLevelChanged(int level);
    void mainContactorClosedChanged(bool closed);
    void heaterErrorContactorClosedChanged(bool closed);
    void isHeatingChanged(bool heating);
    void dischargeContactorClosedChanged(bool closed);
    void chargeContactorClosedChanged(bool closed);
    void limitedContactorClosedChanged(bool closed);
    void heaterContactorClosedChanged(bool closed);


protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_powerLevel;
    int m_warnLevel;
    bool m_mainContactorClosed;
    bool m_heaterErrorContactorClosed;
    bool m_isHeating;
    bool m_dischargeContactorClosed;
    bool m_chargeContactorClosed;
    bool m_limitedContactorClosed;
    bool m_heaterContactorClosed;

    void drawBattery(QPainter &painter, int x, int y, int width, int height);
    void drawWireToMainContactor(QPainter &painter, int batteryX, int batteryY, int batteryWidth, int batteryHeight);
    void drawMainContactor(QPainter &painter, int x, int y, int size);
    void drawWireToHeaterErrorContactor(QPainter &painter, int startX, int startY, int batteryWidth);
    void drawHeaterErrorContactor(QPainter &painter, int x, int y, int batteryWidth);
    void drawHeater(QPainter &painter, int x, int y, int side);
    void drawWireToDischargeContactor(QPainter &painter, int batteryX, int batteryY, int batteryWidth, int batteryHeight);
    void drawDischargeContactor(QPainter &painter, int x, int y, int batteryWidth);
    void drawWireToChargeContactor(QPainter &painter, int dischargeContactorX, int dischargeContactorY, int batteryWidth);
    void drawChargeContactor(QPainter &painter, int x, int y, int batteryWidth);
    void drawWireToBusMinus(QPainter &painter, int startX, int startY, int batteryWidth);
    void drawWireToLimitedContactor(QPainter &painter, int midX, int midY, int batteryWidth);
    void drawLimitedContactor(QPainter &painter, int x, int y, int batteryWidth);
    void drawWireToHeaterContactor(QPainter &painter, int heaterX, int heaterY, int heaterSize, int batteryWidthint, int batteryY, int batteryHeight);
    void drawHeaterContactor(QPainter &painter, int x, int y, int batteryWidth, int batteryY, int batteryHeight);
};

#endif // CIRCUITDIAGRAMWIDGET_H
