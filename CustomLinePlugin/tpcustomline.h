#ifndef TPCUSTOMLINE_H
#define TPCUSTOMLINE_H

#include <QWidget>
#include <QtUiPlugin/QDesignerExportWidget>

class QDESIGNER_WIDGET_EXPORT TPCustomLine : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int x1 READ x1 WRITE setX1 NOTIFY x1Changed)
    Q_PROPERTY(int y1 READ y1 WRITE setY1 NOTIFY x1Changed)
    Q_PROPERTY(int x2 READ x2 WRITE setX2 NOTIFY x2Changed)
    Q_PROPERTY(int y2 READ y2 WRITE setY2 NOTIFY y2Changed)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
    Q_PROPERTY(int radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(int line2Length READ line2Length WRITE setLine2Length NOTIFY line2LengthChanged)
    Q_PROPERTY(double angleBetweenLines READ angleBetweenLines WRITE setAngleBetweenLines NOTIFY angleBetweenLinesChanged)
    Q_PROPERTY(int startCircleRadius READ startCircleRadius WRITE setStartCircleRadius NOTIFY startCircleRadiusChanged)
    Q_PROPERTY(int penWidth READ penWidth WRITE setPenWidth NOTIFY penWidthChanged)
    Q_PROPERTY(double rotationAngle READ rotationAngle WRITE setRotationAngle NOTIFY rotationAngleChanged)

public:
    explicit TPCustomLine(QWidget *parent = nullptr);
    ~TPCustomLine();

    int x1() const;
    void setX1(int x1);

    int y1() const;
    void setY1(int y1);

    int x2() const;
    void setX2(int x2);

    int y2() const;
    void setY2(int y2);

    QColor lineColor() const;
    void setLineColor(const QColor &color);

    int radius() const;
    void setRadius(int radius);

    int line2Length() const;
    void setLine2Length(int length);

    double angleBetweenLines() const;
    void setAngleBetweenLines(double angle);

    int startCircleRadius() const;
    void setStartCircleRadius(int radius);

    int penWidth() const;
    void setPenWidth(int width);

    double rotationAngle() const;
    void setRotationAngle(double angle);

signals:
    void x1Changed(int x1);
    void y1Changed(int y1);
    void x2Changed(int x2);
    void y2Changed(int y2);
    void lineColorChanged(const QColor &color);
    void radiusChanged(int radius);
    void line2LengthChanged(int length);
    void angleBetweenLinesChanged(double angle);
    void startCircleRadiusChanged(int radius);
    void penWidthChanged(int width);
    void rotationAngleChanged(double angle);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_x1;
    int m_y1;
    int m_x2;
    int m_y2;
    QColor m_lineColor;
    int m_radius;
    int m_line2Length;
    double m_angleBetweenLines;
    int m_startCircleRadius;
    int m_penWidth;
    double m_rotationAngle;
};

#endif // TPCUSTOMLINE_H
