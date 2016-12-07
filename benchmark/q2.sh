#!/bin/sh
j=0;
i=0;
b=unsorted;
if [ -f time.txt ] 
then 
	rm time.txt
fi
#for k in "unsorted" "sorted" "bst" "rbtree" "treap" "chained-0.5" "chained-0.75" "chained-1.0" "chained-5.0" "chained-10.0" "chained-100.0" "open-0.5" "open-0.6" "open-0.7" "open-0.8" "open-0.9" "open-1.0"
#do
    #for j in 1 2 4 8
    #do
        for i in "../test/input0" #"../text/input1" "../test/input2" "../test/input3"
        do
            echo $i:
            ./timeout.py -t 6000 ./djikstras.cpp <  $i >> time.txt
            if [ ! $? ]
             then
                echo INFINITY
                break 2
            fi 
        done
    #done
#done
    
