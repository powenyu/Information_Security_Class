from PIL import Image

def pngToPpm(name):
    with Image.open(name+'.png') as photo:
        photo.save('temp.ppm', 'ppm')


def ppmToPng(name):
    with Image.open('temp.ppm') as photo:
        photo.save(name+'.png', 'png')


def getPpmInfo():
    with open('temp.ppm', 'rb') as file:
        ppmFormat = file.readline()
        ppmSize = file.readline()
        ppmMaxColor = file.readline()
        ppmHeader = ppmFormat+ppmSize+ppmMaxColor
        ppmData = file.read()
    return ppmHeader, ppmData


def padding(data):
    paddingNum = 16-len(data) % 16
    paddingBytes = bytes([paddingNum])
    while paddingNum != 0:
        data += paddingBytes
        paddingNum -= 1
    return data


def blocking(data):
    blocks = []
    i = 0
    while i < len(data):
        blocks.append(data[i:i+16])
        i += 16
    return blocks


def xorTwoBytes(b1, b2):

    xorBytes = bytes()
    for i in range(16):
        xorBytes += bytes([b1[i] ^ b2[i]])
    return xorBytes


def createPpmInfo(ppmHeader, ppmData):
    ppmInfo = ppmHeader
    for i in ppmData:
        ppmInfo += i
    return ppmInfo


def setPpmInfo(data):
    with open('temp.ppm', 'wb') as file:
        file.write(data)
