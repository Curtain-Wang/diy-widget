#ifndef TPSCALE_H
#define TPSCALE_H

#include <QWidget>
#include <QList>
#include <QPainter>
#include <QtUiPlugin/QDesignerExportWidget>

class QDESIGNER_WIDGET_EXPORT TPScale : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(double level READ level WRITE setLevel NOTIFY levelChanged)
    Q_PROPERTY(double warnLevelLow READ warnLevelLow WRITE setWarnLevelLow)
    Q_PROPERTY(double warnLevelHigh READ warnLevelHigh WRITE setWarnLevelHigh)
    Q_PROPERTY(double highest READ highest WRITE setHighest)
    Q_PROPERTY(double lowest READ lowest WRITE setLowest)
    Q_PROPERTY(int division READ division WRITE setDivision)
    // Q_PROPERTY(int widgetWidth READ widgetWidth WRITE setWidgetWidth)
    // Q_PROPERTY(int widgetHeight READ widgetHeight WRITE setWidgetHeight)

public:
    explicit TPScale(QWidget *parent = nullptr);

    double level() const;
    void setLevel(double level);

    double warnLevelLow() const;
    void setWarnLevelLow(double warnLevelLow);

    double warnLevelHigh() const;
    void setWarnLevelHigh(double warnLevelHigh);

    double highest() const;
    void setHighest(double highest);

    double lowest() const;
    void setLowest(double lowest);

    int division() const;
    void setDivision(int division);

    int widgetWidth() const;
    void setWidgetWidth(int widgetWidth);

    // int widgetHeight() const;
    // void setWidgetHeight(int widgetHeight);

    QSize sizeHint() const override;

    QSize minimumSizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

signals:
    void levelChanged(double level);

private:
    void checkWarnLevel();
    void updateLabels();

    double m_level = 37.0;
    double m_warnLevelLow = 12.0;
    double m_warnLevelHigh = 48.0;
    double m_highest = 60.0;
    double m_lowest = 0.0;
    int m_division = 5;
    int m_minWidth = 50;
    int m_minHeight = 100;
    int m_scale = 2;//高宽比

    QList<QString> m_labels;
};


#endif // TPSCALE_H
