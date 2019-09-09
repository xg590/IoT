import io
import socket
import struct
import time
import picamera

camera = picamera.PiCamera()
camera.resolution = (640, 480) 
camera.rotation = 270
camera.start_preview()
time.sleep(2) 

try:
    client_socket = socket.socket() 
    client_socket.connect(('192.168.0.94', 8000))
    connection = client_socket.makefile('wb')
    stream = io.BytesIO()
    for _ in camera.capture_continuous(stream, 'jpeg'): 
        connection.write(struct.pack('<L', stream.tell()))
        connection.flush() 
        stream.seek(0)
        connection.write(stream.read())  
        stream.seek(0)
        stream.truncate()  
        time.sleep(1)
finally:
    connection.write(struct.pack('<L', 0))
    connection.close()
    client_socket.close()