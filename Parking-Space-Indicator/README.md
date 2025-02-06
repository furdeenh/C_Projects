# Gated Parking Lot System

## Overview

This project aims to create a gated parking management system for a parking lot with eight spaces. It utilizes a microphone to detect vehicles entering (signaled by a horn) and a keypad for vehicles exiting by entering a passcode. This system assigns a unique passcode for each vehicle, controlling access and ensuring efficient use of the parking lot.

## Project Goals

- **Hardware Integration**: Learn to use the Pmod keypad and BASYS MX3 Board effectively.
- **Interrupt Handling**: Understand and implement Change Notice (CN) and timer interrupts.
- **Multiple Interrupts Management**: Develop skills to handle multiple interrupts for various inputs and outputs.

## Hardware Requirements

- **BASYS MX3 Board**
- **One Pmod keypad (with cable)**

## Inputs

- **Pmod Keypad**: For entering passcodes and mode-switching.
- **On-board Microphone**: To detect the sound of a car horn as a signal for a vehicle intending to enter the parking lot.

## Outputs

- **LCD**: Displays the state of the lot and instructions.
- **SSDs**: Show passcode information.
- **LEDs**: Indicate which parking spaces are empty or occupied.
- **RGB LED**: Signals alarm states.

## Functional Description

The system operates in six main modes:

1. **Ready**: The initial state, ready for vehicle entry/exit and displaying passcodes.
2. **CarIn**: Activated by a car horn, generating a ticket with a unique passcode for the new vehicle.
3. **EnterCode**: For vehicles exiting, requiring passcode entry.
4. **CarOut**: Opens the gate upon correct passcode entry, allowing vehicle exit.
5. **ShowPasscode**: Displays the passcode for a parked car.
6. **Alarm**: Activated upon errors or invalid operations.

## Key Features

- **Mode Transitions**: Utilizes keypad inputs and microphone detection to switch between modes effectively.
- **Passcode Management**: Generates and verifies unique passcodes for each parked vehicle.
- **LED Indicators**: Use LEDs to visually represent the occupancy of parking spaces.
- **Alarm System**: Implements an alarm system for error handling, indicated by the RGB LED and error codes on the SSD.

## Development Focus

- **CN Interrupts**: For detecting keypad presses.
- **Timer Control**: Using timer interrupts for precise timing without relying on `delay_ms`.
- **Display Stability**: Ensures stable, flicker-free display on SSDs and LEDs.
- **Immediate Button Response**: Ensures button presses have immediate effects without interrupting display functionalities.

## Customer Satisfaction

Ensuring a well-functioning system includes familiarization with all aspects of the project, timely and well-presented demonstrations, and maintaining clean, well-documented code.


