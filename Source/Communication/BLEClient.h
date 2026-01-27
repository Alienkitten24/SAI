#pragma once

#include "simpleble/SimpleBLE.h"
#include <utility>
#include <functional>

class BLEClient
{
public:
    BLEClient();
    ~BLEClient();

    void start();
    // void stop();

    SimpleBLE::ByteArray fetch();
    void subscribe();

    std::function<void(const std::vector<uint8_t>& msg)> onNotify;

private:
    SimpleBLE::BluetoothUUID m_targetService;
    SimpleBLE::Adapter m_adapter;
    SimpleBLE::Peripheral m_peripheral;
    std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID> m_uuid;

    SimpleBLE::Adapter getAdapter();
    SimpleBLE::Peripheral getPeripheral();
    std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID> getServiceCharacteristicPair();
};