#!/usr/bin/env python2.7
import maping
import math
i, vert, edge = maping.load_map('./map.txt')
f = open('./buildings.txt')
f1=open('./adjlist.txt', 'w+')
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
#print len(vert)
for v in vert:
    flag = False
    for e in new_edge:
        if e[1] == v[1] and e[2] == v[2]:
            e[5] = v[3]
            flag = True
        if e[3] == v[1] and e[4] == v[2]:
            e[6] = v[3]
            flag = True
    if flag:
        new_vert.append(list(v))
#    print('{} {} {} {}'.format(*v))
#print('')
#print len(new_edge)
for e in new_edge:
    if('-'+e[0] in f):
        e[-1] = 0
#    print('{} {} {} {} {} {} {} {}'.format(*e))


#here be new code 

# newedge = list of edges vert is list vertices
# check for vertex in edge pump through into dictionary
for i in new_vert:
    f1.write('{} {} \n'.format(i[1], i[2]))
    for j in new_edge:
        if (i[1] == j[1] and i[2] == j[2]): 
            f1.write('{} {} {} \n'.format(j[7], j[3], j[4]))
        elif (i[1] == j[3] and i[2] == j[4]):  
            f1.write('{} {} {} \n'.format(j[7], j[1], j[2]))
    f1.write('-1 -1 -1\n')
            
