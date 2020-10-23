# Overview
I'm tired of tripping over the torch lines and the foot pedal lines when welding. This project attempts to convert a standard Miller `RFCS-14 HD` TIG pedal to be wireless.  I am not smart enough to make the torch lines (power/coolant)
wireless, so these will have to stay for the time being.

## Hardware
I am lazy and want to minimize any PCB design, if any at all for this project.  Use the [Sparkfun Pro nRF52840 Mini](https://www.sparkfun.com/products/15025?_ga=2.169850529.1870647789.1602994609-37046419.1602533839) board
for both ends of the BLE connection.  The nice thing is that it already has a LiPo charger and connection for the foot
pedal side.

We just need to build up the analog interfaces on either side, and a power supply for the welder side.

## Software
Because I am a machocist, we are going to use the Nordic SDK, and attempt to have a fully contained build system with
this project.

## References
[nRF52840 Advanced Development With the nRF5 SDK](https://learn.sparkfun.com/tutorials/nrf52840-advanced-development-with-the-nrf5-sdk)

## Dependencies
### MacOS
1. Install [Adafruit's nRF25_nrfutil](https://github.com/adafruit/Adafruit_nRF52_nrfutil) so we can use the DFU
bootloader.
```
pip3 install adafruit-nrfutil
```

2. Install the gcc toolchain.
```
wget https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu-rm/10-2020q2/gcc-arm-none-eabi-10-2020-q2-preview-mac.pkg

# Install.  Add `/Applications/ARM/bin/` to PATH via bash_profile.
```

3. Install cmake and Qt.
```
brew install cmake qt
```

## Building Firmware
### MacOS
```
# Find the name of the serial port created by the bootloader.  Put the board into bootloader and look for something like `tty.usbmodem141401` under `/dev`

# Jump into the `fw` directory and create a `build` directory. And then jump into that.  Run CMake, specifying the name of the serial port found earlier.  The first time running CMake will take a bit of time as the Nordic SDK is being downloaded as a dependency.
cmake -DSERIAL_PORT=/dev/tty.usbmodem141401 ..

# Build it.
make -j

# Flash it.  Put your board into booloader first.
make bootload

# Success!
```

## Building Software
### MacOS
```
# Jump into the `sw` directory and create a `build` directory. And then jump into that.
cmake ..

# Build it.
make -j
```
