#!/bin/bash
#��һ��������cms�ļ�
#�ڶ���������mem�ļ�
#�������������result.log
if [ -e ./result.log ]
then
	`rm -rf ./result.log`
fi
cms=$1

mem=$2

#ȥ�����õ�����
cat  $cms|awk -F' ' '{if($0 ~/message/)print$0}' >cms_reg

cat cms_reg |grep "11991=[0-9]\+" -o |sort |uniq >tmp_mem_grepkey11991
cat $mem |grep "11991=[0-9]\+" -o |sort |uniq >tmp_cms_grepkey11991

grep -wf tmp_mem_grepkey11991 tmp_cms_grepkey11991|sort > same_grepkey11991

cat cms_reg |grep "12058=[0-9]\+" -o |sort |uniq >tmp_mem_grepkey12058
cat $mem |grep "12058=[0-9]\+" -o |sort |uniq >tmp_cms_grepkey12058

grep -wf tmp_mem_grepkey12058 tmp_cms_grepkey12058|sort > same_grepkey12058

#������е�11991=
#11991=�Ŀ�����

#��ϴ��������
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



#ÿһ�е�client����
while read client_line
do
	echo $client_line|awk -F"[.^]A" '{for(i=8;i<(NF-1);i++)printf("%d:%s\n",i,$i)}'|sort>>tmp1
done < client_gresult


#ÿһ�е�mem����

while read mem_line
do
	rm  tmp2 tmp3 -rf >>/dev/null
	#ɾ��֮ǰ���ɵ�tmp2 tmp3
	echo $mem_line|awk -F"[.^]A" '{for(i=8;i<(NF-1);i++)printf("%d:%s\n",i,$i)}'|sort>tmp2

#�ó�tmp1-->cmsfile ��mem�ļ��������
#sort tmp1 tmp2 tmp2 | uniq -u >tmp3
awk '{if(ARGIND==1) {val[$0]}else{if($0 in val)  delete val[$0]}}END{for(i in val) print i}' tmp2 tmp1 >tmp3


tmp=`cat tmp3`
#tmp3��С��Ϊ0
#tmp3 ��ʽ �� ����:...=,,,
#tmp3 �������tmp2��tmp1û����

#tmp3�Ƿ��ж�����
if [ -n "$tmp"  ]
then
	echo "failed">>result.log
   for i in  `cat -v tmp3`
   do
	tmp_i=$i
	#����ԭ�е�i��tmp_i
	#tmp_i�ĸ�ʽ
	i=`echo $i`
	i_mem=`echo $i|awk -F':' '{print $2}'`
	#ȡ���������� ----��i_mem

	ikey=`echo $i|awk -F'=' '{print $1}' `
	#ȡ���� ---��i
	
	#tmp1ȡtmp1��ikey�ȡ�����������
	i=`grep   $ikey tmp1|awk -F':' '{print $2}'`
	i=`echo $i|awk -F' ' '{print $1}'`	

#���ú��ֵ�ANSI�б���M-��ԭ���ж��Ƿ�ֵΪ���֣��Ǿͽ��к��ֵ��滻����
  result=`echo $i|grep "M-"`
#=============================��ʼ�滻����=============================
  if [ -n "$result" ]
  then 
#��ȡֵ

  #��ֵͬ�����ڵ��� ANSI����ʽ
  mem_line=`cat -vn mem_gresult_source|grep $i_mem|head -n 1|awk -F' ' '{print $1}' `
  client_line=`cat -vn client_gresult_source|grep $i|head -n 1|awk -F' ' '{print $1}'`
 
  #����Ϊkey=value 
  #��ͬ��key
  diff_key=`echo $i_mem|awk -F'=' '{print $1}'

  #ֵ��λ��,��tmp3�в�ѯ��������ż�һ
  site=`cat tmp3|grep $tmp_i|awk -F':' '{print $1}'`
  let site=site+1

  i=`cat client_gresult_source|head -n $client_line|tail -1|awk -F'=' '{print $'""$site""'}'`
  i_mem=`cat mem_gresult_source|head -n $mem_line  |tail -1|awk -F'=' '{print $'""$site""'}'`
#ȡ����site��λ�õ�ֵ ��ʽ�� key=value������һ��key

#��ȡkey=value
#��ȡ��һ��key�ĳ���
  next_key=`echo $i_mem|cat -v|awk -F'[.^A]' '{print $NF}'` 
  let nextkey_length=${#next_key}+1
# +1�Ǽ��Ϸ���ĳ���


  i_value=` echo $i|cut -c1-$((${#i}-${#next_key}-1))`
  i_mem_value=` echo $i_mem|cut -c1-$((${#i_mem}-${#next_key}-1))`
#��ȡ��

  echo "client:"$diff_key"="$i_value"  mem:"$diff_key"="$i_mem_value >>result.log
#�������־

#==============�滻��������===================
else
#������Ǻ���i����ԭ����i
  echo "client:"$i" mem:$i_mem" >> result.log
fi 
 done

else
   echo "success" >> result.log
fi
done < mem_gresult
done
