int sensorPin = A0;    // Select input pin for the FSR.
int motorPin = 8;      // Select output pin for the motor.
int sensorValue = 0;  // Store FSR value here.
int threshold = 50; // Set a threshold for minimum FSR active state. 
int peakValue = 0; // Start peakValue for FSR at 0.e
int noise = 5; // Keep little fluctuations and signal noise from messing things up. 
int potPin = A3; // Select input pin for potentiometer. 
float potValue = 0; // Start potentiometer value at zero.

void setup() {
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600); // Start serial communication
  
}

void loop() {
  sensorValue = analogRead(sensorPin); // Read FSR.
  sensorValue=map(sensorValue, 0, 1023, 0, 255); // Map FSR to analog output levels.
  potValue=analogRead(potPin); // Read potentiometer.
  potValue=map(potValue, 0, 1023, 0, 100); // Map pot to multiplier that will be used below to control the sensistivity of the FSR (kind of like a wet/dry mixer).
  potValue=potValue / 100; // Turn pot value into a percentage.
  sensorValue=sensorValue * potValue; // 
 
  Serial.print(sensorValue); Serial.println(" # "); // Print how hard I am squeezing in serial monitor. 
  Serial.print(potValue); Serial.println(" x "); // Print how I am adjusting range w/ potentiometer in serial monitor.
  
  if (sensorValue > peakValue) {
    peakValue = sensorValue;
  } // Look for new peak. 
     
      if (sensorValue <= threshold - noise) { // When there is a dip in the FSR...
      if (peakValue > threshold + noise) { // you have a new peak value:
      Serial.println(peakValue);
      // reset the peak variable:
      peakValue = 0;
    }
     analogWrite(motorPin, 0); // Keep a gentle breeze from turning my motor on.
  }
     if (sensorValue > threshold){ // Don't let a light breeze turn motor on. 
        analogWrite(motorPin, peakValue); // Turn motor at speed that's based on FSR value.
     }
     delay(100); // Let's keep from making this motor jump speeds like crazy. 
}

