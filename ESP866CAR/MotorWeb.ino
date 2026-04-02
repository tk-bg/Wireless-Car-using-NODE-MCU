#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Servo.h>

#define DRIVE_MOTOR_POWER D1           // If the motor does not spin or does funky rotation, try changing the pin number 
#define DRIVE_MOTOR_DIRECTION D4

#define STEER_MOTOR_POWER D0

int drivePower = 1023;                 //Set the motor speed 1023 is maximum
uint8_t driveDirection = HIGH;         //If the motor is spinning in opposite direction, change "HIGH" to "LOW"

Servo steerServo;
int steerAngle = 90;                 

const char* ssid = "poco";             //Change the network name here
const char* password = "password";     //change the password as per your network, if the network does not have one, remove the line or add "//" at the start of the line

ESP8266WebServer server(80);

const char *webpage = 
#include "motorPage.h"                 //if you are to change the name of the motorPage change it here aswell
;

void handleRoot() {
  server.send(200, "text/html", webpage);
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void){
  
  pinMode(DRIVE_MOTOR_POWER, OUTPUT);     
  pinMode(DRIVE_MOTOR_DIRECTION, OUTPUT);
  steerServo.attach(STEER_MOTOR_POWER);
  steerServo.write(steerAngle);
  pinMode(LED_BUILTIN, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  
  Serial.begin(115200);                    //Set the baude rate
  WiFi.begin(ssid,password);               //If the network does not have a password, remove ",password"
  Serial.println(""); 

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
{
  digitalWrite(LED_BUILTIN, HIGH);  //This here is just indicate that the ESP 8266 is connected to the network, you can remove if not required the light blinks multiple times
  delay(100);                      
  digitalWrite(LED_BUILTIN, LOW);   
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);  
  delay(100);                      
  digitalWrite(LED_BUILTIN, LOW);   
  delay(100);  
  digitalWrite(LED_BUILTIN, HIGH);  
  delay(100);                      
  digitalWrite(LED_BUILTIN, LOW);   
  delay(100);  
  digitalWrite(LED_BUILTIN, HIGH);  
  delay(100);                      
  digitalWrite(LED_BUILTIN, LOW);   
  delay(100);  
  digitalWrite(LED_BUILTIN, HIGH);  
  delay(100);                      
  digitalWrite(LED_BUILTIN, LOW);   
  delay(100);    
  digitalWrite(LED_BUILTIN, HIGH);  
  delay(100);                      
  digitalWrite(LED_BUILTIN, LOW);   
  delay(100);  
  digitalWrite(LED_BUILTIN, HIGH);  
  delay(100);                      
  digitalWrite(LED_BUILTIN, LOW);   
  delay(100);
}

  if (MDNS.begin("WifiCar")) {
    Serial.println("MDNS Responder Started");
  }

  server.on("/", handleRoot);

  server.on("/forward", [](){
    Serial.println("forward");
    analogWrite(DRIVE_MOTOR_POWER, drivePower);
    digitalWrite(DRIVE_MOTOR_DIRECTION, driveDirection);
    server.send(200, "text/plain", "forward");
  });
  server.on("/driveStop", [](){
    Serial.println("driveStop");
    analogWrite(DRIVE_MOTOR_POWER, 0);
    server.send(200, "text/plain", "driveStop");
  });
  server.on("/back", [](){
    Serial.println("back");
    analogWrite(DRIVE_MOTOR_POWER, drivePower);
    digitalWrite(DRIVE_MOTOR_DIRECTION, !driveDirection);
    server.send(200, "text/plain", "back");
  });
  server.on("/right", [](){
    Serial.println("right");                                      //Your servo might need to be caliberated and the orientation might not be correct
    steerAngle = 180;                                             // Adjust this angle for right as needed
    steerServo.write(steerAngle);
    server.send(200, "text/plain", "right");
  });
  server.on("/left", [](){
    Serial.println("left");
    steerAngle = 0;                                               // Adjust this angle for left steer as needed
    steerServo.write(steerAngle);
    server.send(200, "text/plain", "left");
  });
  server.on("/steerStop", [](){
    Serial.println("steerStop");
    steerAngle = 90;                                              // Set the center position, initially it will be 90
    steerServo.write(steerAngle);
    server.send(200, "text/plain", "steerStop");
  });

  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP Server Started");
}

void loop(void){
  server.handleClient();
}