#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LED1 2
#define LED2 3
#define LED3 4
#define LED4 5
#define LED5 6
#define LED6 7
#define BUTTON 8

#define Button1 11
#define Button2 10
#define Button3 9
#define Reset 12
#define Buzzer 13

// Initialize the library with the I2C address of the display
LiquidCrystal_I2C lcd(0x27, 16, 2);


//----------------- store the custom characters in arrays ---------------------//

byte hrt[8] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000
};

byte smil[8] = {
  B00000,
  B00000,
  B01010,
  B00000,
  B10001,
  B01110,
  B00000,
  B00000
};

byte mansmil[8] =

  {

    B00000,
    B00000,
    B01010,
    B00000,
    B10001,
    B01110,
    B00000,
    B00000

  };
byte man2hrt[8] =

  {

    B00000,
    B01010,
    B11111,
    B11111,
    B11111,
    B01110,
    B00100,
    B00000

  };


byte average[8] =

  {
    0b00000,
    0b10001,
    0b01010,
    0b10001,
    0b00100,
    0b01110,
    0b10001,
    0b00000

  };

byte Q1[8] = {

  0b00000,
  0b10101,
  0b10101,
  0b01010,
  0b01010,
  0b00101,
  0b00101,
  0b00010
};

byte Q2[8] = {

  0b00000,
  0b01010,
  0b01010,
  0b10101,
  0b10101,
  0b01010,
  0b01010,
  0b10001
};

byte Q3[8] = {

  0b00000,
  0b10101,
  0b10101,
  0b01010,
  0b01010,
  0b10100,
  0b10100,
  0b01000
};

byte Q4[8] = {

  0b00010,
  0b00001,
  0b00001,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

byte Q5[8] = {

  0b01010,
  0b00100,
  0b01010,
  0b11111,
  0b10001,
  0b11111,
  0b11111,
  0b01110
};

byte Q6[8] = {

  0b01000,
  0b10000,
  0b10000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

byte smile[8] = {

  B00000,
  B00000,
  B01010,
  B00000,
  B10001,
  B01110,
  B00000,
  B00000
};


int ledPins[] = { LED1, LED2, LED3, LED4, LED5, LED6 };
int selectedLed = -1;
int count = 0;

int buttonState = 0;
int prev_buttonState = 0;


void setup() {




  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();


  //---- create custom characters ----//

  lcd.createChar(1, hrt);

  lcd.createChar(2, smil);

  lcd.createChar(3, mansmil);

  lcd.createChar(11, man2hrt);

  lcd.createChar(4, average);

  lcd.createChar(5, Q1);

  lcd.createChar(6, Q2);

  lcd.createChar(7, Q3);

  lcd.createChar(8, Q4);

  lcd.createChar(9, Q5);

  lcd.createChar(10, Q6);

  lcd.createChar(12, smile);

  lcd.setCursor(0, 0);
  lcd.print("     SHADOW");
  lcd.setCursor(3, 1);
  lcd.print("Footwork's");
  lcd.setCursor(0, 0);
  lcd.write(5);
  lcd.setCursor(1, 0);
  lcd.write(6);
  lcd.setCursor(2, 0);
  lcd.write(7);
  lcd.setCursor(0, 1);
  lcd.write(8);
  lcd.setCursor(1, 1);
  lcd.write(9);
  lcd.setCursor(2, 1);
  lcd.write(10);
  lcd.setCursor(13, 0);
  lcd.write(5);
  lcd.setCursor(14, 0);
  lcd.write(6);
  lcd.setCursor(15, 0);
  lcd.write(7);
  lcd.setCursor(13, 1);
  lcd.write(8);
  lcd.setCursor(14, 1);
  lcd.write(9);
  lcd.setCursor(15, 1);
  lcd.write(10);




  delay(5000);
  Serial.begin(9600);  // initialize serial communication





  // initialize LED pins as outputs
  for (int i = 0; i < 6; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  pinMode(BUTTON, INPUT_PULLUP);   // initialize the button pin as an input with pull-up resistor
  pinMode(Button1, INPUT_PULLUP);  //initializing buttons for 2 min mode
  pinMode(Button2, INPUT_PULLUP);  //intializing button for 5 min mode
  pinMode(Button3, INPUT_PULLUP);  //initializing button for 10 min mode
  pinMode(Reset, INPUT_PULLUP);    // initialize the reset button pin as an input with pull-up resistor
  pinMode(Buzzer, OUTPUT);         // initialize the buzzer pin as an output
}


void RandomLED() {
  buttonState = digitalRead(BUTTON);

  if (selectedLed == -1) {                   // if no LED is selected
    int randomLed = random(0, 6);            // generate a random number between 0 and 5
    digitalWrite(ledPins[randomLed], HIGH);  // turn on the selected LED
    selectedLed = randomLed;                 // store the index of the selected LED
  }


  if (prev_buttonState != buttonState) {
    if (!digitalRead(BUTTON)) {  // if the button is pressed

      tone(Buzzer, 2600,200);  // generate a tone of 1000Hz on the buzzer
      count++;
      //Serial.print(count);
      digitalWrite(ledPins[selectedLed], LOW);  // turn off the selected LED
      selectedLed = -1;                         // reset the selected LED


      // print the elapsed time in milliseconds
      // Serial.print("Button pressed after ");
      // Serial.print(elapsedTime);
      //Serial.println(" milliseconds");
    } else {
      noTone(Buzzer);  // stop the tone on the buzzer
    }
  }
  prev_buttonState = buttonState;
}





void loop() {

  bool resetButtonPressed = false;  // Flag to indicate if reset button is pressed

  selectedLed = -1;  // reset the selected LED

  count = 0;
  lcd.clear();
  lcd.print("Select Level");
  lcd.setCursor(0, 1);
  lcd.print("LVL1 /LVL2 /LVL3");

  while (digitalRead(Button1) || digitalRead(Button2) || digitalRead(Button3)) {

    if (!digitalRead(Button1))  //2 mins
    {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print(" Ready ");
      tone(Buzzer,388,1000);
      delay(1500);
      lcd.print("  Steady");
      tone(Buzzer,388,1000);
      delay(1500);
      lcd.setCursor(0, 1);
      lcd.print("    !!GO!!");
      tone(Buzzer,320,1500);
      delay(400);
      lcd.clear();


      lcd.print("    Level 1");
      lcd.setCursor(0, 0);
      lcd.write(5);
      lcd.setCursor(1, 0);
      lcd.write(6);
      lcd.setCursor(2, 0);
      lcd.write(7);
      lcd.setCursor(0, 1);
      lcd.write(8);
      lcd.setCursor(1, 1);
      lcd.write(9);
      lcd.setCursor(2, 1);
      lcd.write(10);
      lcd.setCursor(13, 0);
      lcd.write(5);
      lcd.setCursor(14, 0);
      lcd.write(6);
      lcd.setCursor(15, 0);
      lcd.write(7);
      lcd.setCursor(13, 1);
      lcd.write(8);
      lcd.setCursor(14, 1);
      lcd.write(9);
      lcd.setCursor(15, 1);
      lcd.write(10);




      //write code for adding 2 mins timer and displaying it on lcd


      unsigned long startTime = millis();
      unsigned long elapsedTime = 0;               // initialize elapsedTime to 0
      const unsigned long timerDuration = 120000;  // 2 minutes in milliseconds
      unsigned long remainingTime = timerDuration - elapsedTime;


      while (millis() - startTime < 120000) {  // currently 10 seconds
        // Update the elapsedTime variable
        elapsedTime = millis() - startTime;
        remainingTime = timerDuration - elapsedTime;  // update the remainingTime variable

        // Calculate the minutes and seconds
        int minutes = remainingTime / 60000;
        int seconds = (remainingTime % 60000) / 1000;

        // Display the remaining time on the LCD
        lcd.setCursor(6, 1);
        if (minutes < 10) {
          lcd.print("0");
        }
        lcd.print(minutes);
        lcd.print(":");
        if (seconds < 10) {
          lcd.print("0");
        }
        lcd.print(seconds);

        // Check if the timer has reached zero
        if (remainingTime <= 0) {
          lcd.setCursor(0, 1);
          lcd.print("Time's up!");
          // Add additional code here for any actions to be taken after the timer expires
        }
        RandomLED();

        //Reset Button
        if (digitalRead(Reset) == LOW) {
          resetButtonPressed = true;  // Set the resetButtonPressed flag
          // Turn off all LEDs
      for (int i = 0; i < 6; i++) {
        digitalWrite(ledPins[i], LOW);
      }
          loop();                     // Break the loop and exit the program
        }


        delay(50);
      }
      // Turn off all LEDs
      for (int i = 0; i < 6; i++) {
        digitalWrite(ledPins[i], LOW);
      }


      lcd.clear();
      lcd.setCursor(0, 0);
      if (count >= 36)  // 75% of 48 i.e.
      {
        lcd.print("Awesome  ");
        lcd.write(11);  //heart
      } else if (count >= 21) {
        lcd.print("Great Going  ");
        lcd.write(12);  //smile
      } else {
        lcd.print("Try harder  ");
        lcd.write(4);  //average
      }
      lcd.setCursor(0, 1);
      lcd.print("Score = ");
      lcd.print(count);



      delay(15000);
      break;
    }


    else if (!digitalRead(Button2))  // 5 min
    {

      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print(" Ready ");
      tone(Buzzer,388,1000);
      delay(1500);
      lcd.print("  Steady");
      tone(Buzzer,388,1000);
      delay(1500);
      lcd.setCursor(0, 1);
      lcd.print("    !!GO!!");
      tone(Buzzer,320,1500);
      delay(400);
      lcd.clear();


      lcd.clear();
      lcd.print("    LEVEL 2");
      lcd.setCursor(0, 0);
      lcd.write(5);
      lcd.setCursor(1, 0);
      lcd.write(6);
      lcd.setCursor(2, 0);
      lcd.write(7);
      lcd.setCursor(0, 1);
      lcd.write(8);
      lcd.setCursor(1, 1);
      lcd.write(9);
      lcd.setCursor(2, 1);
      lcd.write(10);
      lcd.setCursor(13, 0);
      lcd.write(5);
      lcd.setCursor(14, 0);
      lcd.write(6);
      lcd.setCursor(15, 0);
      lcd.write(7);
      lcd.setCursor(13, 1);
      lcd.write(8);
      lcd.setCursor(14, 1);
      lcd.write(9);
      lcd.setCursor(15, 1);
      lcd.write(10);


      //write code for adding 5 mins timer and displaying it on lcd


      unsigned long startTime = millis();
      unsigned long elapsedTime = 0;               // initialize elapsedTime to 0
      const unsigned long timerDuration = 300000;  // 5 minutes in milliseconds
      unsigned long remainingTime = timerDuration - elapsedTime;
      while (millis() - startTime < 300000) {
        // Update the elapsedTime variable
        elapsedTime = millis() - startTime;
        remainingTime = timerDuration - elapsedTime;  // update the remainingTime variable

        // Calculate the minutes and seconds
        int minutes = remainingTime / 60000;
        int seconds = (remainingTime % 60000) / 1000;

        // Display the remaining time on the LCD
        lcd.setCursor(6, 1);
        if (minutes < 10) {
          lcd.print("0");
        }
        lcd.print(minutes);
        lcd.print(":");
        if (seconds < 10) {
          lcd.print("0");
        }
        lcd.print(seconds);

        // Check if the timer has reached zero
        if (remainingTime <= 0) {
          lcd.setCursor(0, 1);
          lcd.print("Time's up!");
          // Add additional code here for any actions to be taken after the timer expires
        }
        RandomLED();

        //Reset Button
        if (digitalRead(Reset) == LOW) {
          resetButtonPressed = true;  // Set the resetButtonPressed flag
          // Turn off all LEDs
      for (int i = 0; i < 6; i++) {
        digitalWrite(ledPins[i], LOW);
      }
          loop();                     // Break the loop and exit the program
        }

        delay(50);
      }
      // Turn off all LEDs
      for (int i = 0; i < 6; i++) {
        digitalWrite(ledPins[i], LOW);
      }



      lcd.clear();
      lcd.setCursor(0, 0);
      if (count >= 67)  // 75% of 90 i.e.
      {
        lcd.print("Awesome  ");
        lcd.write(11);  //smile
      } else if (count >= 49) {
        lcd.print("Great Going  ");
        lcd.write(3);  //man
      } else {
        lcd.print("Try harder  ");
        lcd.write(4);  //average
      }
      lcd.setCursor(0, 1);
      lcd.print("Score = ");
      lcd.print(count);


      delay(10000);
      break;
    }

    else if (!digitalRead(Button3))  //10 min
    {


      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print(" Ready ");
      tone(Buzzer,388,1000);
      delay(1500);
      lcd.print("  Steady");
      tone(Buzzer,388,1000);
      delay(1500);
      lcd.setCursor(0, 1);
      lcd.print("    !!GO!!");
      tone(Buzzer,320,1500);
      delay(400);
      lcd.clear();


      lcd.clear();
      lcd.print("    LEVEL 3");
      lcd.setCursor(0, 0);
      lcd.write(5);
      lcd.setCursor(1, 0);
      lcd.write(6);
      lcd.setCursor(2, 0);
      lcd.write(7);
      lcd.setCursor(0, 1);
      lcd.write(8);
      lcd.setCursor(1, 1);
      lcd.write(9);
      lcd.setCursor(2, 1);
      lcd.write(10);
      lcd.setCursor(13, 0);
      lcd.write(5);
      lcd.setCursor(14, 0);
      lcd.write(6);
      lcd.setCursor(15, 0);
      lcd.write(7);
      lcd.setCursor(13, 1);
      lcd.write(8);
      lcd.setCursor(14, 1);
      lcd.write(9);
      lcd.setCursor(15, 1);
      lcd.write(10);


      //write code for adding 10 mins timer and displaying it on lcd


      unsigned long startTime = millis();
      unsigned long elapsedTime = 0;               // initialize elapsedTime to 0
      const unsigned long timerDuration = 600000;  // 10 minutes in milliseconds
      unsigned long remainingTime = timerDuration - elapsedTime;
      while (millis() - startTime < 600000) {
        // Update the elapsedTime variable
        elapsedTime = millis() - startTime;
        remainingTime = timerDuration - elapsedTime;  // update the remainingTime variable

        // Calculate the minutes and seconds
        int minutes = remainingTime / 60000;
        int seconds = (remainingTime % 60000) / 1000;

        // Display the remaining time on the LCD
        lcd.setCursor(6, 1);
        if (minutes < 10) {
          lcd.print("0");
        }
        lcd.print(minutes);
        lcd.print(":");
        if (seconds < 10) {
          lcd.print("0");
        }
        lcd.print(seconds);

        // Check if the timer has reached zero
        if (remainingTime <= 0) {
          lcd.setCursor(0, 1);
          lcd.print("Time's up!");
          // Add additional code here for any actions to be taken after the timer expires
        }
        RandomLED();

        //Reset Button
        if (digitalRead(Reset) == LOW) {
          resetButtonPressed = true;  // Set the resetButtonPressed flag
          // Turn off all LEDs
      for (int i = 0; i < 6; i++) {
        digitalWrite(ledPins[i], LOW);
      }
          loop();                     // Break the loop and exit the program
        }

        delay(50);
      }
      // Turn off all LEDs
      for (int i = 0; i < 6; i++) {
        digitalWrite(ledPins[i], LOW);
      }


      lcd.clear();
      lcd.setCursor(0, 0);
      if (count >= 90)  // 75% of 120 i.e.
      {
        lcd.print("Awesome  ");
        lcd.write(11);  //smile
      } else if (count >= 67) {
        lcd.print("Great Going  ");
        lcd.write(3);  //man
      } else {
        lcd.print("Try harder  ");
        lcd.write(4);  //average
      }

      lcd.setCursor(0, 1);
      lcd.print("Score = ");
      lcd.print(count);
      delay(10000);
      break;
    }
  }
}
