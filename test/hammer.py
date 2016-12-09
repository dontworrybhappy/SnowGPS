#!/bin/bash
p_list='1 10 100 1000'
r_list='1 10 100 1000'
d_list='1 100 400'
x=500
printf '| %10s | %15s | %10s | %10s |\n' "Processes" "Hits/Process" "Distance" "Time"
echo '|------------|-----------------|------------|------------|'
for proc in $p_list ; do
    for hipp in $r_list ; do
        for d in $d_list ; do
            x1=$((x - d))
            x2=$((x + d))
            t=`./thor.py -v "www.johnbot.me/snow?loc=$x1,$x1,$x2,$x2" 2>&1 | \
                       grep -o 'Average.*' | grep -o '[0-9.]*'             | \
                       awk '{s+=$1}END{print s/NR}'`
            printf '| %10d | %15d | %10d | %10f |\n' $proc $hipp $d $t
        done
    done
done
