#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"

#define DHTPIN D2
#define DHTTYPE DHT11

DHT dht (DHTPIN, DHTTYPE);

const char* ssid = "koutane entek wa?";                  // Your wifi Name       
const char* password = "ketikbae";          // Your wifi Password

const char *host = "192.168.43.101"; 

void setup() {

  delay(1000);
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);      // Initialize the Led_OnBoard pin as an output
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot

  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(BUILTIN_LED, LOW);
    delay(250);
    Serial.print(".");
    digitalWrite(BUILTIN_LED, HIGH); 
    delay(250);
  }

  digitalWrite(BUILTIN_LED, HIGH);
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.println("Connected to Network/SSID");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}

void loop() {

  HTTPClient http;    //Declare object of class HTTPClient

   float h = dht.readHumidity();
   float t = dht.readTemperature();

  String humid, temp;
  humid = String (h);
  temp = String (t);

  http.begin("http://localhost/Nodemcu_db_record_view/InsertDB.php");      

  int httpCode_1 = http.POST(humid);
  int httpCode_2 = http.POST(temp);
  String payload = http.getString();    //Get the response payload

  Serial.println(httpCode_1);
  Serial.println(httpCode_2);
  Serial.println(payload);    //Print request response payload

  Serial.println("Humidity=" + humid);
  Serial.println("temperature=" + temp);

  http.end();  //Close connection

  delay(4000);  
  digitalWrite(BUILTIN_LED, LOW);
  delay(6000);
  digitalWrite(BUILTIN_LED, HIGH);
}
