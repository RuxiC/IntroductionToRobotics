# IntroductionToRobotics (2023-2024)

Welcome to my repository "Introductions to Robotics", taken in the 3rd year at the Faculty of Mathematics and Computer Science, University of Bucharest. In this repository you will find my laboratory homeworks and each homework includes requirements, implementation details, code, image and video files. I hope you find it easy to look through my repository.

**Enjoy your journey through it!**

## hw1_RGB_LED_ThreePotentiometer
This homework focuses on controlling each channel (Red, Green, and Blue) of an RGB LED using individual potentiometers and sets the LED color intensity accordingly to their values. For this task I used an RGB LED, 3 potentiometres, 3 resistors and wires. 

![Photo of my setup](https://github.com/RuxiC/IntroductionToRobotics/blob/main/Homeworks/RGB%20LED.jpeg?raw=true)

A link to a video showcasing functionality: https://youtu.be/4wzaLNyriBM?si=iP72ob-rOqtPy4c4

## hw2_Elevator_simulator_wannabe
This  homework  involves  simulating  a  3-floor  elevator  control  system  usingLEDs, buttons, and a buzzer with Arduino. For this task I used 4 LEDs(3 for the floors and 1 for the elevator’s operationalstate), 3 buttons, 1 buzzer, 4 resistors and wires.
This elevator should work like this: each of the 3 LEDs should correspond to one of the 3 floors, with the LED indicating the current floor illuminated. Furthermore, an additional LED should indicate the operational status of the elevator by blinking while the elevator is in motion and remaining steady when stationary. The system should also feature 3 buttons, each representing the call buttons for the 3 floors. Pressing a button should trigger the elevator to simulate movement towards the selected floor after a brief delay of 2-3 seconds. If the elevator is already at the desired floor, pressing the corresponding button should have no effect. Additionally, with the help of the buzzer, a sound will be heard while the elevator is in motion, and when the elevator reaches the desired floor, a different sound will be heard.

![Photo of my setup](https://github.com/RuxiC/IntroductionToRobotics/blob/main/Homeworks/Elevator.jpeg?raw=true)

A link to a video showcasing functionality: https://youtu.be/cEtkX6kGO4M?si=T5QoCj9R8C4q_MOO 

## hw3_7_segment_display_drawing
This homework is about controlling the position of a segment and 'drawing' on a display using a joystick. The movement between segments is natural, with segments jumping directly from the current position to neighboring ones. The initial position is on the decimal point (DP), which will blink. Using the joystick, you can navigate between neighboring positions following a specific movement pattern. Short button presses toggle the segment's state between ON and OFF. Long presses of the button reset the entire display, turning off all segments and moving the current position back to the decimal point. For this task I used one 7-segment display, 1 joystick, resistors and wires. 

![Photo of my setup](https://github.com/RuxiC/IntroductionToRobotics/blob/main/Homeworks/7_segment.jpeg?raw=true)

A link to a video showcasing functionality: https://youtu.be/CIR4kEd2AJE

## hw4_stopwatch_timer
In this homework I tried to implement a stopwatch timer that counts in 10ths of a second and has a save lap functionality. It starts from "000.0" and offers functions such as start/stop, lap recording and reset. The lap button, when pressed during a run, stores up to four lap times, and the reset button clears the display and laps during a pause. For this task I used the 4 digit 7 segment display, 3 buttons, resistors and wires.

![Photo of my setup](https://github.com/RuxiC/IntroductionToRobotics/blob/main/Homeworks/stopwatch_timer.jpeg?raw=true)

A link to a video showcasing functionality: https://youtu.be/7BupqULa6hE

## hw5_Smart_Environment_Monitor_and_Logger
This homework focuses on devoloping a "Smart Environment Monitor and Logger" using Arduino. This system will utilize various sensors to gather environmental data, log this data intoEEPROM, and provide both visual feedback via an RGB LED and user interaction through a Serial Menu. For this task I used an ultrasonic sensor (HC-SR04), a LDR (Light-Dependent Resistor), a RGB LED, resistors and wires.

**Menu Structure:**

**1. Sensor Settings** // Go to submenu

   **1.1 Sensors Sampling Interval.** Here you should be prompted for a value between 1 and 10 seconds. Use this value as a sampling rate for the sensors.
   
   **1.2 Ultrasonic Alert Threshold.** Here you should be prompted for a threshold value for the ultrasonic sensor. You can decide if that is the min or max value (you can signal that something is too close). When sensor value exceeds the threshold value,  an alert should be given. This can be in the form of a message. If the LED is set to Automatic Mode (see section 4.2), it should also turn red if any of the sensors are outside the value.
   
   **1.3 LDR Alert Threshold.** Here you should be prompted for a threshold value for the LDR sensor. You can decide if that is the min or max value (for example, it could signal that night is coming). When sensor value exceeds the threshold value, an alert should be given. This can be in the form of a message. If the LED is set to Automatic Mode (see section 4.2), it should also turn red if any of the sensors are outside the value.
   
   **1.4 Back** // Return to main menu
   
**2. Reset Logger Data.** Should print a message, promting if you to confirm to delete all data. Something like ”are you sure?”, followed by the submenu with YES or NO. In my case, I decided to delete both sensor data at the same time.

   **2.1 Yes.**
   
   **2.2 No.**
   
**3. System Status** // Check current status and health

   **3.1 Current Sensor Readings.** Continuously print sensor readings at the set sampling rate, from all sensors.
   
   **3.2 Current Sensor Settings.** Displays  the  sampling  rate  and threshold value for all sensors.
   
   **3.3 Display Logged Data.** Displays last 10 sensor readings for all sensors. 
   
   **3.2 Back.** Return to Main menu.
   
**4. RGB LED Control** // Go to submenu

   **4.1 Manual Color Control.** Set the RGB colors manually.
   
   **4.2 LED: Toggle Automatic ON/OFF.** If  automatic  mode is ON, then the led color should be GREEN when all sensors value do not exceed threshold values (aka no alert) and RED when there is analert (aka ANY sensor value exceeds the threshold). When automatic mode is OFF, then the LED should use the last saved RGB values.
   
   **4.3 Back** // Return to main menu

![Photo of my setup](https://github.com/RuxiC/IntroductionToRobotics/blob/main/Homeworks/Smart_Environment%20Monitor_and_Logger.jpeg?raw=true)

A link to a video showcasing functionality: https://youtu.be/RYj0fW0AqT4 

## hw6_Mini_Matrix_Game

This homework involves developing a small game on the 8x8 matrix. The game has 3 types of elements: player (blinks slowly), bombs (blinks fast), wall (doesn’t blink). The basic idea is that the game generates walls on the map (50% of the map) and then you move around with the player and destroy them. At the end of the game (if you manage to destroy all the walls), a smiling face will appear on the matrix. I chose to do it Bomberman style. For this task I used a joystick, 8x8 LED matrix, a MAX7219, one capicitor, resistors and wires.

![Photo of my setup](https://github.com/RuxiC/IntroductionToRobotics/blob/main/Homeworks/Mini_Matrix_Game.jpeg?raw=true)

A link to a video showcasing functionality:
