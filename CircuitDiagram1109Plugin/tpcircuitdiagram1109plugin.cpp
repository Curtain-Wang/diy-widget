#include "tpcircuitdiagram1109plugin.h"
#include "tpcircuitdiagram1109.h"

#include <QtPlugin>

TPCircuitDiagram1109Plugin::TPCircuitDiagram1109Plugin(QObject *parent)
    : QObject(parent)
{}

void TPCircuitDiagram1109Plugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool TPCircuitDiagram1109Plugin::isInitialized() const
{
    return m_initialized;
}

QWidget *TPCircuitDiagram1109Plugin::createWidget(QWidget *parent)
{
    return new TPCircuitDiagram1109(parent);
}

QString TPCircuitDiagram1109Plugin::name() const
{
    return QLatin1String("TPCircuitDiagram1109");
}

QString TPCircuitDiagram1109Plugin::group() const
{
    return QLatin1String("My Widgets");
}

QIcon TPCircuitDiagram1109Plugin::icon() const
{
    return QIcon();
}

QString TPCircuitDiagram1109Plugin::toolTip() const
{
    return QLatin1String("1109电路图");
}

QString TPCircuitDiagram1109Plugin::whatsThis() const
{
    return QLatin1String("1109电路图");
}

bool TPCircuitDiagram1109Plugin::isContainer() const
{
    return false;
}

QString TPCircuitDiagram1109Plugin::domXml() const
{
    return QLatin1String(R"(<widget class="TPCircuitDiagram1109" name="tPCircuitDiagram1109">
</widget>)");
}

QString TPCircuitDiagram1109Plugin::includeFile() const
{
    return QLatin1String("tpcircuitdiagram1109.h");
}
