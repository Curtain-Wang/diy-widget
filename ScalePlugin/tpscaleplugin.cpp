#include "tpscaleplugin.h"
#include "tpscale.h"

#include <QtPlugin>

TPScalePlugin::TPScalePlugin(QObject *parent)
    : QObject(parent)
{}

void TPScalePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool TPScalePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *TPScalePlugin::createWidget(QWidget *parent)
{
    return new TPScale(parent);
}

QString TPScalePlugin::name() const
{
    return QLatin1String("TPScale");
}

QString TPScalePlugin::group() const
{
    return QLatin1String("My Widgets");
}

QIcon TPScalePlugin::icon() const
{
    return QIcon();
}

QString TPScalePlugin::toolTip() const
{
    return QLatin1String("刻度盘");
}

QString TPScalePlugin::whatsThis() const
{
    return QLatin1String("刻度盘");
}

bool TPScalePlugin::isContainer() const
{
    return false;
}

QString TPScalePlugin::domXml() const
{
    return QLatin1String(R"(<widget class="TPScale" name="tPScale">
</widget>)");
}

QString TPScalePlugin::includeFile() const
{
    return QLatin1String("tpscale.h");
}
