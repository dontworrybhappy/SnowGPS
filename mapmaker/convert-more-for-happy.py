#!/usr/bin/env python2.7
import sys, pygame, math

def load_map(fname):
    vertices = []
    edges = []
    lv = True
    i = 0
    for line in open(fname):
        if 'VERTICES' in line: pass
        elif 'EDGES' in line: lv = False
        elif lv:
            prefix = line.split()
            name = prefix[0]
            x = int(prefix[1])
            y = int(prefix[2])
            n = int(prefix[3])
            vertices.append((name, x, y, i))
            i += 1
        else:
            prefix = line.split()
            name = prefix[0]
            x1 = int(prefix[1])
            y1 = int(prefix[2])
            x2 = int(prefix[3])
            y2 = int(prefix[4])
            edges.append((name, x1, y1, x2, y2))
    return vertices, edges

def save_map(fname, vertices, edges):
    f=open(fname, 'w+')
    f.write('VERTICES\n')
    for p in vertices:
        f.write('{} {} {} {}\n'.format(*p))
    f.write('EDGES\n')
    for e in edges:
        f.write('{} {} {} {} {}\n'.format(*e))
    f.close()
save_map('./map.txt', *load_map('./map.txt'))
