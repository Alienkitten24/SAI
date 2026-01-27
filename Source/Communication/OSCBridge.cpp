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
    // std::cout << "Notification: ";
    // for (unsigned char c : message) printf("%02x ", c);
    // std::cout << std::endl;

    m_socket.write(m_destAddr, m_destPort, message.data(), (int)message.size()); // inward-facing port
    m_socket.write(m_destAddr, m_destPort+1, message.data(), (int)message.size()); // outward-facing port
    // TODO handle errors that socket.write() could have:
    //      port num invalid (9001 doesn't exist or smth) fix: find new open port
    //      network perms -- OS could prevent packet send due to lack of perms
}
