Beagletomb 0.1.5 Ubuntu install instructions

enables any user to connect with their media library, remotely, at the click of a button

QT/ C++ Mediatomb client

If USING ON A LOCAL NETWORK: MAKE YOUR SERVER A STATIC LOCAL IP FIRST not included

mediatomb install

$ sudo apt-get install tasksel mediatomb 
$ sudo tasksel install lamp-server 
WRITE DOWN PASS

run mediatomb once:

$ mediatomb 
a /.mediatomb folder should have been created with an xml file within your user directory now run the installer included in the docs folder followed by the configure:

$  sudo su 
$ /usr/share/BeagleTomb/docs/install.sh 

run the second option then third. Ignore and exit the tasksel graphical installer, if you completed the steps above properly. Otherwise if you want to do it manually read the mediatomb mysql instructions on mediatomb's website. Once complete, simply end and restart the mediatomb server.

$  pkill mediatomb 
$  sudo mediatomb --port 49152    or any port you want to bind to
This process is not configured automatically on startup. I recommend setting that in your startup menu. You will need mediatomb running or beagletomb will not work. You can add files to mediatomb by browsing to your servers ip and port e.g. http://192.168.1.101:49152 then simply add your media.

beagletomb client install

$  sudo apt-get install mplayer qt4-qmake g++ libmysqlcppconn-dev libsqlite3-dev sqlite3 libqt4-network libqt4-opengl-dev libqt4-opengl libqtgui4 libqtcore4
download beagletomb.v.0.1.5.tar.gz assuming in Downloads directory within your user home folder.

$ tar -xzvf ./Downloads/beagletomb*.tar.gz
$ sudo cp -R ./BeagleTomb /usr/share/
$ cd /usr/share/BeagleTomb
$ qmake 
$ make 
ln -s /usr/share/BeagleTomb/BeagleTomb /usr/bin/BeagleTomb
make your cache directory in your home folder called ".BeagleTomb?"

mkdir -p ~/.BeagleTomb/cache
mkdir -p ~/.BeagleTomb/playlist
Finally run the binary with: $ BeagleTomb? On first open you will be asked to enter your server credentials. Make sure the mediatomb server initialized port and server bound ip matches the address you enter into the beagletomb preference window.

The defaults are:

user: mediatomb pass: mediatomb table: mediatomb SqlDir??: BTmedia.db
