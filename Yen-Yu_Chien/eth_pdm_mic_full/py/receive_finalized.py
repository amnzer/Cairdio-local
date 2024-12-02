import numpy as np
import wave
from scapy.all import sniff

# Function to handle each captured packet and save to .bin
def packet_handler(packet):
    try:
        raw_data = bytes(packet)[14:]  # Trim header by removing first 14 bytes
        if raw_data:
            with open("test.bin", "ab") as f:
                f.write(raw_data)
            print(f"Captured Packet - Raw data saved. Length: {len(raw_data)}")
        else:
            print("No raw packet data available.")
    except Exception as e:
        print(f"Error while processing packet: {e}")

# Function to process .bin data and save as .wav
def process_and_save_to_wav(signed=True):
    try:
        with open("test.bin", "rb") as f:
            bin_data = f.read()

        if not bin_data:
            print("No data found in test.bin. Please check the packet capture.")
            return

        # Ensure the buffer size aligns with 32-bit (4 bytes)
        if len(bin_data) % 4 != 0:
            print("Warning: Truncating bin_data to fit 32-bit alignment.")
            bin_data = bin_data[:len(bin_data) - (len(bin_data) % 4)]

        # Choose dtype based on whether data is signed or unsigned
        dtype = np.int32 if signed else np.uint32
        pcm_data = np.frombuffer(bin_data, dtype=dtype)

        # Set audio parameters
        sample_rate = int(2.4e6 // 64)  # Adjusted based on clock division
        channels = 1
        sampwidth = 4  # 32-bit audio
        
        # Save PCM data to .wav file
        with wave.open("output.wav", "wb") as wf:
            wf.setnchannels(channels)
            wf.setsampwidth(sampwidth)
            wf.setframerate(sample_rate)
            wf.writeframes(pcm_data.tobytes())

        print("Audio saved as output.wav.")
    except Exception as e:
        print(f"Error processing .bin file to .wav: {e}")

# Main function to start packet capture
def main():
    print("Starting packet capture...")
    interface = r"\Device\NPF_{96718AA8-7DEC-4FB8-AADF-8A0E35D43C55}"  # Set your interface
    sniff(iface=interface, prn=packet_handler, count=10000) # 50000
    print("Packet capture complete.")
    
    # Process and save to .wav after capturing packets, try signed=True
    process_and_save_to_wav(signed=True)

if __name__ == "__main__":
    main()