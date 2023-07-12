
from machine import SD
import os

sd = SD()
os.umount('/sd')
os.mount(sd, '/sd')
print("mounted")


# check the content
print("checking content")
print(os.listdir('/sd'))

# try some standard file operations
print("opening")
f = open('/sd/test.txt', 'w')
f.write("teksts")
f = open('/sd/test.txt', 'r')
print(f.read())
f.close()