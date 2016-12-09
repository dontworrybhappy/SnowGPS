#!/bin/bash
#Tests the memory usage and time of dijkstra's
prog='../shortestpath/dijkstras'
gp='./gen_rand_points.sh'
printf '| %10s | %15s | %10s | %10s |\n' "Number of Pairs" "Avg. Distance" "Time" "Mem"
echo '|------------|------------------|------------|------|'
p_list='10 50 500'
for p in $p_list ; do
    d=0
    i=0
    m=0
    t=0
    while [ $i -lt $p ] ; do
        i=$((i+1))
        pts=`$gp`
        a=`echo $gp | ./measure $prog 2>&1 | egrep 'eco|byte'`
        m="$m `echo $a | grep -o '[.0-9]* M' | grep -o '[.0-9]*'`"
        t="$t `echo $a | grep -o '[.0-9]* s' | grep -o '[.0-9]*'`"
        d="$d `echo $pts | awk '{print sqrt(($1-$3)^2 +($2-$4)^2)}'`"
    done
    d=`echo $d |  awk '{s=0; for (i=1; i<=NF; i++) s=s+$i; print s/NF}'`
    m=`echo $m |  awk '{s=0; for (i=1; i<=NF; i++) s=s+$i; print s/NF}'`
    t=`echo $t |  awk '{s=0; for (i=1; i<=NF; i++) s=s+$i; print s/NF}'`
    printf '| %10d | %15f | %10f | %10f |\n' $p $d $t $m
done
