
#!/bin/bash

dbuser="mediatomb"
dbpass="mediatomb"

DFLT_MT="~/.mediatomb/config.xml"
DFLT_SQL="/etc/mysql/my.cnf"

UI_TO='ui enabled="yes"'
UI_FROM='ui enabled="no"'
SQL_TO='<mysql enabled="yes"'
SQL_FROM='<mysql enabled="no"'
SQLite_TO='sqlite3 enabled="no"'
SQLite_FROM='sqlite3 enabled="yes"'

file='/tmp/BT1/config.xml'
TFILE='/tmp/BT1/config2.xml'
SQL_file='/tmp/BT1/mysqlConf'
SQL_fin='/tmp/BT1/my.cnf'
SQLBind_TO=$HOSTIP
SQLBind_FROM='127.0.0.1'
exitMain=0

FinFile="/tmp/BT1/config4.xml"

crtusr2="create user '$dbuser'@'localhost' identified by '$dbuser';"
crtusr="create user '$dbuser'@'%' identified by '$dbuser';"
crtpermiss="grant all on mediatomb.* to '$dbuser'@'%' identified by 'mediatomb';"
crtpermiss2="grant all on mediatomb.* to '$dbuser'@'localhost' identified by 'mediatomb';"
lvmysql="exit"


crtdb="create database mediatomb"


if [ $USER != 'root' ];
then
echo "Beagle Tomb REQUIRES root in order to install"
exit 0
fi

choice=0

while [ $choice != 4 ]
do
clear
echo "Beagle Tomb Setup Menu"
echo "======================"
echo "1) Instructions"
echo "2) Install"
echo "3) Configure"
echo "4) quit"
read choice

case $choice in
2)
echo  "What is your Server's local IP?"
read HOSTIP
echo  "What is your preferred mediatomb Username?"
read dbuser
echo  "What is your preferred mediatomb Password?"
read dbpass
echo "***** Mysql Table and User install*****"
echo "***************************************"
echo "*"
echo "*"
echo " the field below you must enter your root password to your mysql database "
echo " if you just installed mysql it's the password you set during installation"
echo " note:  this password is not stored "
echo "*"
echo "*"
mysql -u root -p << eof 
$crtusr2
$crtusr
$crtpermiss
$crtpermiss2
$lvmysql
eof
echo " mediatomb user+password+permissions created."
echo " creating table..... "
mysql -u mediatomb --password=$dbpass << eof
$crtdb
eof
echo " Filling database....."
mysql mediatomb -u mediatomb --password=$dbpass < /usr/share/mediatomb/mysql.sql
echo " Install Complete. Hit enter return to menu. Next step:  configuration."
read fin1

;;
3)
# sh configure.sh
mkdir -p /tmp/BT/
mkdir -p /tmp/BT1/
chmod 777 /tmp/BT1/
chmod 777 /tmp/BT/
cp ~/.mediatomb/config.xml $TFILE

sed "s/$UI_FROM/$UI_TO/g" "$TFILE" > $file
sed "s/$SQL_FROM/$SQL_TO/g" "$file" > $TFILE
sed "s/$SQLite_FROM/$SQLite_TO/g" "$TFILE" > $file


sed '21q' $file > /tmp/BT/atestout.txt 
sed -e :a -e '$q;N;127,$D;ba' $file > /tmp/BT/dtestoutput.txt
echo "<host>"$HOSTIP"</host>" > /tmp/BT/btestout.txt
echo "<username>"$dbuser"</username>" > /tmp/BT/ctestout.txt
echo "<password>"$dbpass"</password>" >> /tmp/BT/ctestout.txt
cat /tmp/BT/* > $FinFile

cp $FinFile ~/.mediatomb/config.xml

sudo chown mediatomb:mediatomb ~/.mediatomb/config.xml

cp $DFLT_SQL $SQL_file

sed "s/$SQLBind_FROM/$SQLBind_TO/g" "$SQL_file" > $SQL_fin

cp -f $SQL_fin $DFLT_SQL

 rm -R /tmp/BT
 rm -R /tmp/BT1
echo " Configure Complete. Hit enter to return to menu."
read fin
;;
1)

step=1
step1='16q'
step2='35q'
step3='70q'
step4='85q'
file='instructions'
Instchoice=0
while [ $Instchoice != "x" ]
do
	case $step in
	1)
	sed $step1 $file 
	read Instchoice 	
	step="2"
	;;
	2)
	sed $step2 $file 
	read Instchoice 
	step="3" 
	;;
	3)
	sed $step3 $file 
	read Instchoice 
	step="4"
	;;
	4)
	sed $step4 $file 
	read Instchoice 
	;;
	esac	
done
;;
esac
done
exit
