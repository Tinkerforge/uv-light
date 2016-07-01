using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change XYZ to the UID of your UV Light Bricklet

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletUVLight uvl = new BrickletUVLight(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Get current UV light (unit is µW/cm²)
		long uvLight = uvl.GetUVLight();
		Console.WriteLine("UV Light: " + uvLight + " µW/cm²");

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
