#ifndef TUIO_SENDER_H
#define TUIO_SENDER_H

#include <QObject>
#include <QPointF>
#include <QPointingDeviceUniqueId>

#include "../TUIO20_CPP/TUIO2/TuioServer.h"
#include "../TUIO20_CPP/TUIO2/UdpSender.h"

using namespace TUIO2;

class TuioSender : public QObject
{
    Q_OBJECT

public:

    explicit TuioSender(QObject *parent = 0);
    virtual ~TuioSender();

    Q_INVOKABLE void press(const QPointingDeviceUniqueId &uid, int pointId, qreal x, qreal y, qreal angle, qreal shearAngle, qreal radius, qreal pressure, const QVector2D &velocity);
    Q_INVOKABLE void update(const QPointingDeviceUniqueId &uid, int pointId, qreal x, qreal y, qreal angle, qreal shearAngle, qreal radius, qreal pressure, const QVector2D &velocity);
    Q_INVOKABLE void release(const QPointingDeviceUniqueId &uid, int pointId, qreal x, qreal y, qreal angle, qreal shearAngle, qreal radius, qreal pressure, const QVector2D &velocity);

signals:

protected:
    TuioPointer *pointer(int pointId);

private:

private:
    OscSender *m_sender = new TUIO2::UdpSender();
    TuioServer *m_server = new TuioServer(m_sender);
    QVector<TuioPointer *> m_pointers;
};

#endif // TUIO_SENDER_H
