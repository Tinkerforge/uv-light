function octave_example_simple()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your UV Light Bricklet

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    uvl = java_new("com.tinkerforge.BrickletUVLight", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current UV light (unit is µW/cm²)
    uvLight = uvl.getUVLight();
    fprintf("UV Light: %d µW/cm²\n", java2int(uvLight));

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end

function int = java2int(value)
    if compare_versions(version(), "3.8", "<=")
        int = value.intValue();
    else
        int = value;
    end
end
