#!/bin/bash
#回收站一键安装

myhome=${HOME}
trash_dir=$myhome'/.trash'
shell_file=$myhome'/myrm.sh'
if [ ! -f $shell_file ]
then
	cp ./myrm.sh $shell_file -f
fi



if [ ! -d $trash_dir ]
then 	
	mkdir -p $trash_dir
fi	
echo "垃圾桶目录已创建"


grep -q "alias rm='sh "$shell_file"'" ~/.bashrc
if [ $? -ne 0 ]
then 
	echo "alias rm='sh "$shell_file"'" >> ~/.bashrc
	echo "环境变量配置已完成"
else
	echo "环境变量配置已完成"
fi

grep -q "alias remove='/usr/bin/rm'" ~/.bashrc
if [ $? -ne 0 ]
then 
	echo "alias remove='/usr/bin/rm'" >> ~/.bashrc
	echo "新增remove命令，用于删除垃圾箱里的文件"
	echo "usage remove ~/.trash/filename"
else
	echo "新增remove命令，用于删除垃圾箱里的文件"
	echo "usage remove ~/.trash/filename"
fi



source ~/.bashrc&&echo "已完成Linux垃圾桶配置"
