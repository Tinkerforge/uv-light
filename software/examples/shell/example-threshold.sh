#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your UV Light Bricklet

# Get threshold callbacks with a debounce time of 10 seconds (10000ms)
tinkerforge call uv-light-bricklet $uid set-debounce-period 10000

# Handle incoming UV light reached callbacks (parameter has unit µW/cm²)
tinkerforge dispatch uv-light-bricklet $uid uv-light-reached\
 --execute "echo UV Light: {uv_light} µW/cm². UV Index > 3. Use sunscreen!" &

# Configure threshold for UV light "greater than 750 µW/cm²" (unit is µW/cm²)
tinkerforge call uv-light-bricklet $uid set-uv-light-callback-threshold greater 750 0

echo "Press key to exit"; read dummy

kill -- -$$ # Stop callback dispatch in background
