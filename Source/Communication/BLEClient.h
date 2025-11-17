#pragma once

#include "simpleble/SimpleBLE.h"
#include <utility>

class BLEClient
{
public:
    BLEClient();
    ~BLEClient();

    SimpleBLE::ByteArray fetch();

private:
    SimpleBLE::BluetoothUUID m_targetService;
    SimpleBLE::Adapter m_adapter;
    SimpleBLE::Peripheral m_peripheral;
    std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID> m_uuid;

    SimpleBLE::Adapter getAdapter();
    SimpleBLE::Peripheral getPeripheral();
    std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID> getServiceCharacteristicPair();
};