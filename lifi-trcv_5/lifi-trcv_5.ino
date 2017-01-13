unsigned long pulse_int = 1000; // Micros. Length of a pulse interrupt.
unsigned long pulse_1 = 800; // Micros. Length of a 1 pulse;
unsigned long pulse_0 = 100; // Micros. Length of a 0 pulse.
unsigned long next_interrupt = 0; // Micros. Wait until this time to pulse again. 

void setup() 
{
  Serial.begin(4800);
  while(!Serial);
  pinMode(13, OUTPUT);
  Serial.println("Emitter Ready");
}

void loop() 
{
  if (!Serial.available()) return;
  Serial.setTimeout(10); // small timeout to read bytes as they are written
  String ascii_str = Serial.readString();
  for(int i = 0; i < ascii_str.length(); i++) {
    transmit_byte((int) ascii_str[i]);
  }
  Serial.print("OK\r\n"); // feedback for the client
}

void transmit_byte(int c)
{
  for (int order = 7; order >= 0; order--) {
    if ((c & (1<<order)) != 0) {
      while (pulse('1') == 1);
    }
    else {
      while (pulse('0') == 1);
    }
    while (pulse('i') == 1);
  }
}

int pulse(char sig)
{
  if(micros() < next_interrupt) // If delay not elapsed...
    return 1; // Wait longer

  if(sig == '1')  // ON signal
    next_interrupt = micros() + pulse_1; // Wait the appropriate time
  else if(sig == '0') // OFF signal
    next_interrupt = micros() + pulse_0; // Wait the appropriate time
  else if(sig == 'i') // Interrupt signal
    next_interrupt = micros() + pulse_int;  // Wait the interrupt time
  
  digitalWrite(13, (sig == 'i') ? LOW : HIGH); // LED on
  return 0;
}

