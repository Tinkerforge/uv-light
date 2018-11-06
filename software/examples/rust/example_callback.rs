use std::{error::Error, io, thread};
use tinkerforge::{ipconnection::IpConnection, uv_light_bricklet::*};

const HOST: &str = "127.0.0.1";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your UV Light Bricklet

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection
    let uv_light_bricklet = UVLightBricklet::new(UID, &ipcon); // Create device object

    ipcon.connect(HOST, PORT).recv()??; // Connect to brickd
                                        // Don't use device before ipcon is connected

    //Create listener for UV light events.
    let uv_light_listener = uv_light_bricklet.get_uv_light_receiver();
    // Spawn thread to handle received events. This thread ends when the uv_light_bricklet
    // is dropped, so there is no need for manual cleanup.
    thread::spawn(move || {
        for event in uv_light_listener {
            println!("UV Light: {}{}", event as f32 / 10.0, " mW/m²");
        }
    });

    // Set period for UV light listener to 1s (1000ms)
    // Note: The UV light callback is only called every second
    //       if the UV light has changed since the last call!
    uv_light_bricklet.set_uv_light_callback_period(1000);

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
