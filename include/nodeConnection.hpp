#pragma once

#include<QObject>
#include<QString>
#include<QUrl>

#include"client/qclient.hpp"
#include"client/qclientMQTT.hpp"

#if defined(USE_QML)
#include <QtQml/qqmlregistration.h>
#endif
#include <QtCore/QtGlobal>
#if defined(WINDOWS_NCONN)
# define NCONN_EXPORT Q_DECL_EXPORT
#else
#define NCONN_EXPORT Q_DECL_IMPORT
#endif

namespace qiota{


class NCONN_EXPORT NodeConnection: public QObject
{
    Q_OBJECT
#if defined(USE_QML)
    Q_PROPERTY(QUrl  nodeaddr READ nodeaddr WRITE set_naddr NOTIFY naddrChanged)
    Q_PROPERTY(QString  jwt READ jwt WRITE setjwt NOTIFY jwtChanged)
    Q_PROPERTY(ConState  state READ state NOTIFY stateChanged)
    QML_ELEMENT
    QML_SINGLETON
#endif


public:
    enum ConState {
        Disconnected = 0,
        Connected
    };
    Q_ENUM(ConState)

    QUrl nodeaddr()const{return m_restClient->getNodeAddress();}
    void setNodeAddr(QUrl naddr);


    static NodeConnection* instance();
    ConState state(void){return m_state;}
    qiota::Client* rest(){return m_restClient;};
    qiota::ClientMqtt * mqtt(){return m_mqttClient;};

signals:
    void stateChanged();

private:
    NodeConnection(QObject *parent = nullptr);
    void setState(const ConState& state){if(m_state!=state){m_state=state;emit stateChanged();}}
    static NodeConnection* m_instance;
    Client* m_restClient;
    ClientMqtt * m_mqttClient;
    void setNodeAddrWss(const QUrl wss);
    ConState m_state;

};
};
