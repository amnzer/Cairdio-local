# ENABLE FreeRTOS & UART and CONFIGURE On-Board DDR RAM with FreeRTOS

This repository showcases the setup and configuration of FreeRTOS, a real-time operating system, on the FPGA platform. The setup includes configuring UART (Universal Asynchronous Receiver/Transmitter) for serial communication, which forms the foundation for managing multiple tasks and enhancing debugging capabilities. Additionally, it involves configuring the on-board DDR (Double Data Rate) RAM within the FreeRTOS environment to enable the system to record and store large volumes of data, such as audio inputs from PDM microphones, in DDR RAM.

## Implementation

A basic setup for my FPGA, the ARTY S7-50, can be seen [here](https://community.element14.com/technologies/fpga-group/b/blog/posts/arty-s7-50-first-baremetal-software-project).

By following this guide, you can establish the basic functionality of the ARTY S7. However, to enable FreeRTOS, an AXI Timer is also required. You can use the AXI LED settings in the guide as an example to set up the Timer.

After completing all the steps, you can build the HDL wrapper and generate the bitstream. Once you export the hardware, you will obtain an XSA file. I have included my XSA and XDC files in this repository.

Here is a general overview of the block diagram I built:
<img width="1003" alt="ARTY S7 FreeRTOS" src="https://github.com/user-attachments/assets/fdd03d65-a541-4d29-96f1-9c37cf1f4ae2">

## Hardware/Software setting
- FPGA: ARTY S7-50
* Vivado: 2024.1
+ Vitis: 2024.1
- Serial Terminal Program: Tera Term 5
* PC: Window11

## Results
After creating the FreeRTOS block design for the ARTY S7-50 and generating the bitstream, we can create our FreeRTOS platform in the Vitis IDE (remember to select FreeRTOS in the OS system choices). Then, we can create an application and write C code to control our FPGA. Details of my C code can be seen in the Vitis application folder.

### LED&Buttom control test
Here is my code to control the LED and Buttom. 
```
data = XGpio_DiscreteRead(&btn_device, BTN_CHANNEL);
data &= BTN_MASK;

if (data != 0) {
 data = LED_MASK & data;
} else {
  data = 0;
}
XGpio_DiscreteWrite(&led_device, LED_CHANNEL, data);
```
This code snippet is designed to interact with GPIO devices, specifically for reading button inputs and controlling LED outputs on a hardware board. Initially, it reads the state of buttons connected to a specific channel (BTN_CHANNEL) using the XGpio_DiscreteRead function, which fetches the button states and stores them in the data variable. The button states are then filtered using a bitmask (BTN_MASK) to ensure only relevant bits are considered, effectively isolating the button presses of interest. If any button is pressed (data != 0), the code maps the button state directly to corresponding LEDs using another bitmask (LED_MASK). This ensures that only certain LEDs corresponding to the pressed buttons are activated. If no buttons are pressed (data == 0), all LEDs are turned off. Finally, the result is written to the LED device using XGpio_DiscreteWrite, updating the LEDs to reflect the state of the buttons.

![Freertos_blinking_LED](https://github.com/user-attachments/assets/64dc7798-2d4c-453e-95a7-038ab41c1b63)

### UART control test
xx

### DDR3 memory test
xx
