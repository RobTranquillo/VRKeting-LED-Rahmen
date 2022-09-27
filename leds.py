"""
Functions to easy control the LED stripe  
"""

# general imports
import machine, neopixel, time

# my imports
import namedcolors as colors

# hardware config
count = 46
pin = 12

# global hardware driver 
np = neopixel.NeoPixel(machine.Pin(pin), count)

def OnOff():
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