#PDM to PCM Conversion

This repository contains the implementation of a PDM (Pulse Density Modulation) to PCM (Pulse Code Modulation) conversion using a FIR (Finite Impulse Response) filter designed for FPGA platforms. The code is written in C++ and utilizes HLS (High-Level Synthesis) pragmas to facilitate synthesis into FPGA hardware.

##Code Overview
pdm_to_pcm.cpp: The main file containing the PDM to PCM conversion logic.
pdm_to_pcm.h: Header file defining interfaces and constants.
pdm_to_pcm_test.cpp: Verify the functionality of the PDM to PCM conversion module defined in pdm_to_pcm.cpp
