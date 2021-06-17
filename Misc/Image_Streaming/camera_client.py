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
        # After capture, stream position equals size of buffered jpeg data
        jpeg_len = stream.tell() # find stream position
        connection.write(struct.pack('<L', jpeg_len)) 
        connection.flush() 
        stream.seek(0) # rewind stream position because we want to read from the start
        jpeg_data = stream.read()
        connection.write(jpeg_data)  
        time.sleep(1)
        # Prepare for new capture
        stream.seek(0) # rewind stream position because we need write the captured from the start
        stream.truncate(0) # Dump buffer data
finally:
    connection.write(struct.pack('<L', 0))
    connection.close()
    client_socket.close()
