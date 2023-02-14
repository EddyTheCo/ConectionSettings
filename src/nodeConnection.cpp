#include"nodeConnection.hpp"


using namespace qiota;

Node_Conection::Node_Conection():rest_client(new Client()),mqtt_client(new ClientMqtt()),isconnected_(false)
{
    connect(rest_client,&qiota::Client::stateChanged,this,[=]()
    {
        if(rest_client->state()==Client::ClientState::Connected)
        {
            set_node_addr_wss(rest_client->get_node_address());
            isconnected_=true;
            emit connected();
        }
    });


}
void Node_Conection::publish(const qiota::qblocks::Block & block_)
{
    if(isconnected_)
    {
        rest_client->send_block(block_);
    }
}
void Node_Conection::set_node_addr_wss(const QUrl wss)
{
    auto node_addr_wss_=wss;
    node_addr_wss_.setScheme("wss");
    node_addr_wss_.setPort(443);
    node_addr_wss_.setPath("/api/mqtt/v1");
    mqtt_client->set_node_address(node_addr_wss_);
}
