#include <iostream>
#include <cstdlib>
#include "pdm_to_pcm.h"  // Include the header where the pdm_to_pcm function prototype is declared.

// Function to generate random PDM data and expected PCM output
void generate_test_data(hls::stream<ap_uint<PDM_BIT_WIDTH>>& pdm_stream, int& expected_pcm_output) {
    int pdm_high_count = 0;
    std::cout << "Generated PDM Signal: ";
    for (int i = 0; i < DECIMATION_FACTOR; i++) {
        ap_uint<PDM_BIT_WIDTH> pdm_bit = std::rand() % 2;  // Randomly generate 0 or 1
        pdm_stream.write(pdm_bit);
        pdm_high_count += pdm_bit.to_uint();  // Sum the high bits to compute expected output
        std::cout << pdm_bit.to_uint() << " "; // Display each PDM bit as it is generated
    }
    std::cout << std::endl;
    expected_pcm_output = pdm_high_count / DECIMATION_FACTOR;  // Calculate expected average
}

int main() {
    // Seed the random number generator for reproducibility
    std::srand(123);

    // Initialize the stream objects for input and output
    hls::stream<ap_uint<PDM_BIT_WIDTH>> test_pdm_stream;
    hls::stream<ap_uint<PCM_BIT_WIDTH>> test_pcm_stream;

    // Variables to hold the expected and actual output
    int expected_pcm_output = 0;
    int actual_pcm_output = 1;
    short done = 0;

    // Generate test data and expected results
    generate_test_data(test_pdm_stream, expected_pcm_output);

    // Perform the conversion
    pdm_to_pcm(test_pdm_stream, test_pcm_stream, done);

    // Read the output from the PCM stream
    if (!test_pcm_stream.empty()) {
        actual_pcm_output = test_pcm_stream.read().to_uint();
        std::cout << "Actual PCM Output: " << actual_pcm_output << std::endl;
    } else {
        std::cout << "No PCM output generated." << std::endl;
    }

    // Display expected PCM output
    std::cout << "Expected PCM Output: " << expected_pcm_output << std::endl;

    // Determine pass or fail
    if (actual_pcm_output == expected_pcm_output) {
        std::cout << "Test Passed." << std::endl;
    } else {
        std::cout << "Test Failed." << std::endl;
    }

    return 0;
}