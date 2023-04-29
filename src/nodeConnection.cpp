#include"nodeConnection.hpp"
#include <QCryptographicHash>

using namespace qiota;

qiota::Client* Node_Conection::rest_client=nullptr;

qiota::ClientMqtt * Node_Conection::mqtt_client=nullptr;

Node_Conection::ConState Node_Conection::state_=Node_Conection::Disconnected;

Node_Conection::Node_Conection(QObject *parent):QObject(parent)
{
    rest_client=new Client(this);
    mqtt_client=new ClientMqtt(this);

    connect(rest_client,&qiota::Client::stateChanged,this,[=]()
    {
        if(rest_client->state()==Client::ClientState::Connected)
        {
            connect(mqtt_client,&QMqttClient::stateChanged,this,[=](QMqttClient::ClientState state )
            {
                if(state==QMqttClient::Connected)
                {
                    emit naddrChanged();
                    set_state(Connected);
                }
            });
            set_node_addr_wss(rest_client->get_node_address());
        }
        else
        {
            set_state(Disconnected);
        }
    });
    connect(rest_client,&qiota::Client::last_blockid,this,[=](qblocks::c_array id)
    {
        emit newBlock(id.toHexString());
    });
}

void Node_Conection::set_node_addr_wss(const QUrl wss)
{
    auto node_addr_wss_=wss;
    node_addr_wss_.setScheme("wss");
    node_addr_wss_.setPort(443);
    node_addr_wss_.setPath("/api/mqtt/v1");
    mqtt_client->set_node_address(node_addr_wss_);
}


