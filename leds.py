"""
Functions to easy control the LED stripe  
"""

# general imports
import machine, random, neopixel, time

# my imports
from colors import *

# hardware config
pin = 12
count = 94   
#inner ring 0-45
#outer 93-46 //muss rückwärts, weil falschrum angebaut

# global hardware driver 
np = neopixel.NeoPixel(machine.Pin(pin), count)

#######################
# Higher Functions
#######################

"""
control wich program should start 
"""
def run(program):
    if (program == "onePixel"): PixelWithTail()
    if (program == "allRandom"): AllRandom()
    if (program == "circle"): Circle(RandomColor())
    if (program[:8] == "ledIndex"): LedIndex(RandomColor(), int(program[8:]))

"""
Display one one active LED
"""
def  LedIndex(color, index):
    print("Only light up LED: " + str(index))
    SwitchAllByMap(ColorMapSingle(off))
    SwitchLed(index)

"""
One random pixel walks all LEDs
"""
def PixelWithTail():
    PixelWithTailColor(RandomColor())

"""
Rotate one inner and one outer LED together
"""
def Circle(color):
    SwitchAllByMap(ColorMapSingle(off))
    CircleAround(color)

"""
Light up second LED for 3 seconds
"""
def OnOffSingle():
    SwitchLed(1)
    time.sleep(3)
    SwitchLed(1, off)

    

"""
All LEDs on, every one with a complete random color
"""
def AllRandom():
    SwitchAllByMap(ColorMapSingle(off))
    SwitchAllByMap(ColorMapRandom())

"""
all LEDs blue
"""
def AllBlue():
    SwitchAllByMap(ColorMapSingle(off))
    SwitchAllByMap(ColorMapSingle(blue))

#######################
# Foundation Functions
#######################

"""
Rotate 4 pixels aligned as one line
"""
def CircleAround(color):
    setOfLEDs = (
        (1, 3, 4),
        (2, 5, 7)
    )
    for leds in setOfLEDs:
        SwitchAllByMap(ColorMapArray(color, leds))
        time.sleep(0.5)


"""
One pixle goes its way alonge the stripe
"""
def PixelWithTailColor(color):
    SwitchAllByMap(ColorMapSingle(off))    
    for fullAnimStep in range(count):
        map = []
        for pixel in range(count):
            if fullAnimStep == pixel:
                map.append(color)
            else:
                map.append(off)                
        SwitchAllByMap(map)
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
build a LED map where all lights are in one color defined by an array
"""
def ColorMapArray(color, array):
    map = []
    for i in range(count):
        if i in array:
            map.append(color)
        else:
            map.append(off)
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
def SwitchAllByMap(colorMap):
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