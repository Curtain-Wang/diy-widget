#ifndef TPHEATER_H
#define TPHEATER_H

#include <QWidget>
#include <QtUiPlugin/QDesignerExportWidget>

class QDESIGNER_WIDGET_EXPORT TPHeater : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool isHeating READ isHeating WRITE setHeating NOTIFY heatingChanged)

public:
    explicit TPHeater(QWidget *parent = nullptr);

    bool isHeating() const { return m_isHeating; }
    void setHeating(bool heating);

signals:
    void heatingChanged(bool heating);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    bool m_isHeating = true;
};

#endif // TPHEATER_H
