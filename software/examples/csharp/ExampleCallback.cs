using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change XYZ to the UID of your UV Light Bricklet

	// Callback function for UV light callback (parameter has unit µW/cm²)
	static void UVLightCB(BrickletUVLight sender, long uvLight)
	{
		Console.WriteLine("UV Light: " + uvLight + " µW/cm²");
	}

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletUVLight uvl = new BrickletUVLight(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Register UV light callback to function UVLightCB
		uvl.UVLightCallback += UVLightCB;

		// Set period for UV light callback to 1s (1000ms)
		// Note: The UV light callback is only called every second
		//       if the UV light has changed since the last call!
		uvl.SetUVLightCallbackPeriod(1000);

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
