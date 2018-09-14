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
        // Set period for UV light callback to 1s (1000ms)
        // Note: The UV light callback is only called every second
        //       if the UV light has changed since the last call!
        uvl.setUVLightCallbackPeriod(1000);
    }
);

// Register UV light callback
uvl.on(Tinkerforge.BrickletUVLight.CALLBACK_UV_LIGHT,
    // Callback function for UV light callback
    function (uvLight) {
        console.log('UV Light: ' + uvLight/10.0 + ' mW/m²');
    }
);

console.log('Press key to exit');
process.stdin.on('data',
    function (data) {
        ipcon.disconnect();
        process.exit(0);
    }
);
