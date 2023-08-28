# Multilayered Car Parking Project
Improvised version of [Smart Car Parking Project](https://github.com/jinmax100/smartcarparking/), which is capable of precise 3D structural movement. Slot Reservation Feature has been facilitated with the help of interactive Android Application.


# Circuit Design
![circuit_final](https://user-images.githubusercontent.com/51187747/69153403-44c9b300-0b06-11ea-9011-534b818f62e3.jpg)

## System Information
* [Arduino Mega 2560](https://store.arduino.cc/products/arduino-mega-2560-rev3) as a main control unit running mega_code.ino, and houses [Arduino Ethernet Shield](https://store.arduino.cc/products/arduino-ethernet-shield-2) which shares occupancy of slots over network.
* [Arduino Uno](https://store.arduino.cc/products/arduino-uno-rev3) running uno_code.ino communicates with Arduino Mega via I2C, and provides step signals to motor drivers.
* Series of X,Y,Z [Stepper Motors](https://www.elprocus.com/stepper-motor-types-advantages-applications/) to provide 3D Structual Movement.
* User Interface Panel contains [Matrix Keypad](https://www.electroduino.com/4x4-keypad-module/) allowing user to register Code Sequences, and [16x2 LCD Panel](https://www.electronicsforu.com/technology-trends/learn-electronics/16x2-lcd-pinout-diagram) to display relevant outputs.
* [Limit Switches](https://electricalgang.com/working-principle-of-limit-switch/) used for manual control of the structure during emergency and power cuts.

# A Complete Structure

## Structure Design

![Model Diagram](https://user-images.githubusercontent.com/51187747/69150872-a89dad00-0b01-11ea-95a6-319fb780ab63.jpg)

## Mechanical Structure

![IMG_0642](https://github.com/jinmax100/multilayeredcarparking/assets/51187747/73793dcb-9e29-4c8e-8d56-71f65fde8193)

## User Interface Panel

![Controlbox](https://github.com/jinmax100/multilayeredcarparking/assets/51187747/372c2b7c-2cf3-4d32-96e6-d35329148788)

# Android Application for Reservation Feature

<img src="https://user-images.githubusercontent.com/51187747/69150997-e569a400-0b01-11ea-95dd-734e2dfdf17d.png" width="400" height="630"> <img src="https://user-images.githubusercontent.com/51187747/69152895-59597b80-0b05-11ea-9d24-964de936a14d.png" width="400" height="630">

- User is allowed to select one of four unreserved slots (indicated by Green Color)
- Once reserved the slot indicator changes to RED preventing other users from booking it
- When the vehicle is retrieved from any of the slots, the slot color switches to Green automatically, thereby allowing other users to reserve it.
- User Information which comprises of Name, Vehicle Number and Contact Number is logged in the database

# AUTHORS
* [Jeevan Sapkota](https://github.com/jinmax100) (Project Lead)
* Dipesh Dhamala (Project Memmber)
* Kailash Shrestha (Project Member)
* Jyoti KC (Project Member)

# LICENSE
[License Terms](https://github.com/jinmax100/multilayeredcarparking/blob/master/LICENSE)
