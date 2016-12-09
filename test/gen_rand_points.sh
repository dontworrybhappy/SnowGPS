#!/bin/bash
#Picks 2 random nodes from the map file
map='../mapmaker/map.txt'
lines=`awk '/EDGES/{ print NR; exit }' $map`
head -n $((lines-1)) $map | tail -n $((lines-2)) | sort -R | head -n 2 | cut -d\  -f 2-3
