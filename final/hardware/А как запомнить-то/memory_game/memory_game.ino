#include "buz_notes.h"
#include "ir_codes.h"
#include <GyverOLED.h>
GyverOLED<SSD1306_128x32, OLED_NO_BUFFER> oled;

#define CHOICE_OFF 0   //Used to control LEDs
#define CHOICE_NONE 0  //Used to check buttons
#define CHOICE_RED (1 << 0)
#define CHOICE_GREEN (1 << 1)
#define CHOICE_BLUE (1 << 2)
#define CHOICE_WHITE (1 << 3)
#define CHOICE_YELLOW (1 << 4)


#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 4
#define LED_WHITE 7
#define LED_YELLOW 8

// Button pin definitions

#include <NecDecoder.h>
NecDecoder ir;

// Buzzer pin definitions

#define BUZZER1 A2
#define BUZZER2 A3

// Define game parameters

#define ROUNDS_TO_WIN 13       //Number of rounds to succesfully remember before you win. 13 is do-able.
#define ENTRY_TIME_LIMIT 5000  //Amount of time to press a button before game times out. 3000ms = 3 sec


#define MODE_MEMORY 0
#define MODE_BATTLE 1
#define MODE_BEEGEES 2

#include "images.h"


// Game state variables
byte gameMode = MODE_MEMORY;  //By default, let's play the memory game
byte gameBoard[32];           //Contains the combination of buttons as we advance
byte gameRound = 0;           //Counts the number of succesful rounds the player has made it through

// String flags[13]=[
//   "a",
//   "a",
//   "a",
//   "a",
//   "a",
//   "a",
//   "a",
//   "a",
//   "a",
//   "a",
//   "a",
//   "a",
//   "a"
// ];

// в прерывании вызываем tick()
void irIsr() {
  ir.tick();
}

void setup() {
  //Setup hardware inputs/outputs. These pins are defined in the hardware_versions header file

  //Enable pull ups on inputs
  Serial.begin(9600);
  oled.init();       // инициализация
  oled.clear();      // очистка
  oled.setScale(2);  // масштаб текста (1..4)
  oled.home();       // курсор в 0,0
  oled.print("Сыграем?");
  delay(1000);
  oled.setScale(1);
  // курсор на начало 3 строки
  oled.setCursor(0, 3);
  oled.print("Да это ADSL и что?");
  




  // подключил на D2, прерывание 0
  attachInterrupt(0, irIsr, FALLING);  // ИК порт

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);

  pinMode(BUZZER1, OUTPUT);
  pinMode(BUZZER2, OUTPUT);

  //Mode checking
  gameMode = MODE_MEMORY;  // By default, we're going to play the memory game

  // Check to see if the lower right button is pressed
  // if (checkButton() == CHOICE_YELLOW) play_beegees();
  // Check to see if upper right button is pressed
  // if (checkButton() == CHOICE_GREEN)
  // {
  //   gameMode = MODE_BATTLE; //Put game into battle mode
  //   //Turn on the upper right (green) LED
  //   setLEDs(CHOICE_GREEN);
  //   toner(CHOICE_GREEN, 150);
  //   setLEDs(CHOICE_RED | CHOICE_BLUE | CHOICE_YELLOW); // Turn on the other LEDs until you release button
  //   while(checkButton() != CHOICE_NONE) ; // Wait for user to stop pressing button
  //   //Now do nothing. Battle mode will be serviced in the main routine
  // }
  play_winner();  // After setup is complete, say hello to the world
}


void loop() {
  attractMode();  // Blink lights while waiting for user to press a button
  // Indicate the start of game play
  setLEDs(CHOICE_RED | CHOICE_GREEN | CHOICE_BLUE | CHOICE_YELLOW | CHOICE_WHITE);  // Turn all LEDs on
  delay(1000);
  setLEDs(CHOICE_OFF);  // Turn off LEDs
  delay(250);
  if (gameMode == MODE_MEMORY) {
    // Play memory game and handle result
    if (play_memory() == true){
      play_winner();  // Player won, play winner tones
      oled.clear();
      oled.print("TulaCTF{pip_bup_bob}");
      delay(20000);
    }
    else
      play_loser();  // Player lost, play loser tones
  }

  if (gameMode == MODE_BATTLE) {
    play_battle();  // Play game until someone loses
    play_loser();   // Player lost, play loser tones
  }
}



//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//The following functions are related to game play only
// Play the regular memory game
// Returns 0 if player loses, or 1 if player wins
boolean play_memory(void) {
  randomSeed(millis());  // Seed the random generator with random amount of millis()
  gameRound = 0;         // Reset the game to the beginning
  while (gameRound < ROUNDS_TO_WIN) {
    add_to_moves();  // Add a button to the current moves, then play them back
    playMoves();     // Play back the current game board
    // Then require the player to repeat the sequence.
    for (byte currentMove = 0; currentMove < gameRound; currentMove++) {
      byte choice = wait_for_button();                     // See what button the user presses
      if (choice == 0) return false;                       // If wait timed out, player loses
      if (choice != gameBoard[currentMove]) return false;  // If the choice is incorect, player loses
    }
    delay(1000);  // Player was correct, delay before playing moves
  }
  return true;  // Player made it through all the rounds to win!
}

// Play the special 2 player battle mode
// A player begins by pressing a button then handing it to the other player
// That player repeats the button and adds one, then passes back.
// This function returns when someone loses
boolean play_battle(void) {
  gameRound = 0;  // Reset the game frame back to one frame
  while (1)       // Loop until someone fails
  {
    byte newButton = wait_for_button();  // Wait for user to input next move
    gameBoard[gameRound++] = newButton;  // Add this new button to the game array
    // Then require the player to repeat the sequence.
    for (byte currentMove = 0; currentMove < gameRound; currentMove++) {
      byte choice = wait_for_button();
      if (choice == 0) return false;                       // If wait timed out, player loses.
      if (choice != gameBoard[currentMove]) return false;  // If the choice is incorect, player loses.
    }
    delay(100);  // Give the user an extra 100ms to hand the game to the other player
  }
  return true;  // We should never get here
}

// Plays the current contents of the game moves
void playMoves(void) {
  for (byte currentMove = 0; currentMove < gameRound; currentMove++) {
    toner(gameBoard[currentMove], 150);
    // Wait some amount of time between button playback
    // Shorten this to make game harder
    delay(150);  // 150 works well. 75 gets fast.
  }
}



// Adds a new random button to the game sequence, by sampling the timer
void add_to_moves(void) {
  for (byte i = 0; i < ROUNDS_TO_WIN; i++)
    gameBoard[i] = 0;
  for (byte i = 0; i < gameRound + 1; i++) {
    byte newButton = random(0, 5);  //min (included), max (exluded)
    // We have to convert this number, 0 to 4, to CHOICEs
    if (newButton == 0) newButton = CHOICE_RED;
    else if (newButton == 1) newButton = CHOICE_GREEN;
    else if (newButton == 2) newButton = CHOICE_BLUE;
    else if (newButton == 3) newButton = CHOICE_WHITE;
    else if (newButton == 4) newButton = CHOICE_YELLOW;

    gameBoard[i] = newButton;  // Add this new button to the game array
  }
  gameRound++;
}



//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//The following functions control the hardware
// Lights a given LEDs
// Pass in a byte that is made up from CHOICE_RED, CHOICE_YELLOW, etc
void setLEDs(byte leds) {
  if ((leds & CHOICE_RED) != 0)
    digitalWrite(LED_RED, HIGH);
  else
    digitalWrite(LED_RED, LOW);
  if ((leds & CHOICE_GREEN) != 0)
    digitalWrite(LED_GREEN, HIGH);
  else
    digitalWrite(LED_GREEN, LOW);
  if ((leds & CHOICE_BLUE) != 0)
    digitalWrite(LED_BLUE, HIGH);
  else
    digitalWrite(LED_BLUE, LOW);
  if ((leds & CHOICE_WHITE) != 0)
    digitalWrite(LED_WHITE, HIGH);
  else
    digitalWrite(LED_WHITE, LOW);
  if ((leds & CHOICE_YELLOW) != 0)
    digitalWrite(LED_YELLOW, HIGH);
  else
    digitalWrite(LED_YELLOW, LOW);
}

// Wait for a button to be pressed.
// Returns one of LED colors (LED_RED, etc.) if successful, 0 if timed out
byte wait_for_button(void) {
  long startTime = millis();                         // Remember the time we started the this loop
  while ((millis() - startTime) < ENTRY_TIME_LIMIT)  // Loop until too much time has passed
  {
    if (ir.available()) {
      // вывести команду (8 бит)
      // Serial.print("0x");
      // Serial.println(ir.readCommand(), HEX);
      switch (ir.readCommand()) {
        case IR_1:
          {
            toner(CHOICE_RED, 150);
            delay(30);
            return CHOICE_RED;
          }
        case IR_2:
          {
            toner(CHOICE_GREEN, 150);
            delay(30);
            return CHOICE_GREEN;
          }
        case IR_3:
          {
            toner(CHOICE_BLUE, 150);
            delay(30);
            return CHOICE_BLUE;
          }
        case IR_4:
          {
            toner(CHOICE_WHITE, 150);
            delay(30);
            return CHOICE_WHITE;
          }
        case IR_5:
          {
            toner(CHOICE_YELLOW, 150);
            delay(30);
            return CHOICE_YELLOW;
          }
        case IR_6:
          {

            break;
          }
        case IR_7:
          {

            break;
          }
        case IR_8:
          {

            break;
          }
        case IR_9:
          {

            break;
          }
        case IR_STAR:
          {
            toner(CHOICE_YELLOW, 150);
            delay(30);
            
            break;
          }
        case IR_0:
          {

            break;
          }
        case IR_HASH:
          {

            break;
          }
        case IR_UP:
          {

            break;
          }
        case IR_LEFT:
          {

            break;
          }
        case IR_OK:
          {

            break;
          }
        case IR_RIGHT:
          {

            break;
          }
        case IR_DOWN:
          {

            break;
          }
      }
    }
  }
  // while ( (millis() - startTime) < ENTRY_TIME_LIMIT) // Loop until too much time has passed
  // {
  //   byte button = checkButton();
  //   if (button != CHOICE_NONE)
  //   {
  //     toner(button, 150); // Play the button the user just pressed
  //     while(checkButton() != CHOICE_NONE) ;  // Now let's wait for user to release button
  //     delay(10); // This helps with debouncing and accidental double taps
  //     return button;
  //   }
  // }
  return CHOICE_NONE;  // If we get here, we've timed out!
}


// Returns a '1' bit in the position corresponding to CHOICE_RED, CHOICE_GREEN, etc.
// byte checkButton(void)
// {
//   if (digitalRead(BUTTON_RED) == 0) return(CHOICE_RED);
//   else if (digitalRead(BUTTON_GREEN) == 0) return(CHOICE_GREEN);
//   else if (digitalRead(BUTTON_BLUE) == 0) return(CHOICE_BLUE);
//   else if (digitalRead(BUTTON_YELLOW) == 0) return(CHOICE_YELLOW);
//   return(CHOICE_NONE); // If no button is pressed, return none
// }

// Light an LED and play tone
// Red, 1:     440Hz - 2.272ms - 1.136ms pulse
// Green, 2:  880Hz - 1.136ms - 0.568ms pulse
// Blue, 3:    587.33Hz - 1.702ms - 0.851ms pulse
// White, 4:  784Hz - 1.276ms - 0.638ms pulse
// Yellow, 1: 340Hz - 3.276ms - 2.638ms pulse

void toner(byte which, int buzz_length_ms) {
  setLEDs(which);  //Turn on a given LED
  //Play the sound associated with the given LED
  switch (which) {
    case CHOICE_RED:
      buzz_sound(buzz_length_ms, 1136);
      break;
    case CHOICE_GREEN:
      buzz_sound(buzz_length_ms, 568);
      break;
    case CHOICE_BLUE:
      buzz_sound(buzz_length_ms, 851);
      break;
    case CHOICE_WHITE:
      buzz_sound(buzz_length_ms, 638);
      break;
    case CHOICE_YELLOW:
      buzz_sound(buzz_length_ms, 2638);
      break;
  }

  setLEDs(CHOICE_OFF);  // Turn off all LEDs
}



// Toggle buzzer every buzz_delay_us, for a duration of buzz_length_ms.
void buzz_sound(int buzz_length_ms, int buzz_delay_us) {
  // Convert total play time from milliseconds to microseconds
  long buzz_length_us = buzz_length_ms * (long)1000;
  // Loop until the remaining play time is less than a single buzz_delay_us
  while (buzz_length_us > (buzz_delay_us * 2)) {
    buzz_length_us -= buzz_delay_us * 2;  //Decrease the remaining play time
    // Toggle the buzzer at various speeds
    digitalWrite(BUZZER1, LOW);
    digitalWrite(BUZZER2, HIGH);
    delayMicroseconds(buzz_delay_us);
    digitalWrite(BUZZER1, HIGH);
    digitalWrite(BUZZER2, LOW);
    delayMicroseconds(buzz_delay_us);
  }
  digitalWrite(BUZZER1, LOW);
  digitalWrite(BUZZER2, LOW);
}



// Play the winner sound and lights
void play_winner(void) {
  setLEDs(CHOICE_GREEN | CHOICE_BLUE);
  winner_sound();
  setLEDs(CHOICE_RED | CHOICE_YELLOW);
  winner_sound();
  setLEDs(CHOICE_GREEN | CHOICE_BLUE);
  winner_sound();
  setLEDs(CHOICE_RED | CHOICE_WHITE);
  winner_sound();
}

// Play the winner sound
// This is just a unique (annoying) sound we came up with, there is no magic to it
void winner_sound(void) {
  // Toggle the buzzer at various speeds
  for (byte x = 250; x > 70; x--) {
    for (byte y = 0; y < 3; y++) {
      digitalWrite(BUZZER2, HIGH);
      digitalWrite(BUZZER1, LOW);
      delayMicroseconds(x);
      digitalWrite(BUZZER2, LOW);
      digitalWrite(BUZZER1, HIGH);
      delayMicroseconds(x);
    }
  }
  digitalWrite(BUZZER1, LOW);
  digitalWrite(BUZZER2, LOW);
}

// Play the loser sound/lights
void play_loser(void) {
  setLEDs(CHOICE_RED | CHOICE_GREEN);
  buzz_sound(255, 1500);
  setLEDs(CHOICE_BLUE | CHOICE_YELLOW);
  buzz_sound(255, 1500);
  setLEDs(CHOICE_RED | CHOICE_GREEN);
  buzz_sound(255, 1500);
  setLEDs(CHOICE_BLUE | CHOICE_WHITE);
  buzz_sound(255, 1500);
}


// Show an "attract mode" display while waiting for user to press button.
void attractMode(void) {
  while (1) {
    setLEDs(CHOICE_RED);
    delay(100);
    if (wait_for_button() != CHOICE_NONE) return;
    setLEDs(CHOICE_GREEN);
    delay(100);
    if (wait_for_button() != CHOICE_NONE) return;
    setLEDs(CHOICE_BLUE);
    delay(100);
    if (wait_for_button() != CHOICE_NONE) return;
    setLEDs(CHOICE_WHITE);
    delay(100);
    if (wait_for_button() != CHOICE_NONE) return;
    setLEDs(CHOICE_YELLOW);
    delay(100);
    if (wait_for_button() != CHOICE_NONE) return;
  }
}


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// The following functions are related to Beegees Easter Egg only
// Notes in the melody. Each note is about an 1/8th note, "0"s are rests.
int melody[] = {
  NOTE_G4, NOTE_A4, 0, NOTE_C5, 0, 0, NOTE_G4, 0, 0, 0,
  NOTE_E4, 0, NOTE_D4, NOTE_E4, NOTE_G4, 0,
  NOTE_D4, NOTE_E4, 0, NOTE_G4, 0, 0,
  NOTE_D4, 0, NOTE_E4, 0, NOTE_G4, 0, NOTE_A4, 0, NOTE_C5, 0
};

int noteDuration = 115;  // This essentially sets the tempo, 115 is just about right for a disco groove :)
int LEDnumber = 0;       // Keeps track of which LED we are on during the beegees loop


// Do nothing but play bad beegees music
// This function is activated when user holds bottom right button during power up
// void play_beegees()
// {
//   //Turn on the bottom right (yellow) LED
//   setLEDs(CHOICE_YELLOW);
//   toner(CHOICE_YELLOW, 150);
//   setLEDs(CHOICE_RED | CHOICE_GREEN | CHOICE_BLUE | CHOICE_WHITE); // Turn on the other LEDs until you release button
//   while(checkButton() != CHOICE_NONE) ; // Wait for user to stop pressing button
//   setLEDs(CHOICE_NONE); // Turn off LEDs
//   delay(1000); // Wait a second before playing song
//   digitalWrite(BUZZER1, LOW); // setup the "BUZZER1" side of the buzzer to stay low, while we play the tone on the other pin.

//   while(checkButton() == CHOICE_NONE) //Play song until you press a button
//   {
//     // iterate over the notes of the melody:
//     for (int thisNote = 0; thisNote < 32; thisNote++) {
//       changeLED();
//       tone(BUZZER2, melody[thisNote],noteDuration);
//       // to distinguish the notes, set a minimum time between them.
//       // the note's duration + 30% seems to work well:
//       int pauseBetweenNotes = noteDuration * 1.30;
//       delay(pauseBetweenNotes);
//       // stop the tone playing:
//       noTone(BUZZER2);
//     }
//   }
// }

// Each time this function is called the board moves to the next LED
void changeLED(void) {
  setLEDs(1 << LEDnumber);           // Change the LED
  LEDnumber++;                       // Goto the next LED
  if (LEDnumber > 4) LEDnumber = 0;  // Wrap the counter if needed
}
