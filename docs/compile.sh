#!/bin/bash
chmod -R 777 /opt/extras.ubuntu.com/beagletomb
cd /opt/extras.ubuntu.com/beagletomb
qmake
make

ln -fs /opt/extras.ubuntu.com/beagletomb/beagletomb /usr/bin/beagletomb
