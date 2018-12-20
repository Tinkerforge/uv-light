use std::{io, error::Error};
use std::thread;
use tinkerforge::{ip_connection::IpConnection, 
                  uv_light_bricklet::*};


const HOST: &str = "localhost";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your UV Light Bricklet.

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection.
    let uvl = UvLightBricklet::new(UID, &ipcon); // Create device object.

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd.
    // Don't use device before ipcon is connected.

		// Get threshold receivers with a debounce time of 10 seconds (10000ms).
		uvl.set_debounce_period(10000);

     let uv_light_reached_receiver = uvl.get_uv_light_reached_callback_receiver();

        // Spawn thread to handle received callback messages. 
        // This thread ends when the `uvl` object
        // is dropped, so there is no need for manual cleanup.
        thread::spawn(move || {
            for uv_light_reached in uv_light_reached_receiver {           
                		println!("UV Light: {} mW/m²", uv_light_reached as f32 /10.0);
		println!("UV Index > 3. Use sunscreen!");
            }
        });

		// Configure threshold for UV light "greater than 75 mW/m²".
		uvl.set_uv_light_callback_threshold('>', 75*10, 0);

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
