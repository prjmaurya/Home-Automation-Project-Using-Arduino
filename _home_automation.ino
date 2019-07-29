#include<Servo.h> 
int LED = 13; // Use the onboard Uno LED
int obstaclePin1 = 7;  // This is our input pin
int obstaclePin2 = 8;  // This is our input pin
int hasObstacle1 = HIGH;  // HIGH MEANS NO OBSTACLE
int hasObstacle2 = HIGH;  // HIGH MEANS NO OBSTACLE
int led_pin = 12 ;// initializing the pin 9 as the led pin
int led = 11;                // the pin that the LED is atteched to
int sensor = 4;              // the pin that the sensor is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)
int flame_sensor_pin = 9 ;// initializing pin 12 as the sensor output pin
int flame_pin = HIGH ; // state of sensor
int input = A1;
int output = 10;
int th=500; // Set threshold level.

int sensor_pin = A0; // Soil Sensor input at Analog PIN A0
int output_value ;


Servo servo_test;
void setup() {
  servo_test.attach(3);
  pinMode(output,OUTPUT);
  digitalWrite(output,LOW);
  pinMode(led, OUTPUT);      // initalize LED as an output
  pinMode(sensor, INPUT);    // initialize sensor as an input
  pinMode(LED, OUTPUT);
  pinMode(obstaclePin1, INPUT);
  pinMode(obstaclePin2, INPUT);
  pinMode ( led_pin , OUTPUT ); // declaring led pin as output pin
  pinMode ( flame_sensor_pin , INPUT ); // declaring sensor pin as input pin for Arduino

  pinMode(5,OUTPUT);
  Serial.println("Reading From the Sensor ...");

  delay(100);

  Serial.begin(9600);  
}




void loop() {
  hasObstacle1 = digitalRead(obstaclePin1);//Reads the output of the obstacle sensor from the 7th PIN of the Digital section of the arduino
  hasObstacle2 = digitalRead(obstaclePin2);
  if (hasObstacle1 == HIGH || hasObstacle2 == HIGH) //LOW means something is ahead, so illuminates the 13th Port connected LED
  {
    Serial.println("Someone is on the door!!");
    digitalWrite(LED, HIGH);//Illuminates the 13th Port LED
    servo_test.write(91);
  }
  else
  {
//    Serial.println("Path is clear");
    digitalWrite(LED, LOW);
    servo_test.write(4);
  }
  delay(100);
  flame_pin = digitalRead ( flame_sensor_pin ) ; // reading from the sensor
  if (flame_pin == LOW ) // applying condition
  {
  Serial.println ( " FLAME , FLAME , FLAME " ) ;
  digitalWrite ( led_pin , HIGH ) ;// if state is high, then turn high the led  
  }

  else
  {
//  Serial.println ( " no flame " ) ;
  digitalWrite ( led_pin , LOW ) ; // otherwise turn it low
  }
  delay(100);
  val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
    digitalWrite(led, HIGH);   // turn LED ON
//    delay(100);                // delay 100 milliseconds 
    
    if (state == HIGH) {
      Serial.println("Motion detected!"); 
      state = LOW;       // update variable state to HIGH
    }
  } 
  else {
      digitalWrite(led, LOW); // turn LED OFF
//      delay(50);             // delay 200 milliseconds 
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
    }
  }
  delay(100);

//    Serial.println(analogRead(input));
  if(analogRead(input)>70){
//    digitalWrite(output,HIGH);
    Serial.println("Impurity level slightly increased!!");
  }
  else if(analogRead(input)>100 ){
    Serial.println("Impurity level increased more!!");
  }
  else if(analogRead(input)>150 ){
    Serial.println("Impure air!!");
  }
  else if(analogRead(input)>200 ){
    Serial.println("Not good for breathing!!");
  }
  else if(analogRead(input)>th){
    Serial.println("Highly Impure Air!!");
    digitalWrite(output,HIGH);
  }
  else
  {
    digitalWrite(output,LOW);
  }
  delay(100);

  output_value= analogRead(sensor_pin);

 output_value = map(output_value,550,10,0,100);

   Serial.print("Mositure : ");

   Serial.print(output_value);

   Serial.println("%");

   if(output_value>0){
      digitalWrite(5,HIGH);
     }
     else{
            digitalWrite(5,LOW);
     }
   delay(1000);

}




