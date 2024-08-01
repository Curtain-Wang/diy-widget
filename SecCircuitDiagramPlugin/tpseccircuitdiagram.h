#ifndef TPSECCIRCUITDIAGRAM_H
#define TPSECCIRCUITDIAGRAM_H

#include <QWidget>
#include <QtUiPlugin/QDesignerExportWidget>

class QDESIGNER_WIDGET_EXPORT TPSecCircuitDiagram : public QWidget
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
    Q_PROPERTY(QColor packColor1 READ packColor1 WRITE setPackColor1 NOTIFY packColor1Changed)
    Q_PROPERTY(QColor packColor2 READ packColor2 WRITE setPackColor2 NOTIFY packColor2Changed)
    Q_PROPERTY(QColor packColor3 READ packColor3 WRITE setPackColor3 NOTIFY packColor3Changed)
    Q_PROPERTY(QColor packColor4 READ packColor4 WRITE setPackColor4 NOTIFY packColor4Changed)
    Q_PROPERTY(QColor packColor5 READ packColor5 WRITE setPackColor5 NOTIFY packColor5Changed)
    Q_PROPERTY(QColor packColor6 READ packColor6 WRITE setPackColor6 NOTIFY packColor6Changed)
    Q_PROPERTY(quint8 language READ language WRITE setLanguage NOTIFY languageChanged)

public:
    explicit TPSecCircuitDiagram(QWidget *parent = nullptr);

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

    QColor packColor1() const;
    void setPackColor1(const QColor &color);

    QColor packColor2() const;
    void setPackColor2(const QColor &color);

    QColor packColor3() const;
    void setPackColor3(const QColor &color);

    QColor packColor4() const;
    void setPackColor4(const QColor &color);

    QColor packColor5() const;
    void setPackColor5(const QColor &color);

    QColor packColor6() const;
    void setPackColor6(const QColor &color);

    quint8 language() const;
    void setLanguage(const quint8 &language);


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
    void packColor1Changed(const QColor &color);
    void packColor2Changed(const QColor &color);
    void packColor3Changed(const QColor &color);
    void packColor4Changed(const QColor &color);
    void packColor5Changed(const QColor &color);
    void packColor6Changed(const QColor &color);
    void languageChanged(quint8 language);

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
    QColor m_packColor1;
    QColor m_packColor2;
    QColor m_packColor3;
    QColor m_packColor4;
    QColor m_packColor5;
    QColor m_packColor6;
    quint8 m_language;

private:
    int chargeContactorEndx;
    int offsetX;
};

#endif // TPSECCIRCUITDIAGRAM_H
