Beagletomb 0.1.5 Ubuntu install instructions

make sure if using on a network that your server is set to static IP.
Instructions not included. Check your router's manufacturer.
--------------------------------
mediatomb and lamp installation:
-------------------------------
$ sudo apt-get install tasksel mediatomb 
$ sudo tasksel install lamp-server 
WRITE DOWN PASSWORD*

run mediatomb once:

$ mediatomb 
a /.mediatomb folder should have been created with an xml file within your user directory now run the installer included in the docs folder followed by the configure:

$  sudo su 
# /opt/BeagleTomb/docs/install.sh 

Run the second option then third. Ignore and exit the tasksel graphical installer, if you completed the steps above properly. 
When requested, enter the password you wrote down earlier during lamp-server install,
Otherwise if you want to do it manually read the mediatomb mysql instructions on mediatomb's website. 

Once complete, simply end and restart the mediatomb server.

$  pkill mediatomb 
$  sudo mediatomb --port 49152    or any port you want to bind to

This process is not configured automatically on startup. It is recommended that you set that in your startup menu. 
You will need mediatomb running or beagletomb will not work.
 
You can add files to mediatomb by browsing to your servers ip and port e.g. http://192.168.1.101:49152 then simply add your media.
**new in 0.1.5 a user can click the admin button within Beagle Tomb's sun **

------------------------
Beagle Tomb Client Install
--------------------------
$  sudo apt-get install mplayer qt4-qmake g++ libmysqlcppconn-dev libsqlite3-dev sqlite3 libqt4-network libqt4-opengl-dev libqt4-opengl libqtgui4 libqtcore4
download beagletomb.v.0.1.5.tar.gz assuming in Downloads directory within your user home folder.

$ tar -xzvf ./Downloads/beagletomb*.tar.gz
$ sudo cp -R ./Downloads/BeagleTomb /opt/
$ cd /opt/BeagleTomb
$ qmake 
$ make 
$ ln -s /opt/BeagleTomb/BeagleTomb /usr/bin/BeagleTomb

Finally run the binary with: 
$ BeagleTomb 

On first open you will be asked to enter your server credentials. 
Make sure the mediatomb server initialized port and server bound ip matches the address you enter into the beagletomb preference window.

The defaults are:

user: mediatomb 
pass: mediatomb 
table: mediatomb 
SqlDir: BTmedia.db
playlist: /home/$USER/.BeagleTomb/playlist/
