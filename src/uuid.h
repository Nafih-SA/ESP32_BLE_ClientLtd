/************** Service UUIDs ************/
BLEUUID SERVICE_UUID = BLEUUID("4fafc201-1fb5-459e-8fcc-c5c9c331914b");
BLEUUID BatteryService = BLEUUID((uint16_t)0x180F);


/********** Characteristic UUID ***********/
BLEUUID CHARACTERISTIC_UUID = BLEUUID("beb5483e-36e1-4688-b7f5-ea07361b26a8");
BLEUUID BatteryCharacteristics = BLEUUID((uint16_t)0x2A19);


/************* Descriptor ***************/
BLEDescriptor BatteryLevelDescriptor(BLEUUID((uint16_t)0x2901));
