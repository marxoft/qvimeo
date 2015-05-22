#include "plugin.h"
#include "../src/authenticationrequest.h"
#include "../src/resourcesmodel.h"
#include "../src/resourcesrequest.h"
#include "../src/streamsmodel.h"
#if QT_VERSION >= 0x050000
#include <qqml.h>
#else
#include <qdeclarative.h>
#endif

namespace QVimeo {

void Plugin::registerTypes(const char *uri) {
    Q_ASSERT(uri == QLatin1String("QVimeo"));

    qmlRegisterType<AuthenticationRequest>(uri, 1, 0, "AuthenticationRequest");
    qmlRegisterType<ResourcesModel>(uri, 1, 0, "ResourcesModel");
    qmlRegisterType<ResourcesRequest>(uri, 1, 0, "ResourcesRequest");
    qmlRegisterType<StreamsModel>(uri, 1, 0, "StreamsModel");
    qmlRegisterType<StreamsRequest>(uri, 1, 0, "StreamsRequest");
}

}

QML_DECLARE_TYPE(QVimeo::AuthenticationRequest)
QML_DECLARE_TYPE(QVimeo::ResourcesModel)
QML_DECLARE_TYPE(QVimeo::ResourcesRequest)
QML_DECLARE_TYPE(QVimeo::StreamsModel)
QML_DECLARE_TYPE(QVimeo::StreamsRequest)
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qvimeoplugin, QVimeo::Plugin)
#endif
