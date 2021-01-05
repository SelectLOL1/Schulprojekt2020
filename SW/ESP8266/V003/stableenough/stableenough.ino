#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

unsigned char buf[20];
unsigned char opt_sensors;
int incomingByte = 0;
int loopCount = 0;
char showTemp = 1, showHum = 1, showLight = 1, showSound = 1, showCO2 = 1, showVOC = 1, showPwr = 1, showEvents = 0;

float sampPeriod = 500;

const char* ssid = "iOsw8tVh3w2";
const char* password = "password :)";

// Change the variable to your Raspberry Pi IP address, so it connects to your MQTT broker
const char* mqtt_server = "192.168.25.203";

// Initializes the espClient. You should change the espClient name if you have multiple ESPs running in your home automation system
WiFiClient espClient;
PubSubClient client(espClient);

// Timers auxiliar variables
long now = millis();
long lastMeasure = 0;

// Don't change the function below. This functions connects your ESP8266 to your router
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}

// This functions is executed when some device publishes a message to a topic that your ESP8266 is subscribed to
// Change the function below to add logic to your program, so when a device publishes a message to a topic that
// your ESP8266 is subscribed you can actually do something
void callback(String topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  Serial.println();
}

// This functions reconnects your ESP8266 to your MQTT broker
// Change the function below if you want to subscribe to more topics with your ESP8266
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    /*
      YOU MIGHT NEED TO CHANGE THIS LINE, IF YOU'RE HAVING PROBLEMS WITH MQTT MULTIPLE CONNECTIONS
      To change the ESP device ID, you will have to give a new name to the ESP8266.
      Here's how it looks:
       if (client.connect("ESP8266Client")) {
      You can do it like this:
       if (client.connect("ESP1_Office")) {
      Then, for the other ESP:
       if (client.connect("ESP2_Garage")) {
      That should solve your MQTT multiple connections problem
    */
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe or resubscribe to a topic
      // You can subscribe to more topics (to control more LEDs in this example)
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(1000);
    }
  }
}

// The setup function sets your ESP GPIOs to Outputs, starts the serial communication at a baud rate of 115200
// Sets your mqtt broker and sets the callback function
// The callback function is what receives messages and actually controls the LEDs
void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  Wire.begin();
}

// For this project, you don't need to change anything in the loop function. Basically it ensures that you ESP is connected to your broker
void loop() {
  if (!client.connected()) {
    delay(random(150, 500));
    reconnect();
  }
  if (!client.loop())
    client.connect("ESP8266Client");

  now = millis();
  // Publishes new temperature and humidity every 30 seconds
  if (now - lastMeasure > 1000) {
    // All sensors except the CO2 sensor are scanned in response to this command
    Wire.beginTransmission(0x2A); // transmit to device
    // Device address is specified in datasheet
    Wire.write(byte(0xC0));       // sends instruction to read sensors in next byte
    Wire.write(0xFF);             // 0xFF indicates to read all connected sensors
    Wire.endTransmission();       // stop transmitting
    // Delay to make sure all sensors are scanned by the AmbiMate
    delay(100);

    Wire.beginTransmission(0x2A); // transmit to device
    Wire.write(byte(0x00));       // sends instruction to read sensors in next byte
    Wire.endTransmission();       // stop transmitting
    Wire.requestFrom(0x2A, 15);    // request 6 bytes from slave device

    // Acquire the Raw Data
    unsigned int i = 0;
    while (Wire.available()) { // slave may send less than requested
      buf[i] = Wire.read(); // receive a byte as character and store in buffer
      i++;
    }

    unsigned int status = buf[0];
    float temperatureC = (buf[1] * 256.0 + buf[2]) / 10.0;
    float humidity = (buf[3] * 256.0 + buf[4]) / 10.0;
    unsigned int light = (buf[5] * 256.0 + buf[6]);
    float batVolts = ((buf[9] * 256.0 + buf[10]) / 1024.0) * (3.3 / 0.330);
    unsigned int co2_ppm = (buf[11] * 256.0 + buf[12]);
    unsigned int voc_ppb = (buf[13] * 256.0 + buf[14]);
    byte macaddr[6];
   
    WiFi.macAddress(macaddr);

    lastMeasure = now;

    // Check if any reads failed and exit early (to try again).
    if (isnan(humidity) || isnan(temperatureC) || isnan(co2_ppm) || isnan(voc_ppb)){
      Serial.println("Failed to read from sensor!");
      return;
    }

    char temperatureTemp[7];
    dtostrf(temperatureC, 6, 2, temperatureTemp);

    char humidityHum[7];
    dtostrf(humidity, 6, 2, humidityHum);
   
    char co2_ppmCO2[7];
    dtostrf(co2_ppm, 6, 2, co2_ppmCO2);

    char voc_ppbVOC[7];
    dtostrf(voc_ppb, 6, 2, voc_ppbVOC);

    char readytofuckingsend[85];
    const char *charmcaddr = reinterpret_cast<const char*>(macaddr);
    char myshitdelimiter[2] = {179,179};
    
    strcpy(readytofuckingsend,charmcaddr);
    strcat(readytofuckingsend,myshitdelimiter);
    strcat(readytofuckingsend,temperatureTemp);
    strcat(readytofuckingsend,myshitdelimiter);
    strcat(readytofuckingsend,humidityHum);
    strcat(readytofuckingsend,myshitdelimiter);
    strcat(readytofuckingsend,co2_ppmCO2);
    strcat(readytofuckingsend,myshitdelimiter);
    strcat(readytofuckingsend,voc_ppbVOC);
    strcat(readytofuckingsend,myshitdelimiter);
    
    Serial.println(readytofuckingsend);
    // Publishes Temperature and Humidity values
    client.publish("room/HoleInTheWall", readytofuckingsend);

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t Temperature: ");
    Serial.print(temperatureC);
    Serial.println("*C ");
    Serial.print(WiFi.macAddress());
    Serial.print("   ");
    Serial.print("co2 in ppm: ");
    Serial.println(co2_ppm);
    Serial.print("VOC in ppb: ");
    Serial.println(voc_ppb);
  }
}
