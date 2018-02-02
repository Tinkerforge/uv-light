#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_uv_light'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XYZ' # Change XYZ to the UID of your UV Light Bricklet

ipcon = IPConnection.new # Create IP connection
uvl = BrickletUVLight.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Get threshold callbacks with a debounce time of 10 seconds (10000ms)
uvl.set_debounce_period 10000

# Register UV light reached callback
uvl.register_callback(BrickletUVLight::CALLBACK_UV_LIGHT_REACHED) do |uv_light|
  puts "UV Light: #{uv_light} µW/cm²"
  puts 'UV Index > 3. Use sunscreen!'
end

# Configure threshold for UV light "greater than 750 µW/cm²"
uvl.set_uv_light_callback_threshold '>', 750, 0

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
