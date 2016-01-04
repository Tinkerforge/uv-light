#!/usr/bin/perl

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletUVLight;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change to your UID

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $uvl = Tinkerforge::BrickletUVLight->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Get current UV light (unit is µW/cm²)
my $uv_light = $uvl->get_uv_light();
print "UV Light: $uv_light µW/cm²\n";

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
