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
quadrant = 23 #count / 4 => 94 / 4
innenRechts     = (0, 1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9 ,10)
innenLinks      = (23,24,25,26,27,28,29,30,31,32,33)
innenOben       = (11,12,13,14,15,16,17,18,19,20,21,22,23)
innenUnten      = (34,35,36,37,38,39,40,41,42,43,44,45)
aussenRechts    = (93,92,91,90,89,88,87,86,85,84,83,82)
aussenOben      = (81,80,79,78,77,76,75,74,73,72,71,70)
aussenLinks     = (70,69,68,67,66,65,64,63,62,61,60,59,58)
aussenUnten     = (46,47,48,49,50,51,52,53,54,55,56,57)

# global hardware driver 
np = neopixel.NeoPixel(machine.Pin(pin), count)

#######################
# Higher Functions
#######################

"""
control wich program should start 
"""
def run(program):
    if (program == "None") : { }
    if (program == "onePixel"): PixelWithTail()
    if (program == "allRandom"): AllRandom()
    if (program == "circle"): Circle(RandomColor())
    if (program[:8] == "ledIndex"): LedIndex(RandomColor(), int(program[8:]))
    if (program == "scanner"): Scanner()
    if (program == "flash"): Flash()


"""
Quick flash of light
"""
def Flash():
    SwitchAllByMap(ColorMapSingle(off))
    randomMap = []
    for i in range(count):
        randomMap.append(RandomColor())
    SwitchAllByMap(randomMap)
    #Todo: --->>
    #TweenToMap(startMap, endMap, time)
    time.sleep(1)
    SwitchAllByMap(ColorMapSingle(off))


"""
Vertical and horizontal lines
"""
def Scanner():
    SwitchAllByMap(ColorMapSingle(off))
    for repeat in range(4):
        HorizontalScanner(RandomColor(), 1)
        VerticalScanner(RandomColor(), 1)

"""
Display one one active LED
"""
def LedIndex(color, index):
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
On each of four sides one pixel is light up in sync 
"""
def HorizontalScanner(color, loops = 1):
    for loop in range(loops):
        for i in range(12):
            activeLeds = (innenOben[i], aussenOben[i], reversed(innenUnten)[i], aussenUnten[i])
            SwitchAllByMap(ColorMapArray(color, activeLeds))
        for i in reversed(range(12)):
            activeLeds = (innenOben[i], aussenOben[i], reversed(innenUnten)[i], aussenUnten[i])
            SwitchAllByMap(ColorMapArray(color, activeLeds))
"""
On each of four sides one pixel is light up in sync 
"""
def VerticalScanner(color, loops = 1):
    for loop in range(loops):
        for i in range(11):
            activeLeds = (innenRechts[i], reversed(innenLinks)[i],reversed(aussenLinks)[i+1], aussenRechts[i])
            SwitchAllByMap(ColorMapArray(color, activeLeds))
        for i in reversed(range(11)):
            activeLeds = (innenRechts[i], reversed(innenLinks)[i],reversed(aussenLinks)[i+1], aussenRechts[i])
            SwitchAllByMap(ColorMapArray(color, activeLeds))
        

"""
Helper function to reverse an list
"""
def reversed(orgList):
    newList = []
    for i in range(len(orgList)):
        newList.append(orgList[len(orgList)-1-i])
    return tuple(newList)

"""
Rotate 4 pixels aligned as one line
"""
def CircleAround(color):    
    for rounds in range(4):
        for i in range(quadrant):
            activeLeds = (i, i+quadrant, count-i, count-(i+quadrant))
            #print("active: " + str(activeLeds))
            SwitchAllByMap(ColorMapArray(color, activeLeds))
            time.sleep(0.02)


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