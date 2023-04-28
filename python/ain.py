import iotv
import sys
from smbus import SMBus
import time


if len(sys.argv) != 4:
    print('Syntax: python3 ain.py <vertebra addr> <a|b> <n dac 1-4>')
    exit()

addr = sys.argv[1]
side = sys.argv[2]
ndac = int(sys.argv[3])

print(iotv.ain(addr, side, ndac))
