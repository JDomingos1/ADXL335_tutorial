int xInput = A0; // the A0 pin is connected to xinput
int yInput = A1; // the A1 pin is connected to yinput
int zInput = A2; // the A2 pin is connected to zinput

// initialize minimum and maximum Raw Ranges for each axis
int RawMin = 0;
int RawMax = 1023;

// Take multiple samples to reduce noise
const int sampleSize = 10;

void setup() 
{
  analogReference(EXTERNAL); //connect 3.3v to AREF
  Serial.begin(9600); // Start serial communication
}

void loop() 
{
  //Read raw values
  int xRaw = ReadAxis(xInput);
  int yRaw = ReadAxis(yInput);
  int zRaw = ReadAxis(zInput);

  // Convert raw values to 'milli-Gs"
  long xScaled = map(xRaw, RawMin, RawMax, -3000, 3000);
  long yScaled = map(yRaw, RawMin, RawMax, -3000, 3000);
  long zScaled = map(zRaw, RawMin, RawMax, -3000, 3000);

  // re-scale to fractional Gs
  float xAccel = xScaled / 1000.0;
  float yAccel = yScaled / 1000.0;
  float zAccel = zScaled / 1000.0;
  // Output data to serial monitor
  Serial.println("3 Axis Lecture");
  Serial.println("--------------------------------------------------------");
  Serial.print("X: ");
  Serial.print(xRaw);
  Serial.print("; ");
  Serial.print("| ");
  Serial.print(xAccel,0);
  Serial.println("G; ");
  Serial.print("Y: ");
  Serial.print(yRaw);
  Serial.print("; ");
  Serial.print("| ");
  Serial.print(yAccel,0);
  Serial.println("G; ");
  Serial.print("Z: ");
  Serial.print(zRaw);
  Serial.print("; ");
  Serial.print("| ");
  Serial.print(zAccel,0);
  Serial.println("G; ");
  Serial.println("--------------------------------------------------------");
  



  delay(1000);
}

// Take samples and return the average
int ReadAxis(int axisPin)
{
  long reading = 0;
  analogRead(axisPin); // Read the axis pin
  delay(1);
  for (int i = 0; i < sampleSize; i++)
  {
  reading += analogRead(axisPin);
  }
  return reading/sampleSize;
}
