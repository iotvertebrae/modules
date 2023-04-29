import iotv
import sys
from smbus import SMBus

if len(sys.argv) != 5:
    print('Syntax: python3 aout.py <vertebra addr> <a|b> <n dac 1-4> <value 0-4095>')
    exit()

addr = sys.argv[1]
side = sys.argv[2]
ndac = int(sys.argv[3])
value = int(sys.argv[4])

iotv.aout(addr, side, ndac, value)
