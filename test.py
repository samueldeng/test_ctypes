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
    print("field1:", field1.decode('ascii').strip(' '))
    print("field2:", field2)
    print("field3:", field3)
    print("field4:", field4.decode('ascii').strip(' '))
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
            msg = Message()
            msg.type = 1
            msg.len = 4
            # 使用 struct 模块将字符串转换为字节数组
            data_str = "test"
            data_bytes = struct.pack('%ds' % msg.len, data_str.encode('ascii'))  # 将字符串编码为字节对象
            # 创建一个 ctypes 字节数组并赋值给 data 字段
            data_array = (ctypes.c_char * msg.len).from_buffer_copy(data_bytes)
            msg.data = ctypes.cast(data_array, ctypes.POINTER(ctypes.c_char))
            msg.checksum = 1234
            print(libsum_so.send_message(msg))
            time.sleep(1)

    except KeyboardInterrupt:
        libsum_so.stop_trade_client()
        print("Bye Bye")
        sys.exit(0)
