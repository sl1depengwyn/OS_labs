#/bin/bash

file="number.txt"
lock="${file}.lock"


while true
do
	while [ -f $lock ]
	do
		:
	done
# here we creating file lock and by doing this tell all other processes that now file is busy
	echo "lock" > $lock

	if [ ! -f $file ]
	then
		echo 0 > $file
	fi


	n=$(tail -n 1 $file)
	n=$(expr $n + 1)
	echo $n >> $file

	rm $lock
done



