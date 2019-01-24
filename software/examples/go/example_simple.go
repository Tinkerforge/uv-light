package main

import (
	"fmt"
	"github.com/Tinkerforge/go-api-bindings/ipconnection"
	"github.com/Tinkerforge/go-api-bindings/uv_light_bricklet"
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

	// Get current UV light.
	uvLight, _ := uvl.GetUVLight()
	fmt.Printf("UV Light: %f mW/m²\n", float64(uvLight)/10.0)

	fmt.Print("Press enter to exit.")
	fmt.Scanln()
}
