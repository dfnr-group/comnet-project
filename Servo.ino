#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <BlynkSimpleEsp32.h> 
#include <Servo.h>

Servo servo_blue, servo_black;

char auth[] = ""; //Blynk Authentication code//
char ssid[] = ""; //Wifi Username//
char pass[] = ""; //Wifi Password//
int pin_value;

void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.print("Connected to WiFi :");
  Serial.println(WiFi.SSID());
  Blynk.begin(auth, ssid, pass,"blynk-cloud.com",8080);
  servo_blue.attach(32); //connect servo blue to pin 14
  servo_black.attach(33); //connect servo black to pin 12
}

BLYNK_CONNECTED(){
  Blynk.syncVirtual(V1);
}
BLYNK_WRITE(V1)
{
  pin_value = param.asInt();
  Serial.println(pin_value);
  Blynk.virtualWrite(V5, pin_value);
}
void loop()
{
  Blynk.run();
}

BLYNK_WRITE(V2) //close

{
  servo_black.write(180);
  delay(2200);
  servo_black.write(90);
  //if (pin_value = 1)
    //servo_black.write(90);
}

BLYNK_WRITE(V3) //open

{
  servo_black.write(0);
  delay(1500);
  servo_black.write(90);
}

BLYNK_WRITE(V4)
{
  if (param.asInt())
    servo_blue.write(90);
  else
    servo_blue.write(0);
}
