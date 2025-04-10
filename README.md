# 🌡️ DIY Weather Display: ESP8266 + BMP280 + OLED

![smart_weather_display]([project-image.jpg](https://github.com/Dhaivatjoshi/smart_weather_display/blob/main/img/IMG_0712.jpg)) <!-- Replace with your actual image file name -->

A simple and compact weather station that displays live temperature data using an **ESP8266**, **BMP280 sensor**, and a **128x32 OLED display**. The project communicates via I2C and runs on 3.3V logic.

## 🛠️ Components Used

- ESP8266 (NodeMCU or similar)
- BMP280 (Temperature & Pressure Sensor)
- 128x32 OLED Display (I2C)
- Breadboard & Jumper Wires
- 3.3V Power Supply (e.g., Breadboard Power Module)

## 🔌 Wiring

| Module      | ESP8266 Pin |
|-------------|-------------|
| BMP280 SDA  | D2 (GPIO4)  |
| BMP280 SCL  | D1 (GPIO5)  |
| OLED SDA    | D2 (GPIO4)  |
| OLED SCL    | D1 (GPIO5)  |
| VCC         | 3.3V        |
| GND         | GND         |

> ⚠️ Important: Ensure the BMP280 module you use supports 3.3V logic to avoid hardware damage.

## 💻 Features

- Reads live temperature data from the BMP280
- Displays real-time temperature on OLED screen
- I2C communication for both BMP280 and OLED
- Lightweight and low-power design

## 🧠 How It Works

The ESP8266 continuously polls the BMP280 sensor via I2C and updates the OLED screen with current temperature readings every second. Ideal for beginners exploring IoT and sensor integration.

## 📷 Project Demo

![Working Setup](working-demo.jpg) <!-- Replace with your actual demo image -->

📺 Watch the YouTube build video: [YouTube Link](https://your-video-link.com)  
📘 View the KiCad wiring schematic: Included in `/schematic` folder

## 🔗 License

This project is open-source and free to use under the [MIT License](LICENSE).

---


