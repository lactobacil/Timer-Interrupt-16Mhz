/*
 * Task 1
1) For the ATMega328P (16MHz) micro-controller find which registers to set for a timer to trigger an interrupt after 1.02 seconds and
write a function in C to set these to the required values. 
Also comment each line of code to say what it does. 
The code does not need to be tested but should be proper C syntax and logically correct.
We would like the timer used to be at the highest resolution possible. With the highest efficiency code.
2) Write a function to increment a counter variable called “itter” each time the timer interrupt is called. 
You should declare the variable in the global scope and assume it is used by other areas of code, 
not just the interrupt.
 */

// Tested the code with atmega328p, should find and oscilloscope to test the timing
// Declare Variables as they could be accessed in other places. 
// Good practice is to use volatile for dealing with interrupt integers. 
volatile int itter;
//volatile bool flag = 0; //flag for testing
volatile bool LED = false; 

//Declare Timing variables to test time elapsed
unsigned long StartTime;
unsigned long EndTime;

void setup() {
  // put your setup code here, to run once

  Serial.begin(9600); //Set serial for testing, and baudrate to 9600
  pinMode(13, OUTPUT); // 
  
  cli(); //Disable all the interrupts for setup, as nothing will be triggerred during setup.
  
  //Initiate TCCR1A and TCCR1B, set all the bit in register to 0 to reset, since default is 1.
  TCCR1A = B00000000;
  TCCR1B = B00000000;
  
  //Configure Prescaler by assigning the bits, set prescaler to 256
  TCCR1B |= (1 << CS12);
  
  //Set register of the register A to compare with OCR1A variable, set enable bit
  TIMSK1 |= (1 << OCIE1A);

  //Count the timer for 1.02 seconds, then trigger the interrupt
  // for prescaler 256, Pulse Time 1/62.5 khz = 16us. 
  // 1.02s -> 1020 ms then, 1020ms/16us = 63750 (Max 65535 to keep resolution at its finest)
  // If prescaler is 1024, then the reload is around 15500, however, good practice is to keep the reload value close to 65535 for better resolution
  OCR1A = 63750;
  
  sei(); //Enable all the interrupts back again. 
  StartTime = millis();
}


//TIMER1 Calls an ISR for after 1020ms or 1.02 seconds, the matching interrupt is TIMER1_COMPA_vect, disable interrupt if calling only once is needed.
ISR(TIMER1_COMPA_vect){
  TCNT1  = 0; //Reset the timer in TCNT1 register to zero as the counter have reached the count.
  itter++; //Itter Increment every 1.02 seconds, declared globally
  LED = !LED; // LED for testing 
  digitalWrite(13,LED); //Write the built in LED (D13)

  
  //Testing the time. I know it's bad to put print function or string manipulations to an interrupt, but this is for testing, without oscilloscope. 
  EndTime = millis();
}

void loop() {
  //Asynchronous printer with the isr to test the timer, and the variable of itter. 
  Serial.println(EndTime - StartTime);
  Serial.println("\n");
  Serial.println(itter);
  
}
