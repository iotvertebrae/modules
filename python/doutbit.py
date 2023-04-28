import iotv
import sys
from smbus import SMBus

if len(sys.argv) != 5:
    print('Syntax: python3 doutbit.py <vertebra addr> <a|b> <pos in byte> <0-1>')
    exit()

addr = sys.argv[1]
side = sys.argv[2]
posbyte = int(sys.argv[3])
value = int(sys.argv[4])

iotv.doutbit(addr, side, posbyte, value)
