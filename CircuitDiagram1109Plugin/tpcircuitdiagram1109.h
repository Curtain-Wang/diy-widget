#ifndef TPCIRCUITDIAGRAM1109_H
#define TPCIRCUITDIAGRAM1109_H
#include <QWidget>
#include <QtUiPlugin/QDesignerExportWidget>

class QTimer;
class QRect;
class QDESIGNER_WIDGET_EXPORT TPCircuitDiagram1109 : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(double m_current1 READ current1 WRITE setCurrent1)
    Q_PROPERTY(double current2 READ current2 WRITE setCurrent2)
    Q_PROPERTY(int m_chargeLevel1 READ chargeLevel1 WRITE setChargeLevel1)
    Q_PROPERTY(int m_chargeLevel2 READ chargeLevel2 WRITE setChargeLevel2)
    Q_PROPERTY(bool m_dischargeContactorClosed1 READ dischargeContactorClosed1 WRITE setDischargeContactorClosed1)
    Q_PROPERTY(bool m_dischargeContactorClosed2 READ dischargeContactorClosed2 WRITE setDischargeContactorClosed2)
    Q_PROPERTY(bool m_chargeContactorClosed1 READ chargeContactorClosed1 WRITE setChargeContactorClosed1)
    Q_PROPERTY(bool m_chargeContactorClosed2 READ chargeContactorClosed2 WRITE setChargeContactorClosed2)
    Q_PROPERTY(bool m_limitedContactorClosed1 READ limitedContactorClosed1 WRITE setLimitedContactorClosed1)
    Q_PROPERTY(bool m_limitedContactorClosed2 READ limitedContactorClosed2 WRITE setLimitedContactorClosed2)
    Q_PROPERTY(int m_warningLevel READ warningLevel WRITE setWarningLevel)
    Q_PROPERTY(double m_systemVoltage READ systemVoltage WRITE setSystemVoltage)
    Q_PROPERTY(bool m_mainContactorClosed READ mainContactorClosed WRITE setMainContactorClosed)
    Q_PROPERTY(bool m_heaterFaultContactorClosed READ heaterFaultContactorClosed WRITE setHeaterFaultContactorClosed)
    Q_PROPERTY(bool m_isHeating READ isHeating WRITE setIsHeating)
    Q_PROPERTY(bool m_heaterContactorClosed READ heaterContactorClosed WRITE setHeaterContactorClosed)
    Q_PROPERTY(QList<QColor> m_packColors1 READ packColors1 WRITE setPackColors1)
    Q_PROPERTY(QList<QColor> m_packColors2 READ packColors2 WRITE setPackColors2)
    Q_PROPERTY(int m_language READ language WRITE setLanguage)
    Q_PROPERTY(int m_componentState READ componentState WRITE setComponentState)


public:
    explicit TPCircuitDiagram1109(QWidget *parent = nullptr);
    ~TPCircuitDiagram1109();

    double current1() const;
    void setCurrent1(double value);

    double current2() const;
    void setCurrent2(double value);

    int chargeLevel1() const;
    void setChargeLevel1(int value);

    int chargeLevel2() const;
    void setChargeLevel2(int value);

    bool dischargeContactorClosed1() const;
    void setDischargeContactorClosed1(bool value);

    bool dischargeContactorClosed2() const;
    void setDischargeContactorClosed2(bool value);

    bool chargeContactorClosed1() const;
    void setChargeContactorClosed1(bool value);

    bool chargeContactorClosed2() const;
    void setChargeContactorClosed2(bool value);

    bool limitedContactorClosed1() const;
    void setLimitedContactorClosed1(bool value);

    bool limitedContactorClosed2() const;
    void setLimitedContactorClosed2(bool value);

    int warningLevel() const;
    void setWarningLevel(int value);

    double systemVoltage() const;
    void setSystemVoltage(double value);

    bool mainContactorClosed() const;
    void setMainContactorClosed(bool value);

    bool heaterFaultContactorClosed() const;
    void setHeaterFaultContactorClosed(bool value);

    bool isHeating() const;
    void setIsHeating(bool value);

    bool heaterContactorClosed() const;
    void setHeaterContactorClosed(bool value);

    QList<QColor> packColors1() const;
    void setPackColors1(const QList<QColor> &value);

    QList<QColor> packColors2() const;
    void setPackColors2(const QList<QColor> &value);

    int language() const;
    void setLanguage(int value);

    int componentState() const;
    void setComponentState(int value);

    void init();
    void drawWireToMainContactor(QPainter &painter, int batteryX, int batteryY, int batteryWidth, int batteryHeight);
    void drawMainContactor(QPainter &painter, int x, int y, int batteryWidth);
    void drawWireToSystemVoltage(QPainter &painter, int mainContactorX, int mainContactorY, int batteryWidth);
    void drawSystemVoltage(QPainter &painter, int startX, int startY);
    void drawWireToDischargeContactor(QPainter &painter, int startX, int startY);
    void drawBottomWire(QPainter &painter, int startX, int startY);
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
    //绘制渐变直线线段
    void drawGradientLineSegment(int x1, int y1, int x2, int y2, Qt::GlobalColor edgeColor, QPainter &painter, double color2At = 0.5);
    //绘制渐变折线线段
    void drawGradientPolylineSegment(int x1, int y1, int x2, int y2, int x3, int y3, Qt::GlobalColor edgeColor, QPainter &painter);
    void buildEnergyPositionListWithLimit();
    void buildChargeHeatEnergyPositionList();
    void buildEnergyPositionListWithCharge();
    //绘制串电压
    void drawSeriesVoltage(QPainter &painter,int n);
    // signals:
    //     void current1Changed(double value);
    //     void current2Changed(double value);
    //     void chargeLevel1Changed(int value);
    //     void chargeLevel2Changed(int value);
    //     void dischargeContactorClosed1Changed(bool value);
    //     void dischargeContactorClosed2Changed(bool value);
    //     void chargeContactorClosed1Changed(bool value);
    //     void chargeContactorClosed2Changed(bool value);
    //     void limitedContactorClosed1Changed(bool value);
    //     void limitedContactorClosed2Changed(bool value);
    //     void warningLevelChanged(int level);
    //     void systemVoltageChanged(double value);
    //     void mainContactorClosedChanged(bool value);
    //     void heaterFaultContactorClosedChanged(bool value);
    //     void isHeatingChanged(bool value);
    //     void heaterContactorClosedChanged(bool value);
    //     void packColors1Changed(const QList<QColor>& colors);
    //     void packColors2Changed(const QList<QColor>& colors);
    //     void customLanguageChanged(int language);
    //     void componentStateChanged(int state);

private slots:
    void on_timer_timeout();
protected:
    void paintEvent(QPaintEvent *event) override;



private:

    double m_current1;
    double m_current2;
    int m_chargeLevel1;
    int m_chargeLevel2;
    bool m_dischargeContactorClosed1;
    bool m_dischargeContactorClosed2;
    bool m_chargeContactorClosed1;
    bool m_chargeContactorClosed2;
    bool m_limitedContactorClosed1;
    bool m_limitedContactorClosed2;

    int m_warningLevel;
    double m_systemVoltage;
    bool m_mainContactorClosed;
    bool m_heaterFaultContactorClosed;
    bool m_isHeating;
    bool m_heaterContactorClosed;
    QList<QColor> m_packColors1 = QList<QColor>(6);
    QList<QColor> m_packColors2 = QList<QColor>(6);
    int m_language;
    //0其他1充电2放电
    int m_componentState;
private:
    int chargeContactorEndx;
    int offsetX;
    double mianContactorStartX;
    double horizontalEndX;
    Qt::GlobalColor energyColor;
    // QWidget interface
    //能量块的宽度
    const int ENERGY_BLOCK_WIDTH = 40;
    const double HALF_ENERGY_BLOCK_WIDTH = 20.0;
    //充电开始位置
    const int CHARGE_START = 420;
    //充电结束位置
    const int DISCHARGE_START = 0;
    //定时执行次数，每20次加一个能量块
    int count = 9;
    QList<qint32> energyPositionList;
    QList<qint32> chargeHeatPositionList;
    //电池主体
    QRect rect;
    //画图要用，判断是否是第二个电池
    bool isSec;
    QTimer* timer;
    //能量块参数
private:
    QList<qint32> fromPositive1;
    QList<qint32> fromPositive2;


// protected:
//     void resizeEvent(QResizeEvent *event);
};

#endif // TPCIRCUITDIAGRAM1109_H
