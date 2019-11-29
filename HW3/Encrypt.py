from Crypto.Cipher import AES
import Utils

def encryptECB(blocks, key):
    cipher = AES.new(key, AES.MODE_ECB)
    cipherBlocks = [cipher.encrypt(x) for x in blocks]
    return cipherBlocks


def encryptCBC(blocks, key):
    IV = b'2189354898452880'
    cipher = AES.new(key, AES.MODE_ECB)

    cipherBlocks = []
    xorBytes = Utils.xorTwoBytes(IV, blocks[0])
    cipherText = cipher.encrypt(xorBytes)
    cipherBlocks.append(cipherText)
    for i in range(1, len(blocks)):
        xorBytes = Utils.xorTwoBytes(cipherText, blocks[i])
        cipherText = cipher.encrypt(xorBytes)
        cipherBlocks.append(cipherText)

    return cipherBlocks


def encryptOFB(blocks, key):
    IV = b'1594826730846139'
    cipher = AES.new(key, AES.MODE_ECB)
    cipherText = cipher.encrypt(IV)
    cipherBlocks = []
    for i in range(len(blocks)):
        cipherBlocks.append(Utils.xorTwoBytes(blocks[i], cipherText))
        cipherText = cipher.encrypt(cipherText)

    return cipherBlocks


name = input('file name(with format): ')
key = input('key: ')
mode = input('mode: ')
bytesKey = bytes(key, encoding='utf-8')
bytesKey = bytesKey[0:16]
Utils.pngToPpm(name)
header, rawData = Utils.getPpmInfo()

data = Utils.padding(rawData)
blocks = Utils.blocking(data)
if mode == 'ECB':
    cipherBlocks = encryptECB(blocks, bytesKey)
elif mode == 'CBC':
    cipherBlocks = encryptCBC(blocks, bytesKey)
elif mode == 'OFB':
    cipherBlocks = encryptOFB(blocks, bytesKey)
ppmInfo = Utils.createPpmInfo(header, cipherBlocks)

Utils.setPpmInfo(ppmInfo)
Utils.ppmToPng('encrypt'+mode+'_'+name)
