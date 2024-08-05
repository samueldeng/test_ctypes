import ctypes


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
    print("{:}  data: {}  len: {:d}".format(message, message.data, message.len))
    for idx in range(message.len):
        print("        {:d}: {:}".format(idx, message.data[idx]))


cmpfunc = CmpFuncType(callback)


if __name__ == "__main__":
    libsum_so.start_trade_client(cmpfunc)
    libsum_so.join_trade_client()