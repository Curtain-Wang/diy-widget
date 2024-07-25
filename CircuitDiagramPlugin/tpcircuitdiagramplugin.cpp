#include "tpcircuitdiagramplugin.h"
#include "tpcircuitdiagram.h"

#include <QtPlugin>

TPCircuitDiagramPlugin::TPCircuitDiagramPlugin(QObject *parent)
    : QObject(parent)
{}

void TPCircuitDiagramPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool TPCircuitDiagramPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *TPCircuitDiagramPlugin::createWidget(QWidget *parent)
{
    return new TPCircuitDiagram(parent);
}

QString TPCircuitDiagramPlugin::name() const
{
    return QLatin1String("TPCircuitDiagram");
}

QString TPCircuitDiagramPlugin::group() const
{
    return QLatin1String("My Widgets");
}

QIcon TPCircuitDiagramPlugin::icon() const
{
    return QIcon();
}

QString TPCircuitDiagramPlugin::toolTip() const
{
    return QLatin1String("电路图一");
}

QString TPCircuitDiagramPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool TPCircuitDiagramPlugin::isContainer() const
{
    return false;
}

QString TPCircuitDiagramPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="TPCircuitDiagram" name="tPCircuitDiagram">
</widget>)");
}

QString TPCircuitDiagramPlugin::includeFile() const
{
    return QLatin1String("tpcircuitdiagram.h");
}
