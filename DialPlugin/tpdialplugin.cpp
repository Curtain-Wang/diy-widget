#include "tpdialplugin.h"
#include "tpdial.h"

#include <QtPlugin>

TPDialPlugin::TPDialPlugin(QObject *parent)
    : QObject(parent)
{}

void TPDialPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool TPDialPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *TPDialPlugin::createWidget(QWidget *parent)
{
    return new TPDial(parent);
}

QString TPDialPlugin::name() const
{
    return QLatin1String("TPDial");
}

QString TPDialPlugin::group() const
{
    return QLatin1String("My Widgets");
}

QIcon TPDialPlugin::icon() const
{
    return QIcon();
}

QString TPDialPlugin::toolTip() const
{
    return QLatin1String("自定义仪表盘");
}

QString TPDialPlugin::whatsThis() const
{
    return QLatin1String("自定义仪表盘");
}

bool TPDialPlugin::isContainer() const
{
    return false;
}

QString TPDialPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="TPDial" name="tPDial">
</widget>)");
}

QString TPDialPlugin::includeFile() const
{
    return QLatin1String("tpdial.h");
}
