#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#define addr_puluhan 0
#define addr_satuan 1

#define durasi 2
#define pin_relay1 6
#define pin_relay3 4
#define pin_relay2 5
#define pin_relay4 3
#define pin_up A0
#define pin_down A1
#define pin_arus A2
#define pin_tegangan A3
#define increament 5
#define max 80
#define min 0

#define relay1_on digitalWrite(pin_relay1,LOW)
#define relay1_off digitalWrite(pin_relay1,HIGH)

#define relay2_on digitalWrite(pin_relay2,LOW)
#define relay2_off digitalWrite(pin_relay2,HIGH)

#define relay3_on digitalWrite(pin_relay3,LOW)
#define relay3_off digitalWrite(pin_relay3,HIGH)

#define relay4_on digitalWrite(pin_relay4,LOW)
#define relay4_off digitalWrite(pin_relay4,HIGH)

#define up !digitalRead(pin_up)
#define down !digitalRead(pin_down)


double set_point=0;
double tegangan,arus;
double zero_arus;
double zero_tegangan;
int puluhan,satuan;

LiquidCrystal_I2C lcd(0x27, 16, 2);

bool sudah;

void setup()
{

Serial.begin(9600);
pinMode(pin_relay1,OUTPUT);
pinMode(pin_relay3,OUTPUT);
pinMode(pin_relay2,OUTPUT);
pinMode(pin_relay4,OUTPUT);

pinMode(pin_up,INPUT_PULLUP);
pinMode(pin_down,INPUT_PULLUP);


lcd.begin();
lcd.backlight();

zero_arus=analogRead(pin_arus);
zero_tegangan = 501 ; //analogRead(pin_tegangan);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Zero I:");
lcd.print(zero_arus);
lcd.setCursor(0,1);
lcd.print("Zero V:");
lcd.print(zero_tegangan);
lcd.print("  ");


delay(2000);
puluhan= EEPROM.read(addr_puluhan);
satuan = EEPROM.read(addr_satuan);

set_point = puluhan + (satuan/100);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Setpoint:");
lcd.setCursor(0,1);
lcd.print(set_point);
lcd.print("  ");
delay(2000);
}

void xloop(){
  lcd.setCursor(0,0);
  lcd.print("I:");
  lcd.print(arus);
  lcd.print(" V:");
  lcd.print(analogRead(pin_tegangan));
  lcd.print("  ");
  delay(200);
}

double daya;
int count=1;
long last_millis;

void loop(){
  tegangan =get_voltage(pin_tegangan);
  arus =get_current(pin_arus);
  if (up){
    set_point=set_point+increament;
    if (set_point>255){set_point=255;}
    puluhan = floor(set_point);
    satuan= (set_point-puluhan)*100;
    EEPROM.write(addr_puluhan,puluhan);
    EEPROM.write(addr_satuan,satuan);
 
    delay(200);
  }else if (down){
    set_point=set_point-increament;
    if (set_point<min){set_point=min;}
    puluhan = floor(set_point);
    satuan= (set_point-puluhan)*100;
    EEPROM.write(addr_puluhan,puluhan);
    EEPROM.write(addr_satuan,satuan);
 
    delay(200);
  }

  daya = arus*tegangan;
  
  if ((millis()-last_millis)>2000){
  if (daya<=set_point){
    if (sudah==false){
    count++;
    }
  }else {
    sudah=true;
    count--;
  }
  if (count>4){count=4;}
  else if (count<0){count=0;}
  last_millis=millis();
  }

  if (count==0){
    relay1_off;
    relay2_off;
    relay3_off;
    relay4_off;
  }else if (count==1){
    relay1_on;
    relay2_off;
    relay3_off;
    relay4_off;
  }else if (count==2){
    relay1_on;
    relay2_on;
    relay3_off;
    relay4_off;
  }else if (count==3){
    relay1_on;
    relay2_on;
    relay3_on;
    relay4_off;
  }else if (count==4){
    relay1_on;
    relay2_on;
    relay3_on;
    relay4_on;
  }



  lcd.setCursor(0,0);
  lcd.print("I:");
  lcd.print(arus);
  lcd.print(" V:");
  lcd.print((int)tegangan);
  lcd.print(" L:");
  lcd.print(count);
  lcd.print("   ");
  

  lcd.setCursor(0,1);
  lcd.print("P:");
  lcd.print(daya);
  lcd.print(" SP:");
  lcd.print(set_point);
  lcd.print("   ");
  
}

int get_voltage(int ampPin)
{
  int sampleDuration = 100;   
  int sampleCount = 0;
  unsigned long rSquaredSum = 0;
  int rawZero = zero_tegangan;               
  uint32_t startTime = millis();  
  while((millis()-startTime) < sampleDuration)
  {
    int RawVoltageIn = analogRead(ampPin)- rawZero;
    rSquaredSum += abs(RawVoltageIn);
    sampleCount++;
  }
  rSquaredSum=rSquaredSum / sampleCount ;
  // y = 2,4653x - 20,575
  double voltage  = (2.4653*rSquaredSum) - 20.575;
  if (voltage<0){voltage=0;}
  return (int) voltage;
}

int absolute(int a){
  if (a<0){a=a*-1;}
  return a;
}
float get_current(int ampPin)
{
  int sampleDuration = 100;   
  int sampleCount = 0;
  unsigned long rSquaredSum = 0;
  int rawZero = zero_arus;               
  uint32_t startTime = millis();  
  while((millis()-startTime) < sampleDuration)
  {
    int RawCurrentIn = analogRead(ampPin) - rawZero;
    rSquaredSum += abs(RawCurrentIn);
    sampleCount++;
  }
  rSquaredSum = rSquaredSum / sampleCount;
  //y = 0,028x - 0,0372

   double current  = (0.028*rSquaredSum ) - 0.0372;
   if (current<0){current=0;}
  return current;
}
