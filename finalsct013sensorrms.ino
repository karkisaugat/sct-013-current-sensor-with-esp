float sensor = 33;
long lastsample = 0;
long Samplesum = 0;
long Samplecount = 0;
float s;
float vpc = (3.3 / 4095) * 1000; 

void setup() {
  Serial.begin(115200);
  pinMode(sensor, INPUT);
}

void loop() {
  if (millis() > lastsample) {
    s = analogRead(sensor)-2990;
 
  
    float y = s * vpc;
    Samplesum += y * y; 
    Samplecount++;
    lastsample = millis();
  }
  
  if (Samplecount == 1000) {
    float mean = Samplesum / Samplecount;
    float rms = sqrt(mean);
    float mV = rms / 30; 
    

   float y1= (-0.02515 *mV*mV)+ (1.546 *mV)-0.8228 ;// data callibration
    if (y1 <= 0.2) {
      y1 = 0;
    } else {
      y1 -= 0.2;
    }
    Serial.println(y1,1);
    
    Samplesum = 0;
    Samplecount = 0;
  }
}
