#ifndef TPDIAL_H
#define TPDIAL_H

#include <QWidget>
#include <QtUiPlugin/QDesignerExportWidget>

class QDESIGNER_WIDGET_EXPORT TPDial : public QWidget
{
    Q_OBJECT
//    Q_PROPERTY(QColor background READ background WRITE setBackground DESIGNABLE true)
//    Q_PROPERTY(QColor foreground READ foreground WRITE setForeground DESIGNABLE true)
    Q_PROPERTY(int maxValue READ maxValue WRITE setMaxValue DESIGNABLE true)
    Q_PROPERTY(int minValue READ minValue WRITE setMinValue DESIGNABLE true)
    Q_PROPERTY(int startAngle READ startAngle WRITE setStartAngle DESIGNABLE true)
    Q_PROPERTY(int endAngle READ endAngle WRITE setEndAngle DESIGNABLE true)
    Q_PROPERTY(int scaleMajor READ scaleMajor WRITE setScaleMajor DESIGNABLE true)
    Q_PROPERTY(int scaleMinor READ scaleMinor WRITE setScaleMinor DESIGNABLE true)
    Q_PROPERTY(double value READ value WRITE setValue DESIGNABLE true)
    Q_PROPERTY(int precision READ precision WRITE setPrecision DESIGNABLE true)
    Q_PROPERTY(QString units READ units WRITE setUnits DESIGNABLE true)
    Q_PROPERTY(QString title READ title WRITE setTitle DESIGNABLE true)
    Q_PROPERTY(bool targetFlag READ targetFlag WRITE setTargetFlag DESIGNABLE true)
    Q_PROPERTY(double targetValue READ targetValue WRITE setTargetValue DESIGNABLE true)

public:
    TPDial(QWidget *parent = nullptr);
    ~TPDial();

    QColor background() const { return m_background; }
    void setBackground(const QColor &color) { m_background = color; update(); }

    QColor foreground() const { return m_foreground; }
    void setForeground(const QColor &color) { m_foreground = color; update(); }

    int maxValue() const { return m_maxValue; }
    void setMaxValue(int val) { m_maxValue = val; update(); }

    int minValue() const { return m_minValue; }
    void setMinValue(int val) { m_minValue = val; update(); }

    int startAngle() const { return m_startAngle; }
    void setStartAngle(int angle) { m_startAngle = angle; update(); }

    int endAngle() const { return m_endAngle; }
    void setEndAngle(int angle) { m_endAngle = angle; update(); }

    int scaleMajor() const { return m_scaleMajor; }
    void setScaleMajor(int scale) { m_scaleMajor = scale; update(); }

    int scaleMinor() const { return m_scaleMinor; }
    void setScaleMinor(int scale) { m_scaleMinor = scale; update(); }

    double value() const { return m_value; }
    void setValue(double val) { m_value = val; update(); }

    int precision() const { return m_precision; }
    void setPrecision(int precision) { m_precision = precision; update(); }

    QString units() const { return m_units; }
    void setUnits(const QString &units) { m_units = units; update(); }

    QString title() const { return m_title; }
    void setTitle(const QString &title) { m_title = title; update(); }

    bool targetFlag() const { return m_targetFlag; }
    void setTargetFlag(bool flag) { m_targetFlag = flag; update(); }

    double targetValue() const { return m_targetValue; }
    void setTargetValue(double value) { m_targetValue = value; update(); }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void drawCrown(QPainter *painter);
    void drawBackground(QPainter *painter);
    void drawScale(QPainter *painter);
    void drawScaleNum(QPainter *painter);
    void drawTitle(QPainter *painter);
    void drawIndicator(QPainter *painter);
    void drawNumericValue(QPainter *painter);

    QColor m_background;
    QColor m_foreground;
    int m_maxValue;
    int m_minValue;
    int m_startAngle;
    int m_endAngle;
    int m_scaleMajor;
    int m_scaleMinor;
    double m_value;
    int m_precision;
    QString m_units;
    QString m_title;
    bool m_targetFlag;
    double m_targetValue;

public slots:
    void UpdateAngle();
};

#endif // TPDIAL_H
