#!/bin/bash
cd /opt/BeagleTomb
qmake
make
cp -R /opt/BeagleTomb/ /usr/share/BeagleTomb
rm -R /opt/BeagleTomb/


ln -s /usr/share/BeagleTomb/BeagleTomb /usr/bin/BeagleTomb
chmod 777 /usr/bin/BeagleTomb
