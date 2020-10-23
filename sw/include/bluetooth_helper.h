#ifndef BLUETOOTH_HELPER_H_
#define BLUETOOTH_HELPER_H_

#include <memory>

#include <QObject>

// Forward declare Qt stuff so we don't drag it into everything.
class QBluetoothDeviceDiscoveryAgent;
class QBluetoothDeviceInfo;

class BluetoothHelper : public QObject
{
    Q_OBJECT

 public:
    BluetoothHelper();
    virtual ~BluetoothHelper();

 private slots:
    void add_device(const QBluetoothDeviceInfo &info);
    void discovery_finished();

 private:
    std::unique_ptr<QBluetoothDeviceDiscoveryAgent> discovery_agent_;
};

#endif
