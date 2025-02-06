# Alarm Clock Project

## Overview

This project aims to implement a simple, high-speed alarm clock using the BASYS MX3 board. The focus is on practicing state machine design and the method of displaying digits using seven-segment displays (SSDs). Users can set both clock and alarm times using on-board buttons, with the time displayed in hours and minutes.

## Project Goals

- **State Machine Design**: Implement a functional state machine for the alarm clock's operation.
- **SSD Display Method**: Learn and apply techniques for displaying digits on SSDs effectively.

## Hardware Requirements

- **BASYS MX3 Board**

## Inputs and Outputs

- **Inputs**: Five on-board buttons (BTNC, BTNL, BTNR, BTNU, and BTND).
- **Outputs**:
  - Four on-board SSDs for hours (0-23) and minutes (0-59).
  - LCD for displaying the current mode with user-friendly descriptions.

## Functional Description

The alarm clock features four main modes of operation:

1. **Set Clock**: Initial mode where the clock time can be set. Hours and minutes can be incremented or decremented, and the LCD displays "Set Clock".
2. **Set Alarm**: Allows setting the alarm time. Operates similarly to setting the clock, with the LCD showing "Set Alarm".
3. **Display Time**: Shows the current time, updating every second. Transitions to "Alarming" mode when the alarm time is reached.
4. **Alarming**: In this mode, the SSDs flash, and a tone plays. The alarm lasts for 10 minutes or until a specific button combination is pressed to return to Display Time mode.

## Modes Transition

- Transitions between modes are controlled by specific button presses, outlined in the project documentation.
- Special attention is given to button sensitivity and immediate response requirements to ensure a single press results in a single action.

## Display Quality and Customer Satisfaction

- Ensures no flickering of SSD displays and maintains uniform brightness.
- Emphasizes correct operation, familiarity with the project, punctuality, presentation, and well-documented code.

