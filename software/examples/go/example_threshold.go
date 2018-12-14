package main

import (
	"fmt"
	"tinkerforge/ipconnection"
	"tinkerforge/uv_light_bricklet"
)

const ADDR string = "localhost:4223"
const UID string = "XYZ" // Change XYZ to the UID of your UV Light Bricklet.

func main() {
	ipcon := ipconnection.New()
	defer ipcon.Close()
	uvl, _ := uv_light_bricklet.New(UID, &ipcon) // Create device object.

	ipcon.Connect(ADDR) // Connect to brickd.
	defer ipcon.Disconnect()
	// Don't use device before ipcon is connected.

	// Get threshold receivers with a debounce time of 10 seconds (10000ms).
	uvl.SetDebouncePeriod(10000)

	uvl.RegisterUVLightReachedCallback(func(uvLight uint32) {
		fmt.Printf("UV Light: %d mW/m²\n", float64(uvLight)/10.0)
		fmt.Println("UV Index > 3. Use sunscreen!")
	})

	// Configure threshold for UV light "greater than 75 mW/m²".
	uvl.SetUVLightCallbackThreshold('>', 75*10, 0)

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

}
