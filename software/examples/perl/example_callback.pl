#!/usr/bin/perl

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletUVLight;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change XYZ to the UID of your UV Light Bricklet

# Callback subroutine for UV light callback (parameter has unit µW/cm²)
sub cb_uv_light
{
    my ($uv_light) = @_;

    print "UV Light: $uv_light µW/cm²\n";
}

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $uvl = Tinkerforge::BrickletUVLight->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Register UV light callback to subroutine cb_uv_light
$uvl->register_callback($uvl->CALLBACK_UV_LIGHT, 'cb_uv_light');

# Set period for UV light callback to 1s (1000ms)
# Note: The UV light callback is only called every second
#       if the UV light has changed since the last call!
$uvl->set_uv_light_callback_period(1000);

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
