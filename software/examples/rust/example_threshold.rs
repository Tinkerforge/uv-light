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

    // Get threshold listeners with a debounce time of 10 seconds (10000ms)
    uv_light_bricklet.set_debounce_period(10000);

    //Create listener for UV light reached events.
    let uv_light_reached_listener = uv_light_bricklet.get_uv_light_reached_receiver();
    // Spawn thread to handle received events. This thread ends when the uv_light_bricklet
    // is dropped, so there is no need for manual cleanup.
    thread::spawn(move || {
        for event in uv_light_reached_listener {
            println!("UV Light: {}{}", event as f32 / 10.0, " mW/m²");
            println!("UV Index > 3. Use sunscreen!");
        }
    });

    // Configure threshold for UV light "greater than 75 mW/m²"
    uv_light_bricklet.set_uv_light_callback_threshold('>', 75 * 10, 0);

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
