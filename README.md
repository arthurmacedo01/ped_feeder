# Ped Feeder

## Overview

The Ped Feeder is a platformio-based project designed to automate the feeding process for pets, specifically tailored for small animals like birds, rodents, or other similar pets. The system is built using an ESP32 microcontroller, a servo motor for dispensing food, and it communicates with a web application via MQTT for remote control.

## Features

- **Scheduled Feeding:** Configure specific feeding times for your pet.
- **Manual Dispensing:** Dispense food manually at any time through the web application.
- **Web Application Control:** Control the Ped Feeder remotely using a user-friendly web application.
- **MQTT Communication:** Utilizes MQTT for efficient and reliable communication between the ESP32 and the web application.

## Components

- **ESP32 Microcontroller:** The brain of the system, responsible for controlling the servo motor and handling communication with the web application.
- **Servo Motor:** Used to dispense food in a controlled manner.
- **ESP-IDF:** The ESP32 IoT Development Framework used for programming the ESP32.
- **PlatformIO:** A cross-platform build system for IoT development with the ESP-IDF framework.
- **MQTT Protocol:** Enables communication between the ESP32 and the web application.

## Installation and Setup

1. Clone the repository:
2. Open the project using PlatformIO:
3. Configure Wi-Fi and MQTT settings:
4. Upload the firmware to the ESP32
5. Run the web application

## Usage
1. Power on the Ped Feeder.
2. Access the web application in your browser.
3. Schedule feeding times or manually dispense food as needed.

## Troubleshooting
If you encounter issues, check the console logs for both the ESP32 and the web application for error messages.
Ensure that the Wi-Fi credentials and MQTT broker information are accurate.
