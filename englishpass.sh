#!/bin/bash

function rand(){   
    min=$1   
    max=$(($2-$min+1))   
    num=$(($RANDOM+1000000000)) #增加一个10位的数再求余   
    echo $(($num%$max+$min))   
}   

while [ "1" == "1" ]
do

echo "输入想使用的功能"
echo "1:查单词"
echo "2:背单词"
echo "其他:退出"
read selection

case $selection in

1)
	while [ "1" == "1" ]
	do
	echo "输入想查询的单词:[输入0退出]"
	read  vocabulary
	if [[ $vocabulary == "0" ]]
	then
		break
	fi
	awk -F' ' '{if($1=="'$vocabulary'"){print $2}}' Word
		
	done

;;
2)
	while [ "1" == "1" ]
	do
		echo "请选择背单词的方法："
		echo "1:单词填空"
		echo "2:默写单词"
		echo "其他:返回"		
		read yourselect
		case $yourselect in 
		
		1)
			while [ "1" == "1" ]
			do
				rnd=$(rand 1 `cat Word|wc -l`)
				word=`sed  -n "$rnd,1p" Word|awk -F' ' '{print $1}'`
				chinese=`sed  -n "$rnd,1p" Word|awk -F' ' '{print $2}'`
				word_length=`echo ${#word}`
				rnd=$(rand 1 $[word_length-1])
				key=${word:$rnd:1}	
				clear
				echo ${word:0:$rnd}"_"${word:$[rnd+1]}
				echo "输入答案:[输入0退出]"
				read charater
				if [[ $charater == "0" ]]
				then
					break
				
				fi
				echo "===" 
				echo "===" 
				if [[ $charater == $key ]]
				then
					echo "Right!"
					echo $word"   "$chinese
				else
					echo "Wrong!"
					echo $word"   "$chinese
				fi
				echo "==="
				echo "==="
			done
		;;
		2)
			while [ "1" == "1" ]
			do	
				rnd=$(rand 1 `cat Word|wc -l`)
				word=`sed  -n "$rnd,1p" Word|awk -F' ' '{print $1}'`
				chinese=`sed  -n "$rnd,1p" Word|awk -F' ' '{print $2}'`
				echo $chinese
				echo "输出答案"
				read answer
				echo "=="
				echo "=="
				if [[ $answer == $word ]]
				then
					echo "Right"
					echo $word"   "$chinese
				else
					echo "Wrong!"
					echo $word"   "$chinese
				fi
				echo "=="
				echo "=="
			done
		;;
		*)
			echo "hello"
			break
		;;
		esac
	done
;;

*)
	echo Bye
	break
	;;
esac

done
