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
### LED&Buttom control test
xx

### UART control test
xx

### DDR3 memory test
xx
