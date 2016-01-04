#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change to your UID

# Handle incoming UV light callbacks (parameter has unit µW/cm²)
tinkerforge dispatch uv-light-bricklet $uid uv-light &

# Set period for UV light callback to 1s (1000ms)
# Note: The UV light callback is only called every second
#       if the UV light has changed since the last call!
tinkerforge call uv-light-bricklet $uid set-uv-light-callback-period 1000

echo "Press key to exit"; read dummy

kill -- -$$ # Stop callback dispatch in background
