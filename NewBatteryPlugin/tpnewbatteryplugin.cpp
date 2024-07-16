#include "tpnewbatteryplugin.h"
#include "tpnewbattery.h"

#include <QtPlugin>

TPNewBatteryPlugin::TPNewBatteryPlugin(QObject *parent)
    : QObject(parent)
{}

void TPNewBatteryPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool TPNewBatteryPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *TPNewBatteryPlugin::createWidget(QWidget *parent)
{
    return new TPNewBattery(parent);
}

QString TPNewBatteryPlugin::name() const
{
    return QLatin1String("TPNewBattery");
}

QString TPNewBatteryPlugin::group() const
{
    return QLatin1String("My Widgets");
}

QIcon TPNewBatteryPlugin::icon() const
{
    return QIcon();
}

QString TPNewBatteryPlugin::toolTip() const
{
    return QLatin1String("蓄电池");
}

QString TPNewBatteryPlugin::whatsThis() const
{
    return QLatin1String("蓄电池");
}

bool TPNewBatteryPlugin::isContainer() const
{
    return false;
}

QString TPNewBatteryPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="TPNewBattery" name="tPNewBattery">
</widget>)");
}

QString TPNewBatteryPlugin::includeFile() const
{
    return QLatin1String("tpnewbattery.h");
}
