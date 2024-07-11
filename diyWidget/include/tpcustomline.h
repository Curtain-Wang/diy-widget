#ifndef TPCUSTOMLINE_H
#define TPCUSTOMLINE_H

#include <QWidget>
#include <QtUiPlugin/QDesignerExportWidget>

class QDESIGNER_WIDGET_EXPORT TPCustomLine : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int x1 READ x1 WRITE setX1 NOTIFY x1Changed)
    Q_PROPERTY(int y1 READ y1 WRITE setY1 NOTIFY y1Changed)
    Q_PROPERTY(int x2 READ x2 WRITE setX2 NOTIFY x2Changed)
    Q_PROPERTY(int y2 READ y2 WRITE setY2 NOTIFY y2Changed)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)

public:
    explicit TPCustomLine(QWidget *parent = nullptr);

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

signals:
    void x1Changed(int x1);
    void y1Changed(int y1);
    void x2Changed(int x2);
    void y2Changed(int y2);
    void lineColorChanged(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_x1;
    int m_y1;
    int m_x2;
    int m_y2;
    QColor m_lineColor;
};

#endif // TPCUSTOMLINE_H
