#include "tpseccircuitdiagramplugin.h"
#include "tpseccircuitdiagram.h"

#include <QtPlugin>

TPSecCircuitDiagramPlugin::TPSecCircuitDiagramPlugin(QObject *parent)
    : QObject(parent)
{}

void TPSecCircuitDiagramPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool TPSecCircuitDiagramPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *TPSecCircuitDiagramPlugin::createWidget(QWidget *parent)
{
    return new TPSecCircuitDiagram(parent);
}

QString TPSecCircuitDiagramPlugin::name() const
{
    return QLatin1String("TPSecCircuitDiagram");
}

QString TPSecCircuitDiagramPlugin::group() const
{
    return QLatin1String("My Widgets");
}

QIcon TPSecCircuitDiagramPlugin::icon() const
{
    return QIcon();
}

QString TPSecCircuitDiagramPlugin::toolTip() const
{
    return QLatin1String("第二版电路图");
}

QString TPSecCircuitDiagramPlugin::whatsThis() const
{
    return QLatin1String("第二版电路图");
}

bool TPSecCircuitDiagramPlugin::isContainer() const
{
    return false;
}

QString TPSecCircuitDiagramPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="TPSecCircuitDiagram" name="tPSecCircuitDiagram">
</widget>)");
}

QString TPSecCircuitDiagramPlugin::includeFile() const
{
    return QLatin1String("tpseccircuitdiagram.h");
}
