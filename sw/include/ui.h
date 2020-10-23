#ifndef UI_H_
#define UI_H_

#include <QObject>

// Forward declare Qt stuff so we don't drag it into everything.
class BluetoothHelper;

class UI : public QObject
{
    Q_OBJECT

 public:
    UI();
    virtual ~UI() = default;

 private:
    BluetoothHelper bt_;
};

#endif  // UI_H_
