Imports System
Imports Tinkerforge

Module ExampleCallback
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change XYZ to the UID of your UV Light Bricklet

    ' Callback subroutine for UV light callback
    Sub UVLightCB(ByVal sender As BrickletUVLight, ByVal uvLight As Long)
        Console.WriteLine("UV Light: " + uvLight.ToString() + " µW/cm²")
    End Sub

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim uvl As New BrickletUVLight(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Register UV light callback to subroutine UVLightCB
        AddHandler uvl.UVLightCallback, AddressOf UVLightCB

        ' Set period for UV light callback to 1s (1000ms)
        ' Note: The UV light callback is only called every second
        '       if the UV light has changed since the last call!
        uvl.SetUVLightCallbackPeriod(1000)

        Console.WriteLine("Press key to exit")
        Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
