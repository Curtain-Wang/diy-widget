#ifndef HEATER_H
#define HEATER_H

#include <QWidget>

class Heater : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool isHeating READ isHeating WRITE setHeating NOTIFY heatingChanged)

public:
    explicit Heater(QWidget *parent = nullptr);

    bool isHeating() const { return m_isHeating; }
    void setHeating(bool heating);

signals:
    void heatingChanged(bool heating);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    bool m_isHeating = true;
};

#endif // HEATER_H
