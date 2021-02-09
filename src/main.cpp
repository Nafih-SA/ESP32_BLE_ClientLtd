#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include "uuid.h"

BLESecurity *pSecurity = new BLESecurity();
BLEServer *pServer = NULL;
BLECharacteristic *pCharacteristic = NULL;
BLECharacteristic *pCharacteristic2 = NULL;
BLECharacteristic *pCharacteristic3 = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint32_t value = 0;
int connID = 0;

/*********** To Send Data *********/
class MyCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    std::string value = pCharacteristic->getValue();

    if (value.length() > 0)
    {
      Serial.println("*********");
      Serial.print(value.c_str());

      Serial.println();
      Serial.println("*********");
    }
  }
};

/********** Multiclient ***********/
class MyServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    if(pServer->getConnId() && !connID)
    {
      pServer->disconnect(connID);
      connID++;
      Serial.println("Kicked 0 out");    
    }
    else if(!(pServer->getConnId()) && connID)
    {
      pServer->disconnect(connID);
      connID--;  
      Serial.println("Kicked 1 out");  
    }
    Serial.printf("\nThe Connection ID is %d\n",connID);
    deviceConnected = true;
    BLEDevice::startAdvertising();
  };

  void onDisconnect(BLEServer *pServer)
  {
    deviceConnected = false;
  }
};

/********** Custom Functions **********/
void addService(BLEService **name, BLECharacteristic **ptr, BLEUUID sUUID, BLEUUID cUUID)
{
  *name = pServer->createService(sUUID);
  // Create a BLE Characteristic
  *ptr = (*name)->createCharacteristic(
      cUUID, BLECharacteristic::PROPERTY_READ |
                 BLECharacteristic::PROPERTY_WRITE |
                 BLECharacteristic::PROPERTY_NOTIFY |
                 BLECharacteristic::PROPERTY_INDICATE);

  // Create a BLE Descriptor
  (*ptr)->addDescriptor(new BLE2902());

  // Start the service
  (*name)->start();
}

void addCharacteristic(BLEService **Cname, BLECharacteristic **Cptr, BLEUUID cUUID)
{
  *Cptr = (*Cname)->createCharacteristic(
      cUUID, BLECharacteristic::PROPERTY_READ |
                 BLECharacteristic::PROPERTY_WRITE |
                 BLECharacteristic::PROPERTY_NOTIFY |
                 BLECharacteristic::PROPERTY_INDICATE);
  // Create a BLE Descriptor
  (*Cptr)->addDescriptor(new BLE2902());
  (*Cname)->start();
}

/************** Set-up ************/
void setup()
{
  Serial.begin(115200);
  Serial.println("Starting BLE Server");

  BLEDevice::init("ESP32_BLE_Test");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  /********** Service 1 **************/
  BLEService *s1;
  addService(&s1, &pCharacteristic, SERVICE10_UUID, CHARACTERISTIC11_UUID); //Create Service
  addCharacteristic(&s1, &pCharacteristic2, CHARACTERISTIC12_UUID);         //Add a second characteristic
  pCharacteristic2->setCallbacks(new MyCallbacks());                        //Add upload (write) option

  /********** Service 2 **************/
  BLEService *s2;
  addService(&s2, &pCharacteristic3, SERVICE20_UUID, CHARACTERISTIC21_UUID);

  // Start advertising
  BLEAdvertisementData pAdvertisementData = BLEAdvertisementData();
  BLEAdvertisementData qAdvertisementData = BLEAdvertisementData();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  // pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setAppearance(192);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  pAdvertisementData.setName("B_ESP"); // Value already set in init()
  // pAdvertisementData.setShortName("B-ESP");
  pAdvertisementData.setManufacturerData("004C");
  pAdvertisementData.setCompleteServices(SERVICE_UUID);
  pAdvertising->setAdvertisementData(pAdvertisementData);
  BLEDevice::startAdvertising();

  Serial.println("Characteristic defined! Now you can read it in your phone!");
}

/************* Loop *************/
void loop()
{

  if (deviceConnected)
  {
    pCharacteristic2->setValue((uint8_t *)&value, 4);
    pCharacteristic2->notify();
    pCharacteristic->setValue((uint8_t *)&value, 4);
    pCharacteristic->notify();
    pCharacteristic3->setValue((uint8_t *)&value, 4);
    pCharacteristic3->notify();
    value++;
    delay(100); // bluetooth stack will go into congestion, if too many packets are sent, in 6 hours test i was able to go as low as 3ms
  }
  // disconnecting
  if (!deviceConnected && oldDeviceConnected)
  {
    delay(500);                  // give the bluetooth stack the chance to get things ready
    pServer->startAdvertising(); // restart advertising
    Serial.println("start advertising");
    oldDeviceConnected = deviceConnected;
  }
  // connecting
  if (deviceConnected && !oldDeviceConnected)
  {
    // do stuff here on connecting
    // pServer->disconnect(oldDeviceConnected);
    oldDeviceConnected = deviceConnected;

  }

  delay(500);
}