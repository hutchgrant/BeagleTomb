BeagleTomb 0.1.6 Ubuntu install instructions

Enables any user to connect with their entire media library, remotely, at the click of a buttion
Create playlists of your remote media, browse audio/video quickly and easily.


mediatomb install
$ sudo apt-get install tasksel mediatomb 
$ sudo tasksel install lamp-server 
WRITE DOWN PASS

run mediatomb once:

$ mediatomb 
a .mediatomb folder should have been created with an xml file within your user directory now run the installer included in the docs folder followed by the configure:

$  sudo su 
# /opt/extras.ubuntu.com/beagletomb/docs/install.sh 
run the second option then third. Ignore and exit the tasksel graphical installer, if you completed the steps above properly. Otherwise if you want to do it manually read the mediatomb mysql instructions on mediatomb's website. Once complete, simply end and restart the mediatomb server.

$  pkill mediatomb 
$  sudo mediatomb --port 49152    or any port you want to bind to
This process is not configured automatically on startup. I recommend setting that in your startup menu. You will need mediatomb running or beagletomb will not work. You can add files to mediatomb by browsing to your servers ip and port e.g. http://192.168.1.101:49152 then simply add your media.


If you haven't already, set your host machine to a static IP on your router.


beagletomb client install

$  sudo apt-get install mplayer libqt4-dev

download beagletomb.v.0.1.3.tar.gz assuming in Downloads directory within your user home folder.
 $ cd ~/Downloads
 $  tar -zxvf beagletomb*.tar.gz 
 $ sudo mkdir /opt/extras.ubuntu.com
 $ sudo cp -R beagletomb /opt/extras.ubuntu.com/
 $ chmod 777 -R /opt/extras.ubuntu.com/beagletomb

compile and run
 $ cd /opt/extras.ubuntu.com/beagletomb
 $ qmake 
 $ make

 link it with:
 $ ln -fs /opt/extras.ubuntu.com/beagletomb/beagletomb /usr/bin/beagletomb
 
 Finally run the binary with: 
 $ beagletomb 

On first open you will be asked to enter your server credentials. Make sure the mediatomb server initialized port and server bound ip matches the address you enter into the beagletomb preference window.

The defaults are:

user: mediatomb pass: mediatomb table: mediatomb SqlDir?: BTmedia.db


