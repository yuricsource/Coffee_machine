# ESP32C3 MQTT Device for Home Assistant

This project implements an MQTT device using the ESP32C3 microcontroller programmed in C++ with the ESP-IDF (version 5.2). The device connects to a Home Assistant server to provide sensor data or control devices.

## Table of Contents
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Installation](#installation)
- [Configuration](#configuration)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Features
- Connects to Home Assistant via MQTT
- Supports multiple sensors/actuators
- Configurable via JSON
- Secure connection using TLS
- Over-the-air (OTA) updates

## Hardware Requirements
- ESP32C3 Development Board
- Sensors/Actuators (e.g., DHT11/DHT22, relay module)
- Power Supply
- USB Cable

## Software Requirements
- ESP-IDF v5.2
- C++ compiler
- Home Assistant server
- MQTT Broker (e.g., Mosquitto)

## Installation
### Setting up ESP-IDF
1. Follow the [ESP-IDF installation guide](https://docs.espressif.com/projects/esp-idf/en/v5.2/esp32/get-started/index.html) to set up ESP-IDF v5.2.
2. Clone this repository:
    ```bash
    git clone https://github.com/yourusername/esp32c3-mqtt-home-assistant.git
    cd esp32c3-mqtt-home-assistant
    ```

### Building and Flashing
1. Configure the project:
    ```bash
    idf.py menuconfig
    ```
2. Build the project:
    ```bash
    idf.py build
    ```
3. Flash the firmware to your ESP32C3:
    ```bash
    idf.py flash
    ```
4. Monitor the output:
    ```bash
    idf.py monitor
    ```

## Configuration
### Home Assistant Configuration
1. Add MQTT integration in Home Assistant.
2. Configure your sensors/actuators in Home Assistant's `configuration.yaml`:
    ```yaml
    mqtt:
      sensor:
        - name: "Temperature Sensor"
          state_topic: "home/esp32c3/temperature"
        - name: "Humidity Sensor"
          state_topic: "home/esp32c3/humidity"
      switch:
        - name: "Relay"
          command_topic: "home/esp32c3/relay"
    ```

### Device Configuration
Edit the `config.json` file in the project directory to match your MQTT broker settings:
```json
{
  "wifi_ssid": "your_wifi_ssid",
  "wifi_password": "your_wifi_password",
  "mqtt_broker": "mqtt://your_mqtt_broker",
  "mqtt_port": 1883,
  "mqtt_user": "your_mqtt_user",
  "mqtt_password": "your_mqtt_password"
}
