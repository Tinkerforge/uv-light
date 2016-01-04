#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_uv_light'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XYZ' # Change to your UID

ipcon = IPConnection.new # Create IP connection
uvl = BrickletUVLight.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Register UV light callback (parameter has unit µW/cm²)
uvl.register_callback(BrickletUVLight::CALLBACK_UV_LIGHT) do |uv_light|
  puts "UV Light: #{uv_light} µW/cm²"
end

# Set period for UV light callback to 1s (1000ms)
# Note: The UV light callback is only called every second
#       if the UV light has changed since the last call!
uvl.set_uv_light_callback_period 1000

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
