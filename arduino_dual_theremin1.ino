// Dual Ultrasonic Theremin with Scale Quantization & Moving Average Filtering
// - Pitch: HC-SR04 on TRIG D9, ECHO D8
// - Volume: HC-SR04 on TRIG D7, ECHO D6
// - Audio out: Piezo on D5
// - Optional LED brightness: D3 (PWM)
// - Serial Plotter: 4 labeled series printed every ~50 ms (115200 baud)

const int trig1 = 9, echo1 = 8; // Pitch sensor
const int trig2 = 7, echo2 = 6; // Volume sensor
const int buz   = 5;            // Piezo
const int led   = 3;            // Optional LED (PWM)
const int N     = 5;            // Moving average window size

// Scale in MIDI note numbers (C major, ~2 octaves from C4=60)
int scale[] = {60, 62, 64, 65, 67, 69, 71, 72,
               74, 76, 77, 79, 81, 83, 84};
int scaleLen = sizeof(scale) / sizeof(scale[0]);

long buf1[N], buf2[N]; // ring buffers for smoothing
int  idx = 0;

// ----- Ultrasonic helpers -----
long readUS(int t, int e) {
  digitalWrite(t, LOW); delayMicroseconds(2);
  digitalWrite(t, HIGH); delayMicroseconds(10);
  digitalWrite(t, LOW);
  return pulseIn(e, HIGH, 25000); // timeout 25ms (~4m)
}
float distCM(int t, int e) {
  long u = readUS(t, e);
  return u ? (u * 0.0343f / 2.0f) : 60.0f; // cap to 60 cm if no echo
}

// ----- Music helpers -----
float mtof(int m) { return 440.0f * pow(2.0f, (m - 69) / 12.0f); } // MIDI->Hz

int quantizeToScale(float freqHz) {
  float bestDiff = 1e9;
  int bestNote = scale[0];
  for (int i = 0; i < scaleLen; ++i) {
    float f = mtof(scale[i]);
    float d = fabs(f - freqHz);
    if (d < bestDiff) { bestDiff = d; bestNote = scale[i]; }
  }
  return bestNote;
}

// ----- Moving average smoothing -----
float smooth(long *buf, float val) {
  buf[idx] = (long)val;
  long sum = 0;
  for (int i = 0; i < N; ++i) sum += buf[i];
  return (float)sum / N;
}

void setup() {
  pinMode(trig1, OUTPUT); pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT); pinMode(echo2, INPUT);
  pinMode(buz, OUTPUT);
  pinMode(led, OUTPUT);

  for (int i = 0; i < N; ++i) { buf1[i] = 30; buf2[i] = 30; }

  Serial.begin(115200);
  // No header needed for Arduino Plotter when using label:value pairs
}

void loop() {
  static unsigned long lastPlot = 0;

  // Advance smoothing index
  idx = (idx + 1) % N;

  // Read & smooth distances (cm)
  float d1 = smooth(buf1, distCM(trig1, echo1)); // pitch control
  float d2 = smooth(buf2, distCM(trig2, echo2)); // volume control

  // Map pitch distance (5–50 cm) logarithmically to ~C4–C6
  // Base C4 = 261.6 Hz; (50 - d1)/25 spans ~2 octaves
  float freqIn = 261.6f * pow(2.0f, (50.0f - d1) / 25.0f);
  int   note   = quantizeToScale(freqIn);
  int   fHz    = (int)mtof(note);

  // Map volume distance (5–50 cm) to duty (perceptual: closer = louder)
  int duty = map((int)d2, 5, 50, 255, 10);
  duty = constrain(duty, 0, 255);

  // Audio + optional LED amplitude indicator
  tone(buz, fHz, 10);         // short tone burst; refreshed every loop
  analogWrite(led, duty);     // LED brightness proportional to volume

  // ---- Serial Plotter output: 4 labeled series, tab-separated ----
  if (millis() - lastPlot > 50) {  // ~20 Hz update for smooth graph
    lastPlot = millis();
    Serial.print("d1_cm:");   Serial.print(d1, 2);   Serial.print('\t');
    Serial.print("d2_cm:");   Serial.print(d2, 2);   Serial.print('\t');
    Serial.print("noteHz:");  Serial.print(fHz);     Serial.print('\t');
    Serial.print("duty:");    Serial.println(duty);
  }

  delay(10); // small pacing delay
}