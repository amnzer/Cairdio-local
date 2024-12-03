#ifndef PDM_TO_PCM_H
#define PDM_TO_PCM_H

#include <hls_stream.h>
#include <ap_int.h>

#define PDM_BIT_WIDTH 1   
#define PCM_BIT_WIDTH 16  // PCM output bit width
#define DECIMATION_FACTOR 64  // Adjust based on PDM data rate and desired PCM data rate

// PDM to PCM conversion function
void pdm_to_pcm(hls::stream<ap_uint<PDM_BIT_WIDTH>>& pdm_stream, hls::stream<ap_uint<PCM_BIT_WIDTH>>& pcm_stream, short &done);

#endif // PDM_TO_PCM_H