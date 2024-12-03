#include <hls_stream.h>
#include <ap_int.h>
#include <iostream>
#include "pdm_to_pcm.h"

#define FILTER_TAPS 5
#define DECIMATION_FACTOR 64  // Example decimation factor

void pdm_to_pcm(hls::stream<ap_uint<PDM_BIT_WIDTH>>& pdm_stream, hls::stream<ap_uint<PCM_BIT_WIDTH>>& pcm_stream, short &done) {

    #pragma HLS INTERFACE axis port=pdm_stream
    #pragma HLS INTERFACE axis port=pcm_stream


    #pragma HLS INTERFACE mode=s_axilite port=return
    #pragma HLS INTERFACE mode=s_axilite port=done

    // Define FIR filter coefficients
    const float coefficients[FILTER_TAPS] = {0.1, 0.2, 0.4, 0.2, 0.1};

    // Buffer to store the last N samples
    float sample_buffer[FILTER_TAPS] = {0};

    // Accumulate the outputs for decimation
    static float output_accumulator = 0.0f;
    static int sample_count = 0;

    // Read and process each sample
    while (!pdm_stream.empty()) {
        #pragma HLS UNROLL
        ap_uint<PDM_BIT_WIDTH> pdm_sample = pdm_stream.read();

        // Multiply the sample by 10 to increase its amplitude
        float amplified_sample = pdm_sample.to_uint() * 10.0f;

        // Shift samples in the buffer to make room for the new sample
        for (int i = FILTER_TAPS - 1; i > 0; --i) {
            sample_buffer[i] = sample_buffer[i - 1];
        }

        // Insert the new, amplified sample at the beginning of the buffer
        sample_buffer[0] = amplified_sample;

        // Apply the FIR filter
        float output = 0.0f;
        for (int i = 0; i < FILTER_TAPS; ++i) {
            output += sample_buffer[i] * coefficients[i];
        }

        // Accumulate the filter output
        output_accumulator += output;
        sample_count++;

        // Output PCM sample every DECIMATION_FACTOR samples
        if (sample_count == DECIMATION_FACTOR) {
            float avg_output = output_accumulator / DECIMATION_FACTOR;
            ap_uint<PCM_BIT_WIDTH> pcm_sample = static_cast<ap_uint<PCM_BIT_WIDTH>>(avg_output);
            pcm_stream.write(pcm_sample);

            // Debug: Output the calculated values to help with verification
            std::cout << "FIR Output Accumulator: " << output_accumulator << ", Average Output: " << avg_output
                      << ", PCM Output: " << pcm_sample.to_uint() << std::endl;

            // Reset the accumulator and sample count
            output_accumulator = 0.0f;
            sample_count = 0;
        }
    }

    done = 1;
}