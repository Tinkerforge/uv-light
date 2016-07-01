import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletUVLight;

public class ExampleCallback {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;

	// Change XYZ to the UID of your UV Light Bricklet
	private static final String UID = "XYZ";

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletUVLight uvl = new BrickletUVLight(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Add UV light listener (parameter has unit µW/cm²)
		uvl.addUVLightListener(new BrickletUVLight.UVLightListener() {
			public void uvLight(long uvLight) {
				System.out.println("UV Light: " + uvLight + " µW/cm²");
			}
		});

		// Set period for UV light callback to 1s (1000ms)
		// Note: The UV light callback is only called every second
		//       if the UV light has changed since the last call!
		uvl.setUVLightCallbackPeriod(1000);

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
