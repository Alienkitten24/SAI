#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

#include "BLEClient.h"

using namespace std::chrono_literals;

BLEClient::BLEClient()
{
}

BLEClient::~BLEClient()
{
    // TODO wrap in try catch 
    m_peripheral.disconnect();
}

void BLEClient::start()
{
    // initialize expected target service UUID
    m_targetService = SimpleBLE::BluetoothUUID("12341000-1234-1234-1234-123456789abc");

    m_adapter = getAdapter();
    m_peripheral = getPeripheral();
    
    m_peripheral.connect();
    std::cout << "Connected to peripheral, discovering services..." << std::endl;
    
    m_uuid = getServiceCharacteristicPair();
}

SimpleBLE::Adapter BLEClient::getAdapter()
{
    if (!SimpleBLE::Adapter::bluetooth_enabled()) {
        std::cout << "Bluetooth is not enabled!" << std::endl;
        throw std::runtime_error("Bluetooth not enabled");
    }

    auto adapter_list = SimpleBLE::Adapter::get_adapters();

    // no adapter found
    if (adapter_list.empty()) {
        std::cerr << "No adapter was found." << std::endl;
        throw std::runtime_error("No adapter found");
    }

    // only one found, returning directly
    if (adapter_list.size() == 1) {
        auto adapter = adapter_list.at(0);
        std::cout << "Using adapter: " << adapter.identifier() << " [" << adapter.address() << "]" << std::endl;
        return adapter;
    }

    // TODO: support multiple adapters. For now use the first.
    return adapter_list.at(0);
}

SimpleBLE::Peripheral BLEClient::getPeripheral()
{
    std::vector<SimpleBLE::Peripheral> peripherals;

    m_adapter.set_callback_on_scan_found([&](SimpleBLE::Peripheral peripheral) {
        std::cout << "Found device: " << peripheral.identifier() << " [" << peripheral.address() << "]" << std::endl;
        if (peripheral.is_connectable()) {
            peripherals.push_back(peripheral);
        }
    });

    m_adapter.set_callback_on_scan_start([]() { std::cout << "Scan started." << std::endl; });
    m_adapter.set_callback_on_scan_stop([]() { std::cout << "Scan stopped." << std::endl; });
    // Scan for 5 seconds and return.
    m_adapter.scan_for(5000);

    std::cout << "The following devices were found:" << std::endl;
    for (size_t i = 0; i < peripherals.size(); i++) {
        std::cout << "[" << i << "] " << peripherals[i].identifier() << " [" << peripherals[i].address() << "]"
                  << std::endl;
    }

    for (auto &p : peripherals) {
        if (p.identifier() == "Audimo") {
            std::cout << "Audimo Detected" << std::endl;
            return p;
        }
    }

    std::cout << "throwing..." << std::endl;
    throw std::runtime_error("Audimo not found");
}

std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID> BLEClient::getServiceCharacteristicPair()
{
    std::vector<std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID>> uuids;
    for (auto service : m_peripheral.services()) {
        for (auto characteristic : service.characteristics()) {
            uuids.push_back(std::make_pair(service.uuid(), characteristic.uuid()));
        }
    }

    std::cout << "The following services and characteristics were found:" << std::endl;
    std::cout << "Total found: " << uuids.size() << std::endl;
    if (uuids.size() == 0) {
        std::cerr << "WARNING: No services/characteristics discovered! Check if peripheral is fully connected and discovered." << std::endl;
    }
    for (size_t i = 0; i < uuids.size(); i++) {
        std::cout << "[" << i << "] " << uuids[i].first << " " << uuids[i].second << std::endl;
    }

    for (auto& u : uuids) {
        if (u.first == m_targetService) {
            std::cout << "Target Service Found" << std::endl;
            return u;
        }
    }

    throw std::runtime_error("Target Service Not Found");
}


SimpleBLE::ByteArray BLEClient::fetch()
{
    return m_peripheral.read(m_uuid.first, m_uuid.second);
    // try {
    //     std::cout << "Attempting to read from service: " << m_uuid.first 
    //               << " characteristic: " << m_uuid.second << std::endl;
        
    //     // Check if still connected
    //     if (!m_peripheral.is_connected()) {
    //         std::cerr << "WARNING: Peripheral is not connected!" << std::endl;
    //         throw std::runtime_error("Peripheral disconnected");
    //     }
        
    //     SimpleBLE::ByteArray data = m_peripheral.read(m_uuid.first, m_uuid.second);
    //     std::cout << "Successfully read " << data.size() << " bytes" << std::endl;
    //     return data;
    // }
    // catch (const std::exception& e) {
    //     std::cerr << "fetch() error: " << e.what() << std::endl;
    //     throw;
    // }
}

void BLEClient::subscribe()
{
    m_peripheral.notify(
        m_uuid.first,
        m_uuid.second,
        [&](SimpleBLE::ByteArray bytes) {
            if (onNotify) {
                std::vector<uint8_t> v(bytes.begin(), bytes.end());
                onNotify(v);
            }
        }
    );
}