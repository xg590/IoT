img=${1%.xz}
YOUR_SSID=$2
YOUR_WIFI_PASSWORD=$3
xz -dk $img.xz 
mkdir /tmp/raspbian_os_boot
sudo mount -o offset=$((8192*512)),umask=0002,uid=$UID $img /tmp/raspbian_os_boot  
touch        /tmp/raspbian_os_boot/ssh                  # Enable ssh server at first boot    
cat << EOF > /tmp/raspbian_os_boot/wpa_supplicant.conf  # Join WiFi network
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
country=US
update_config=1
network={
    ssid="${YOUR_SSID}"
    psk="${YOUR_WIFI_PASSWORD}"
    key_mgmt=WPA-PSK
}
EOF
cat << EOF > /tmp/raspbian_os_boot/userconf.txt
pi:$(echo 'raspberry' | openssl passwd -6 -stdin)
EOF
sudo umount /tmp/raspbian_os_boot
mkdir /tmp/raspbian_os_sys
sudo mount -o offset=$((532480*512)) $img /tmp/raspbian_os_sys/
cat << EOF | sudo tee -a /tmp/raspbian_os_sys/etc/ssh/sshd_config 1> /dev/null
PasswordAuthentication no
PubkeyAuthentication yes
PermitRootLogin no
EOF
sudo mkdir -p /tmp/raspbian_os_sys/var/www/html
sudo mkdir -p /tmp/raspbian_os_sys/etc/samba
cat << EOF | sudo tee /tmp/raspbian_os_sys/etc/samba/smb.conf 1> /dev/null
[global]
   workgroup = WORKGROUP
   server string = %h server (Samba, Ubuntu)
   log file = /var/log/samba/log.%m
   max log size = 1000
   logging = file
   panic action = /usr/share/samba/panic-action %d
   server role = standalone server
   obey pam restrictions = yes
   unix password sync = yes
   passwd program = /usr/bin/passwd %u
   passwd chat = *Enter\snew\s*\spassword:* %n\n *Retype\snew\s*\spassword:* %n\n *password\supdated\ssuccessfully* .
   pam password change = yes
   map to guest = bad user
   bind interfaces only = yes
[pi]
    comment = Samba on Ubuntu
    path = /var/www/html
    read only = no
    guest ok  = yes
    browsable = yes
    create mask = 0644
    directory mask = 0755
    public = yes
    force user = pi
EOF
mkdir -p                                        /tmp/raspbian_os_sys/home/pi/.ssh
ssh-keygen -t rsa -b 4096 -N '' -C '' -f        /tmp/raspbian_os_sys/home/pi/.ssh/id_rsa
cp /tmp/raspbian_os_sys/home/pi/.ssh/id_rsa.pub /tmp/raspbian_os_sys/home/pi/.ssh/authorized_keys 
sudo umount                                     /tmp/raspbian_os_sys/