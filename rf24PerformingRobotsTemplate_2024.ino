/*
   Using the nRF24L01 radio module to communicate
   between two Arduinos with much increased reliability following
   various tutorials, conversations, and studying the nRF24L01 datasheet
   and the library reference.

   Transmitter is
   https://github.com/michaelshiloh/resourcesForClasses/tree/master/kicad/Arduino_Shield_RC_Controller

  Receiver is
  https://github.com/michaelshiloh/resourcesForClasses/blob/master/kicad/nRF_servo_Mega

   This file contains code for both transmitter and receiver.
   Transmitter at the top, receiver at the bottom.
   One of them is commented out, so you need to comment in or out
   the correct section. You don't need to make changes to this 
   part of the code, just to comment in or out depending on
   whether you are programming your transmitter or receiver

   You need to set the correct address for your robot.

   Search for the phrase CHANGEHERE to see where to 
   comment or uncomment or make changes.

   These sketches require the RF24 library by TMRh20
   Documentation here: https://nrf24.github.io/RF24/index.html

   change log

   11 Oct 2023 - ms - initial entry based on
                  rf24PerformingRobotsTemplate
   26 Oct 2023 - ms - revised for new board: nRF_Servo_Mega rev 2
   28 Oct 2023 - ms - add demo of NeoMatrix, servo, and Music Maker Shield
	 20 Nov 2023 - as - fixed the bug which allowed counting beyond the limits
   22 Nov 2023 - ms - display radio custom address byte and channel
   12 Nov 2024 - ms - changed names for channel and address allocation for Fall 2024                  
                      https://github.com/michaelshiloh/resourcesForClasses/blob/master/kicad/nRF_servo_Mega    
                      https://github.com/michaelshiloh/resourcesForClasses/blob/master/kicad/nRFControlPanel
*/


// Common code
//

// Common pin usage
// Note there are additional pins unique to transmitter or receiver
//

// nRF24L01 uses SPI which is fixed
// on pins 11, 12, and 13 on the Uno
// and on pins 50, 51, and 52 on the Mega

// It also requires two other signals
// (CE = Chip Enable, CSN = Chip Select Not)
// Which can be any pins:

// CHANGEHERE
// For the transmitter
//const int NRF_CE_PIN = A4, NRF_CSN_PIN = A5;

// CHANGEHERE
// for the receiver
const int NRF_CE_PIN = A11, NRF_CSN_PIN = A15;

// nRF 24L01 pin   name
//          1      GND
//          2      3.3V
//          3      CE
//          4      CSN
//          5      SCLK
//          6      MOSI/COPI
//          7      MISO/CIPO

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(NRF_CE_PIN, NRF_CSN_PIN);  // CE, CSN

//#include <printf.h>  // for debugging

// See note in rf24Handshaking about address selection
//

// Channel and address allocation:
// Rama and Hind Y: Channel 30, addr = 0x76
// Ahsen and Pranav: Channel 40, addr = 0x73
// Sara & Toomie:  Channel 50, addr = 0x7C
// Avinash and Vahagn: Channel 60, addr = 0xC6
// Hind A & Javeria:  Channel 70, addr = 0xC3
// Mbebo and Aaron: Channel 80, addr = 0xCC
// Linh and Luke: Channel 90, addr = 0x33

// CHANGEHERE
const byte CUSTOM_ADDRESS_BYTE = 0x76;  // change as per the above assignment
const int CUSTOM_CHANNEL_NUMBER = 30;   // change as per the above assignment

// Do not make changes here
const byte xmtrAddress[] = { CUSTOM_ADDRESS_BYTE, CUSTOM_ADDRESS_BYTE, 0xC7, 0xE6, 0xCC };
const byte rcvrAddress[] = { CUSTOM_ADDRESS_BYTE, CUSTOM_ADDRESS_BYTE, 0xC7, 0xE6, 0x66 };

const int RF24_POWER_LEVEL = RF24_PA_LOW;

// global variables
uint8_t pipeNum;
unsigned int totalTransmitFailures = 0;

struct DataStruct {
  uint8_t stateNumber;
};
DataStruct data;

void setupRF24Common() {

  // RF24 setup
  if (!radio.begin()) {
    Serial.println(F("radio  initialization failed"));
    while (1)
      ;
  } else {
    Serial.println(F("radio successfully initialized"));
  }

  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(CUSTOM_CHANNEL_NUMBER);
  radio.setPALevel(RF24_POWER_LEVEL);
}

// CHANGEHERE
/*
// Transmitter code

// Transmitter pin usage
const int LCD_RS_PIN = 3, LCD_EN_PIN = 2, LCD_D4_PIN = 4, LCD_D5_PIN = 5, LCD_D6_PIN = 6, LCD_D7_PIN = 7;
const int SW1_PIN = 8, SW2_PIN = 9, SW3_PIN = 10, SW4_PIN = A3, SW5_PIN = A2;

// LCD library code
#include <LiquidCrystal.h>

// initialize the library with the relevant pins
LiquidCrystal lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);


const int NUM_OF_STATES = 37; //16 characters
char* theStates[] = { "00 S1 Stop the c",
                      "01 S1P I call di",
                      "02 S2 Ms Scarlet",
                      "03 S2 Me? Oh jus",
                      "04 S2 Mr Wright!",
                      "05 S2P I don't t",
                      "06 S2 You're so ",
                      "07 S2 She's tryi",
                      "08 S2 Mr Wright!",
                      "09 S2P Speak for",
                      "10 S2 This case ",
                      "11 S3 Ladies and",
                      "12 S3 Each of yo",
                      "13 S3P That's ri",
                      "14 S3 Ms Scarlet",
                      "15 S3P But let's",
                      "16 S3 Perhaps no",
                      "17 S3P Classic r",
                      "18 S3 Fair point",
                      "19 S3P Ooooh! De",
                      "20 S3 Indeed the",
                      "21 S3 Interestin",
                      "22 S3 And that l",
                      "23 S3P Hehehe vi",
                      "24 S3 And finall",
                      "25 S3 What?",
                      "26 S3 What are y",
                      "27 S3 Well well ",
                      "28 S3 You see wh",
                      "29 S3 Ladies and",
                      "30 S3P What me?!",
                      "31 S3 Ahh but th",
                      "32 S3 Hahaha! Yo",
                      "33 S3P And I wou",
                      "34 S3 I couldn't",
                      "35 S3P Nooo! Cur",
                      "36 S3 Ladies and" };

void updateLCD() {

  lcd.clear();
  lcd.print(theStates[data.stateNumber]);
  lcd.setCursor(0, 1);  // column, line (from 0)
  lcd.print("not transmitted yet");
}

void countDown() {
  data.stateNumber = (data.stateNumber > 0) ? (data.stateNumber - 1) : 0;
  updateLCD();
}

void countUp() {
  if (++data.stateNumber >= NUM_OF_STATES) {
    data.stateNumber = NUM_OF_STATES - 1;
  }
  updateLCD();
}


void spare1() {}
void spare2() {}

void rf24SendData() {

  radio.stopListening();  // go into transmit mode
  // The write() function will block
  // until the message is successfully acknowledged by the receiver
  // or the timeout/retransmit maxima are reached.
  int retval = radio.write(&data, sizeof(data));

  lcd.clear();
  lcd.setCursor(0, 0);  // column, line (from 0)
  lcd.print("transmitting");
  lcd.setCursor(14, 0);  // column, line (from 0)
  lcd.print(data.stateNumber);

  Serial.print(F(" ... "));
  if (retval) {
    Serial.println(F("success"));
    lcd.setCursor(0, 1);  // column, line (from 0)
    lcd.print("success");
  } else {
    totalTransmitFailures++;
    Serial.print(F("failure, total failures = "));
    Serial.println(totalTransmitFailures);

    lcd.setCursor(0, 1);  // column, line (from 0)
    lcd.print("error, total=");
    lcd.setCursor(13, 1);  // column, line (from 0)
    lcd.print(totalTransmitFailures);
  }
}

class Button {
  int pinNumber;
  bool previousState;
  void (*buttonFunction)();
public:

  // Constructor
  Button(int pn, void* bf) {
    pinNumber = pn;
    buttonFunction = bf;
    previousState = 1;
  }

  // update the button
  void update() {
    bool currentState = digitalRead(pinNumber);
    if (currentState == LOW && previousState == HIGH) {
      Serial.print("button on pin ");
      Serial.print(pinNumber);
      Serial.println();
      buttonFunction();
    }
    previousState = currentState;
  }
};

const int NUMBUTTONS = 5;
Button theButtons[] = {
  Button(SW1_PIN, countDown),
  Button(SW2_PIN, rf24SendData),
  Button(SW3_PIN, countUp),
  Button(SW4_PIN, spare1),
  Button(SW5_PIN, spare2),
};

void setupRF24() {

  setupRF24Common();

  // Set us as a transmitter
  radio.openWritingPipe(xmtrAddress);
  radio.openReadingPipe(1, rcvrAddress);

  // radio.printPrettyDetails();
  Serial.println(F("I am a transmitter"));

  data.stateNumber = 0;
}

void setup() {
  Serial.begin(9600);
  Serial.println(F("Setting up LCD"));

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();
  // Print a message to the LCD.
  lcd.print("Radio setup");

  // Display the address in hex
  lcd.setCursor(0, 1);
  lcd.print("addr 0x");
  lcd.setCursor(7, 1);
  char s[5];
  sprintf(s, "%02x", CUSTOM_ADDRESS_BYTE);
  lcd.print(s);

  // Display the channel number
  lcd.setCursor(10, 1);
  lcd.print("ch");
  lcd.setCursor(13, 1);
  lcd.print(CUSTOM_CHANNEL_NUMBER);

  Serial.println(F("Setting up radio"));
  setupRF24();

  // If setupRF24 returned then the radio is set up
  lcd.setCursor(0, 0);
  lcd.print("Radio OK state=");
  lcd.print(theStates[data.stateNumber]);

  // Initialize the switches
  pinMode(SW1_PIN, INPUT_PULLUP);
  pinMode(SW2_PIN, INPUT_PULLUP);
  pinMode(SW3_PIN, INPUT_PULLUP);
  pinMode(SW4_PIN, INPUT_PULLUP);
  pinMode(SW5_PIN, INPUT_PULLUP);
}



void loop() {
  for (int i = 0; i < NUMBUTTONS; i++) {
    theButtons[i].update();
  }
  delay(50);  // for testing
}


void clearData() {
  // set all fields to 0
  data.stateNumber = 0;
}

// End of transmitter code
// CHANGEHERE
*/

// Receiver Code
// CHANGEHERE

// Additional libraries for music maker shield
#include <Adafruit_VS1053.h>
#include <SD.h>

// Servo library
#include <Servo.h>

// Additional libraries for graphics on the Neo Pixel Matrix
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif

// Additional pin usage for receiver

// Adafruit music maker shield
#define SHIELD_RESET -1  // VS1053 reset pin (unused!)
#define SHIELD_CS 7      // VS1053 chip select pin (output)
#define SHIELD_DCS 6     // VS1053 Data/command select pin (output)
#define CARDCS 4         // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3  // VS1053 Data request, ideally an Interrupt pin
Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

// Connectors for NeoPixels and Servo Motors are labeled
// M1 - M6 which is not very useful. Here are the pin
// assignments:
// M1 = 19
// M2 = 20
// M3 = 21
// M4 = 16
// M5 = 18
// M6 = 17

// Servo motors
const int PUPPET_SERVO_PIN = 21;
const int STOMACH_SERVO_PIN = 20;
const int MUSTACHE_SERVO_PIN = 16;
const int LEFTEYE_SERVO_PIN = 17;
const int RIGHTEYE_SERVO_PIN = 18;
//const int ANTENNA_SERVO_PIN = 10;
//const int TAIL_SERVO_PIN = 11;
//const int GRABBER_SERVO_PIN = 12;

// Neopixel
const int NEOPIXELPIN = 18;
const int NUMPIXELS = 64;
//#define NEOPIXELPIN 18
//#define NUMPIXELS 64  // change to fit
//Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, NEOPIXELPIN,
                            NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
                            NEO_GRB            + NEO_KHZ800);

Servo puppet;  // change names to describe what's moving
Servo stomach;
Servo lefteye;
Servo righteye;
Servo mustache;
//Servo tail;
//Servo grabber;
//Servo disk;

// change as per your robot
const int NOSE_WRINKLE = 45;
const int NOSE_TWEAK = 90;
const int TAIL_ANGRY = 0;
const int TAIL_HAPPY = 180;
const int GRABBER_RELAX = 0;
const int GRABBER_GRAB = 180;

void setup() {
  Serial.begin(9600);
  // printf_begin();

  // Set up all the attached hardware
  setupMusicMakerShield();
  setupServoMotors();
  setupNeoPixels();

  setupRF24();

  // Brief flash to show we're done with setup()
  flashNeoPixels();
  Serial.println("setup done");
}

void setupRF24() {
  setupRF24Common();

  // Set us as a receiver
  radio.openWritingPipe(rcvrAddress);
  radio.openReadingPipe(1, xmtrAddress);

  // radio.printPrettyDetails();
  Serial.println(F("I am a receiver"));
}

void setupMusicMakerShield() {
  if (!musicPlayer.begin()) {  // initialise the music player
    Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
    while (1)
      ;
  }
  Serial.println(F("VS1053 found"));

  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD card failed or not present"));
    while (1)
      ;  // don't do anything more
  }

  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(20, 20);

  // Timer interrupts are not suggested, better to use DREQ interrupt!
  //musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT); // timer int

  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int
}

void setupServoMotors() {
  puppet.write(40); 
  puppet.attach(PUPPET_SERVO_PIN);
  stomach.write(30);
  stomach.attach(STOMACH_SERVO_PIN);
  lefteye.write(80);
  lefteye.attach(LEFTEYE_SERVO_PIN);
  righteye.write(110);
  righteye.attach(RIGHTEYE_SERVO_PIN);
  mustache.write(85);
  mustache.attach(MUSTACHE_SERVO_PIN);
  //nose.write(90);
  //  antenna.attach(ANTENNA_SERVO_PIN);
  //  tail.attach(TAIL_SERVO_PIN);
  //  grabber.attach(GRABBER_SERVO_PIN);
  //
  //  tail.write(TAIL_HAPPY);
}

void setupNeoPixels() {
  //  pixels.begin();
  //  pixels.clear();
  //  pixels.show();
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(matrix.Color(200, 30, 40));
}

void flashNeoPixels() {

  // Using the Matrix library
  matrix.fillScreen(matrix.Color(0, 255, 0));
  matrix.show();
  delay(500);
  matrix.fillScreen(0);
  matrix.show();

  //  // all on
  //  for (int i = 0; i < NUMPIXELS; i++) {  // For each pixel...
  //    pixels.setPixelColor(i, pixels.Color(0, 100, 0));
  //  }
  //  pixels.show();
  //  delay(500);
  //
  //  // all off
  //  pixels.clear();
  //  pixels.show();
}
void puppetTalk() {
  puppet.write(130); 
  delay(300);
  puppet.write(40);
  delay(300);
  puppet.write(130); 
  delay(300);
  puppet.write(40);
  delay(300);
  puppet.write(130); 
  delay(300);
  puppet.write(40);
  delay(300);
}

void stomachLaugh() {
  stomach.write(20);
  delay(300);
  stomach.write(30);
  delay(300);
  stomach.write(20);
  delay(300);
  stomach.write(30);
  delay(300);
  stomach.write(20);
  delay(300);
  stomach.write(30);
  delay(300);
}

void mustacheTalk() {
  mustache.write(95);
  delay(250);
  mustache.write(85);
  delay(250);
  mustache.write(95);
  delay(250);
  mustache.write(85);
  delay(250);
  mustache.write(95);
  delay(250);
  mustache.write(85);
  delay(250);
}

void lookatPuppet() {
  lefteye.write(30);
  righteye.write(60);
}

void lookStraight() {
  lefteye.write(80);
  righteye.write(110);
}

void loop() {
  // If there is data, read it,
  // and do the needfull
  // Become a receiver
  radio.startListening();
  if (radio.available(&pipeNum)) {
    radio.read(&data, sizeof(data));
    Serial.print(F("message received Data = "));
    Serial.print(data.stateNumber);
    Serial.println();

    switch (data.stateNumber) {
      case 0: //DETECTIVE: Stop the commotion everyone... DONE
        musicPlayer.startPlayingFile("/track001.mp3");
        lookStraight();
        mustacheTalk();
        delay(300);
        mustacheTalk();
        delay(350);
        mustacheTalk();
        delay(300);
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        delay(1000);
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        delay(500);
        mustacheTalk();
        mustacheTalk();
        delay(500);
        stomachLaugh();
        mustacheTalk();
        // play track 0
        // display something on LEDs
        break;
      case 1: //PUPPET: I call dibs.. DONE
        musicPlayer.startPlayingFile("/track002.mp3");
        lookatPuppet();
        puppetTalk();
        delay(500);
        lookStraight();
        // Serial.print(F("moving nose to 180 and drawing rectangle"));
        // nose.write(180);

        // matrix.drawRect(2, 2, 5, 5, matrix.Color(200, 90, 30));
        // matrix.show();

        // Serial.println(F("Playing track 002"));

        break;
      case 2: //DETECTIVE: Miss Scarlet! What are you... DONE
        musicPlayer.startPlayingFile("/track003.mp3");
        mustacheTalk();
        mustacheTalk();
        // Serial.println(F("moving nose to 30"));
        // nose.write(30);

        // matrix.drawRect(2, 2, 5, 5, matrix.Color(0, 200, 30));
        // matrix.show();

        // Serial.println(F("Playing track 001"));
        // musicPlayer.startPlayingFile("/track001.mp3");
        break;
      case 3: //DETECTIVE: Me? Oh just sniffing... DONE
        musicPlayer.startPlayingFile("/track004.mp3");
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        delay(300);
        stomachLaugh();
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        stomachLaugh();
        break;
      case 4: //DETECTIVE: Mr Wright! Did you here that... DONE
        musicPlayer.startPlayingFile("/track005.mp3");
        lookatPuppet();
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        break;
      case 5: //PUPPET: I don't trust her one bit... DONE
        musicPlayer.startPlayingFile("/track006.mp3");
        puppet.write(130); 
        delay(300);
        puppet.write(40);
        delay(300);
        puppet.write(130); 
        delay(300);
        puppet.write(40);
        delay(600);
        puppet.write(130); 
        delay(300);
        puppet.write(40);
        delay(300);
        puppet.write(130); 
        delay(300);
        puppet.write(40);
        delay(500);
        puppetTalk();
        break;
      case 6: //DETECTIVE: You're so right, Mr Wright... DONE
        musicPlayer.startPlayingFile("/track007.mp3");
        mustacheTalk();
        delay(500);
        lookStraight();
        mustacheTalk();
        mustacheTalk();
        delay(300);
        stomachLaugh();
        break;
      case 7: //DETECTIVE: She's trying to throw us off... DONE
        musicPlayer.startPlayingFile("/track008.mp3");
        lookatPuppet();
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        stomachLaugh();
        lookStraight();
        break;
      case 8: //DETECTIVE: Mr Wright! I really didn't.. DONE
        musicPlayer.startPlayingFile("/track009.mp3");
        lookatPuppet();
        mustacheTalk();
        mustacheTalk();
        stomachLaugh();
        break;
      case 9: //PUPPET: Speak for yourself Hawk... DONE
        musicPlayer.startPlayingFile("/track010.mp3");
        lookatPuppet();
        puppetTalk();
        puppetTalk();
        break;
      case 10: //DETECTIVE: This case just got personal... DONE
        musicPlayer.startPlayingFile("/track011.mp3");
        mustacheTalk();
        delay(500);
        mustacheTalk();
        lookStraight();
        break;
      case 11: //DETECTIVE: Ladies and gentlemen! Or should I say sus... DONE
        musicPlayer.startPlayingFile("/track012.mp3");
        mustacheTalk();
        mustache.write(95);
        delay(250);
        mustache.write(85);
        delay(250);
        mustache.write(95);
        delay(250);
        mustache.write(85);
        delay(250);
        stomachLaugh();
        delay(700);
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        break;
      case 12: //DETECTIVE: Each of you had a motive, a reason... DONE
        musicPlayer.startPlayingFile("/track013.mp3");
        mustacheTalk();
        delay(500);
        mustacheTalk();
        mustacheTalk();
        delay(200);
        mustacheTalk();
        mustacheTalk();
        delay(200);
        mustacheTalk();
        delay(500);
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        stomachLaugh();
        break;
      case 13: //PUPPET: That's right! Nobody pulls one over... DONE
        musicPlayer.startPlayingFile("/track014.mp3");
        lookatPuppet();
        puppet.write(130); 
        delay(300);
        puppet.write(40);
        delay(500);
        puppetTalk();
        puppetTalk();
        delay(300);
        lookStraight();
        break;
      case 14: //DETECTIVE: Miss Scarlet, the mysterious femme... DONE
        musicPlayer.startPlayingFile("/track015.mp3");
        mustacheTalk();
        delay(700);
        mustacheTalk();
        mustacheTalk();
        delay(1000);
        mustacheTalk();
        mustacheTalk();
        delay(300);
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        mustache.write(95);
        delay(250);
        mustache.write(85);
        delay(250);
        mustache.write(95);
        delay(250);
        mustache.write(85);
        delay(250);
        stomachLaugh();
        break;
      case 15: //PUPPET: But let's not ignore the obvious hawk... DONE
        musicPlayer.startPlayingFile("/track016.mp3");
        lookatPuppet();
        puppetTalk();
        delay(200);
        puppetTalk();
        puppet.write(130); 
        delay(300);
        puppet.write(40);
        delay(500);
        lookStraight();
        break;
      case 16: //DETECTIVE: Perhaps not. Then there's you Mr Green... DONE
        musicPlayer.startPlayingFile("/track017.mp3");
        mustacheTalk();
        delay(400);
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        break;
      case 17: //PUPPET: Classic rich guy excuse... DONE
        musicPlayer.startPlayingFile("/track018.mp3");
        lookatPuppet();
        puppet.write(130); 
        delay(300);
        puppet.write(40);
        delay(300);
        puppet.write(130); 
        delay(300);
        puppet.write(40);
        delay(700);
        puppetTalk();
        delay(300);
        lookStraight();
        break;
      case 18: //DETECTIVE: Fair point. But what about Dr Orchid... DONE
        musicPlayer.startPlayingFile("/track019.mp3");
        mustacheTalk();
        delay(200);
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        mustache.write(95);
        delay(250);
        mustache.write(85);
        delay(250);
        mustache.write(95);
        delay(250);
        mustache.write(85);
        delay(250);
        stomachLaugh();
        break;
      case 19: //PUPPET: Ooooh! Defensive much... DONE
        musicPlayer.startPlayingFile("/track020.mp3");
        lookatPuppet();
        puppet.write(130); 
        delay(300);
        puppet.write(40);
        delay(300);
        puppet.write(130); 
        delay(300);
        puppet.write(40);
        delay(500);
        puppet.write(130); 
        delay(300);
        puppet.write(40);
        delay(300);
        puppet.write(130); 
        delay(300);
        puppet.write(40);
        delay(300);
        lookStraight();
        break;
      case 20: //DETECTIVE: Indeed they are! Then we have Professor Plum... DONE
        musicPlayer.startPlayingFile("/track021.mp3");
        mustacheTalk();
        delay(200);
        mustacheTalk();
        mustache.write(95);
        delay(250);
        mustache.write(85);
        delay(250);
        mustache.write(95);
        delay(250);
        mustache.write(85);
        delay(250);
        stomachLaugh();
        delay(500);
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        break;
      case 21: //DETECTIVE: Interesting...because I do... DONE
        musicPlayer.startPlayingFile("/track022.mp3");
        mustacheTalk();
        delay(800);
        mustacheTalk();
        delay(100);
        mustacheTalk();
        delay(500);
        mustacheTalk();
        mustacheTalk();
        delay(500);
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        delay(500);
        mustacheTalk();
        delay(500);
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        break;
      case 22: //DETECTIVE: And that leads us to you Mrs. Peacock... DONE
        musicPlayer.startPlayingFile("/track023.mp3");
        mustacheTalk();
        delay(500);
        mustacheTalk();
        mustacheTalk();
        delay(1200);
        mustacheTalk();
        mustacheTalk();
        mustache.write(95);
        delay(250);
        mustache.write(85);
        delay(250);
        break;
      case 23: //PUPPET: Hehehe! Victim of bad acting maybe! DONE
        musicPlayer.startPlayingFile("/track024.mp3");
        lookatPuppet();
        puppet.write(130); 
        delay(300);
        puppet.write(40);
        delay(500);
        puppetTalk();
        delay(200);
        puppetTalk();
        delay(300);
        lookStraight();
        break;
      case 24: //DETECTIVE: And finally, Wadsworth... DONE
        musicPlayer.startPlayingFile("/track025.mp3");
        mustacheTalk();
        delay(800);
        mustacheTalk();
        delay(700);
        mustacheTalk();
        mustacheTalk();
        delay(200);
        mustacheTalk();
        delay(1200);
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        mustache.write(95);
        delay(250);
        mustache.write(85);
        delay(250);
        break;
      case 25: //DETECTIVE: What? DONE
        musicPlayer.startPlayingFile("/track026.mp3");
        mustache.write(95);
        delay(250);
        mustache.write(85);
        delay(250);
        break;
      case 26: //DETECTIVE: What are you implying here? DONE
        musicPlayer.startPlayingFile("/track027.mp3");
        mustacheTalk();
        break;
      case 27: //DETECTIVE: Well, well well. Isn't this a tangled... DONE
        musicPlayer.startPlayingFile("/track028.mp3");
        mustacheTalk();
        mustacheTalk();
        delay(200);
        mustacheTalk();
        mustacheTalk();
        delay(600);
        mustacheTalk();
        mustacheTalk();
        delay(900);
        mustacheTalk();
        mustacheTalk();
        delay(700);
        mustacheTalk();
        break;
      case 28: //DETECTIVE: You see, while everyone was so quick to defend... DONE
        musicPlayer.startPlayingFile("/track029.mp3");
        mustacheTalk();
        delay(400);
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        delay(400);
        mustacheTalk();
        mustacheTalk();
        break;
      case 29: //DETECTIVE: Ladies and gentlemen! Allow me to introduce... DONE
        musicPlayer.startPlayingFile("/track030.mp3");
        mustacheTalk();
        delay(500);
        mustacheTalk();
        delay(500);
        lookatPuppet();
        mustacheTalk();
        mustacheTalk();
        break;
      case 30: //PUPPET: What me?! That's proposterous... DONE
        musicPlayer.startPlayingFile("/track031.mp3");
        puppet.write(130); 
        delay(300);
        puppet.write(40);
        delay(500);
        puppet.write(130); 
        delay(300);
        puppet.write(40);
        delay(300);
        puppetTalk();
        puppet.write(130); 
        delay(300);
        puppet.write(40);
        delay(300);
        break;
      case 31: //DETECTIVE: Ahh but that's where it gets interesting... DONE
        musicPlayer.startPlayingFile("/track032.mp3");
        mustacheTalk();
        mustacheTalk();
        delay(1000);
        mustacheTalk();
        delay(600);
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        delay(800);
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        delay(500);
        mustacheTalk();
        mustacheTalk();
        mustacheTalk();
        stomachLaugh();
        break;
      case 32: //DETECTIVE: Hahaha! You don't know what Mr Wright... DONE
        musicPlayer.startPlayingFile("/track033.mp3");
        lookStraight();
        stomachLaugh();
        delay(1200);
        mustacheTalk();
        mustache.write(95);
        delay(250);
        mustache.write(85);
        delay(900);
        mustacheTalk();
        mustacheTalk();
        mustache.write(95);
        delay(250);
        mustache.write(85);
        delay(250);
        break;
      case 33: //PUPPET: And I would've gotten away with it too... DONE
        musicPlayer.startPlayingFile("/track034.mp3");
        lookatPuppet();
        puppetTalk();
        delay(100);
        puppetTalk();
        delay(100);
        puppetTalk();
        break;
      case 34: //DETECTIVE: I couldn't help myself. The thrill of solving... DONE
        musicPlayer.startPlayingFile("/track035.mp3");
        mustacheTalk();
        delay(100);
        mustacheTalk();
        delay(200);
        mustacheTalk();
        mustache.write(95);
        delay(250);
        mustache.write(85);
        delay(700);
        mustacheTalk();
        mustacheTalk();
        break;
      case 35: //PUPPET: Noooo! Curse you Hawk, you betrayed me! DONE
        musicPlayer.startPlayingFile("/track036.mp3");
        puppet.write(130); 
        delay(1000);
        puppet.write(40);
        delay(300);
        puppetTalk();
        break;
      case 36: //DETECTIVE: Ladies and gentlemen! Justice has been served... DONE
        musicPlayer.startPlayingFile("/track037.mp3");
        lookStraight();
        mustacheTalk();
        delay(300);
        mustacheTalk();
        delay(900);
        mustacheTalk();
        delay(400);
        mustacheTalk();
        mustache.write(95);
        delay(250);
        mustache.write(85);
        delay(250);
        lookatPuppet();
        delay(10000);
        lookStraight();
        break;
      default:
        Serial.println(F("Invalid option"));
    }



  }
}  // end of loop()
// end of receiver code
// CHANGEHERE
