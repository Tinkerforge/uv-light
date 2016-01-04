#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change to your UID

# Get current UV light (unit is µW/cm²)
tinkerforge call uv-light-bricklet $uid get-uv-light
