A simple demo to show the QRCode for QRPay on a 0.96" OLED display

## Connections

| ESP32  |             |
| ------ | ----------- |
| GPIO21 | Display SDA |
| GPIO22 | Display SCL |
| GPIO16 | Button      |

## Usage

Generating a QRCode of random amount when press button

Config WiFi credential at head of `main.cpp`

```cpp
#define WIFI_SSID ""
#define WIFI_PASS ""
```
