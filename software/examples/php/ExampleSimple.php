<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletUVLight.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletUVLight;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your UV Light Bricklet

$ipcon = new IPConnection(); // Create IP connection
$uvl = new BrickletUVLight(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Get current UV light
$uv_light = $uvl->getUVLight();
echo "UV Light: $uv_light µW/cm²\n";

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$ipcon->disconnect();

?>
