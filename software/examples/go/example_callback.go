package main

import (
	"fmt"
	"github.com/tinkerforge/go-api-bindings/ipconnection"
	"github.com/tinkerforge/go-api-bindings/uv_light_bricklet"
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

	uvl.RegisterUVLightCallback(func(uvLight uint32) {
		fmt.Printf("UV Light: %f mW/m²\n", float64(uvLight)/10.0)
	})

	// Set period for UV light receiver to 1s (1000ms).
	// Note: The UV light callback is only called every second
	//       if the UV light has changed since the last call!
	uvl.SetUVLightCallbackPeriod(1000)

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

}
