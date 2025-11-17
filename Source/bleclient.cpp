#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include <string>
#include <cstdio>

#include "utils.hpp"

#include "simpleble/SimpleBLE.h"

using namespace std::chrono_literals;

int main() {
    auto adapter_optional = Utils::getAdapter();

    if (!adapter_optional.has_value()) {
        return EXIT_FAILURE;
    }

    auto adapter = adapter_optional.value();

    std::vector<SimpleBLE::Peripheral> peripherals;

    adapter.set_callback_on_scan_found([&](SimpleBLE::Peripheral peripheral) {
        std::cout << "Found device: " << peripheral.identifier() << " [" << peripheral.address() << "]" << std::endl;
        if (peripheral.is_connectable()) {
            peripherals.push_back(peripheral);
        }
    });

    // TODO prolly makes more sense to inf loop scan and break when audimo found 
    adapter.set_callback_on_scan_start([]() { std::cout << "Scan started." << std::endl; });
    adapter.set_callback_on_scan_stop([]() { std::cout << "Scan stopped." << std::endl; });
    // Scan for 5 seconds and return.
    adapter.scan_for(5000);

    std::cout << "The following devices were found:" << std::endl;
    for (size_t i = 0; i < peripherals.size(); i++) {
        std::cout << "[" << i << "] " << peripherals[i].identifier() << " [" << peripherals[i].address() << "]"
                  << std::endl;
    }

    SimpleBLE::Peripheral peripheral;
    bool found = false;
    for (auto& p : peripherals) {
        // std::cout << p.identifier() << " " << p.address() << std::endl; 
        if (p.identifier() == "Audimo") {
            std::cout << "Audimo Detected" << std::endl;
            peripheral = p;
            found = true;
            break;
        }
    }
    if (!found) {
        std::cerr << "Audimo not found" << std::endl;
        return 1;
    }

    std::cout << "Connecting to " << peripheral.identifier() << " [" << peripheral.address() << "]" << std::endl;
    peripheral.connect();

    std::cout << "Successfully connected, printing services and characteristics.." << std::endl;

    // Store all service and characteristic uuids in a vector.
    std::vector<std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID>> uuids;
    for (auto service : peripheral.services()) {
        for (auto characteristic : service.characteristics()) {
            uuids.push_back(std::make_pair(service.uuid(), characteristic.uuid()));
        }
    }

    std::cout << "The following services and characteristics were found:" << std::endl;
    for (size_t i = 0; i < uuids.size(); i++) {
        std::cout << "[" << i << "] Service: " << uuids[i].first << " Characteristic: " << uuids[i].second << std::endl;
        // Try to print characteristic properties if available
        auto service = peripheral.services();
        for (auto& svc : service) {
            if (svc.uuid() == uuids[i].first) {
                for (auto& chr : svc.characteristics()) {
                    if (chr.uuid() == uuids[i].second) {
                        std::cout << "    Properties: ";
                        if (chr.can_read()) std::cout << "READ ";
                        if (chr.can_write_request()) std::cout << "WRITE ";
                        if (chr.can_write_command()) std::cout << "WRITE_NO_RESP ";
                        if (chr.can_notify()) std::cout << "NOTIFY ";
                        if (chr.can_indicate()) std::cout << "INDICATE ";
                        std::cout << std::endl;
                    }
                }
            }
        }
    }

    SimpleBLE::BluetoothUUID targetService = "12341000-1234-1234-1234-123456789abc";
    std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID> uuid;
    found = false;
    for (auto& u : uuids) {
        if (u.first == targetService) {
            std::cout << "Target Service Found" << std::endl;
            uuid = u;
            found = true;
            break;
        }
    }
    if (!found) {
        std::cerr << "Target Service Not Found" << std::endl;
        return 1;
    }

    // Check characteristic capabilities
    auto services = peripheral.services();
    bool can_read = false;
    bool can_notify = false;
    for (auto& svc : services) {
        if (svc.uuid() == uuid.first) {
            for (auto& chr : svc.characteristics()) {
                if (chr.uuid() == uuid.second) {
                    can_read = chr.can_read();
                    can_notify = chr.can_notify();
                    if (!can_read) {
                        std::cout << "Characteristic cannot be read. Available properties: ";
                        if (chr.can_write_request()) std::cout << "WRITE ";
                        if (chr.can_write_command()) std::cout << "WRITE_NO_RESP ";
                        if (chr.can_notify()) std::cout << "NOTIFY ";
                        if (chr.can_indicate()) std::cout << "INDICATE ";
                        std::cout << std::endl;
                    }
                    break;
                }
            }
            break;
        }
    }

    std::cout << "Peripheral connected? " << (peripheral.is_connected() ? "yes" : "no") << std::endl;
    std::cout << "Starting read with UUID: " << uuid.first << " " << uuid.second << std::endl;

    // Try a single read first; if it fails, fall back to notifications (if available)
    try {
        SimpleBLE::ByteArray rx_data = peripheral.read(uuid.first, uuid.second);
        std::cout << "Initial read succeeded. Data: ";
        for (unsigned char c : rx_data) {
            printf("%02x ", c);
        }
        std::cout << std::endl;

        // Continue reading in a loop
        while (true) {
            rx_data = peripheral.read(uuid.first, uuid.second);
            std::cout << "Characteristic content is: ";
            for (unsigned char c : rx_data) {
                printf("%02x ", c);
            }
            std::cout << std::endl;
            std::this_thread::sleep_for(0.05s);
        }
    } catch (const std::exception& e) {
        std::cerr << "Read failed: " << e.what() << std::endl;
        if (can_notify) {
            std::cout << "Falling back to notifications..." << std::endl;
            try {
                peripheral.notify(uuid.first, uuid.second, [](SimpleBLE::ByteArray data) {
                    std::cout << "Notification: ";
                    for (unsigned char c : data) printf("%02x ", c);
                    std::cout << std::endl;
                });
                std::cout << "Notifications enabled. Listening for 30s..." << std::endl;
                std::this_thread::sleep_for(30s);
                peripheral.unsubscribe(uuid.first, uuid.second);
            } catch (const std::exception& e2) {
                std::cerr << "Notifications failed: " << e2.what() << std::endl;
                return 1;
            }
        } else {
            std::cerr << "Characteristic does not support notifications; cannot proceed." << std::endl;
            return 1;
        }
    }

    peripheral.disconnect();

    return EXIT_SUCCESS;
}