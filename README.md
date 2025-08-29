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

The system outputs sound through a piezo buzzer or speaker, allowing users to produce music-like tones by moving their hands in free space. Optional LEDs provide visual feedback of pitch and volume levels.  

---

## Components  
The following components are required for implementation:  

- **Arduino Uno R3** – microcontroller for computation and control.  
- **2 × HC-SR04 Ultrasonic Sensors** – gesture input for pitch and volume.  
- **Piezo buzzer or small speaker** – audio output device.  
- **Pushbuttons (optional)** – octave shifting or scale selection.  
- **LEDs + 220 Ω resistors (optional)** – visual feedback for pitch/volume.  
- **Breadboard and jumper wires** – prototyping connections.  

---

## Working Principle  

The operation of the dual-ultrasonic theremin is based on the integration of sensing, signal processing, and acoustic mapping. In the first stage, each ultrasonic sensor measures the distance of a hand placed above it; however, the raw readings are often noisy and discontinuous due to the reflective nature of ultrasonic signals. To address this, a smoothing mechanism is applied, most commonly a moving average or median filter, while more advanced implementations may employ a Kalman filter for predictive correction, similar to the radar project. Once stabilized, the hand distance captured by the pitch sensor is transformed into a musical frequency through a logarithmic mapping function, ensuring that perceived pitch changes correspond naturally to human auditory sensitivity. To maintain harmonic coherence, the computed pitch is then quantized to the nearest note within a predefined scale array, such as C major, thereby restricting output to musically consonant notes. In parallel, the second ultrasonic sensor governs the amplitude of the output signal, with hand distance mapped to the PWM duty cycle using exponential or logarithmic scaling in order to better approximate human loudness perception. Collectively, these stages enable the theremin to translate free-hand gestures into stable, musically structured sounds in real time.

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

- Gain experience in **gesture recognition** using ultrasonic sensors.  
- Understand the role of **signal processing** in stabilizing real-world sensor data.  
- Implement **scale quantization** to align engineering systems with music theory.  
- Explore the relationship between **control signals, acoustics, and perception**.  
- Acquire practical skills in **Arduino programming, real-time filtering, and embedded system design**.  

---

## Repository Structure  
```bash
02_dual_ultrasonic_theremin/
├── dual_ultrasonic_theremin.ino   # Arduino source code
├── README.md                      # Project documentation (this file)
