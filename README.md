# Secure-Home-V1
# An Automated Multi-Sensor Security System

An autonomous, 24/7 event-driven home security system prototype built on the ATmega328P architecture. By transitioning away from standard linear, sequential scripts, this project utilizes a **Finite State Machine (FSM)** and **Hardware Interrupt Service Routines (ISRs)** to achieve microsecond-level detection and multi-sensory data integration.

## 💻 System Architecture & Logic Flow

The system runs as an event-driven Finite State Machine operating across three distinct states:
* **DISARMED:** System idle. RGB LED is Solid Green. Displays "SYSTEM READY" on the screen.
* **ARMED:** Monitoring active. RGB LED is Solid Blue. Explicitly clears stale register flags upon entry to prevent immediate false triggers.
* **ALARM:** Threat detected. RGB LED flashes Red alternating with a 1kHz Piezo buzzer alert using a non-blocking execution model.

### System Block Diagram

  [ PIR Sensor (Digital Pin 2) ] ----(Hardware Interrupt)----> [                  ] ----> [ 16x2 I2C LCD (Status Display) ]
  [ Push Button (Digital Pin 3) ] ---(Software Debounced)----> [   Arduino Uno    ] ----> [ RGB LED (Visual Alarm Pins 9,10,11) ]
  [ Photoresistor (Analog Pin A0) ] -(Analog Threshold Check)-> [  (ATmega328P)   ] ----> [ Piezo Buzzer (Audio Alert Pin 8) ]

Component,Purpose,Technical Justification
Arduino Uno,Microcontroller Core,"Coordinates system logic, captures external asynchronous triggers, and processes state updates."
HC-SR501 PIR Sensor,Motion Detection,Delivers passive infrared motion tracking; mapped directly to a hardware interrupt pin for low-latency preemption.
Photoresistor (LDR),Environmental Light Sensor,"Serves as a secondary trigger path to capture rapid changes in illumination levels (e.g., flashlights)."
16x2 I2C LCD,Local Status Interface,Minimizes I/O pin consumption by routing display transmissions through a 2-wire I2C protocol bus.
RGB LED & Piezo Buzzer,Multi-Sensory Alert Terminal,"Delivers concurrent, synchronous visual (color-coded status updates) and audio alerting layers."
Resistors (220Ω & 10KΩ),Circuit Integrity,220Ω inline resistors limit current to the LED elements; 10KΩ pull-down resistors prevent floating inputs.
