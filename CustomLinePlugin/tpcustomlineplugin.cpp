#include "tpcustomlineplugin.h"
#include "tpcustomline.h"

#include <QtPlugin>

TPCustomLinePlugin::TPCustomLinePlugin(QObject *parent)
    : QObject(parent)
{}

void TPCustomLinePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool TPCustomLinePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *TPCustomLinePlugin::createWidget(QWidget *parent)
{
    return new TPCustomLine(parent);
}

QString TPCustomLinePlugin::name() const
{
    return QLatin1String("TPCustomLine");
}

QString TPCustomLinePlugin::group() const
{
    return QLatin1String("My Widgets");
}

QIcon TPCustomLinePlugin::icon() const
{
    return QIcon(QLatin1String(":/icons8-green-square-48.png"));
}

QString TPCustomLinePlugin::toolTip() const
{
    return QLatin1String("自定义线条");
}

QString TPCustomLinePlugin::whatsThis() const
{
    return QLatin1String("自定义线条");
}

bool TPCustomLinePlugin::isContainer() const
{
    return false;
}

QString TPCustomLinePlugin::domXml() const
{
    return QLatin1String(R"(<widget class="TPCustomLine" name="tPCustomLine">
</widget>)");
}

QString TPCustomLinePlugin::includeFile() const
{
    return QLatin1String("tpcustomline.h");
}
