"""
LED Demo Stuff
"""
import machine, neopixel, time

n = 48
p = 12

np = neopixel.NeoPixel(machine.Pin(p), n)

def Main():
    Leds_on()
    time.sleep(5)
    Leds_off()

# ON
def Leds_on():
    np[0] = (255, 0, 0)
    np[3] = (125, 204, 223)
    np[7] = (120, 153, 23)
    np[9] = (255, 0, 153)
    np.write()

# OFF
def Leds_off():
    np[0] = (0, 0, 0)
    np[3] = (0, 0, 0)
    np[7] = (0, 0, 0)
    np[9] = (0, 0, 0)
    np.write()

# Start the main programm
Main();