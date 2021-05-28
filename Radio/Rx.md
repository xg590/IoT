### Ubuntu 20.04.02
```
echo 'blacklist dvb_usb_rtl28xxu' | sudo tee --append /etc/modprobe.d/blacklist-dvb_usb_rtl28xxu.conf
sudo apt install rtl-sdr gqrx-sdr gnuradio 
````
