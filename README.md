# ESP8266 PC Power

## Overview

This project uses an ESP8266 microcontroller to create a web server for remotely managing a computer's power state. It includes features like a login page, failed login handling, and a control panel for turning on the computer.

## Features

- **Login Page:** Secure access to the control panel.
- **Failed Login Handling:** Informative messages for incorrect login attempts.
- **Control Panel:** Simple interface to remotely turn on the computer.

## Hardware Requirements

- **ESP8266 Microcontroller:** Used as the main controller for the web server. I used "Wemos D1 Mini".
- **Relay switch:** Relay swich is used as a switch (who would have guessed). i used "JQC-3FF-S-Z Module KY-019 5V One 1 Channel Relay"
- You can purchase the required ESP8266 microcontroller, such as the "Wemos D1 Mini," from [this link](https://www.aliexpress.com/w/wholesale-Wemos-D1-mini.html?spm=a2g0o.productlist.search.0).
- You'll need a relay switch like [this one](https://www.aliexpress.com/item/1005005654379195.html?spm=a2g0o.productlist.main.17.20203358jZkazw&algo_pvid=ee9f0dc9-ca21-4938-b951-e6865958626a).

## ESP8266 and Relay Switch Connection

To enable communication between the ESP8266 and the relay switch, follow these wiring instructions:

- Connect the **ESP8266 5V pin** to the **Relay Switch 5V pin**.
- Connect the **ESP8266 GND (Ground) pin** to the **Relay Switch GND (Ground) pin**.
- Connect the **Relay Switch IN pin** to the **ESP8266 D1 pin**.

## ESP8266 Power Options

You have the flexibility to power the ESP8266 through various methods:

1. **Motherboard Connection:**
   - Connect the **ESP8266 Ground (GND) pin** to the **Motherboard Ground pin**.
   - Connect the **ESP8266 5V pin** to the **Motherboard 5V pin**.
   - *Note: Refer to your motherboard manual for an appropriate port; I connected mine to an available port providing USB power to the computer's front panel.*

2. **USB Port:**
   - Use the **ESP8266 USB port**.
   - Connect it to a power source like a phone charger or a computer's USB port.
   - *Note:If you choice computer's USB port, this option may depend on your motherboard's settings.*

Ensure secure connections based on your preferred power option for reliable functionality.

## Setup

1. Connect the ESP8266 and relay switch to your computer.
2. Update Wi-Fi credentials and login details in the code.
3. Upload the code to the ESP8266.

## Modifying Default Credentials

To enhance the security of your ESP8266 Computer Control, consider changing the default login credentials. Follow these steps:

1. Open the Arduino sketch file.
2. Locate **line 211**, which contains the following code:

   ```cpp
   if (username.equals("admin") && password.equals("admin")) {
   
Update the values within the parentheses to your preferred username and password. For example:

  ```cpp
  if (username.equals("your_name") && password.equals("your_password")) {
````

## Modifying URL Paths

To enhance security, consider modifying the URL paths in the code. Follow these steps:

1. Open the Arduino sketch file.
2. Locate **line 32** for the control panel path and **line 33** for the turn-on path. Change them to unique identifiers, for example.

   ```cpp
   server.on("/controlpanel", HTTP_GET, handlePower);
   server.on("/turnon, HTTP_GET, handleTurnOn);
  
To somesting like:

   ```cpp
   server.on("/rianKziYiCgMkdeMQkTDptmEPBPhtJqjMtRQStHx", HTTP_GET, handlePower);
   server.on("/fhHeBfgTeeTTspNBnCtXFAdnRggEDMjXQjTzGXjn", HTTP_GET, handleTurnOn);
````
And also change **line 213** and **line 285** in the code to match what you modified on lines 32 and 33.

 ```cpp
   server.sendHeader("Location", "/controlpanel", true);
   html += "            fetch('/turnon');";
````
To 

 ```cpp
   server.sendHeader("Location", "/rianKziYiCgMkdeMQkTDptmEPBPhtJqjMtRQStHx", true);
   html += "            fetch('/fhHeBfgTeeTTspNBnCtXFAdnRggEDMjXQjTzGXjn');";
````

## Usage

1. Power on the ESP8266 and ensure the relay switch is connected.
2. Connect to the Wi-Fi network.
3. Open a web browser and navigate to the ESP8266's IP address.
4. Log in using specified credentials.

