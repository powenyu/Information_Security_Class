from Crypto.Cipher import AES
import Utils


def decryptECB(blocks, key):
    cipher = AES.new(key, AES.MODE_ECB)
    plainBlocks = [cipher.decrypt(x) for x in blocks]
    return plainBlocks


def decryptCBC(blocks, key):
    IV = b'2189354898452880'
    cipher = AES.new(key, AES.MODE_ECB)

    plainBlocks = []
    plainBlocks.append(Utils.xorTwoBytes(cipher.decrypt(blocks[0]), IV))
    for i in range(1, len(blocks)):
        plainBlocks.append(Utils.xorTwoBytes(
            cipher.decrypt(blocks[i]), blocks[i-1]))
    return plainBlocks


def decryptOFB(blocks, key):
    IV = b'1594826730846139'
    cipher = AES.new(key, AES.MODE_ECB)
    plainText = cipher.encrypt(IV)
    plainBlocks = []
    for i in range(len(blocks)):
        plainBlocks.append(Utils.xorTwoBytes(blocks[i], plainText))
        plainText = cipher.encrypt(plainText)

    return plainBlocks


name = input('file name(with format): ')
key = input('key: ')
mode = input('mode: ')
bytesKey = bytes(key, encoding='utf-8')
bytesKey = bytesKey[0:16]
Utils.pngToPpm('encrypt'+mode+'_'+name)
header, rawData = Utils.getPpmInfo()

data = Utils.padding(rawData)
blocks = Utils.blocking(data)
if mode == 'ECB':
    plainBlocks = decryptECB(blocks, bytesKey)
elif mode == 'CBC':
    plainBlocks = decryptCBC(blocks, bytesKey)
elif mode == 'OFB':
    plainBlocks = decryptOFB(blocks, bytesKey)
ppmInfo = Utils.createPpmInfo(header, plainBlocks)

Utils.setPpmInfo(ppmInfo)
Utils.ppmToPng('decrypt'+mode+'_'+name)
