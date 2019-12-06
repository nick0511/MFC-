#!/bin/bash

while [ "1" == "1" ]
do

	echo "输入你的选择"
	echo "1		:显示用户数目"
	echo "2		:显示所有用户"
	echo "3		:增加用户"
	echo "4		:删除普通用户"
	echo "其他	:退出"
	read seletion	
case $seletion in
	1)
		echo "用户数目："
		cat /etc/passwd|wc -l
	;;
	2)
		echo "所有用户："
		cat /etc/passwd|cut -d':' -f1
	;;
	3)
		home_dir=""
		echo "增加用户功能："	
		echo "输入用户名："
		read username
		echo "输入密码"
		read password
		echo "输入用户家目录(不输入默认为/home/"$username")"	
		read home_dir
		if [ -z $home_dir]
		then
			useradd $username
		else
			useradd $username -d $home_dir	
		fi
		echo $password|passwd --stdin $username
	;;
	4)
		echo "输入删除的用户名"
		read username
		userdel $username
		echo "用户"$username"以删除"
		
	;;
	*)
		echo BYEBYE
		exit 0
	;;


esac
	
done
