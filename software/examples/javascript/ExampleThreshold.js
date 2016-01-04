var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'XYZ'; // Change to your UID

var ipcon = new Tinkerforge.IPConnection(); // Create IP connection
var uvl = new Tinkerforge.BrickletUVLight(UID, ipcon); // Create device object

ipcon.connect(HOST, PORT,
    function (error) {
        console.log('Error: ' + error);
    }
); // Connect to brickd
// Don't use device before ipcon is connected

ipcon.on(Tinkerforge.IPConnection.CALLBACK_CONNECTED,
    function (connectReason) {
        // Get threshold callbacks with a debounce time of 10 seconds (10000ms)
        uvl.setDebouncePeriod(10000);

        // Configure threshold for UV light "greater than 750 µW/cm²" (unit is µW/cm²)
        uvl.setUVLightCallbackThreshold('>', 750, 0);
    }
);

// Register UV light reached callback
uvl.on(Tinkerforge.BrickletUVLight.CALLBACK_UV_LIGHT_REACHED,
    // Callback function for UV light reached callback (parameter has unit µW/cm²)
    function (uvLight) {
        console.log('UV Light: ' + uvLight + ' µW/cm²');
        console.log('UV Index > 3. Use sunscreen!');
    }
);

console.log('Press key to exit');
process.stdin.on('data',
    function (data) {
        ipcon.disconnect();
        process.exit(0);
    }
);
