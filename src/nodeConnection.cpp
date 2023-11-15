#include"nodeConnection.hpp"
#include <QCryptographicHash>

using namespace qiota;

Node_Conection * Node_Conection::m_instance=nullptr;
Node_Conection* Node_Conection::instance()
{
    if (!m_instance) m_instance=new Node_Conection();
    return m_instance;
}
Node_Conection::Node_Conection(QObject *parent):QObject(parent),rest_client(new Client(this)),mqtt_client(new ClientMqtt(this)),
    state_(Node_Conection::Disconnected)
{
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


