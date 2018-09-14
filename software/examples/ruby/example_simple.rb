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

# Get current UV light
uv_light = uvl.get_uv_light
puts "UV Light: #{uv_light/10.0} mW/m²"

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
