## Raspberry Pi Video Streaming
### What I want
* Low latency
* Low burden for the raspberry pi on rover
* Secure video transmission between rover and intermediate server. 
* Least library dependency on rover (Install package is a nightmare on raspberry pi)
### Solution
1. Avoid <i>picamera</i> and use <i>raspivid</i> 
2. Redirect raspivid stdout (video stream in h264) to server via <i>ssh</i>
3. Encoding on the intermediate server then distribute in mjpeg 
### Implement (Proof of concept)
1. Capture video and listen on a local port 3333 on raspberry pi (it turned out that there is no noticeable burden on raspberry pi)
```shell
raspivid --timeout 0 --width 640 --height 360 --bitrate 1000000 --framerate 25 --profile baseline --listen -o tcp://127.0.0.1:3333
```
2. Initiate a remote port forwarding from raspberry pi and listen on port 2222 of remote server 
```shell
ssh -R 2222:127.0.0.1:3333 remote_server
```
3. View the stream from remote_server
```shell
ffplay -i tcp://127.0.0.1:2222
```
### Instead of ffplay, use Opencv (Python) and capture 10s video stream
```shell
sudo apt update 
sudo apt install -y python3 python3-pip
pip3 install opencv-python 
python3
>>> import cv2 
>>> cap = cv2.VideoCapture("tcp://127.0.0.1:2222")
>>> count = 0 
>>> while(cap.isOpened()): 
>>>     count += 1
>>>     if count > 250: break
>>>     ret, frame = cap.read() 
>>>     if not ret: break
>>>     cv2.imshow('frame',frame) 
>>>     cv2.waitKey(1)  
>>> cap.release()
>>> cv2.destroyAllWindows()
``` 
### Re-streaming in mjpeg
see [video_streaming.ipynb](https://github.com/xg590/IoT/blob/master/Video_Streaming/video_streaming.ipynb)
