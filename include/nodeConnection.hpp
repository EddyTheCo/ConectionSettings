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

class NCONN_EXPORT Node_Conection: public QObject
{
    Q_OBJECT
#if defined(USE_QML)
    Q_PROPERTY(QUrl  nodeaddr READ nodeaddr WRITE set_naddr NOTIFY naddrChanged)
    Q_PROPERTY(QString  jwt READ jwt WRITE setjwt NOTIFY jwtChanged)
    Q_PROPERTY(ConState  state READ state NOTIFY stateChanged)
    QML_ELEMENT
    QML_SINGLETON
#endif
    Node_Conection(QObject *parent = nullptr);
public:
    enum ConState {
        Disconnected = 0,
        Connected
    };
    Q_ENUM(ConState)
    Q_INVOKABLE QJsonObject info(){return rest_client->info();}
    QUrl nodeaddr()const{return rest_client->get_node_address();}
    QString jwt(){return rest_client->get_jwt();}
    void set_naddr(QUrl naddr){rest_client->set_node_address(naddr);}
    void set_state(ConState state_m){if(state_!=state_m){state_=state_m;emit stateChanged(state_);}}
    void setjwt(QString jwt_){rest_client->set_jwt(jwt_);}

    static Node_Conection* instance();
    ConState state(void){return state_;}
    qiota::Client* rest(){return rest_client;};
    qiota::ClientMqtt * mqtt(){return mqtt_client;};

signals:
    void naddrChanged();
    void jwtChanged();
    void stateChanged(Node_Conection::ConState);
    void newBlock(QString);


private:
    static Node_Conection* m_instance;
    qiota::Client* rest_client;
    qiota::ClientMqtt * mqtt_client;
    void set_node_addr_wss(const QUrl wss);
    ConState state_;
    QString hrp_;
};
