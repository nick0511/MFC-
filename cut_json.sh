function DT0109()
{
#第一个参数是很大的日志
#第二个参数是生产文件
log=$1
file=$2
#获取log_dt文件，保存字段
var=$3
	 awk   'BEGIN{FS="'$var'"}{print $2}'  $log|awk -F'":' '{for(i=1;i<NF;i++){if($i ~/,/){split($i,arr,",");print arr[2],NR}}}'|tr -s '\n'>log_dt
	 awk   'BEGIN{FS="'$var'"}{print $2}'  $log|awk -F'":' '{for(i=1;i<NF;i++){if($i ~/,/){split($i,arr,",");print arr[3],NR}}}'|tr -s '\n'|grep '.[[:space:]][0-9]'>>log_dt

#获取生产日志的格式文件
 	grep $var $file|awk 'BEGIN{FS="'$var'"}{print $2}'|awk -F'":' '{for(i=1;i<NF;i++){if($i ~/,/){split($i,arr,",");print arr[2],NR}}}'|tr -s '\n'>0109file
 	grep $var $file|awk 'BEGIN{FS="'$var'"}{print $2}'|awk -F'":' '{for(i=1;i<NF;i++){if($i ~/,/){split($i,arr,",");print arr[3],NR}}}'|tr -s '\n'|grep '.[[:space:]][0-9]'>>0109file
#获取格式文件种数
file_num=`awk -F' '  '{print $2}' 0109file|uniq`
log_num=`awk -F' '  '{print $2}' log_dt|uniq`
for j in $log_num
do	
	grep $j log_dt|awk -F' ' '{print $1}'>cmp_tmp1
	flag=0
	for i in $file_num
	do
		grep $i 0109file|awk -F' ' '{print $1}'>cmp_tmp2
		diff cmp_tmp1 cmp_tmp2>>/dev/null 
		if [ $? -eq 0 ]
		then
			flag=1
			break
		fi
	done
	line_num=`grep $j log_dt|awk -F' ' '{print $2}'|uniq`

	if [[ $flag -eq 0 ]]
	then
		echo $line_num>>$var"_log"
	else
		echo success >>$var"_log"
	fi
done


}

DT0109 $1 $2 'DATA-TBS-0115;'
