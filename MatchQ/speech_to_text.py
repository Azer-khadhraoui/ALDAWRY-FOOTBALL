import serial
import numpy as np
import scipy.io.wavfile as wavfile
import speech_recognition as sr
import time
import os
import platform

# Serial port configuration
SERIAL_PORT = 'COM9'  # Replace with your Arduino's port (e.g., '/dev/ttyUSB0' on Linux)
BAUD_RATE = 250000  # Match Arduino baud rate
SAMPLE_RATE = 9000  # Match Arduino sample rate
RECORD_SECONDS = 5  # Duration to record
MARKER = 0xFF  # Synchronization marker
OUTPUT_DIR = "D:\projet app desktop\MatchQ"  # Output directory

# Ensure output directory exists
if not os.path.exists(OUTPUT_DIR):
    os.makedirs(OUTPUT_DIR)

# Initialize serial connection
try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    time.sleep(2)  # Wait for Arduino to initialize
    ser.flushInput()  # Clear serial buffer
except serial.SerialException as e:
    print(f"Serial port error: {e}")
    exit(1)

# Record audio samples
print("Recording...")
samples = []
invalid_samples = 0
start_time = time.time()
while time.time() - start_time < RECORD_SECONDS:
    if ser.in_waiting >= 3:  # Wait for marker + 2 bytes
        byte1 = ser.read(1)
        if byte1 and byte1[0] == MARKER:  # Found marker
            try:
                high_byte = ser.read(1)[0]
                low_byte = ser.read(1)[0]
                sample = (high_byte << 8) | low_byte  # Reconstruct sample
                if 0 <= sample <= 1023:  # Validate ADC range
                    samples.append(sample)
                else:
                    invalid_samples += 1
                    print(f"Invalid sample: {sample}")
            except IndexError:
                print("Error reading sample bytes")
                continue
        else:
            continue

ser.close()
print(f"Recorded {len(samples)} samples, {invalid_samples} invalid samples")

# Convert to audio signal
if samples:
    samples = np.array(samples, dtype=np.float32)  # Use float32 to avoid overflow
    samples = samples - np.mean(samples)  # Center around 0 (remove DC bias)
    samples = (samples / 1023.0 * 32767).astype(np.int16)  # Scale to 16-bit PCM
else:
    print("No valid samples recorded")
    exit(1)

# Save to WAV file
wav_filename = os.path.join(OUTPUT_DIR, "recording.wav")
wavfile.write(wav_filename, SAMPLE_RATE, samples)
print(f"Saved to {wav_filename}")


# Speech-to-text using Google API
recognizer = sr.Recognizer()
text_filename = os.path.join(OUTPUT_DIR, "transcription.txt")
with sr.AudioFile(wav_filename) as source:
    audio = recognizer.record(source)
    try:
        text = recognizer.recognize_google(audio)
        print("Transcription:", text)
        with open(text_filename, 'w', encoding='utf-8') as f:
            f.write(text)
        print(f"Saved transcription to {text_filename}")
    except sr.UnknownValueError:
        print("Could not understand audio")
        with open(text_filename, 'w', encoding='utf-8') as f:
            f.write("Error: Could not understand audio")
    except sr.RequestError as e:
        print(f"API error: {e}")
        with open(text_filename, 'w', encoding='utf-8') as f:
            f.write(f"Error: API error: {e}")