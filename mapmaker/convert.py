#!/usr/bin/env python2.7
import maping
import math
i, vert, edge = maping.load_map('./map.txt')
f = open('./buildings.txt')
f = f.read()
new_edge = []
new_vert = []
new_v_id = 0
for e in edge:
    ne = list(e)
    ne.append(-1) #first node
    ne.append(-1) #second node
    ne.append(math.sqrt((ne[1] - ne[3])**2 + (ne[2] - ne[4])**2)) #distance
    new_edge.append(ne)
print len(vert)
for v in vert:
    for e in new_edge:
        if e[1] == v[1] and e[2] == v[2]:
            e[5] = v[3]
        if e[3] == v[1] and e[4] == v[2]:
            e[6] = v[3]
    new_vert.append(list(v))
    print('{} {} {} {}'.format(*v))
print('')
print len(new_edge)
for e in new_edge:
    if(e[0] in f):
        e[-1] = 0
    print('{} {} {} {} {} {} {} {}'.format(*e))
