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
Here is my code to control the LED and button.
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
Here is my code to control the UART interface.
```
// Check if UART has received data
received_count = XUartLite_Recv(&uart, &uart_input, 1);
if (received_count != 0) {  // Check if data was received
    if (uart_input == 'R') {
        capture_enabled = 1; // Enable capturing
        xil_printf("Recording started.\r\n");
    } else if (uart_input == 'S') {
        capture_enabled = 0; // Disable capturing
        xil_printf("Recording stopped.\r\n");
    }
}
```
This code snippet is designed to manage recording operations controlled via UART commands on a hardware device. It begins by checking if any data has been received from the UART using the XUartLite_Recv function. This function attempts to read a single byte of data into the uart_input variable and returns the number of bytes received, which is stored in received_count. If received_count is not zero, indicating that data was indeed received, the code then checks the value of uart_input. If the received character is 'R', recording is enabled (capture_enabled is set to 1), and a message "Recording started." is printed to the terminal. Conversely, if the character is 'S', recording is disabled (capture_enabled is set to 0), and a message "Recording stopped." is printed. This mechanism allows for simple control of recording states through UART commands.

And here is the serial terminal display.

<img width="414" alt="b92d9a435efda6dbadaca1f315408c3" src="https://github.com/user-attachments/assets/41e0314c-08e6-4c83-9848-000c5836f356">

On the display, after we press "R" on the keyboard, "Recording started" appears in our terminal and the button press count begins. After pressing "S" on the keyboard, "Recording stopped" appears in our terminal, and it stops recording our button presses.

### DDR3 memory test
Here is my code to control the DDR3 memory.

First we set a pointer to access the button press counts in DDR memory.
```
// DDR memory address where button press counts are stored
#define DDR_BASE_ADDR 0x80000000
#define DDR_BUTTON_COUNT_OFFSET 0x100

// Define a pointer to access the button press counts in DDR memory
volatile u32 *button_press_counts = (u32 *)(DDR_BASE_ADDR + DDR_BUTTON_COUNT_OFFSET);
```
For detailed DDR memory addresses, you can check in xparameters.h. In my design, it appears like this:
```
#define XPAR_MIG_0_BASEADDRESS 0x80000000
```

Then we initialize DDR memory area to 0.
```
for (int i = 0; i < 4; i++) {
    button_press_counts[i] = 0;
}
```

When we stop the recording, we display our counts number.
```
for (int btn_index = 0; btn_index < 4; btn_index++) {
    u32 mask = 1 << btn_index;
    if ((data & mask) != 0 && (last_data & mask) == 0) {
        button_press_counts[btn_index]++;  // Increment the count for this button
        xil_printf("Button %d Pressed! Total presses: %d\r\n", btn_index + 1, button_press_counts[btn_index]);
    }
}
```
This code snippet is designed to detect and count button presses for a set of four buttons. It loops through each button, identified by btn_index, from 0 to 3. For each button, it creates a mask by left-shifting 1 by the button's index, which helps isolate the state of each button in the data variable. The condition ((data & mask) != 0 && (last_data & mask) == 0) checks if the current button was pressed in this cycle and was not pressed in the previous cycle, ensuring that only new presses are counted. If the condition is true, the corresponding button's count in the button_press_counts array is incremented. Additionally, a message is printed to the terminal indicating which button was pressed and displaying the total number of times that button has been pressed. This allows for real-time monitoring and verification of button press events.

And here is the serial terminal display.

<img width="426" alt="80b35f6fef6887f4e12c466f64ffea9" src="https://github.com/user-attachments/assets/5e39dc0f-310f-4f5f-ab43-db1122b3b11d">

In the terminal, we can see that after we stop the recording, it correctly displays our button_press_counts pointer, which is stored in our DDR memory.



