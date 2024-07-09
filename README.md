__Water Level Management System__

**Description**

The Water Level Management System is designed to monitor and control the water levels in a reservoir or tank. It provides real-time data on water levels and automates actions based on predefined thresholds to ensure efficient water management.
we have used various sensors such as the HC-SR04 Ultrasonic sensor and the HW-038 water level sensor with their programming code files  and ESP32, Arduino Uno R3 as the MCUs , and the sim8000L as the sms sending device plus the i2c lcd for displaying the water levels 

**Features**<br>
__Real-time Monitoring:<br>__
Continuously monitors water levels using sensors and records the data.<br>
__Threshold Alerts:<br>__
Alerts administrators when water levels exceed or fall below set thresholds through text sms using the sim800L gsm module technology <br>.
**Automated Control:<br>**
Automatically controls inlets or valves to maintain desired water levels according to the data recorded by the water level sensors<br> .
__Historical Data:<br>__
Logs and displays historical water level data for analysis on thingspeak iot data visualisation platform in form of line graphs according to the data recorded by the system over time .<br>
__User Interface:<br>__
Provides a user-friendly interface for system configuration and monitoring where the water levels shall always be displayed on the i2c lcd display and sms alerts shall be sent to screen display mobile phones whenever the water levels exceed the set critical levels range 


**Usage**<br>

for water level usage patterns we shall use thingspeak.com iot data visualisation platform so you may need to create an account with it if you domt have one.

<br>**Dashboard:** <br>
Upon accessing the cloud platform fir the project, the dashboard displays real-time water level data and status with usage line graphs and time period.
<br>**Settings:**<br> 
Configure threshold levels, email notifications, and other settings in the code snippets included in the github repository for the different components.
<br>**Logs:** <br>View historical water level data and system logs for analysis.
<br>__Contributing__<br>
Contributions are welcome! boosting our project is what we prefer. Please fork the repository and submit a pull request with your changes. For major updates, please open an issue first to discuss potential changes.


Acknowledgements
Sensor Integration: Thanks to Arduino for their sensor integration support and great thanks to our project coordinator Mr. Engineer Baino for his endless support and guidance as we work towards archieving the objectives of our project.

For support, reach out to: juniormusasizi6@gmail.com,  arindaj33@gmail.com, alvinnahereza@gmail.com, mutsakaemmason@gmail.com, mayaj5424@gmail.com

