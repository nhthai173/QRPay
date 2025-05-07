#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define INTERNAL_QR // Comment this line to use QR code generator from server

#if defined(INTERNAL_QR)
#include "qr_utils.h"
QRCode qrcode;
#else
#include "httpclient_utils.h"
HTTPClient http;
#endif

#define WIFI_SSID ""
#define WIFI_PASS ""

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void connect_wifi()
{
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
}


#if defined(INTERNAL_QR)

void displayTransactionQRCode(uint32_t amount = 0)
{
  generateTransactionQR(&qrcode, amount);
  displayQR(&display, &qrcode, 0, 0, 30);
}

#else

void stringDataToBuffer(String str, uint8_t *buf)
{
  String temp = "";
  uint16_t bufIndex = 0;
  for (uint16_t i = 0; i < str.length(); i++)
  {
    if (str[i] == ',')
    {
      buf[bufIndex++] = (uint8_t)temp.toInt();
      temp = "";
    }
    else
    {
      temp += str[i];
    }
  }
}

void displayTransactionQRCode(uint32_t amount = 0)
{
  uint8_t buf[512]; // 512 bytes for 64x64 image
  String url = "http://nht.local:3008/test/" + String(amount);
  stringDataToBuffer(
      httpGET(&http, url.c_str()),
      buf);
  display.drawBitmap(0, 60, buf, 64, 64, WHITE);
  display.display();
}

#endif


void setup()
{
  // Button to random amount
  pinMode(16, INPUT_PULLUP);

  // Start serial
  Serial.begin(115200);
  while (!Serial)
    delay(10);

  // Start display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  // Connect to the same network with server
  #ifndef INTERNAL_QR
  connect_wifi();
  #endif

  // Initialize display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setRotation(1);
}

void loop()
{

  // Create random QR in range 1 - 100
  if (digitalRead(16) == LOW)
  {
    uint16_t amount = random(1, 100);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.printf("%d.000 VND", amount);
    display.display();

    displayTransactionQRCode(amount * 1000);
    delay(500); // avoid button bounce
  }

  delay(10); // Slow down loop
}