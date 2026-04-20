#include "roundedwidgetplugin.h"
#include "roundedwidget.h"

#include <QtPlugin>

RoundedWidgetPlugin::RoundedWidgetPlugin(QObject *parent)
    : QObject(parent)
{}

void RoundedWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool RoundedWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *RoundedWidgetPlugin::createWidget(QWidget *parent)
{
    return new RoundedWidget(parent);
}

QString RoundedWidgetPlugin::name() const
{
    return QLatin1String("RoundedWidget");
}

QString RoundedWidgetPlugin::group() const
{
    return QLatin1String("Containers");
}

QIcon RoundedWidgetPlugin::icon() const
{
    return QIcon(QLatin1String(":/roundedIcon.png"));
}

QString RoundedWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString RoundedWidgetPlugin::whatsThis() const
{
    return QLatin1String("Виджет с закруглённой рамкой");
}

bool RoundedWidgetPlugin::isContainer() const
{
    return true;
}

QString RoundedWidgetPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="RoundedWidget" name="roundedWidget">
</widget>)");
}

QString RoundedWidgetPlugin::includeFile() const
{
    return QLatin1String("roundedwidget.h");
}
