#include <Servo.h>
#include <Keypad.h>

// Define the password
const String password = "1234"; // Change this to your desired password

// Initialize the servo motor
Servo myServo;

// Define the pins for the servo motor
const int servoPin = 9;

// Initialize the keypad
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

// Define the keymap
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Connect keypad ROW0, ROW1, ROW2, ROW3 to these Arduino pins
byte rowPins[ROWS] = {7, 6, 5, 4}; 

// Connect keypad COL0, COL1, COL2, COL3 to these Arduino pins
byte colPins[COLS] = {3, 2, A1, A0}; 

// Create the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Variable to store the entered password
String enteredPassword = "";

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Attach the servo motor to the defined pin
  myServo.attach(servoPin);

  // Set the servo to the locked position
  myServo.write(0);

  // Print a message to the serial monitor
  Serial.println("Enter password:");
}

void loop() {
  // Get the key pressed
  char key = keypad.getKey();

  // If a key is pressed
  if (key) {
    // Print the pressed key to the serial monitor
    Serial.print(key);

    // Add the pressed key to the entered password
    enteredPassword += key;

    // If the key is '#', check the entered password
    if (key == '#') {
      // Remove the '#' from the entered password
      enteredPassword.remove(enteredPassword.length() - 1);

      // Check if the entered password matches the defined password
      if (enteredPassword == password) {
        // Unlock the door (move the servo to the unlocked position)
        myServo.write(90);

        // Print a message to the serial monitor
        Serial.println(" - Access Granted");
      } else {
        // Print a message to the serial monitor
        Serial.println(" - Access Denied");
      }

      // Clear the entered password
      enteredPassword = "";
    }

    // If the key is '*', clear the entered password
    if (key == '*') {
      // Clear the entered password
      enteredPassword = "";

      // Print a message to the serial monitor
      Serial.println("\nPassword cleared");
    }
  }
}
