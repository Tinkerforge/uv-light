use std::{error::Error, io};

use tinkerforge::{ipconnection::IpConnection, uv_light_bricklet::*};

const HOST: &str = "127.0.0.1";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your UV Light Bricklet

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection
    let uv_light_bricklet = UVLightBricklet::new(UID, &ipcon); // Create device object

    ipcon.connect(HOST, PORT).recv()??; // Connect to brickd
                                        // Don't use device before ipcon is connected

    // Get current UV light
    let uv_light = uv_light_bricklet.get_uv_light().recv()?;
    println!("UV Light: {}{}", uv_light as f32 / 10.0, " mW/m²");

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
