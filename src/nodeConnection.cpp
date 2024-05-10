#include "nodeConnection.hpp"
#include <QCryptographicHash>

namespace qiota
{

NodeConnection *NodeConnection::m_instance = nullptr;
NodeConnection *NodeConnection::instance()
{
    if (!m_instance)
    {
        m_instance = new NodeConnection();
#if defined(USE_QML)
        QJSEngine::setObjectOwnership(m_instance, QJSEngine::CppOwnership);
#endif
    }
    return m_instance;
}
NodeConnection::NodeConnection(QObject *parent)
    : QObject(parent), m_restClient(new Client(this)), m_mqttClient(new ClientMqtt(this)),
      m_state(NodeConnection::Disconnected)
{
    connect(m_restClient, &qiota::Client::stateChanged, this, [=]() {
        if (m_restClient->state() == Client::ClientState::Connected)
        {
            connect(m_mqttClient, &QMqttClient::stateChanged, this, [=](QMqttClient::ClientState state) {
                if (state == QMqttClient::Connected)
                {
                    setState(Connected);
                }
            });
            setNodeAddrWss(m_restClient->getNodeAddress());
        }
        else
        {
            setState(Disconnected);
        }
    });
}

void NodeConnection::setNodeAddrWss(const QUrl wss)
{
    auto nodeAddrWss = wss;
    nodeAddrWss.setScheme("wss");
    nodeAddrWss.setPort(443);
    nodeAddrWss.setPath("/api/mqtt/v1");
    m_mqttClient->setNodeAddress(nodeAddrWss);
}

} // namespace qiota
