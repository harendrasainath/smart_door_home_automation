#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "MaxPayne";
const char* password = "ioty1234";

IPAddress ip(192,168,43,123);
IPAddress gateway(192,168,43,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);
int control = 5;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);                           // Start connecting to the WiFi network.

  while (WiFi.status() != WL_CONNECTED) {               // Wait until the connection is successful.
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  WiFi.config(ip, gateway,subnet);
  Serial.println("WiFi connected");
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.println(WiFi.localIP());                       // Print the IP Address of the device
  Serial.println("/");
}

void lighton() {
  digitalWrite(control,LOW);
  Serial.println("on");
  server.send(200, "text/plain", "LIght ON");
}

void lightoff() {
  digitalWrite(control,HIGH);
  Serial.println("off");
  server.send(200, "text/plain", "Light OFF");
}

void handleNotFound() {
  server.send(200, "text/plain", "Not Found");                                        // Send a message "Not Found" in case of undefined requests.
}

void setup() {
  pinMode(control, OUTPUT);
  Serial.begin(115200);
  setup_wifi();

  //  WiFi.config(ip, gateway,subnet);
  server.begin();
  Serial.println("Server started");
  server.on("/lighton", lighton);                                                         // Method to execute/process client requests with the URL "/lighton"
  server.on("/lightoff", lightoff);                                                        // Method to execute/process client requests with the URL "/lightoff"
  server.onNotFound(handleNotFound);
}

void loop()
{
  server.handleClient();
}


