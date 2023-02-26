#pragma once

#include<QObject>
#include<QString>
#include<QUrl>
#include <QtQml/qqmlregistration.h>
#include"client/qclient.hpp"
#include"client/qclientMQTT.hpp"


class Node_Conection: public QObject
{
    Q_OBJECT

       Q_PROPERTY(QUrl  nodeaddr READ nodeaddr WRITE set_naddr NOTIFY naddrChanged)
       Q_PROPERTY(QString  jwt READ jwt WRITE setjwt NOTIFY jwtChanged)
       Q_PROPERTY(ConState  state READ state NOTIFY stateChanged)
       QML_ELEMENT
       QML_SINGLETON

public:

    Node_Conection();
    enum ConState {
        Disconnected = 0,
        Connected
    };
    Q_ENUM(ConState)
    QUrl nodeaddr()const{return rest_client->get_node_address();}
    QString jwt()const{return rest_client->get_jwt();}
    void set_naddr(QUrl naddr){rest_client->set_node_address(naddr);}
    void setjwt(QString jwt_){rest_client->set_jwt(jwt_);}
    static qiota::Client* rest_client;
    static qiota::ClientMqtt * mqtt_client;
    static ConState state(void){return state_;}

signals:
    void naddrChanged();
    void jwtChanged();
    void stateChanged(Node_Conection::ConState);

private:
    void set_node_addr_wss(const QUrl wss);
    static ConState state_;


};
