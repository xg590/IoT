## Image Streaming Scheme for my Rover
Captrue images in jpeg format by the on-board PiCamera and send them to a streaming webserver. <br>
The motion jpeg could be rendered in user's browser. <br>
This scheme will minimize the burden on Raspberry Pi Zero W of the Rover. (Around 5% cpu consumption, 10% RAM comsumption at most) <br>
If the capture is at 480p and 1fps then bandwidth comsumption is about 800kbps (of course, equals the size of a jpeg image) <br>
