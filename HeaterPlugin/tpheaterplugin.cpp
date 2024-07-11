#include "tpheaterplugin.h"
#include "tpheater.h"

#include <QtPlugin>

TPHeaterPlugin::TPHeaterPlugin(QObject *parent)
    : QObject(parent)
{}

void TPHeaterPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool TPHeaterPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *TPHeaterPlugin::createWidget(QWidget *parent)
{
    return new TPHeater(parent);
}

QString TPHeaterPlugin::name() const
{
    return QLatin1String("TPHeater");
}

QString TPHeaterPlugin::group() const
{
    return QLatin1String("My Widgets");
}

QIcon TPHeaterPlugin::icon() const
{
    return QIcon();
}

QString TPHeaterPlugin::toolTip() const
{
    return QLatin1String("自定义加热器");
}

QString TPHeaterPlugin::whatsThis() const
{
    return QLatin1String("自定义加热器");
}

bool TPHeaterPlugin::isContainer() const
{
    return false;
}

QString TPHeaterPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="TPHeater" name="tPHeater">
</widget>)");
}

QString TPHeaterPlugin::includeFile() const
{
    return QLatin1String("tpheater.h");
}
