#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 38

Adafruit_NeoPixel led(1, LED_PIN, NEO_GRB + NEO_KHZ800);

#define SERVICE_UUID "12345678-1234-1234-1234-1234567890ab"
#define CHARACTERISTIC_UUID "abcdefab-1234-1234-1234-abcdefabcdef"

//const char* ssid = "Zyxel_624621";
//const char* password = "L3773XPU";

class CommandCallbacks : public BLECharacteristicCallbacks {
 void onWrite(BLECharacteristic *pCharacteristic) {
 String value = pCharacteristic->getValue();
 Serial.print("Received: ");
 Serial.println(value);
 if (value == "R") {
 led.setPixelColor(0, led.Color(0, 255, 0));
 }
 else if (value == "G") {
 led.setPixelColor(0, led.Color(255, 0, 0));
 }
 else if (value == "W") {
 led.setPixelColor(0, led.Color(255, 255, 255));
 }
 else if (value == "B") {
 led.setPixelColor(0, led.Color(0, 0, 255));
 }
 else if (value == "O") {
 led.clear();
 }
 led.show();
 }
 
};

void setup()
{
  Serial.begin(115200);
  delay(1000);

  led.begin();
  led.setBrightness(50);
  led.clear();
  led.show();
 
  BLEDevice::init("My-ESP32-S3");
  BLEServer *pServer=BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic =
  pService->createCharacteristic(CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_WRITE);

  pCharacteristic->setCallbacks(new CommandCallbacks());
  pService->start();
  
  BLEAdvertising *pAdvertising =
  BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->start();

  Serial.println("BLE STARTED!");
  Serial.println("Connect with nRF Connect.");

}
void loop()
{
  delay(1000);
}