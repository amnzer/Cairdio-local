#include "xparameters.h"
#include "xil_printf.h"
#include "xgpio.h"
#include "xuartlite.h"
#include "xil_types.h"

// Get device IDs from xparameters.h
#define BTN_ID XPAR_AXI_GPIO_BUTTONS_BASEADDR
#define LED_ID XPAR_AXI_GPIO_LED_BASEADDR
#define UART_DEVICE_ID XPAR_AXI_UARTLITE_0_BASEADDR
#define BTN_CHANNEL 1
#define LED_CHANNEL 1
#define BTN_MASK 0b1111
#define LED_MASK 0b1111

// DDR memory address where button press counts are stored
#define DDR_BASE_ADDR 0x80000000
#define DDR_BUTTON_COUNT_OFFSET 0x100

// Define a pointer to access the button press counts in DDR memory
volatile u32 *button_press_counts = (u32 *)(DDR_BASE_ADDR + DDR_BUTTON_COUNT_OFFSET);

int main() {
    XGpio_Config *cfg_ptr;
    XGpio led_device, btn_device;
    XUartLite uart;
    u32 data;
    u32 last_data = 0;
    u8 uart_input;

    xil_printf("Entered function main\r\n");

    // Initialize LED Device
    cfg_ptr = XGpio_LookupConfig(LED_ID);
    XGpio_CfgInitialize(&led_device, cfg_ptr, cfg_ptr->BaseAddress);

    // Initialize Button Device
    cfg_ptr = XGpio_LookupConfig(BTN_ID);
    XGpio_CfgInitialize(&btn_device, cfg_ptr, cfg_ptr->BaseAddress);

    // Initialize UART Lite
    if (XUartLite_Initialize(&uart, UART_DEVICE_ID) != XST_SUCCESS) {
        xil_printf("UART initialization failed\r\n");
        return XST_FAILURE;
    }

    // Set Button Tristate
    XGpio_SetDataDirection(&btn_device, BTN_CHANNEL, BTN_MASK);

    // Set Led Tristate
    XGpio_SetDataDirection(&led_device, LED_CHANNEL, 0);

    // Initialize DDR memory area to 0
    for (int i = 0; i < 4; i++) {
        button_press_counts[i] = 0;
    }

    while (1) {
        // Check if UART has received data
        if (XUartLite_Recv(&uart, &uart_input, 1)) {
            if (uart_input == 'R') {
                xil_printf("Recording started.\r\n");
            } else if (uart_input == 'S') {
                xil_printf("Recording stopped. Displaying counts:\r\n");
                for (int i = 0; i < 4; i++) {
                    xil_printf("Button %d: %d presses\r\n", i + 1, button_press_counts[i]);
                }
                continue;  // Skip processing to show results
            }
        }

        data = XGpio_DiscreteRead(&btn_device, BTN_CHANNEL);
        data &= BTN_MASK;

        for (int btn_index = 0; btn_index < 4; btn_index++) {
            u32 mask = 1 << btn_index;
            if ((data & mask) != 0 && (last_data & mask) == 0) {
                button_press_counts[btn_index]++;  // Increment the count for this button
                xil_printf("Button %d Pressed! Total presses: %d\r\n", btn_index + 1, button_press_counts[btn_index]);
            }
        }

        if (data != 0) {
            data = LED_MASK & data;
        } else {
            data = 0;
        }
        XGpio_DiscreteWrite(&led_device, LED_CHANNEL, data);
        last_data = data;
    }
}