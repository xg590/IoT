## Raspberry Pi Streaming
### What I want
* Low latency
* Low burden for the raspberry pi on rover
* Secure video transmission between rover and intermediate server. 
* Least library dependency on rover (Install package is a nightmare on raspberry pi)
### Solution
1. Avoid python and use <i>raspivid</i> 
2. Redirect stdout (video stream in h264) of raspivid to server via <i>ssh</i>
3. Encoding on the intermediate server and then distribute in webm (maybe)
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
### Python
```shell
sudo apt update 
sudo apt install screen python3 python3-pip
pip3 install jupyter
mkdir ~/.jupyter
cat << EOF >> ~/.jupyter/jupyter_notebook_config.py
c.NotebookApp.ip = '0.0.0.0'
c.NotebookApp.port = 8888
c.NotebookApp.password = 'sha1:ffed18eb1683:ee67a85ceb6baa34b3283f8f8735af6e2e2f9b55'
EOF
.local/bin/jupyter-notebook
```
```python 
```
