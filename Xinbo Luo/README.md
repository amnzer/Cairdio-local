# Noise Reduction and Signal Classification Framework

**Note:** This README provides an overview of the project. For detailed information, refer to the project report and code documentation.

---

## Table of Contents
1. [Introduction](#introduction)
2. [Noise Reduction](#noise-reduction)
   - [FFT-Based Noise Subtraction](#fft-based-noise-subtraction)
   - [Pre-Trained Models for Noise Reduction](#pre-trained-models-for-noise-reduction)
3. [Signal Segmentation](#signal-segmentation)
4. [Deep Learning Models for Classification](#deep-learning-models-for-classification)
   - [CNN](#cnn)
   - [EfficientNet](#efficientnet)
   - [ResNet and RCN](#resnet-and-rcn)
5. [Tools and Libraries](#tools-and-libraries)

---

## Introduction
This project focuses on reducing noise from audio recordings and classifying signals into noisy or non-noisy categories. Additionally, it includes segmentation of clean signals to discard noisy sections and ensure high-quality data for further analysis. The workflow integrates classical signal processing techniques, pre-trained models, and deep learning classifiers to achieve these objectives.

---

## Noise Reduction
### FFT-Based Noise Subtraction
- **Purpose**: Remove noise from recordings by analyzing their frequency spectra.
- **Method**:
  1. Perform Fast Fourier Transform (FFT) to convert signals into the frequency domain.
  2. Apply thresholding or band-pass filtering to remove noise-dominated frequencies.
  3. Perform inverse FFT to reconstruct the cleaned signal.
- **Outputs**:
  - Time-domain plots of the original and cleaned signals.
  - Enhanced audio recordings.

### Pre-Trained Models for Noise Reduction
- **noisereduce**:
  - Implements spectral gating for noise suppression.
  - Customizable parameters to handle varying noise profiles.
- **DeepFilterNet**:
  - A deep learning-based approach for real-time noise suppression.
  - Pre-trained on large datasets for robust noise reduction.
- **Outputs**:
  - Noise-free audio signals.
  - Enhanced Signal-to-Noise Ratio (SNR) metrics.

---

## Deep Learning Models for Classification
### CNN
- **Purpose**: Classify spectrogram images into noisy or non-noisy categories.
- **Workflow**:
  1. Extract spectrogram images from audio recordings.
  2. Train a Convolutional Neural Network (CNN) on these images using binary classification.
  3. Evaluate performance using ROC-AUC and confusion matrix.
- **Outputs**:
  - Classification accuracy and AUC metrics.
  - Confusion matrix visualizations.

### EfficientNet
- **Purpose**: Use EfficientNetB0 for lightweight and efficient classification.
- **Workflow**:
  1. Load pre-trained EfficientNetB0 with frozen weights from ImageNet.
  2. Add custom dense layers for binary classification.
  3. Train using augmented spectrogram data with techniques like rotation, scaling, and flipping.
- **Outputs**:
  - Validation accuracy: 91.46%.
  - ROC-AUC: 0.91.

### ResNet and RCN
- **Purpose**: Use ResNet-50 and RCN (ResNet with modifications) for improved classification.
- **Workflow**:
  1. Load ResNet-50 and fine-tune selected layers.
  2. Train with spectrograms using similar augmentation techniques.
  3. Evaluate performance with metrics similar to EfficientNet.
- **Outputs**:
  - Classification accuracy and AUC metrics comparable to EfficientNet.
  - Fine-tuned model ready for deployment.

---

## Signal Segmentation
- **Purpose**: Extract clean segments of signals while discarding noisy sections to improve downstream analysis.
- **Methods**:
  1. **SNR-Based Segmentation**:
     - Compute Signal-to-Noise Ratio (SNR) for rolling windows.
     - Identify and retain segments with the highest SNR.
  2. **Energy-Based Segmentation**:
     - Calculate energy of segments to detect clean portions.
  3. **Zero-Crossing Rate (ZCR) and Spectral Flatness**:
     - Use these metrics to identify clean signal sections.
- **Outputs**:
  - Clean signal segments for further processing.
  - Time-domain plots showing retained segments.

---

## Tools and Libraries
This project uses the following Python libraries:
- `numpy`: Numerical computations.
- `matplotlib`: Visualization of signals and frequency spectra.
- `scipy`: FFT and filtering operations.
- `librosa`: Audio processing and feature extraction.
- `tensorflow` and `keras`: Deep learning model development.
- `noisereduce`: Noise suppression.
- `DeepFilterNet`: Machine learning-based noise reduction.


