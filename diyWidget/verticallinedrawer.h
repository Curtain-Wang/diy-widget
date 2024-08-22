#ifndef VERTICALLINEDRAWER_H
#define VERTICALLINEDRAWER_H

#include <QWidget>
#include <QColor>

class VerticalLineDrawer : public QWidget
{
    Q_OBJECT

public:
    explicit VerticalLineDrawer(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    void drawGradientLineSegment(int x1, int y1, int x2, int y2, Qt::GlobalColor edgeColor, QPainter &painter, double color2At = 0.5);
    void drawGradientPolylineSegment(int x1, int y1, int x2, int y2, int x3, int y3, Qt::GlobalColor edgeColor, QPainter &painter);

};

#endif // VERTICALLINEDRAWER_H
