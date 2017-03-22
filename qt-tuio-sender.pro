QT       += qml quick
TARGET = build/org/ecloud/tuio/tuioplugin
TEMPLATE = lib

INCLUDEPATH += TUIO20_CPP/oscpack TUIO20_CPP/TUIO2

TUIO_SOURCES = \
    TUIO20_CPP/TUIO2/TuioTime.cpp \
    TUIO20_CPP/TUIO2/TuioPoint.cpp \
    TUIO20_CPP/TUIO2/TuioObject.cpp \
    TUIO20_CPP/TUIO2/TuioComponent.cpp \
    TUIO20_CPP/TUIO2/TuioToken.cpp \
    TUIO20_CPP/TUIO2/TuioPointer.cpp \
    TUIO20_CPP/TUIO2/TuioBounds.cpp \
    TUIO20_CPP/TUIO2/TuioSymbol.cpp \
    TUIO20_CPP/TUIO2/TuioDispatcher.cpp \
    TUIO20_CPP/TUIO2/TuioManager.cpp \
    TUIO20_CPP/TUIO2/TuioServer.cpp \
    TUIO20_CPP/TUIO2/UdpSender.cpp \
    TUIO20_CPP/TUIO2/TcpSender.cpp \
    TUIO20_CPP/oscpack/osc/OscTypes.cpp \
    TUIO20_CPP/oscpack/osc/OscOutboundPacketStream.cpp \
    TUIO20_CPP/oscpack/ip/posix/NetworkingUtils.cpp \
    TUIO20_CPP/oscpack/ip/posix/UdpSocket.cpp \

SOURCES += src/plugin.cpp src/tuiosender.cpp $$TUIO_SOURCES

HEADERS += src/tuiosender.h

QMAKE_CXXFLAGS += -std=c++11

OTHER_FILES += examples/*.qml org/ecloud/tuio/qmldir

target.path = $$[QT_INSTALL_QML]/org/ecloud/tuio
qmldir.path = $$[QT_INSTALL_QML]/org/ecloud/tuio
qmldir.files = build/org/ecloud/tuio/qmldir
INSTALLS += target qmldir
