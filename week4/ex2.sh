#!/bin/bash
./ex2 &
for i in $(seq 25)
do
	pstree
	sleep 2
done


