// library initialization
#include <SoftwareSerial.h> // calls a library called SoftwareSerial.h
#include <TinyGPS++.h> // calls a library called TinyGPS++.h

// object initialization
SoftwareSerial gpsSerial(8,9); // 8 As RXD pin, 9 As TXD pin -> Arduino Pro Micro to GPS Module Sensor
TinyGPSPlus gps; // create an object with the name gps

// variable initialization
double lat, lng; // data with double type is used for GPS sensor purposes
String latitude, longitude; // data with String type is used for GPS sensor purposes

// Method: setup
void setup() {
  Serial.begin(9600); // start serial communication inside the Arduino Pro Micro
  Serial1.begin(9600); // start serial communication to Wemos D1 Mini
  gpsSerial.begin(9600); // start serial communication to GPS Module Sensor
}

// Method: loop
void loop() {  
  sensor(); // calling the sensor method
  view_data(); // calling the view_data method
  send_data(); // calling the send_data method
}

// Method: sensor
void sensor(){
  if(gpsSerial.available()){
    while (gpsSerial.available()){ // if there is serial communication from the GPS sensor then
      gps.encode(gpsSerial.read()); // reading GPS data
      if (gps.location.isValid()){ // if the GPS location is valid then
        lat = (gps.location.lat()); // this float variable is to hold gps data -> latitude
        lng = (gps.location.lng()); // this float variable is to hold gps data -> longitude
      }      
    }
  }
//  lat = -7.3364958; lng = 112.6367014; // dummy Data
  latitude = String(lat, 6); // this string variable is to hold gps data -> latitude
  longitude = String(lng, 6); // this string variable is to hold gps data -> longitude
  delay(1000); // delay -> 1 second
}

// Method: view_data
void view_data(){
  // display data to the Arduino Pro Micro serial monitor
  Serial.println("Transmit serial data to Wemos D1 Mini...");
  Serial.println("latitude : " + latitude + "\nlongitude : " + longitude + "\n");
  delay(7000); // delay -> 7 second
}

// Method: send_data
void send_data(){
  // send data from Arduino Pro Micro to Wemos D1 Mini
  Serial1.print(latitude+","+longitude);
}
