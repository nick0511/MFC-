#!/bin/bash
#����վһ����װ

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
echo "����ͰĿ¼�Ѵ���"


grep -q "alias rm='sh "$shell_file"'" ~/.bashrc
if [ $? -ne 0 ]
then 
	echo "alias rm='sh "$shell_file"'" >> ~/.bashrc
	echo "�����������������"
else
	echo "�����������������"
fi

grep -q "alias remove='/usr/bin/rm'" ~/.bashrc
if [ $? -ne 0 ]
then 
	echo "alias remove='/usr/bin/rm'" >> ~/.bashrc
	echo "����remove�������ɾ������������ļ�"
	echo "usage remove ~/.trash/filename"
else
	echo "����remove�������ɾ������������ļ�"
	echo "usage remove ~/.trash/filename"
fi



source ~/.bashrc&&echo "�����Linux����Ͱ����"
