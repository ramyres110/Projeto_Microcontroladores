const int ledPin = LED_BUILTIN;

int currentBPM = 120; // Default tempo: 120 Beats Per Minute
long delayBetweenBeats = 60000 / currentBPM;

// --- Setup ---
void setup() {
  pinMode(ledPin, OUTPUT);
  
  Serial.begin(9600);

  Serial.println("--- Arduino LED Metronome ---");
  Serial.println("Enter a new BPM (e.g., 60, 120, 180) in the Serial Monitor and press Enter.");
  Serial.print("Current BPM: ");
  Serial.println(currentBPM);
  Serial.println("-----------------------------");
}

// --- Loop ---
void loop() {
  if (Serial.available()) {
    String inputString = Serial.readStringUntil('\n');
    int newBPM = inputString.toInt();

    if (newBPM > 20 && newBPM <= 300) {
      currentBPM = newBPM;
      delayBetweenBeats = 60000 / currentBPM;

      Serial.print("BPM updated to: ");
      Serial.println(currentBPM);
    } else {
      Serial.println("Invalid BPM. Please enter a number between 20 and 300.");
    }
    Serial.println("-----------------------------");
  }
  digitalWrite(ledPin, HIGH);
  delay(50);
  digitalWrite(ledPin, LOW);
  delay(delayBetweenBeats - 50);
}
