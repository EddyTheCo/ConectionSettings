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

    Node_Conection(QObject *parent = nullptr);
    enum ConState {
        Disconnected = 0,
        Connected
    };
    Q_ENUM(ConState)
    Q_INVOKABLE QJsonObject info(){return rest_client->info();}
    QUrl nodeaddr()const{return rest_client->get_node_address();}
    static QString jwt(){return rest_client->get_jwt();}
    void set_naddr(QUrl naddr){
        qDebug()<<"setting naddres started";

        rest_client->set_node_address(naddr);
        qDebug()<<"setting naddres finished";
    }
    void set_state(ConState state_m){if(state_!=state_m){state_=state_m;emit stateChanged(state_);}}
    void setjwt(QString jwt_){rest_client->set_jwt(jwt_);}
    static qiota::Client* rest_client;
    static qiota::ClientMqtt * mqtt_client;
    static ConState state(void){return state_;}


signals:
    void naddrChanged();
    void jwtChanged();
    void stateChanged(Node_Conection::ConState);
    void newBlock(QString);


private:
    void set_node_addr_wss(const QUrl wss);
    static ConState state_;
    static QString hrp_;
};
