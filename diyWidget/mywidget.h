#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QColor>

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void updatePosition();  // 定时器槽函数，用于更新填充位置

private:
    void drawHorZigzagLine(QPainter &painter, int startX, int startY, int endX, int endY, const QColor &lineColor, const QColor &fillColor);  // 用于绘制水平折线
    void drawVerZigzagLine(QPainter &painter, int startX, int startY, int endX, int endY, const QColor &lineColor, const QColor &fillColor);  // 用于绘制垂直折线
    QTimer *timer;  // 定时器指针
    int offset;    // 用于控制填充区域的位置
};

#endif // MYWIDGET_H
