# Mechanical-Vibration-Analysis-Prototype
Real-time vibration monitoring using Arduino and MPU6050 for predictive maintenance
# Real-Time Mechanical Vibration Analysis System

## Overview

This project is an Arduino-based vibration monitoring system using the MPU6050 accelerometer. It implements a **Condition-Based Maintenance (CBM)** approach to detect machine faults in real time.

## Objective

To detect:

* Mass imbalance
* Shaft misalignment
* Structural looseness

before they cause failures.

---

## Hardware Used

* Arduino UNO
* MPU6050 Accelerometer
* 16x2 LCD (I2C)
* LEDs (Green, Yellow, Red)
* Resistors, Breadboard, Jumper wires
* USB Cable
* Power Bank
---

## How It Works

1. Measures acceleration using MPU6050
2. Removes gravity (1g)
3. Calculates vibration magnitude
4. Compares with thresholds:

| Condition         | Range       | Indicator     |
| ----------------- | ----------- | ------------- |
| Normal            | < 2.0g      | 🟢 Green LED  |
| Warning           | 2.0g – 5.0g | 🟡 Yellow LED |
| Critical(Alert!)  | > 5.0g      | 🔴 Red LED    |

---

## Features

* Real-time vibration monitoring
* Edge processing (no internet required)
* LCD display output
* Low-cost solution for SMEs

---

## System Design

https://github.com/Prabhashi07/Mechanical-Vibration-Analysis-Prototype/blob/main/Circuit%20Diagram.jpeg

---

## Industry Relevance

This project provides an affordable alternative to expensive industrial systems like:

* enDAQ
* SKF systems

---

## Project Structure

See folders for code, circuit diagrams, and documentation.

---

## Team Members

* WSA Wijerathna
* ADS Perera
* EPR Chirantha
* Sani Suraweera
* KADNP Weerasinghe


---

## Future Improvements

* Add IoT dashboard
* Store vibration history
* Use FFT for frequency analysis

---

## ⭐ If you like this project, give it a star!
