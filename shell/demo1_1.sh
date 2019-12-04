#!/bin/bash
#第一个参数是cms文件
#第二个参数是mem文件
#结果输出到后面的result.log
if [ -e ./result.log ]
then
	`rm -rf ./result.log`
fi
cms=$1

mem=$2

#去掉不用的数据
cat  $cms|awk -F' ' '{if($0 ~/message/)print$0}' >cms_reg

cat cms_reg |grep "11991=[0-9]\+" -o |sort |uniq >tmp_mem_grepkey11991
cat $mem |grep "11991=[0-9]\+" -o |sort |uniq >tmp_cms_grepkey11991

grep -wf tmp_mem_grepkey11991 tmp_cms_grepkey11991|sort > same_grepkey11991

cat cms_reg |grep "12058=[0-9]\+" -o |sort |uniq >tmp_mem_grepkey12058
cat $mem |grep "12058=[0-9]\+" -o |sort |uniq >tmp_cms_grepkey12058

grep -wf tmp_mem_grepkey12058 tmp_cms_grepkey12058|sort > same_grepkey12058

#输出共有的11991=
#11991=的可能性

#清洗处理数据
#echo $mem_gresult
gcount=0
for i in `cat same_grepkey11991`
do
let gcount=gcount+1
i12=`head -n $gcount same_grepkey12058|tail -1`
rm tmp1 tmp2 tmp3 client_gresult mem_gresult -rf >>/dev/null



cat -v  cms_reg|grep $i|grep $i12 >client_gresult
cat -v  $mem|grep $i|grep $i12 >mem_gresult
cat cms_reg|grep $i|grep $i12 >client_gresult_source
cat $mem|grep $i|grep $i12 >mem_gresult_source



#每一行的client数据
while read client_line
do
	echo $client_line|awk -F"[.^]A" '{for(i=8;i<(NF-1);i++)printf("%d:%s\n",i,$i)}'|sort>>tmp1
done < client_gresult


#每一行的mem数据

while read mem_line
do
	rm  tmp2 tmp3 -rf >>/dev/null
	#删除之前生成的tmp2 tmp3
	echo $mem_line|awk -F"[.^]A" '{for(i=8;i<(NF-1);i++)printf("%d:%s\n",i,$i)}'|sort>tmp2

#得出tmp1-->cmsfile 和mem文件差异的行
#sort tmp1 tmp2 tmp2 | uniq -u >tmp3
awk '{if(ARGIND==1) {val[$0]}else{if($0 in val)  delete val[$0]}}END{for(i in val) print i}' tmp2 tmp1 >tmp3


tmp=`cat tmp3`
#tmp3大小不为0
#tmp3 格式 ： 项数:...=,,,
#tmp3 保存的是tmp2有tmp1没的项

#tmp3是否有东西？
if [ -n "$tmp"  ]
then
	echo "failed">>result.log
   for i in  `cat -v tmp3`
   do
	tmp_i=$i
	#保存原有的i到tmp_i
	#tmp_i的格式
	i=`echo $i`
	i_mem=`echo $i|awk -F':' '{print $2}'`
	#取项数的内容 ----》i_mem

	ikey=`echo $i|awk -F'=' '{print $1}' `
	#取项数 ---》i
	
	#tmp1取tmp1的ikey项，取项数后的内容
	i=`grep   $ikey tmp1|awk -F':' '{print $2}'`
	i=`echo $i|awk -F' ' '{print $1}'`	

#利用汉字的ANSI中必有M-的原理判断是否值为汉字，是就进行汉字的替换操作
  result=`echo $i|grep "M-"`
#=============================开始替换操作=============================
  if [ -n "$result" ]
  then 
#获取值

  #不同值的所在的行 ANSI码形式
  mem_line=`cat -vn mem_gresult_source|grep $i_mem|head -n 1|awk -F' ' '{print $1}' `
  client_line=`cat -vn client_gresult_source|grep $i|head -n 1|awk -F' ' '{print $1}'`
 
  #假设为key=value 
  #不同的key
  diff_key=`echo $i_mem|awk -F'=' '{print $1}'

  #值的位置,从tmp3中查询，等于序号加一
  site=`cat tmp3|grep $tmp_i|awk -F':' '{print $1}'`
  let site=site+1

  i=`cat client_gresult_source|head -n $client_line|tail -1|awk -F'=' '{print $'""$site""'}'`
  i_mem=`cat mem_gresult_source|head -n $mem_line  |tail -1|awk -F'=' '{print $'""$site""'}'`
#取出第site的位置的值 格式： key=value方格下一个key

#截取key=value
#获取下一个key的长度
  next_key=`echo $i_mem|cat -v|awk -F'[.^A]' '{print $NF}'` 
  let nextkey_length=${#next_key}+1
# +1是加上方格的长度


  i_value=` echo $i|cut -c1-$((${#i}-${#next_key}-1))`
  i_mem_value=` echo $i_mem|cut -c1-$((${#i_mem}-${#next_key}-1))`
#获取键

  echo "client:"$diff_key"="$i_value"  mem:"$diff_key"="$i_mem_value >>result.log
#输出到日志

#==============替换操作结束===================
else
#如果不是汉字i就是原来的i
  echo "client:"$i" mem:$i_mem" >> result.log
fi 
 done

else
   echo "success" >> result.log
fi
done < mem_gresult
done
