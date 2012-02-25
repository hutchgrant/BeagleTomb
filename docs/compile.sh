#!/bin/bash
chmod 777 /opt/BeagleTomb/
cd /opt/BeagleTomb
qmake
make

ln -s /opt/BeagleTomb/BeagleTomb /usr/bin/BeagleTomb
chmod 777 /usr/bin/BeagleTomb
