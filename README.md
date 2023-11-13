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

