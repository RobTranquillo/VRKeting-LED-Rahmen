"""
LED Demo Stuff
"""

#std lib 
import time

#custom libs
import leds

# leds.OnOffSingle()
# leds.AllBlue()
# while True:
#     leds.PixelWithTail()
#     leds.AllRandom()
#     time.sleep(4)


import webserver

while True:
    program = webserver.handleWebRequest()
    print("Run programm: " + program)
    leds.run(program)