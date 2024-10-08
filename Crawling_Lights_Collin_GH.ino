/*
Code written by Collin Milliron

This code is written for the Arduino platform. This program was tested on the Elegoo UNO R3

Hook up a Pot with the wiper plugged into A0

Hook up LED's from outputs 3, 6, 9, 10, 11 each through a resistor to Ground

*/

// These constants won't change. They're used to give names to the pins used:

int Pot = A0;  // Analog input pin that the potentiometer is attached to
int Red = 3; // Analog output pin connected to LED red
int Yellow = 6; // Analog output pin connected to LED yellow
int Green = 9; // Analog output pin connected to LED green
int Blue = 10; // Analog output pin connected to LED blue
int White = 11; // Analog output pin connnected to LED white

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
int multiplier = 0;	//Once the total physical range of the wiper is divided by 5, the multiplier allows the LED to shine at full brightness at the end of each cycle by boosting voltage by a factor of 5
int limiter = 0;	//Such reckless boosting of voltage on my part, amirite? ^^^^. Tsk tsk. The limiter limits the total multiplied voltage sent to the LED to 5v maximum. Perhaps this is not necessary, but am I such a fool for wanting to protect my investments? I practically went into bankrupcy trying to afford this $30 Arduino so goddamnit I'll be careful if I want to.

//Bitch. I love you

void setup() {
  // Initialize Serial Output
  Serial.begin(9600);
  // initialize analog pins powering the LEDs as an output.
  pinMode(3, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {

  // read the analog in value:
  sensorValue = analogRead(Pot);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  // change the analog out value:

//White LED
int multiplier = outputValue * 5;
int limiter = min(multiplier, 255);

//Other LEDs
int blueCycle = constrain(outputValue, 51, 101);
int blueValue = map(blueCycle, 51, 101, 0, 255);

int greenCycle = constrain(outputValue, 102, 153);
int greenValue = map(greenCycle, 102, 153, 0, 255);

int yellowCycle = constrain(outputValue, 154, 205);
int yellowValue = map(yellowCycle, 154, 205, 0, 255);

int redCycle = constrain(outputValue, 206, 255);
int redValue = map(redCycle, 206, 255, 0, 255);

//Logic

if (outputValue >= 0) {
  analogWrite(White, limiter);    // White LED
}

if (51 <= outputValue <= 101) {    //Blue LED
  analogWrite(Blue, blueValue);    // LED on
}
else if (51 > outputValue) {
  analogWrite(Blue, 0);    // LED off
}

if (102 <= outputValue <= 153) {	//Green LED
  analogWrite(Green, greenValue);    // LED on
}
else if (102 > outputValue) {
  analogWrite(Green, 0);    // LED off
}

if (154 <= outputValue <= 205) {	//Yellow LED
  analogWrite(Yellow, yellowValue);    // LED on
}
else if (154 > outputValue) {
  analogWrite(Yellow, 0);    // LED off
}

if (206 <= outputValue <= 255) {	//Red LED
  analogWrite(Red, redValue);    // LED on
}
else if (206 > outputValue) {
  analogWrite(Red, 0);    // LED off
}

//Print sensor value and delay 1ms

  Serial.println(sensorValue);
  delay(1); 
}