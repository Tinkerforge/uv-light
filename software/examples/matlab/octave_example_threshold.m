function octave_example_threshold()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your UV Light Bricklet

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    uvl = javaObject("com.tinkerforge.BrickletUVLight", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get threshold callbacks with a debounce time of 10 seconds (10000ms)
    uvl.setDebouncePeriod(10000);

    % Register UV light reached callback to function cb_uv_light_reached
    uvl.addUVLightReachedCallback(@cb_uv_light_reached);

    % Configure threshold for UV light "greater than 750 µW/cm²"
    uvl.setUVLightCallbackThreshold(">", 750, 0);

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end

% Callback function for UV light reached callback
function cb_uv_light_reached(e)
    fprintf("UV Light: %d µW/cm²\n", java2int(e.uvLight));
    fprintf("UV Index > 3. Use sunscreen!\n");
end

function int = java2int(value)
    if compare_versions(version(), "3.8", "<=")
        int = value.intValue();
    else
        int = value;
    end
end
