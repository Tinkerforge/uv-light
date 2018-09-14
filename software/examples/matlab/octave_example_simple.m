function octave_example_simple()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your UV Light Bricklet

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    uvl = javaObject("com.tinkerforge.BrickletUVLight", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current UV light
    uvLight = uvl.getUVLight();
    fprintf("UV Light: %g mW/m²\n", java2int(uvLight)/10.0);

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
