import iotv
import sys
from smbus import SMBus

if len(sys.argv) != 3:
    print('Syntax: python3 din.py <vertebra addr> <a|b>')
    exit()

addr = sys.argv[1]
side = sys.argv[2]

print (iotv.din(addr, side))


