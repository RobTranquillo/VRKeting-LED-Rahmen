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


# run single intro ligths
leds.run("scanner")

import webserver
while True:
    program = webserver.handleWebRequest()
    print("Run LED programm: " + program)
    leds.run(program)