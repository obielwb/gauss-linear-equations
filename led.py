import RPi.GPIO as gp
from time import sleep

high = gp.high
low = gp.low

red_led = 23
yellow_led = 24
green_led = 25

gp.setmode(gp.BCM)

gp.setup(red_led, gp.OUT, initial=low)
gp.setup(yellow_led, gp.OUT, initial=low)
gp.setup(green_led, gp.OUT, initial=low)

try:
  while True:
    gp.output(red_led, high)
    sleep(5)
    gp.output(red_led, low)
    gp.output(yellow_led, high)
    sleep(2)
    gp.output(yellow_led, low)
    gp.output(green_led, high)
    sleep(5)
    gp.output(green_led, low)
    gp.output(yellow_led, high)
    sleep(2)
    gp.output(yellow_led, low)

except KeyboardInterrupt:
  pass

gp.output(yellow_led, low)
gp.output(red_led, low)
gp.output(green_led, low)

gp.cleanup()
