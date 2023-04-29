import sys
from smbus import SMBus
import time


def ain(addr, side, ndac):

    if   addr == '000':
        i2cAddr = 0x77
    elif addr == '001':
        i2cAddr = 0x73
    elif addr == '010':
        i2cAddr = 0x75
    elif addr == '011':
        i2cAddr = 0x71
    elif addr == '100':
        i2cAddr = 0x76
    elif addr == '101':
        i2cAddr = 0x72
    elif addr == '110':
        i2cAddr = 0x74
    elif addr == '111':
        i2cAddr = 0x70


    if   ndac == 1:
        adcCfg = 0x83C1
        if side.lower() == 'a':
            adcChannel = 0x01
        if side.lower() == 'b':
            adcChannel = 0x10
    elif ndac == 2:
        adcCfg = 0x83D1
        if side.lower() == 'a':
            adcChannel = 0x01
        if side.lower() == 'b':
            adcChannel = 0x10
    elif ndac == 3:
        adcCfg = 0x83E1
        if side.lower() == 'a':
            adcChannel = 0x01
        if side.lower() == 'b':
            adcChannel = 0x10
    elif ndac == 4:
        adcCfg = 0x83F1
        if side.lower() == 'a':
            adcChannel = 0x01
        if side.lower() == 'b':
            adcChannel = 0x10

    i2c = SMBus(1)

    i2c.write_byte(i2cAddr, adcChannel)
    i2c.write_word_data(0x48, 0x01, adcCfg)
    time.sleep(0.001)
    res = i2c.read_word_data(0x48, 0x00)
    i2c.write_byte(i2cAddr, 0x08)

    resDecimal = ((0xFF00 & res) >> 8) | ((0x00FF & res) << 8)

#    print("0x%X --> %d --> %.2fV"%(res, resDecimal, (19.78 * float(resDecimal) / 26640) - 10))

    return resDecimal

def aout(addr, side, ndac, value):

    if   addr == '000':
        i2cAddr = 0x77
    elif addr == '001':
        i2cAddr = 0x73
    elif addr == '010':
        i2cAddr = 0x75
    elif addr == '011':
        i2cAddr = 0x71
    elif addr == '100':
        i2cAddr = 0x76
    elif addr == '101':
        i2cAddr = 0x72
    elif addr == '110':
        i2cAddr = 0x74
    elif addr == '111':
        i2cAddr = 0x70

    if   ndac == 1:
        i2cDacAddr = 0x61
        if side.lower() == 'a':
            dacChannel = 0x01
        if side.lower() == 'b':
            dacChannel = 0x10
    elif ndac == 2:
        i2cDacAddr = 0x60
        if side.lower() == 'a':
            dacChannel = 0x01
        if side.lower() == 'b':
            dacChannel = 0x10
    elif ndac == 3:
        i2cDacAddr = 0x61
        if side.lower() == 'a':
            dacChannel = 0x02
        if side.lower() == 'b':
            dacChannel = 0x20
    elif ndac == 4:
        i2cDacAddr = 0x60
        if side.lower() == 'a':
            dacChannel = 0x02
        if side.lower() == 'b':
            dacChannel = 0x20


    i2c = SMBus(1)

    i2c.write_byte(i2cAddr, dacChannel)
    bA = 0xFF & (value >> 4)
    bB = 0xFF & ((0xFF & value) << 4)
    i2c.write_i2c_block_data(i2cDacAddr, 0x40, [bA, bB])
    i2c.write_byte(i2cAddr, 0x08)

def din(addr, side):
    res = 0x00
    i2c = SMBus(1)

    if   addr == '000':
        i2cAddr = 0x27
    elif addr == '001':
        i2cAddr = 0x26
    elif addr == '010':
        i2cAddr = 0x25
    elif addr == '011':
        i2cAddr = 0x24
    elif addr == '100':
        i2cAddr = 0x23
    elif addr == '101':
        i2cAddr = 0x22
    elif addr == '110':
        i2cAddr = 0x21
    elif addr == '111':
        i2cAddr = 0x20

    i2c.write_word_data(i2cAddr, 0x04, 0x0000)  # Polarity

    if side.lower() == 'a':
        i2c.write_word_data(i2cAddr, 0x06, 0x00FF)
        res = i2c.read_byte_data(i2cAddr, 0x00)

    if side.lower() == 'b':
        i2c.write_word_data(i2cAddr, 0x06, 0xFF00)
        res = i2c.read_byte_data(i2cAddr, 0x01)

    resp = res
    resp = "{0:0>8b}".format(res)
    resp = resp.replace('1', 'x')
    resp = resp.replace('0', '1')
    resp = resp.replace('x', '0')
    i2c.close()

    return resp

def dout(addr, side, value):

    chipEnable = 0xC0
    res = 0x00

    i2c = SMBus(1)

    if   addr == '000':
        i2cAddr = 0x27
    elif addr == '001':
        i2cAddr = 0x26
    elif addr == '010':
        i2cAddr = 0x25
    elif addr == '011':
        i2cAddr = 0x24
    elif addr == '100':
        i2cAddr = 0x23
    elif addr == '101':
        i2cAddr = 0x22
    elif addr == '110':
        i2cAddr = 0x21
    elif addr == '111':
        i2cAddr = 0x20

    i2c.write_word_data(i2cAddr, 0x04, 0x0000)  # Polarity

    if side.lower() == 'a':
    #    print ('0x%X'%(chipEnable | value))
        i2c.write_word_data(i2cAddr, 0x06, 0xFF00)
        i2c.write_word_data(i2cAddr, 0x02, chipEnable | value)
        i2c.write_word_data(i2cAddr, 0x02, value)

    if side.lower() == 'b':
        i2c.write_word_data(i2cAddr, 0x06, 0x00FF)
        i2c.write_word_data(i2cAddr, 0x02, (chipEnable | value) << 8)
        i2c.write_word_data(i2cAddr, 0x02, value << 8)

    i2c.close()

def doutbit(addr, side, posbyte, value):

    chipEnable = 0xC0
    res = 0x00

    i2c = SMBus(1)

    if   addr == '000':
        i2cAddr = 0x27
    elif addr == '001':
        i2cAddr = 0x26
    elif addr == '010':
        i2cAddr = 0x25
    elif addr == '011':
        i2cAddr = 0x24
    elif addr == '100':
        i2cAddr = 0x23
    elif addr == '101':
        i2cAddr = 0x22
    elif addr == '110':
        i2cAddr = 0x21
    elif addr == '111':
        i2cAddr = 0x20

    valPrev = 0
    if side.lower() == 'a':
        valPrev = i2c.read_byte_data(i2cAddr, 0x00)

    if side.lower() == 'b':
        valPrev = i2c.read_byte_data(i2cAddr, 0x01)

#    print ('res = ', end='')
#    print ('0x%X'%res)

    valBit = pow(2, posbyte)
    valuef = 0
    if value == 0:
        valuef = valPrev & ~valBit        
    if value == 1:
        valuef = valPrev | valBit        

    i2c.write_word_data(i2cAddr, 0x04, 0x0000)  # Polarity

    if side.lower() == 'a':
    #    print ('0x%X'%(chipEnable | value))
        i2c.write_word_data(i2cAddr, 0x06, 0xFF00)
        i2c.write_word_data(i2cAddr, 0x02, chipEnable | valuef)
        i2c.write_word_data(i2cAddr, 0x02, valuef)

    if side.lower() == 'b':
        i2c.write_word_data(i2cAddr, 0x06, 0x00FF)
        i2c.write_word_data(i2cAddr, 0x02, (chipEnable | valuef) << 8)
        i2c.write_word_data(i2cAddr, 0x02, valuef << 8)

    i2c.close()

def asetup():

    i2c = SMBus(1)

    try: i2c.write_byte(0x70, 0x08)
    except: pass
    try: i2c.write_byte(0x71, 0x08)
    except: pass
    try: i2c.write_byte(0x72, 0x08)
    except: pass
    try: i2c.write_byte(0x73, 0x08)
    except: pass
    try: i2c.write_byte(0x74, 0x08)
    except: pass
    try: i2c.write_byte(0x75, 0x08)
    except: pass
    try: i2c.write_byte(0x76, 0x08)
    except: pass
    try: i2c.write_byte(0x77, 0x08)
    except: pass

    i2c.close()

