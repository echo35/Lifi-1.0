int readPIN = 2;
int ledPIN = 13;
int bit_1_time = 800;
int bit_0_time = 100;
int high_flag = 0;
unsigned long high_time = 0;
unsigned long pulse_time = 0;
int pulses_caught = 0;
String str;

void setup() {
  Serial.begin(4800);
  while (!Serial);
  pinMode(readPIN, INPUT_PULLUP);
  pinMode(ledPIN, OUTPUT); 
  Serial.println("Receiver Ready");
}

void loop() {
  receive();
}

void receive() {
  if (!Serial.available()) return;
  
  bool readValue = !digitalRead(readPIN);
  if (readValue == HIGH) {
    high_flag = 1;
    if(high_time == 0) 
      high_time = micros();
  }
  else if (high_flag == 1) {
    pulse_time = micros() - high_time;
    high_time = 0;
    high_flag = 0;
    
    if(pulse_time >= bit_1_time - 0)
      append('1');
    else //if(pulse_time >= bit_0_time) 
      append('0');

    if(str.length() == 8) {
      convertBin(1);  
      str = "";
    }
  }
}


void append(char _bit)
{
  if(millis() < 1000)
    return;
  
  str += _bit;  
}

void convertBin(int printout)
{
  byte ascii = 0;
  int base = 0;
  for(int b = str.length()-1; b >= 0; b--) {
    int bite = 0;
    if(str.charAt(b) == '1')
      bite = 1;
    ascii += (bite * (1<<base));
    base++;
  }
  if(printout == 1)
    Serial.print((char) ascii);
}

