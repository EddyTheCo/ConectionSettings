#include"nodeConnection.hpp"


using namespace qiota;

Node_Conection::Node_Conection():rest_client(new Client()),mqtt_client(new ClientMqtt())
{
    connect(rest_client,&qiota::Client::ready,this,[=]()
    {
        set_node_addr_wss(rest_client->get_node_address());
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
