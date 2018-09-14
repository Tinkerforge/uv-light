var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'XYZ'; // Change XYZ to the UID of your UV Light Bricklet

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

        // Configure threshold for UV light "greater than 75 mW/m²"
        uvl.setUVLightCallbackThreshold('>', 75*10, 0);
    }
);

// Register UV light reached callback
uvl.on(Tinkerforge.BrickletUVLight.CALLBACK_UV_LIGHT_REACHED,
    // Callback function for UV light reached callback
    function (uvLight) {
        console.log('UV Light: ' + uvLight/10.0 + ' mW/m²');
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
