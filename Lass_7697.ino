/* Linkit 7697 BLE Library */
#include <LBLE.h>
#include <LBLEPeriphral.h>

/* BLE GATT Config */
LBLEService lassService("6941b009-085d-4064-8487-180a0690d4ac");
LBLECharacteristicString dustCharacteristic("6941b00A-085d-4064-8487-180a0690d4ac", LBLE_READ);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Initialize
  LBLE.begin();  
  // Wait BLE ready
  while( !LBLE.ready() ) delay(100);
  
  Serial.println("BLE Ready!");
  Serial.print("Ardress : ");
  Serial.println(LBLE.getDeviceAddress());

  // Add to LASS Service
  lassService.addAttribute(dustCharacteristic);
  // Add Service to GATT server
  LBLEPeripheral.addService(lassService);

  // Generate device id for BLE Name
  int id = random(100000, 999999);
  String BLEName = "LASS_"+String(id);

  Serial.print( "Name : " );
  Serial.println(BLEName);
  
  LBLEPeripheral.setName(BLEName.c_str());
  LBLEAdvertisementData adver;
  adver.configAsConnectableDevice(BLEName.c_str());

  // Start GATT server service 
  LBLEPeripheral.begin();
  LBLEPeripheral.advertise(adver); 
}

void loop() {
  // put your main code here, to run repeatedly:

  int data = random(5, 20);
  dustCharacteristic.setValue(String(data));

  delay(200);
}
