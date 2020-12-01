const int inputPin= 2;

void setup(){
pinMode(inputPin, INPUT);
Serial.begin(9600); // Starts the serial communication
Serial.print("Initialized ");
}

void loop(){
int value= digitalRead(inputPin);


if (value == HIGH)
{
  Serial.print("Movement ");
}

}
