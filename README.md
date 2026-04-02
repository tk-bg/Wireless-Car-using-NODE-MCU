# Wireless-Car-using-NODE-MCU
The project is inspired by Brian Lough: https://www.youtube.com/watch?v=0zs-A_fC3Yg&pp=ygUmd2lmaSBlbmFibGVkIGVzcDg2NiBjYXIgYnkgYnJpYW4gbG91Z2jSBwkJ2QoBhyohjO8%3D
His github: https://github.com/witnessmenow/simple-wifi-controlled-rc-car.git
The code is copied from Brian Lough and modified using Gemini, so the program is not optimised and perfect.
The car uses ESP8266 with a servo for steering and a HTML page, communicates through a WIFI network, is possible to control from different routers in same network
If you are using different IO pins change the pins in the MotorWeb.ino page
The network must be the same ie. the car(NODEMCU) and the controlling device must be on the same network.
If the network has a captive login portal, remove the password line indicated by comments in the program.
If you are using a laptop, the the hotkeys can be swapped in the motorpage.h file at the bottom of the program. Using laptop is not reccomended as it causes input flooding, the code is not yet optimised for laptop input
If the network signal is weak the control signals will be delayed and the car may not act as per the input so connect to a strong network.
To connect to the car, connect the NODEMCU to the computer.
Select "NodeMCU 1.0 (ESP-12E Module)" and click ok.
Make the changes as required.
Hit upload, if connection is successful, the board blinks for seconds and the ip address is displayed on the serial moniter.
In your browser enter the ip and the web page will appear.
