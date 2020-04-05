// Array of pins for the columns
// This is the part that cycles through
int cPins[] = {11, 12, 13};

// Number of pins in the column array
int cPinsNo = 3;

// Array of pins for the rows
int rPins[] = {8, 9, 10};

// Number of pins in the row array
int rPinsNo = 3;

// Array for the last known switch states [cPinsNo][rPinsNo]
int colPrev[3][3] = {0};

// Key codes to be used for each button
// (see table above for codes to use)
// (columns and rows are transposed on device)
uint8_t buttonCodes[3][3] = {
  {1, 2, 3},
  {4, 5, 6},
  {7, 8, 9}
};

void setup()
{
  //Start Serial
  Serial.begin(9600);
  Serial.println("Multiplexed Buttons Test");

  //Set the Column Pin Mode
  Serial.println("Setting Column Pins...");

  for (int cPin = 0; cPin < cPinsNo; cPin++)
  {
    pinMode(cPins[cPin], OUTPUT);
    digitalWrite(cPins[cPin], HIGH);
  }

  //Set the Row Pin Mode
  Serial.println("Setting Row Pins...");

  for (int rPin = 0; rPin < rPinsNo; rPin++)
  {
    pinMode(rPins[rPin], INPUT);
    digitalWrite(rPins[rPin], HIGH);
  }
  Serial.println("Ready!");
}

void loop()
{
  // Loop through the columns
  for (int cPin = 0; cPin < cPinsNo; cPin++)
  {
    digitalWrite(cPins[cPin], LOW);

    // Loop through the rows
    for (int rPin = 0; rPin < rPinsNo; rPin++)
    {
      //Check if each switch is pressed
      if (digitalRead(rPins[rPin]) == LOW)
      {
        // Check to see if the state has changed since last time
        if (colPrev[cPin][rPin] == 0)
        {
          // Do action here, switch is on
          Serial.print("|x:");
          Serial.print(cPins[cPin]);
          Serial.print(" |");
          Serial.print("y:");
          Serial.print(rPins[rPin]);
          Serial.print(" |");
          Serial.print("State: ON");
          Serial.print("  |");
          Serial.print("represents:");
          Serial.println(buttonCodes[cPin][rPin]);


          // Update last known state of this switch
          colPrev[cPin][rPin] = 1;
        }
      }
      else {

        // Check to see if the state has changed since last time
        if (colPrev[cPin][rPin] == 1)
        {
          // Do action here, switch is off
          Serial.print("|x:");
          Serial.print(cPins[cPin]);
          Serial.print(" |");
          Serial.print("y: ");
          Serial.print(rPins[rPin]);
          Serial.print(" |");
          Serial.print("State: OFF");
          Serial.print("  |");
          Serial.print("represents:");
          Serial.println(buttonCodes[cPin][rPin]);

          // Update last known state of this switch
          colPrev[cPin][rPin] = 0;
        }
      }
    }
    digitalWrite(cPins[cPin], HIGH);
  }
}
