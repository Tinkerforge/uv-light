#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your UV Light Bricklet

# Get current UV light (unit is µW/cm²)
tinkerforge call uv-light-bricklet $uid get-uv-light
