#!/bin/bash
chmod +x ./capture_arm32
sudo LD_LIBRARY_PATH=../../KSJApi.bin/arm32  ./capture_arm32 1
