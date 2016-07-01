function matlab_example_callback()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletUVLight;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change XYZ to the UID of your UV Light Bricklet

    ipcon = IPConnection(); % Create IP connection
    uvl = handle(BrickletUVLight(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register UV light callback to function cb_uv_light
    set(uvl, 'UVLightCallback', @(h, e) cb_uv_light(e));

    % Set period for UV light callback to 1s (1000ms)
    % Note: The UV light callback is only called every second
    %       if the UV light has changed since the last call!
    uvl.setUVLightCallbackPeriod(1000);

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end

% Callback function for UV light callback (parameter has unit µW/cm²)
function cb_uv_light(e)
    fprintf('UV Light: %i µW/cm²\n', e.uvLight);
end
