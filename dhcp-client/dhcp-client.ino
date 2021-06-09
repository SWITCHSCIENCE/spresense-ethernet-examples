#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02};

void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  // Ethernet.init(10);  // Most Arduino shields
  // Ethernet.init(5);   // MKR ETH shield
  // Ethernet.init(0);   // Teensy 2.0
  // Ethernet.init(20);  // Teensy++ 2.0
  // Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  // Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }
  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  /*
  pinMode(22, OUTPUT);
  digitalWrite(22, 1);  //<-これでresetがONになる
  delay(100);
  digitalWrite(22, 1);  //<-resetをOFF
  delay(100);
  */
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println(
          "Ethernet shield was not found.  Sorry, can't run without hardware. "
          ":(");
    } else if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // no point in carrying on, so do nothing forevermore:
    while (true) {
      delay(1);
    }
  }
  // print your local IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  switch (Ethernet.maintain()) {
    case 1:
      // renewed fail
      Serial.println("Error: renewed fail");
      break;
    case 2:
      // renewed success
      Serial.println("Renewed success");
      // print your local IP address:
      Serial.print("My IP address: ");
      Serial.println(Ethernet.localIP());
      break;
    case 3:
      // rebind fail
      Serial.println("Error: rebind fail");
      break;
    case 4:
      // rebind success
      Serial.println("Rebind success");
      // print your local IP address:
      Serial.print("My IP address: ");
      Serial.println(Ethernet.localIP());
      break;
    default:
      // nothing happened
      break;
  }
}