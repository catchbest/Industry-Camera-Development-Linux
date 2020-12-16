#!/bin/bash
chmod +x ./capture_arm64
sudo LD_LIBRARY_PATH=../../KSJApi.bin/arm64  ./capture_arm64 1
