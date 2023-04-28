import iotv
import sys
from smbus import SMBus

if len(sys.argv) != 4:
    print('Syntax: python3 dout.py <vertebra addr> <a|b> <bbbbbb>')
    exit()

addr = sys.argv[1]
side = sys.argv[2]
value = int(sys.argv[3], base=2)

iotv.dout(addr, side, value)
