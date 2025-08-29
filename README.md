# Dual-Ultrasonic Theremin with Adaptive Signal Processing and Scale Quantization  

## Objectives  
The objective of this project is to design and implement a **gesture-controlled electronic musical instrument**, inspired by the classical theremin, using **dual ultrasonic sensors** and an **Arduino Uno**. Unlike a simple pitch–distance mapping, this implementation integrates signal processing and music theory concepts to provide a more rigorous and musically coherent experience. Specifically, the project aims to:  

- Demonstrate contactless musical control using ultrasonic distance sensors.  
- Apply **moving average filtering** to reduce noise in sensor readings.  
- Implement **logarithmic pitch mapping** to mimic human auditory perception.  
- Apply **scale quantization** to restrict pitches to predefined musical scales (e.g., C major).  
- Map a second ultrasonic sensor to control amplitude (volume) with perceptual scaling.  
- Provide opportunities for extensions, including octave shifting, scale selection, and LED-based visual feedback.  

---

## Project Overview  
This project extends the concept of a theremin by using two HC-SR04 ultrasonic sensors:  

- **Pitch Sensor:** Controls the musical note frequency based on hand distance.  
- **Volume Sensor:** Controls loudness by mapping hand distance to PWM duty cycle.  

The raw distance data is inherently noisy; therefore, a **moving average filter** is applied for smoothing. The filtered pitch values are mapped **logarithmically** to approximate human hearing, and then **quantized** to a musical scale to ensure harmonic output.  

The system outputs sound through a piezo buzzer or speaker, while an optional LED provides a real-time visual indicator of amplitude. Data from both sensors, the quantized note frequency, and the mapped duty cycle are continuously streamed to the Arduino Serial Plotter for real-time visualization.  

👉 [Click here to view and simulate the project in Tinkercad](https://www.tinkercad.com/things/b0iAu5wsWEE-arduino-dual-theremin)
---

## Components  
The following components are required for implementation:  

- **Arduino Uno R3** – microcontroller for computation and control.  
- **2 × HC-SR04 Ultrasonic Sensors** – gesture input for pitch and volume.  
- **Piezo buzzer** – audio output device.  
- **LED + 220 Ω resistor (optional)** – visual indicator of amplitude.  
- **Breadboard and jumper wires** – prototyping connections.  

**Pin Configuration:**  

| Component                | Arduino Pin | Notes |
|---------------------------|-------------|-------|
| HC-SR04 (Pitch) – TRIG    | D9          | Trigger output |
| HC-SR04 (Pitch) – ECHO    | D8          | Echo input |
| HC-SR04 (Volume) – TRIG   | D7          | Trigger output |
| HC-SR04 (Volume) – ECHO   | D6          | Echo input |
| Piezo Buzzer              | D5          | Audio output |
| LED (optional)            | D3 (PWM)    | Brightness ∝ volume |

---

## Working Principle  
The dual-ultrasonic theremin operates by combining gesture sensing, signal processing, and musical quantization into a cohesive system. Each ultrasonic sensor detects the distance of a hand placed above it: the first sensor governs pitch while the second controls volume. Since ultrasonic measurements are inherently noisy, the raw readings are stabilized using a moving average filter. The filtered pitch distance is then transformed into a musical frequency using a logarithmic mapping, ensuring perceptual realism by aligning pitch transitions with human auditory sensitivity. To enforce harmonic consistency, the mapped frequency is quantized to the nearest note in a predefined scale (e.g., C major), thereby restricting the instrument to musically consonant tones. Simultaneously, the second sensor determines amplitude by mapping distance to PWM duty cycle with a perceptual scaling function, allowing closer hand positions to produce louder outputs. The Arduino generates the quantized pitch via the piezo buzzer, while the LED (if connected) provides visual feedback proportional to amplitude. Additionally, the system streams pitch distance, volume distance, quantized frequency, and duty cycle values to the Arduino Serial Plotter, enabling real-time visualization of the theremin’s behavior.  

---

## Applications  
This project illustrates concepts applicable to several domains:  

- **Human–computer interaction:** Gesture-based control systems.  
- **Musical education:** Teaching scale structures and acoustics.  
- **Rehabilitation technology:** Contactless control for patients with limited mobility.  
- **Entertainment systems:** DIY instruments and interactive installations.  

---

## Learning Outcomes  
By completing this project, the following outcomes are expected:  

- Practical experience is gained in **gesture recognition** using ultrasonic sensors.  
- The role of **signal processing** in stabilizing real-world sensor data is understood.  
- **Scale quantization** is implemented to align engineering outputs with music theory.  
- The relationship between **control signals, acoustics, and perception** is explored.  
- Skills in **Arduino programming, real-time filtering, and embedded system design** are developed.  

---

## 📂 Repository Structure  
```bash
02_dual_ultrasonic_theremin/
├── dual_ultrasonic_theremin.ino   # Arduino source code
├── README.md                      # Project documentation (this file)
