"""
LED Demo Stuff
"""

#std lib 
import time

#custom libs
import leds

# run single intro ligths
leds.run("flash")

import webserver
while True:
    program = webserver.handleWebRequest()
    print("Run LED programm: " + program)
    leds.run(program)