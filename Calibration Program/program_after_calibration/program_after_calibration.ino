#define pin_ADC A0 // cek sensor terhubung pada pin A0
int zero_point;

void setup(){
  Serial.begin(9600);
  Serial.println("PASTIKAN BEBAN DALAM KONDISI OFF, SEBELUM KALIBRASI");
  delay(100);
  zero_point=512;  // didapatkan dari nilai zeropoint saat kalibrasi tanpa beban
  Serial.print("NILAI ADC TANPA BEBAN:");
  Serial.println(zero_point);
  delay(2000); 
}

void loop(){
  double nilai_adc_beban = get_adc(pin_ADC); // mencari nilai rata-rata adc dengan RMS
  //y = 0,028x - 0,0372 
  double current  = (0.028*nilai_adc_beban ) - 0.0372; // didapatkan dari hasil polinominal excel
  Serial.print("NILAI ADC DENGAN BEBAN: ");
  Serial.println(nilai_adc_beban);
  
  Serial.print("NILAI ARUS: ");
  Serial.println(current);

  
  delay(200);
}

int get_adc(int ampPin)
{
  int sampleDuration = 100;   
  int sampleCount = 0;
  unsigned long rSquaredSum = 0;
  int rawZero = zero_point;               
  uint32_t startTime = millis();  
  while((millis()-startTime) < sampleDuration)
  {
    int RawCurrentIn = analogRead(ampPin)- rawZero;
    rSquaredSum += abs(RawCurrentIn);
    sampleCount++;
  }
  rSquaredSum=rSquaredSum / sampleCount ;
  return (int) rSquaredSum;
}

int absolute(int a){
  if (a<0){a=a*-1;}
  return a;
}
