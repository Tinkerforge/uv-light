import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletUVLight;

public class ExampleThreshold {
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

		// Get threshold callbacks with a debounce time of 10 seconds (10000ms)
		uvl.setDebouncePeriod(10000);

		// Add UV light reached listener (parameter has unit µW/cm²)
		uvl.addUVLightReachedListener(new BrickletUVLight.UVLightReachedListener() {
			public void uvLightReached(long uvLight) {
				System.out.println("UV Light: " + uvLight + " µW/cm²");
				System.out.println("UV Index > 3. Use sunscreen!");
			}
		});

		// Configure threshold for UV light "greater than 750 µW/cm²" (unit is µW/cm²)
		uvl.setUVLightCallbackThreshold('>', 750, 0);

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
