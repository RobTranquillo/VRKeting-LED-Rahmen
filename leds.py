"""
Functions to easy control the LED stripe  
"""

# general imports
import machine, neopixel, time

# my imports
from colors import *

# hardware config
count = 46
pin = 12

# global hardware driver 
np = neopixel.NeoPixel(machine.Pin(pin), count)

#######################
# Higher Functions
#######################

"""
Light up second LED for 3 seconds
"""
def OnOffSingle():
    SwitchLed(1)
    time.sleep(3)
    SwitchLed(1, off)

#######################
# Foundation Functions
#######################

"""
Switch one single LED to the given color.
Is no color provided, darkgreen is taken.
function is very slow on many LEDs, so don't 
use it for real time switching of many LEDs 
"""
def SwitchLed(pos, col = darkgreen):
    np[pos] = (col[0], col[1], col[2])
    np.write()