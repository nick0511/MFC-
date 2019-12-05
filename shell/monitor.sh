#!/bin/bash
#默认关闭告警
plan_work=0
monitority=1
cpu=2
mem=3
disk=4

sysinfo(){
	echo "以下是系统信息："
	echo "系统版本："`cat /etc/redhat-release`
	echo "计算机名:"`hostname`
	echo "当前用户名："`whoami`
	echo "当前登陆用户数："`uptime |cut -d',' -f2`
	echo "当前登陆用户："`w|tail -n +3|cut -d" " -f1|sort|uniq`
	echo "----------------------------------------------"	
}
cpuinfo(){
cpu_user=`top -b -n 1 | grep Cpu | awk -F' ' '{print $2}'`

echo "用户空间占用CPU百分比："$cpu_user"%"

 

# 获取内核空间占用CPU百分比

cpu_system=`top -b -n 1 | grep Cpu | awk -F' ' '{print $4}'`

echo "内核空间占用CPU百分比："$cpu_system"%"

 

# 获取空闲CPU百分比

cpu_idle=`top -b -n 1 | grep Cpu | awk -F' ' '{print $8}'`

echo "空闲CPU百分比："$cpu_idle"%"

 

# 获取等待输入输出占CPU百分比

cpu_iowait=`top -b -n 1 | grep Cpu | awk -F' ' '{print $10}'`

echo "等待输入输出占CPU百分比："$cpu_iowait"%"


# 获取CPU15分钟前到现在的负载平均值

cpu_load_15min=`uptime | awk '{print $11}' | cut -f 1 -d ','`

echo "CPU 15分钟前到现在的负载平均值："$cpu_load_15min

 

# 获取CPU5分钟前到现在的负载平均值

cpu_load_5min=`uptime | awk '{print $10}' | cut -f 1 -d ','`

echo "CPU 5分钟前到现在的负载平均值："$cpu_load_5min

 

# 获取CPU1分钟前到现在的负载平均值

cpu_load_1min=`uptime | awk '{print $9}' | cut -f 1 -d ','`

echo "CPU 1分钟前到现在的负载平均值："$cpu_load_1min

 

# 获取任务队列(就绪状态等待的进程数)

cpu_task_length=`vmstat -n 1 1 | sed -n 3p | awk '{print $1}'`

echo "CPU任务队列长度："$cpu_task_length



}
meminfo(){
 
# 获取物理内存总量

mem_total=`free | grep Mem | awk '{print $2}'`

echo "物理内存总量："$mem_total


# 已使用内存总量

mem_sys_used=`free | grep Mem | awk '{print $3}'`

echo "已使用内存总量："$mem_sys_used

# 获取未使用内存总量

mem_sys_free=`free | grep Mem | awk '{print $4}'`

echo "剩余内存总量："$mem_sys_free

 

 
	}
diskinfo(){
	partition=""
	read -p"输入查看哪个分区[默认全部]" partition
		
	if [[ $partition == "" ]]
	then
		df -hl
	else
		df -hl $partition
	fi
}
topn(){

	n=""
	while  [[ "1" == "1" ]]
 	do
	read -p "设置显示前几个？(1-10)默认top 5:" n
	if [[ $n == "" ]]
	then
		n=5
		break
	fi
	if [ $n -lt 0 -o $n -gt 10 ]
	then	
		echo "wrong args"
		exit 1
	fi
	break
	done
	top -b -n 1 |sed -n '8,$p'|sort -n -k 9  -r |head -n $n

}

echo "1、查看cpu占用情况"
echo "2、查看内存使用情况"
echo "3、查看磁盘使用情况"
echo "4、获取占用cpuTOP n进程"
echo "5、开启阈值报警"
echo "6、设置检测周期"
echo "7、取消周期检测"


read selection

case $selection in 
	1)
        cpuinfo
	;;
	2)
	meminfo
	;;
	3)
	diskinfo
	;;
	4)
	topn
	;;
	5)
	head -n 10 $0|grep 'monitority=0'  -q
	status=`echo $?`
	if [ $status -eq 0 ]
	then
		echo "处于关闭状态,是否开启？[Y|N]"
		read choice
		if [[ $choice == "Y" ]]
		then
			sed -i '0,/monitority=0/s//monitority=1/' $0
			read -p "cpu阈值" cpu_new
			read -p "memory阈值" mem_new
			read -p "磁盘使用率阈值" disk_new
			cpu_old=`head -n 10 $0|grep cpu`
			mem_old=`head -n 10 $0|grep mem`
			disk_old=`head -n 10 $0|grep disk`
			cpu_new="cpu="$cpu_new
			mem_new="mem="$mem_new
			disk_new="disk="$disk_new
			echo $cpu_old
			sed -i "0,/$cpu_old/s//$cpu_new/" $0
			sed -i "0,/$mem_old/s//$mem_new/" $0
			sed -i "0,/$disk_old/s//$disk_new/" $0
		else
			exit 0
		fi
		
		
	else
		echo "处于开启状态，是否关闭？[Y|N]"
		read choice
		if [[ $choice == "Y" ]]
		then
			sed -i '0,/monitority=1/s//monitority=0/' $0
		else
			exit 0
		fi
	fi
	;;
	6)

		echo "1、查看cpu占用情况"
		echo "2、查看内存使用情况"
		echo "3、查看磁盘使用情况"
		read  -p "设置任务" task
		echo "2、两分钟一次"	
		echo "5、五分钟一次"
		echo "10、十分钟一次"
		read -p "设置间隔" t
		
		ls|grep -q "task_[0-9]\{1,\}"
		if [ $? -eq 0 ]
		then
			tasknum=`ls|grep "task_[0-9]\{1,\}"|awk -F'_' '{print $2+1}'`
		else
			tasknum=0
		fi

		if [ $task -eq 1 ]
		then
		
			
			let cpui=100-cpu
			echo "cpui="$cupi
			cat $0|head -n 35|tail -1  >>"task_"$tasknum
			if [ $monitority -eq 1 ]
			then
			echo 'if [ cpu_idle -lt $cpui ]' >>"task_"$tasknum
			echo "then">>"task_"$tasknum
			echo 'wall cpu warn!'>>"task_"$tasknum
			echo "fi">>"task_"$tasknum
			fi
		elif [ $task -eq 2 ]
		then
			let memi=100-mem
			echo "memi="$memi >>"task_"$tasknum
			cat $0|head -n 85|tail -1 >>"task_"$tasknum

			echo "物理内存总量："'$mem_total'>"task_"$tasknum


			cat $0|head -n 92|tail -1>"task_"$tasknum

			echo '已使用内存总量：$mem_sys_used'>"task_"$tasknum
		
			if [ $monitority -eq 1 ]
			then
			echo 'if [ `echo $mem_total/$mem_sys_used|bc` -lt $memii ]'>"task_"$tasknum
			echo "then">"task_"$tasknum
			
			echo 'wall mem warn!'>"task_"$tasknum
			echo "fi">"task_"$tasknum
			fi
		elif [ $task -eq 3 ]
		then
			let diski=100-disk
			echo "diski="$diski>>"task_"$tasknum
			echo "diskused=`df -lh /|tail -1|awk -F' ' '{print $5}'|cut -d'%' -f1`" >"task_"$tasknum	
			if [ $monitority -eq 1 ]
			then
			echo 'if [ $diskused -gt $diski ]'>"task_"$tasknum
			echo "then">"task_"$tasknum
			echo 'wall disk warn!' >> "task_"$tasknum
			echo "fi">"task_"$tasknum
			fi
		
		fi
		echo '*/'$t' * * * * root bash /root/task_'$tasknum >>/etc/crontab
	
	;;
	7)
			ls|grep "task_[0-9]\{1,\}"
			echo "删除哪个任务？task_?"
			read num
			rm -rf task_$num
	;;
	*)
	break
	;;
	
esac
           
