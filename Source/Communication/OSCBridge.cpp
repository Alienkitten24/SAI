#include "OSCBridge.h"
#include <cstdint>
#include <iostream>

OSCBridge::OSCBridge()
    : m_destAddr("127.0.0.1"), m_destPort(9001)
{
}

OSCBridge::~OSCBridge()
{
    m_socket.shutdown();
}

void OSCBridge::forward(const std::vector<uint8_t>& message)
{
    m_socket.write(m_destAddr, m_destPort, message.data(), (int)message.size());
}