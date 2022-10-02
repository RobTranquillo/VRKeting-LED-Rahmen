"""
Functions to easy control the LED stripe  
"""

# general imports
import machine, random, neopixel, time

# my imports
from colors import *

# hardware config
count = 88   #inner ring 0-45, 
pin = 12

# global hardware driver 
np = neopixel.NeoPixel(machine.Pin(pin), count)

#######################
# Higher Functions
#######################

"""
control wich program should start 
"""
def run(program):
    if (program == "first"): PixelWithTail()
    if (program == "second"): AllRandom()

"""
One random pixel walks all LEDs
"""
def PixelWithTail():
    PixelWithTailColor(RandomColor())


"""
Light up second LED for 3 seconds
"""
def OnOffSingle():
    SwitchLed(1)
    time.sleep(3)
    SwitchLed(1, off)

def AllRandom():
    SwitchAllByColor(ColorMapSingle(off))
    SwitchAllByColor(ColorMapRandom())

def AllBlue():
    SwitchAllByColor(ColorMapSingle(off))
    SwitchAllByColor(ColorMapSingle(blue))

#######################
# Foundation Functions
#######################

def PixelWithTailColor(color):
    SwitchAllByColor(ColorMapSingle(off))    
    for fullAnimStep in range(count):
        map = []
        for pixel in range(count):
            if fullAnimStep == pixel:
                map.append(color)
            else:
                map.append(off)                
        SwitchAllByColor(map)
        time.sleep(0.1)


"""
Get a random color
"""
def RandomColor(): 
    return [random.getrandbits(8),
            random.getrandbits(8),
            random.getrandbits(8)]

def ColorMapRandom():
    map = []
    for i in range(count):
        map.append(RandomColor())
    return map

"""
build a LED map where all lights are in one color
"""
def ColorMapSingle(color):
    map = []
    for i in range(count):
        map.append(color)
    return map

"""
Switch all LEDs by one provided array of colors
Real time fast implementation.
"""
def SwitchAllByColor(colorMap):
    i = 0
    for col in colorMap:
        np[i] = col
        i = i+1
    np.write()

"""
Switch one single LED to the given color.
Is no color provided, darkgreen is taken.
function is very slow on many LEDs, so don't 
use it for real time switching of many LEDs 
"""
def SwitchLed(pos, col = darkgreen):
    np[pos] = (col[0], col[1], col[2])
    np.write()