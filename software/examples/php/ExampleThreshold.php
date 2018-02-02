<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletUVLight.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletUVLight;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your UV Light Bricklet

// Callback function for UV light reached callback
function cb_uvLightReached($uv_light)
{
    echo "UV Light: $uv_light µW/cm²\n";
    echo "UV Index > 3. Use sunscreen!\n";
}

$ipcon = new IPConnection(); // Create IP connection
$uvl = new BrickletUVLight(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Get threshold callbacks with a debounce time of 10 seconds (10000ms)
$uvl->setDebouncePeriod(10000);

// Register UV light reached callback to function cb_uvLightReached
$uvl->registerCallback(BrickletUVLight::CALLBACK_UV_LIGHT_REACHED, 'cb_uvLightReached');

// Configure threshold for UV light "greater than 750 µW/cm²"
$uvl->setUVLightCallbackThreshold('>', 750, 0);

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
