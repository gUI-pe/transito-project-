Vehicle Counter & Image Processing Module

This project contains C functions designed for image smoothing, background subtraction, and vehicle detection/classification using RGB 3-channel images (Imagem3C).
📌 Features

    Gaussian-like Image Smoothing (suavizaImagemX)

        Smooths noise in 3-channel RGB images using a weighted 3x3 spatial filter/kernel (center weight: 20).

        Allocates a duplicate image buffer during processing to preserve source values.

    Background Subtraction (zeraBackGround)

        Compares the input image pixel-by-pixel against a reference background image (bg).

        Zeroes out pixels (sets to RGB (0,0,0)) that fall within a relative brightness tolerance (between 75% and 125% of the background values).

        Masks out irrelevant image boundaries (top, bottom, and right margins) to isolate the Region of Interest (ROI).

        Saves intermediate visual debugging output to disk as .bmp format.

    Vehicle Detection & Classification (contaVeiculos)

        Scans specific horizontal rows within the ROI across the processed image.

        Tracks contiguous pixel segment lengths to detect vehicles and classify them into four size categories:

            Index 0: Extra small/small vehicles (e.g., motorcycles or small cars).

            Index 1: Medium vehicles (e.g., standard cars).

            Index 2: Large vehicles (e.g., vans or trucks).

            Index 3: Extra-large vehicles (e.g., long buses/trailers).

        Returns the total count of detected vehicles.

    Image Memory Management (criaImagem3CX, copiaImagemX)

        Dynamically allocates and deep-copies 3D memory arrays [channel][height][width] for RGB image structures.

🛠 Project Structure & Requirements

    Language: C (ANSI/C99 compatible)

    Headers Required:

        "trabalho3.h"

        "imagem.h"

        <stdio.h>

        <stdlib.h> (for dynamic memory allocation via malloc)
