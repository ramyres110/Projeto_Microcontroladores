const int ledPin = LED_BUILTIN; 
const int dotDuration = 50;
// Derived durations based on Morse code rules:
// - A dash is 3 times the duration of a dot.
// - The space between elements (dot/dash) within a character is 1 dot duration.
// - The space between characters is 3 dot durations.
// - The space between words is 7 dot durations.
const int dashDuration = dotDuration * 3;
const int elementPause = dotDuration;
const int charPause = dotDuration * 3;
const int wordPause = dotDuration * 7;

// --- Setup ---
void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("--- Morse Code LED Blinker ---");
  Serial.println("Enter text in the Serial Monitor and press Enter to convert to Morse code.");
  Serial.println("Supported characters: A-Z, 0-9, and space.");
  Serial.println("------------------------------");
}

// --- Loop ---
void loop() {
  if (Serial.available()) {
    String inputText = Serial.readStringUntil('\n');

    inputText.toUpperCase();

    Serial.print("Converting: ");
    Serial.println(inputText);

    for (int i = 0; i < inputText.length(); i++) {
      char currentChar = inputText.charAt(i);

      if (currentChar == ' ') {
        Serial.print(" ");
        delay(wordPause);
      
      } else {
        String morseCode = charToMorse(currentChar);

        if (morseCode != "") {
          Serial.print(morseCode); 

          for (int j = 0; j < morseCode.length(); j++) {
            char morseChar = morseCode.charAt(j);

            if (morseChar == '.') {
              blinkDot();
            } else if (morseChar == '-') {
              blinkDash();
            }

            if (j < morseCode.length() - 1) {
              delay(elementPause);
            }
          }
          Serial.print(" ");
          delay(charPause);
        } else {
          Serial.print("?");
          delay(charPause);
        }
      }
    }
    Serial.println("\nDone blinking!");
    Serial.println("------------------------------");
  }
}

void blinkDot() {
  digitalWrite(ledPin, HIGH);
  delay(dotDuration);
  digitalWrite(ledPin, LOW);
}

void blinkDash() {
  digitalWrite(ledPin, HIGH);
  delay(dashDuration);
  digitalWrite(ledPin, LOW);
}

String charToMorse(char character) {
  switch (character) {
    case 'A': return ".-";
    case 'B': return "-...";
    case 'C': return "-.-.";
    case 'D': return "-..";
    case 'E': return ".";
    case 'F': return "..-.";
    case 'G': return "--.";
    case 'H': return "....";
    case 'I': return "..";
    case 'J': return ".---";
    case 'K': return "-.-";
    case 'L': return ".-..";
    case 'M': return "--";
    case 'N': return "-.";
    case 'O': return "---";
    case 'P': return ".--.";
    case 'Q': return "--.-";
    case 'R': return ".-.";
    case 'S': return "...";
    case 'T': return "-";
    case 'U': return "..-";
    case 'V': return "...-";
    case 'W': return ".--";
    case 'X': return "-..-";
    case 'Y': return "-.--";
    case 'Z': return "--..";
    case '0': return "-----";
    case '1': return ".----";
    case '2': return "..---";
    case '3': return "...--";
    case '4': return "....-";
    case '5': return ".....";
    case '6': return "-....";
    case '7': return "--...";
    case '8': return "---..";
    case '9': return "----.";
    default:  return "";
  }
}
