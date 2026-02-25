# FireProtect – Smart IoT-Based Fire Alarm System
FireProtect is a multi-sensor, ESP32-powered fire detection system that combines edge intelligence (on-device processing) with real-time cloud telemetry using ThingSpeak.

The system is designed to detect fire hazards through flame, gas, and temperature sensing, execute immediate local safety actions, and simultaneously synchronize data to the cloud for remote monitoring.

**_FireProtect Working Demo Video :_** [https://drive.google.com/file/d/1QWdHHOi6V17ws_iXh-MNUxHICljmwGvG/view?usp=sharing](https://drive.google.com/file/d/1QWdHHOi6V17ws_iXh-MNUxHICljmwGvG/view?usp=sharing)

## Project Overview
FireProtect is an IoT-based smart fire detection and alert system designed for real-time monitoring and rapid emergency response.

- Uses the **ESP32** as the central controller for sensor data acquisition, decision-making, and Wi-Fi communication.

- Integrates **flame, gas (MQ-2), and temperature sensors** to implement multi-parameter fire detection, improving accuracy and reducing false alarms.

- Performs edge-based processing, meaning hazard detection and safety actions are executed directly on the ESP32 without depending on the cloud.

- Activates immediate local alerts such as **buzzer** and relay-controlled devices (pump/exhaust) when fire conditions are detected.

- Uploads real-time sensor data to **ThingSpeak** for remote monitoring, visualization, and historical logging.


## System Working
- **Continuous Environment Monitoring** : The ESP32 continuously collects data from the flame sensor, MQ-2 gas sensor, and temperature sensor to monitor fire-related parameters in real time.

- **On-Device Hazard Analysis** : Sensor readings are processed locally using threshold-based and multi-sensor validation logic to accurately detect potential fire conditions.

- **Immediate Safety Response** : If hazardous conditions are detected, the buzzer is activated and the relay triggers connected safety devices (e.g., pump or exhaust system) instantly.

- **Cloud Logging & Remote Monitoring** : Simultaneously, sensor data is uploaded to ThingSpeak for real-time visualization, historical storage, and remote access via the web dashboard.


## Hardware Architecture
- **ESP32** : The ESP32 acts as the central controller of FireProtect. It reads sensor inputs, executes hazard detection logic, and uploads real-time data to the cloud using its built-in Wi-Fi capability. Its dual-core processing ensures fast response and reliable performance.

- **Flame Sensor (IR-Based)** : Detects infrared radiation emitted by open flames. It provides a digital output when flame intensity crosses a threshold, enabling immediate fire detection.

- **MQ-2 Gas Sensor** : Used to detect combustible gases such as LPG, methane, and smoke. It provides an analog output proportional to gas concentration, allowing threshold-based hazard classification.

- **Temperature Sensor (DHT11)** : Monitors ambient temperature levels to detect abnormal heat rise. It supports environmental validation to reduce false fire alarms.

- **Buzzer** : Acts as the primary local alert mechanism. It is triggered instantly when fire conditions are detected, ensuring immediate on-site warning.


## Sensor Programming
- **Hardware Connections Setup** : Sensors (Flame – digital pin, MQ-2 – analog pin, DHT11 – digital pin) and output devices (buzzer, relay) are interfaced with the ESP32 GPIO pins with proper power (3.3V/5V) and GND connections.

- **Initialization** : ESP32 configures all GPIO modes (INPUT/OUTPUT), initializes Serial communication, and establishes Wi-Fi + ThingSpeak API connection in the setup phase.

- **Sensor Monitoring** : In the main loop, the ESP32 continuously reads digital (flame), analog (gas), and temperature values from connected sensors.

- **Edge-Based Decision Logic** : Sensor readings are compared with predefined thresholds, applying multi-sensor validation to reduce false alarms.

- **Local Alert & Cloud Update** : If hazard conditions are met, the buzzer and relay are triggered instantly, and sensor data is uploaded to ThingSpeak at regulated intervals for real-time monitoring.


## ThingSpeak Cloud Integration
FireProtect integrates with ThingSpeak for real-time data monitoring and cloud storage.
- **Channel Configuration** : A dedicated ThingSpeak channel is created with separate fields for flame status, gas level, and temperature readings.

- **API-Based Communication** : The ESP32 connects to Wi-Fi and uses the ThingSpeak Write API key to securely transmit sensor data via HTTP requests.

- **Structured Data Upload** : Each sensor value is mapped to a specific field and updated at controlled intervals to comply with cloud rate limits.

- **Real-Time Visualization** : ThingSpeak automatically generates live graphs and stores timestamped historical data for analysis and remote monitoring.

This ensures continuous cloud logging while maintaining offline-first local safety functionality.


## Website Integration
A lightweight web interface was developed to provide remote access to FireProtect’s cloud data.

- **Cloud Data Fetching** : The website retrieves real-time sensor values from the ThingSpeak channel using API-based data requests.

- **Live Monitoring Dashboard** : Displays flame status, gas concentration, and temperature readings in a simple, user-friendly format.

- **Remote Accessibility** : Enables users to monitor fire conditions from any device with internet access.

The website acts as an additional monitoring layer, while the core detection and safety logic remain hardware-driven on the ESP32.


## Applications
- **Residential Homes** : Early fire detection to protect lives and property.

- **Laboratories & Server Rooms** : Monitoring gas leaks and overheating equipment.

- **Warehouses & Industrial Units** : Detecting combustible gas buildup and fire hazards.

- **Commercial Buildings & Offices** : Real-time monitoring with remote cloud access.
