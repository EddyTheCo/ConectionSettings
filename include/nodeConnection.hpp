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

       Q_PROPERTY(QUrl  nodeaddr READ nodeaddr WRITE set_naddr NOTIFY node_addrChanged)
       Q_PROPERTY(QString  jwt READ jwt WRITE setjwt  NOTIFY jwtChanged)

       QML_ELEMENT
       QML_SINGLETON

public:

    Node_Conection();
    void set_naddr(QUrl naddr){rest_client->set_node_address(naddr);}
    void setjwt(QString jwt_){rest_client->set_jwt(jwt_);}
    QUrl nodeaddr(void)const{return rest_client->get_node_address();}
    QString jwt(void)const{return rest_client->get_jwt();}
    qiota::Client* rest_client;
    qiota::ClientMqtt * mqtt_client;
    bool isConnected(void)const{return isconnected_;}
    void publish(const qiota::qblocks::Block & block_);
signals:
    void node_addrChanged(QUrl addr);
    void jwtChanged(QString jwt );
    void connected(void);

private:
    void set_node_addr_wss(const QUrl wss);
    bool isconnected_;


};
