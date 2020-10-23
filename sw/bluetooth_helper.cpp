#include "bluetooth_helper.h"

#include <QBluetoothDeviceDiscoveryAgent>

#include <iostream>

BluetoothHelper::BluetoothHelper() :
    QObject(),
    discovery_agent_(new QBluetoothDeviceDiscoveryAgent)
{
    discovery_agent_->setLowEnergyDiscoveryTimeout(5000);
    QObject::connect(discovery_agent_.get(), &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
        this, &BluetoothHelper::add_device);
    /*connect(discoveryAgent, QOverload<QBluetoothDeviceDiscoveryAgent::Error>::of(&QBluetoothDeviceDiscoveryAgent::error),
            this, &Device::deviceScanError);*/
    QObject::connect(discovery_agent_.get(), &QBluetoothDeviceDiscoveryAgent::finished, this,
        &BluetoothHelper::discovery_finished);

    discovery_agent_->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
}

BluetoothHelper::~BluetoothHelper() = default;

void BluetoothHelper::add_device(const QBluetoothDeviceInfo &info)
{
    if (true == info.name().toStdString().empty())
    {
        return;
    }

    if (info.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration)
    {
        std::cout << "Found BLE device: " << info.name().toStdString() << " (RSSI: " << info.rssi() << ")" << std::endl;
    }
}

void BluetoothHelper::discovery_finished()
{
    std::cout << "Discovery finished." << std::endl;
}
