# Autonomous Car Parking Project

- Improvised version of [Smart Car Parking Project](https://github.com/jinmax100/smartcarparking/)
- The system capable of making 3D movement
- Access to increased number of parking slots
- Parking slot status indicated by LEDs
- Interactive Application for Reservation Parking
- Data stored and retrieved via Database (using SQL query)
- Arduino Ethernet Shield used for network connection
- Xampp Server used for localhost

# Circuit Design

![circuit_final](https://user-images.githubusercontent.com/51187747/69153403-44c9b300-0b06-11ea-9011-534b818f62e3.jpg)

# A Complete Structure

## Structure Design

![Model Diagram](https://user-images.githubusercontent.com/51187747/69150872-a89dad00-0b01-11ea-95a6-319fb780ab63.jpg)

## Mechanical Structure

![IMG_0642](https://github.com/jinmax100/multilayeredcarparking/assets/51187747/73793dcb-9e29-4c8e-8d56-71f65fde8193)

## Control Module

![Controlbox](https://github.com/jinmax100/multilayeredcarparking/assets/51187747/372c2b7c-2cf3-4d32-96e6-d35329148788)

- Contains X,Y,Z stepper motors for respective 3D movement
- Control Switches allows Manual Movement of the Structure during emergency
- A Control Module is available for the user to input unique sequence of code for security measure. Onboard Indicator facilitates information about vacant slots.
- The Slot Status is fed to/by Arduino Ethernet Shield everytime Park/Unpark Operation happens

# Android Application for Reservation Feature

<img src="https://user-images.githubusercontent.com/51187747/69150997-e569a400-0b01-11ea-95dd-734e2dfdf17d.png" width="400" height="630"> <img src="https://user-images.githubusercontent.com/51187747/69152895-59597b80-0b05-11ea-9d24-964de936a14d.png" width="400" height="630">

- User is allowed to select one of four unreserved slots (indicated by Green Color)
- Once reserved the slot indicator changes to RED preventing other users from booking it
- When the vehicle is retrieved from any of the slots, the slot color switches to Green automatically, thereby allowing other users to reserve it.
- User Information which comprises of Name, Vehicle Number and Contact Number is logged in the database
