#include <QDir>
#include <QJSEngine>
#include <QLoggingCategory>
#include <QQmlEngine>
#include <QQmlExtensionPlugin>
#include <QtQml>

#include "tuiosender.h"

Q_LOGGING_CATEGORY(lcRegistration, "org.ecloud.tuio.registration")

static const char *ModuleName = "org.ecloud.tuio";

static QObject *TuioSenderSingleton(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    TuioSender *ret = new TuioSender();
    return ret;
}

class TuioPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface/1.0")

public:
    TuioPlugin() : QQmlExtensionPlugin() { }

    virtual void initializeEngine(QQmlEngine *engine, const char * uri) {
        Q_UNUSED(engine)
        qCDebug(lcRegistration) << uri;
    }

    virtual void registerTypes(const char *uri) {
        qCDebug(lcRegistration) << uri;
        Q_ASSERT(uri == QLatin1String(ModuleName));
        qmlRegisterSingletonType<TuioSender>(uri, 1, 0, "TuioSender", TuioSenderSingleton);
    }
};

QT_END_NAMESPACE

#include "plugin.moc"
