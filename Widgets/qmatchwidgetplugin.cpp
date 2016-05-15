#include "qmatchwidget.h"
#include "qmatchwidgetplugin.h"

#include <QtPlugin>

QMatchWidgetPlugin::QMatchWidgetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void QMatchWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool QMatchWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *QMatchWidgetPlugin::createWidget(QWidget *parent)
{
    return new QMatchWidget(parent);
}

QString QMatchWidgetPlugin::name() const
{
    return QLatin1String("QMatchWidget");
}

QString QMatchWidgetPlugin::group() const
{
    return QLatin1String("");
}

QIcon QMatchWidgetPlugin::icon() const
{
    return QIcon();
}

QString QMatchWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString QMatchWidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool QMatchWidgetPlugin::isContainer() const
{
    return false;
}

QString QMatchWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"QMatchWidget\" name=\"qMatchWidget\">\n</widget>\n");
}

QString QMatchWidgetPlugin::includeFile() const
{
    return QLatin1String("qmatchwidget.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qmatchwidgetplugin, QMatchWidgetPlugin)
#endif // QT_VERSION < 0x050000
