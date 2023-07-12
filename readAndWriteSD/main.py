
from machine import SD
import os

sd = SD()
os.umount('/sd')
os.mount(sd, '/sd')
print("mounted")


# checks the content of the sd card
print("checking content")
print(os.listdir('/sd'))

# standard operations
print("opening")
f = open('/sd/test.txt', 'w')
f.write("teksts")
f = open('/sd/test.txt', 'r')
print(f.read())
f.close()