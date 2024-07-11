#ifndef TPBATTERY_H
#define TPBATTERY_H

#include <QWidget>
#include <QtUiPlugin/QDesignerExportWidget>
class QDESIGNER_WIDGET_EXPORT TPBattery : public QWidget
{
    Q_OBJECT
    //自定义属性
    Q_PROPERTY(int powerLevel READ powerLevel WRITE setPowerLevel
                   NOTIFY powerLevelChanged)
    Q_PROPERTY(int warnLevel READ warnLevel WRITE setWarnLevel)
private:
    QColor colorBack = Qt::white; //背景色
    QColor colorBorder= Qt::black; //电池边框颜色
    QColor colorPower = Qt::green; //电量柱颜色
    QColor colorWarning=Qt::red; //电量短缺时的颜色
    int m_powerLevel= 60; //电量值为 0～100，属性 powerLevel 的存储变量
    int m_warnLevel = 20; //电量低阈值，属性 warnLevel 的存储变量
protected:
    void paintEvent(QPaintEvent *event);
public:
    explicit TPBattery(QWidget *parent = 0);
    void setPowerLevel(int pow); //设置当前电量值
    int powerLevel(); //返回当前电量值
    void setWarnLevel(int warn); //设置电量低阈值
    int warnLevel(); //返回电量低阈值
    QSize sizeHint(); //重定义的函数，设置组件的合适大小
signals:
    void powerLevelChanged(int ); //自定义信号
};

#endif // TPBATTERY_H
