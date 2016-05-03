#ifndef FORM2_H
#define FORM2_H

#include "form2_global.h"

#include <extensionsystem/iplugin.h>

namespace Form2 {
namespace Internal {

class Form2Plugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "Form2.json")

public:
    Form2Plugin();
    ~Form2Plugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

private slots:
    void triggerAction();
};

} // namespace Internal
} // namespace Form2

#endif // FORM2_H
