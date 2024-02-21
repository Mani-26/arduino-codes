#include <AltSoftSerial.h>
#include <TinyGPS.h>
#include <SoftwareSerial.h>
#include <math.h>
#include <Wire.h>

//-------------Declaration of variables--------------------------------------

SoftwareSerial sim(2, 3); //make RX arduino line is pin 2, make TX arduino line is pin 3.
AltSoftSerial neogps;
TinyGPS gps;
String sms_status, sender_number, received_date, msg;
String latitude, longitude;

const String EMERGENCY_PHONE = "+918148067039";


#define x A1
#define y A2
#define z A3

//adxl337 accident detected or not
byte updateflag;

int xaxis = 0, yaxis = 0, zaxis = 0;
int deltx = 0, delty = 0, deltz = 0;
int vibration = 2, devibrate = 75;
int magnitude = 0;
int sensitivity = 20;
double angle;
boolean impact_detected = false;
//Used to run impact routine every 2mS.
unsigned long time1;
unsigned long impact_time;
unsigned long alert_delay = 30000;

//----------------------Setup function----------------------------------------

void setup() {

  Serial.begin(9600);
  sim.begin(9600);
  neogps.begin(9600);
  time1 = micros();
  xaxis = analogRead(x);
  yaxis = analogRead(y);
  zaxis = analogRead(z);
  sms_status = "";
  sender_number = "";
  received_date = "";
  msg = "";
  sim.println("AT"); //Check GSM Module
  delay(1000);
  //SendAT("AT", "OK", 2000); //Check GSM Module
  sim.println("ATE1"); //Echo ON
  delay(1000);
  //SendAT("ATE1", "OK", 2000); //Echo ON
  sim.println("AT+CPIN?"); //Check SIM ready
  delay(1000);
  //SendAT("AT+CPIN?", "READY", 2000); //Check SIM ready
  sim.println("AT+CMGF=1"); //SMS text mode
  delay(1000);
  //SendAT("AT+CMGF=1", "OK", 2000); //SMS text mode
  sim.println("AT+CNMI=1,1,0,0,0"); /// Decides how newly arrived SMS should be handled
  delay(1000);
  //SendAT("AT+CNMI=1,1,0,0,0", "OK", 2000); //set sms received format
  //AT +CNMI = 2,1,0,0,0 - AT +CNMI = 2,2,0,0,0 (both are same)

}

//----------------------------loop function-----------------------------

void loop() {
  if (micros() - time1 > 1999) Impact();
  if (updateflag > 0)
  {
    updateflag = 0;
    Serial.println("Impact detected!!");
    Serial.print("Magnitude:");
    Serial.println(magnitude);
    getGps();
    impact_detected = true;
    impact_time = millis();
  }
  if (impact_detected == true)
  {
    if (millis() - impact_time >= alert_delay) {
      makeCall();
      delay(1000);
      sendAlert();
      impact_detected = false;
      impact_time = 0;
    }
  }
  while (sim.available()) {
    parseData(sim.readString());
  }
  while (sim.available()) {
    sim.println(Serial.readString());
  }
}

//-------------------------------Impact function----------------------

void Impact()
{
  time1 = micros(); // resets time value
  int oldx = xaxis; //store previous axis readings for comparison
  int oldy = yaxis;
  int oldz = zaxis;

  xaxis = analogRead(x);
  yaxis = analogRead(y);
  zaxis = analogRead(z);


  //loop counter prevents false triggering. Vibration resets if there is an impact. Don't detect new changes until that "time" has passed.
  vibration--;
  if (vibration < 0) vibration = 0;

  if (vibration > 0) return;
  deltx = xaxis - oldx;
  delty = yaxis - oldy;
  deltz = zaxis - oldz;

  //Magnitude to calculate force of impact.

  magnitude = sqrt(sq(deltx) + sq(delty) + sq(deltz));
  if (magnitude >= sensitivity) //impact detected
  {
    updateflag = 1;
    // reset anti-vibration counter
    vibration = devibrate;
  }

  else
  {
    //reset magnitude of impact to 0
    magnitude = 0;
  }
}

//----------------------------------------------GPS function--------------------

void getGps() {
  boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 2000;) {
    while (neogps.available()) {
      if (gps.encode(neogps.read())) {
        newData = true;
        break;
      }
    }
  }

  if (newData) //If newData is true
  {
    latitude = String(gps.location.lat(), 6);
    //    longitude = String(gps.location.lng(), 6);
    newData = false;
  }
  else {
    Serial.println("No GPS data is available");
    latitude = "";
    longitude = "";
  }

  Serial.print("Latitude= "); Serial.println(latitude);
  Serial.print("Lngitude= "); Serial.println(longitude);
}

//--------------------------------parse function-----------------------------------------

void parseData(String buff) {
  Serial.println(buff);

  unsigned int len, index;
  index = buff.indexOf("\r");
  buff.remove(0, index + 2);
  buff.trim();
  if (buff != "OK") {
    index = buff.indexOf(":");
    String cmd = buff.substring(0, index);
    cmd.trim();

    buff.remove(0, index + 2);
    if (cmd == "+CMTI") {
      //get newly arrived memory location and store it in temp
      //temp = 4
      index = buff.indexOf(",");
      String temp = buff.substring(index + 1, buff.length());
      temp = "AT+CMGR=" + temp + "\r";
      //AT+CMGR=4 i.e. get message stored at memory location 4
      sim.println(temp);
    }
    //--------------------------------------------------------------
    else if (cmd == "+CMGR") {
      if (buff.indexOf(EMERGENCY_PHONE) > 1) {
        buff.toLowerCase();
        if (buff.indexOf("get gps") > 1) {
          getGps();
          String sms_data;
          sms_data = "GPS Location Data\r";
          sms_data += "http://maps.google.com/maps?q=loc:";
          sms_data += latitude + "," + longitude;

          sendSms(sms_data);
        }
      }
    }
  }
}

//-----------------------send alert-------------------

void sendAlert()
{
  String sms_data;
  sms_data = "Accident Alert!!\r";
  sms_data += "http://maps.google.com/maps?q=loc:";
  sms_data += latitude + "," + longitude;

  sendSms(sms_data);
}

//------------------------make call-------------------------

void makeCall()
{
  Serial.println("calling....");
  sim.println("ATD" + EMERGENCY_PHONE + ";");
  delay(20000); //20 sec delay
  sim.println("ATH");
  delay(1000); //1 sec delay
}

//------------------------send sms--------------------------
void sendSms(String text)
{
  //return;
  sim.print("AT+CMGF=1");
  delay(1000);
//  sim.print("AT+CMGS=\"" + EMERGENCY_PHONE + "\"\r");
  sim.print("AT+CMGS="); 
  sim.print("\"+EMERGENCY_PHONE\"");
  delay(1000);
  sim.print(text);
  delay(100);
  sim.write(0x1A); //ascii code for ctrl-26 //sim800.println((char)26); //ascii code for ctrl-26
  delay(1000);
  Serial.println("SMS Sent Successfully.");
}

//-----------------------------send ATfunction-------------------------

boolean SendAT(String at_command, String expected_answer, unsigned int timeout) {

  uint8_t x = 0;
  boolean answer = 0;
  String response;
  unsigned long previous;

  //Clean the input buffer
  while ( sim.available() > 0) sim.read();

  sim.println(at_command);

  x = 0;
  previous = millis();

  //this loop waits for the answer with time out
  do {
    //if there are data in the UART input buffer, reads it and checks for the asnwer
    if (sim800.available() != 0) {
      response += sim800.read();
      x++;
      // check if the desired answer (OK) is in the response of the module
      if (response.indexOf(expected_answer) > 0) {
        answer = 1;
        break;
      }
    }
  } while ((answer == 0) && ((millis() - previous) < timeout));

  Serial.println(response);
  return answer;
}
