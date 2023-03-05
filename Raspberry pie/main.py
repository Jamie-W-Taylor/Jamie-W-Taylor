# Imports
from machine import ADC, Pin
import time

# Todo
# - If the file gets too big and makes the pico run out of disk space, what should it do?
# - maybe add a buzzer to it to stop people stealing stuff

# Define pin for our sensor
lightsensor = ADC(Pin(26))

# Turn off the onboard LED - so no one knows its there and on
onboardLED = Pin(25, Pin.OUT)
onboardLED.value(1)

cupboardDoorOpen = True

while True: # Run forever

    # Read sensor value and store it in a variable called 'light'
    light = lightsensor.read_u16()

    # Turn our reading into a percentage of the analogue range
    lightpercent = round(light/65535*100)

    # Assuming 10% shows that the cupboard is open
    if lightpercent > 10:
        
        if cupboardDoorOpen == False:
            # Just opened, so save it
            # print("Just opened = " + str(lightpercent))
    
            now = time.localtime()
            message = "O:{}:{}:{}\n".format(now[3], now[4], now[5])
    
            with open("cupboard.log", "a") as auditFile:
                auditFile.write(message)
    
        cupboardDoorOpen = True
    
    else:
        if cupboardDoorOpen == True:
            # Just closed, so save it
            # print("Just closed = " + str(lightpercent))
    
            now = time.localtime()
            message = "C:{}:{}:{}\n".format(now[3], now[4], now[5])
    
            with open("cupboard.log", "a") as auditFile:
                auditFile.write(message)
    
        cupboardDoorOpen = False

    # 1 second delay between readings
    time.sleep(1)

