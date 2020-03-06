 //#include<Adafruit_Sensor.h>
#include<Thing.h>
#include<WebThingAdapter.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const int oneWireBus = 0; 
OneWire oneWire(oneWireBus);
DallasTemperature Data(&oneWire);

const char* ssid = "geomeo/webtoall";
const char* password = "ASDFGHJKL";

const String mDNSHostname = "temp";

WebThingAdapter* adapter;

const char *senTypes[] = {"TemperatureSensor",nullptr};
ThingDevice sensors("DS18B20","DS18B20 Weather Sensor",senTypes);
ThingProperty sensortemp("temperature","",NUMBER, "TemperatureSensor");
void setup(){
Serial.begin(115200);
Serial.println("temp value");

//if ( Data.begin() ){
// Serial.println("not initilize Sensor");
// while(1);
//  }

// connect to wifi AP
 Serial.println("Connecting to");
 Serial.println(ssid);
 WiFi.mode(WIFI_STA); 
 WiFi.begin(ssid,password);
 while ( WiFi.status() !=WL_CONNECTED )  {
  delay(500);
  Serial.println(".");
 }
 Serial.println();

 //Show connection details
  Serial.println("Connected!");
  Serial.println("IP address:");
  Serial.println(WiFi.localIP());
  
//Create new webthings connection handle()
adapter = new WebThingAdapter(mDNSHostname,WiFi.localIP());
  
  sensors.addProperty(&sensortemp);
  adapter->addDevice(&sensors);
  adapter->begin();
 Serial.println("Http server started");
 Serial.println("http://");
 Serial.print(WiFi.localIP());
 Serial.print("/things/");
 Serial.print(sensors.id);
   
}

void loop(){
  Data.requestTemperatures();
  ThingPropertyValue tpVal;
  float temp;

  //read sensor values
  temp = Data.getTempCByIndex(0); 
  Serial.println(temp);
  tpVal.number = temp;
  sensortemp.setValue(tpVal);

adapter->update();

  // do nothing for a bit
  delay(1000);
  
}
