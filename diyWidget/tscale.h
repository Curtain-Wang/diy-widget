#ifndef TSCALE_H
#define TSCALE_H

#include <QWidget>
#include <QList>
#include <QPainter>

class TScale : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int level READ level WRITE setLevel NOTIFY levelChanged)
    Q_PROPERTY(int warnLevelLow READ warnLevelLow WRITE setWarnLevelLow)
    Q_PROPERTY(int warnLevelHigh READ warnLevelHigh WRITE setWarnLevelHigh)
    Q_PROPERTY(int highest READ highest WRITE setHighest)
    Q_PROPERTY(int lowest READ lowest WRITE setLowest)
    Q_PROPERTY(int division READ division WRITE setDivision)
    // Q_PROPERTY(int widgetWidth READ widgetWidth WRITE setWidgetWidth)
    // Q_PROPERTY(int widgetHeight READ widgetHeight WRITE setWidgetHeight)

public:
    explicit TScale(QWidget *parent = nullptr);

    int level() const;
    void setLevel(int level);

    int warnLevelLow() const;
    void setWarnLevelLow(int warnLevelLow);

    int warnLevelHigh() const;
    void setWarnLevelHigh(int warnLevelHigh);

    int highest() const;
    void setHighest(int highest);

    int lowest() const;
    void setLowest(int lowest);

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
    void levelChanged(int level);

private:
    void checkWarnLevel();
    void updateLabels();

    int m_level = 37;
    int m_warnLevelLow = 10;
    int m_warnLevelHigh = 90;
    int m_highest = 60;
    int m_lowest = 0;
    int m_division = 5;
    int m_minWidth = 50;
    int m_minHeight = 100;
    int m_scale = 2;//高宽比

    QList<QString> m_labels;
};

#endif // TSCALE_H
