**Water Level Management System**


**Description**

The Water Level Management System is designed to monitor and control the water levels in a reservoir or tank. It provides real-time data on water levels and automates actions based on predefined thresholds to ensure efficient water management.

We have used various sensors such as the HC-SR04 Ultrasonic sensor and the HW-038 water level sensor with their programming code files  and ESP32, Arduino Uno R3 as the MCUs , the sim8000L as the sms sending device, the i2c lcd for displaying the water levels and the LEDs that light up in response to the detected water levels. 

**Features**<br>

__Real-time Monitoring:<br>__

Continuously monitors water levels using sensors and records the data on the cloud.<br>

__Threshold Alerts:<br>__
Alerts administrators when water levels exceed or fall below set thresholds through text sms using the sim800L gsm module technology <br>.

__Historical Data:<br>__
Logs and displays historical water level data for analysis on thingspeak iot data visualisation platform in form of line graphs according to the data recorded by the system over time .<br>

__User Interface:<br>__
Provides a user-friendly interface for system configuration and monitoring where the water levels are always displayed on the i2c lcd display and sms alerts shall be sent to  mobile phones whenever the water levels exceed the set critical levels range 

**Usage**<br>

for water level usage patterns we shall use thingspeak.com iot data visualisation platform so you may need to create an account with it if you donot have one.

<br>**Settings:**<br> 
Configure threshold levels, email notifications, and other settings in the code snippets included in the github repository for the different components.

<br>**Logs:** <br>View historical water level data and system logs for analysis.
<br>
**components**<br>
1. **water level sensors <br>
these are used to measure water levels in the tanks or reservoirs where we use the ultrasonic sensor (HC-SR04) for this project <br>
2. **microcontroller/processor**<br>
these process sensor data and control the system where we use the ESP32 mcu and Arduino Uno MCU<br>
3.**communication modules**<br>
these anable the system to transmit data to the cloud server. for this system we use the built-in Wifi module for ESP32
<br>
4.__data storage__<br>
   The system stores the collected data locally or on the cloud. for cloud storage we use thingspeak data visualisation platform with matlab.<br>
   
<br>**Contributing**<br>
Contributions are welcome! boosting our project is what we prefer. Please fork the repository and submit a pull request with your changes. For major updates, please open an issue first to discuss potential changes.


**Acknowledgements**
Sensor Integration: Thanks to Arduino for their sensor integration support and great thanks to our project co-ordinator Mr. Engineer Baino for his endless support and guidance as we work towards archieving the objectives of our project.

For support, reach out to: 
alvinnahereza@gmail.com ,  juniormusasizi6@gmail.com ,  arindaj33@gmail.com ,  mutsakaemmason@gmail.com ,  mayaj5424@gmail.com

