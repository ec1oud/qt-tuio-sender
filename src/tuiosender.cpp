#include "tuiosender.h"
#include <QVector2D>

TuioSender::TuioSender(QObject *parent) : QObject(parent)
{
    m_server->setSourceName("org.ecloud.t");
}

TuioSender::~TuioSender()
{
    delete m_server;
    delete m_sender;
}

void TuioSender::press(const QPointingDeviceUniqueId &uid, int pointId, qreal x, qreal y, qreal angle, qreal shearAngle, qreal radius, qreal pressure, const QVector2D &velocity)
{
    unsigned uniqueId = (uid.numericId() < 0 ? pointId : (unsigned)uid.numericId());
    qDebug("%x (%d) press @ %0.1lf,%0.1lf ∡ %0.1lf ⦞ %0.1lf ⌀ %0.1lf p %0.1lf v %0.1lf,%0.1lf", pointId, uniqueId, x, y, angle, shearAngle, radius, pressure, velocity.x(), velocity.y());
    m_server->initTuioFrame(TuioTime::getSystemTime());
    // TuioObject* TuioManager::createTuioPointer(unsigned short t_id, unsigned short u_id, float x, float y, float a, float s, float r, float p)
    // TuioObject* TuioManager::addTuioPointer(TuioObject *tobj, unsigned int p_id, float x, float y, float a, float s, float r, float p)
    TuioObject *tptr = m_server->createTuioPointer(pointId, uniqueId, x, y, angle, shearAngle, radius, pressure);
    m_pointers.append(tptr->getTuioPointer());
//    m_server->stopUntouchedMovingObjects();
    m_server->commitTuioFrame();
}

void TuioSender::update(const QPointingDeviceUniqueId &uid, int pointId, qreal x, qreal y, qreal angle, qreal shearAngle, qreal radius, qreal pressure, const QVector2D &velocity)
{
    unsigned uniqueId = (uid.numericId() < 0 ? pointId : (unsigned)uid.numericId());
    qDebug("%x (%d) update @ %0.1lf,%0.1lf ∡ %0.1lf ⦞ %0.1lf ⌀ %0.1lf p %0.1lf v %0.1lf,%0.1lf", pointId, uniqueId, x, y, angle, shearAngle, radius, pressure, velocity.x(), velocity.y());
    auto ptr = pointer(pointId);
    if (ptr) {
        m_server->initTuioFrame(TuioTime::getSystemTime());
        m_server->updateTuioPointer(ptr, x, y, angle, shearAngle, radius, pressure);
//        m_server->stopUntouchedMovingObjects();
        m_server->commitTuioFrame();
    }
}

void TuioSender::release(const QPointingDeviceUniqueId &uid, int pointId, qreal x, qreal y, qreal angle, qreal shearAngle, qreal radius, qreal pressure, const QVector2D &velocity)
{
    unsigned uniqueId = (uid.numericId() < 0 ? pointId : (unsigned)uid.numericId());
    qDebug("%x (%d) release @ %0.1lf,%0.1lf ∡ %0.1lf ⦞ %0.1lf ⌀ %0.1lf p %0.1lf v %0.1lf,%0.1lf", pointId, uniqueId, x, y, angle, shearAngle, radius, pressure, velocity.x(), velocity.y());
    auto ptr = pointer(pointId);
    if (ptr) {
        m_server->removeTuioPointer(ptr);
        m_pointers.removeOne(ptr);
    }
}

TuioPointer *TuioSender::pointer(int pointId)
{
    for (TuioPointer *p : m_pointers)
        if (p->getPointerID() == (unsigned)pointId)
            return p;
    return nullptr;
}
