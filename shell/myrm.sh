#!/bin/bash
input_count=$#
myhome=${HOME}
trash_dir=$myhome'/.trash'
trash_list=$myhome'/.trash_list'

for i in $*
do
	filename=`basename $i`
        	
	echo "rm_time:"`date +%Y-%m-%d_%H:%M:%S`"     -------""  name:"$filename"" >> $trash_list	
	mv $i $trash_dir 
done
