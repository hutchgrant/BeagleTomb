#!/bin/bash
mkdir -p ./tmp/apd/
cp ~/.mediatomb/config.xml ./tmp/config2.xml

echo  "What is your Server's local IP?"
read HOSTIP

STR_TO=$HOSTIP
STR_FROM='localhost'
UI_TO='ui enabled="yes"'
UI_FROM='ui enabled="no"'
SQL_TO='<mysql enabled="yes"'
SQL_FROM='<mysql enabled="no"'
SQLite_TO='sqlite3 enabled="no"'
SQLite_FROM='sqlite3 enabled="yes"'
file='./tmp/config.xml'
TFILE='./tmp/config2.xml'
file2='./tmp/mysqlConf'
TFILE2='./tmp/my.cnf'
SQLBind_TO=$HOSTIP
SQLBind_FROM='127.0.0.1'

# sudo sed "s/$STR_FROM/$STR_TO/g" "$file" > $TFILE
sudo sed "s/$UI_FROM/$UI_TO/g" "$TFILE" > $file
sudo sed "s/$SQL_FROM/$SQL_TO/g" "$file" > $TFILE
sudo sed "s/$SQLite_FROM/$SQLite_TO/g" "$TFILE" > $file


sed '21q' $file > ./tmp/apd/atestout.txt 
sed -e :a -e '$q;N;127,$D;ba' $file > ./tmp/apd/dtestoutput.txt
echo "<host>"$HOSTIP"</host>" > ./tmp/apd/btestout.txt
echo "<username>mediatomb</username>" > ./tmp/apd/ctestout.txt
echo "<password>mediatomb</password>" >> ./tmp/apd/ctestout.txt
cat ./tmp/apd/* > $TFILE

cp $TFILE /etc/mediatomb/config.xml
cp $TFILE ~/.mediatomb/config.xml

sudo chown mediatomb:mediatomb /etc/mediatomb/config.xml
sudo chown mediatomb:mediatomb ~/.mediatomb/config.xml

cp /etc/mysql/my.cnf ./tmp/mysqlConf

sed "s/$SQLBind_FROM/$SQLBind_TO/g" "$file2" > $TFILE2

cp -f $TFILE2 /etc/mysql/my.cnf

rm -R ./tmp/apd
rm ./tmp/mysqlConf
rm ./tmp/config2.xml
rm ./tmp/config.xml


sudo cp ~/BeagleTomb/BT /usr/bin/BT
sudo chmod 777 /usr/bin/BT
