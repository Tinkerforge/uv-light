#!/usr/bin/perl

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletUVLight;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change to your UID

# Callback subroutine for UV light reached callback (parameter has unit µW/cm²)
sub cb_uv_light_reached
{
    my ($uv_light) = @_;

    print "UV Light: $uv_light µW/cm²\n";
    print "UV Index > 3. Use sunscreen!\n";
}

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $uvl = Tinkerforge::BrickletUVLight->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Get threshold callbacks with a debounce time of 10 seconds (10000ms)
$uvl->set_debounce_period(10000);

# Register UV light reached callback to subroutine cb_uv_light_reached
$uvl->register_callback($uvl->CALLBACK_UV_LIGHT_REACHED, 'cb_uv_light_reached');

# Configure threshold for UV light "greater than 750 µW/cm²" (unit is µW/cm²)
$uvl->set_uv_light_callback_threshold('>', 750, 0);

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
