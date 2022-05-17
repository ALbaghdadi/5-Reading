
#include <SPI.h>
#include <Ethernet.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //Setting MAC Address




float ID_location
float voltageAC;
float currentAC;
float voltageDC;
float currentDC;

IPAddress server(172,23,174,101);
//char server[] = "192.168.0.100";
IPAddress ip(10,5,52,2); 

EthernetClient client; 

/* Setup for Ethernet and RFID */

void setup() {

  Serial.begin(9600);
 Serial.println("HI"); 
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
    Serial.println(Ethernet.localIP());
  delay(1000);
}
//------------------------------------------------------------------------------


/* Infinite Loop */
void loop(){

  ID_location =5;
  voltageAC = random(200,280);
  currentAC = random(2,8); 
  voltageDC=random(10,20); 
  currentDC=random(50,80); 
  Sending_To_phpmyadmindatabase(); 
  delay(10000); // interval
  Serial.println("done");
}


  void Sending_To_phpmyadmindatabase()   //CONNECTING WITH MYSQL
 {
   if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    Serial.print("GET /testcode/dht.php?ID_location=");
    client.print("GET /testcode/dht4.php?ID_location=");     //YOUR URL
    Serial.println(ID_location);
    client.print(ID_location);

    client.print("&voltageAC=");
    Serial.println("&voltageAC=");
    client.print(voltageAC);
    Serial.println(voltageAC);
    
    client.print("&currentAC=");
    Serial.println("&currentAC=");
    client.print(currentAC);
    Serial.println(currentAC);
    
    client.print("&voltageDC=");
    Serial.println("&voltageDC=");
    client.print(voltageDC);
    Serial.println(voltageDC);
    
    client.print("&currentDC=");
    Serial.println("&currentDC=");
    client.print(currentDC);
    Serial.println(currentDC);
    
    client.print(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host: 172.23.174.101");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
 }
