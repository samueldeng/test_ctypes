import ctypes
import time
import struct
import threading
import sys

class Message(ctypes.Structure):
    _fields_ = [
        ("type", ctypes.c_int),
        ("len", ctypes.c_int),
        ("data", ctypes.POINTER(ctypes.c_char)),
        ("checksum", ctypes.c_int),        
]

libsum_so = ctypes.CDLL("./trade_client/libtrade_client_api.dylib") 

CmpFuncType = ctypes.CFUNCTYPE(None, Message)

def callback(message):
    print("{:}  type: {}  len: {:d} data: {} checksum: {:d}".format(message, message.type, message.len, message.data, message.checksum))
    field1, field2, field3, field4, field5, field6 = struct.unpack('<ciI5sQH', message.data[0:24])
    print("field1:", field1.decode('utf-8').strip(' '))
    print("field2:", field2)
    print("field3:", field3)
    print("field4:", field4.decode('utf-8').strip(' '))
    print("field5:", field5)
    print("field6:", field6)

cmpfunc = CmpFuncType(callback)

def trade_client_thread():
    libsum_so.start_trade_client(cmpfunc)
    libsum_so.join_trade_client()

if __name__ == "__main__":    
    try:
        threading.Thread(target=trade_client_thread).start()
        while (True):
            time.sleep(20)

    except KeyboardInterrupt:
        libsum_so.stop_trade_client()
        print("Bye Bye")
        sys.exit(0)
