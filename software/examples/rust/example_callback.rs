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

     let uv_light_receiver = uvl.get_uv_light_callback_receiver();

        // Spawn thread to handle received callback messages. 
        // This thread ends when the `uvl` object
        // is dropped, so there is no need for manual cleanup.
        thread::spawn(move || {
            for uv_light in uv_light_receiver {           
                		println!("UV Light: {} mW/m²", uv_light as f32 /10.0);
            }
        });

		// Set period for UV light receiver to 1s (1000ms).
		// Note: The UV light callback is only called every second
		//       if the UV light has changed since the last call!
		uvl.set_uv_light_callback_period(1000);

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
