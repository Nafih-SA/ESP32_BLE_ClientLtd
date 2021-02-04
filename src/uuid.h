/************** Service UUIDs ************/
BLEUUID SERVICE_UUID = BLEUUID("4fafc201-1fb5-459e-8fcc-c5c9c331914b");
BLEUUID BatteryService = BLEUUID((uint16_t)0x180F);
BLEUUID BS = BLEUUID("0xFEAA");

BLEUUID SERVICE10_UUID = BLEUUID("36cb4a3c-66a1-11eb-ae93-0242ac130002");
BLEUUID SERVICE20_UUID = BLEUUID("36cb4dac-66a1-11eb-ae93-0242ac130002");

/********** Characteristic UUID ***********/
BLEUUID CHARACTERISTIC_UUID = BLEUUID("beb5483e-36e1-4688-b7f5-ea07361b26a8");
BLEUUID BatteryCharacteristics = BLEUUID((uint16_t)0x2A19);
BLEUUID CHARACTERISTIC11_UUID = BLEUUID("36cb4ea6-66a1-11eb-ae93-0242ac130002");
BLEUUID CHARACTERISTIC12_UUID = BLEUUID("36cb4f78-66a1-11eb-ae93-0242ac130002");
BLEUUID CHARACTERISTIC21_UUID = BLEUUID("36cb50c2-66a1-11eb-ae93-0242ac130002");


/************* Descriptor ***************/
BLEDescriptor BatteryLevelDescriptor(BLEUUID((uint16_t)0x2901));



/*********** Misc *************/
uint8_t manufacture_specific_data[8] = {0xc9, 0x08, 0x01, 0x02, 0x01, 0x00, 0x03, 0x00};
