#!/usr/bin/python2
import sys, pygame, math
pygame.init()
size = width, height = 1100, 850
screen = pygame.display.set_mode(size)
map_img = pygame.image.load("map.png")
map_img = pygame.transform.scale(map_img, size).convert_alpha()
map_rct = map_img.get_rect()
menu_font = pygame.font.SysFont("monospace", 29)
vertices = []
edges = []
closest = None
second_closest = None
words = "path"
alphabet = [chr(x) for x in range(ord('a'), ord('a')+27)]
keep_going = True
save_file = 'map.txt'

def vert_dist(p, x, y):
    return math.sqrt(((p[1]-x) ** 2) + ((p[2]-y) ** 2))

def load_map(fname):
    vertices = []
    edges = []
    lv = True
    for line in open(fname):
        if 'VERTICES' in line: pass
        elif 'EDGES' in line: lv = False
        elif lv:
            prefix = line.split(':')
            name = prefix[0]
            coords = prefix[1].split(', ')
            x = int(coords[0])
            y = int(coords[1])
            vertices.append((name, x, y))
        else:
            prefix = line.split(':')
            name = prefix[0]
            coords = prefix[1].split(', ')
            x1 = int(coords[0])
            y1 = int(coords[1])
            x2 = int(coords[2])
            y2 = int(coords[3])
            edges.append((name, x1, y1, x2, y2))
    return vertices, edges

def save_map(fname, vertices, edges):
    f=open(fname, 'w+')
    f.write('VERTICES\n')
    for p in vertices:
        f.write('{}:\t{}, {}\n'.format(p[0], p[1], p[2]))
    f.write('EDGES\n')
    for e in edges:
        f.write('{}:\t{}, {}, {}, {}\n'.format(e[0], e[1], e[2], e[3], e[4]))
    f.close()


try:
    vertices, edges = load_map(save_file)
except:
    pass
while keep_going:
    for event in pygame.event.get():
        if event.type == pygame.QUIT: keep_going = False
        elif event.type == pygame.MOUSEBUTTONDOWN:
            mx, my = event.pos
            if event.button == 1:
                vertices.append((words, mx, my))
            elif event.button == 3:
                if closest and second_closest:
                    if closest != second_closest:
                        edges.append((words, 
                            closest[1], closest[2],
                            second_closest[1], second_closest[2]))
                    second_closest = None
                elif closest:
                    second_closest = closest
        elif event.type == pygame.KEYUP:
            k = pygame.key.name(event.key)
            if k in alphabet:
                words += k
            elif k == 'backspace' and len(words) > 0:
                words = words[:-1]
        elif event.type == pygame.MOUSEMOTION:
            mx, my = event.pos
    screen.fill((0, 0, 0))
    screen.blit(map_img, map_rct)
    label = menu_font.render(words, 1, (0,0,0))
    screen.blit(label, (12, 12))

    if vertices:
        closest = reduce(lambda x, y: {True: x, False: y}
                [vert_dist(x, mx, my) < vert_dist(y, mx, my)]
                ,vertices)
    
    for e in edges:
        color = (0, 0, 0)
        pygame.draw.line(screen, color, e[1:3], e[3:5])
    for p in vertices:
        color = (255, 0, 0)
        if p == closest: color = (0, 255, 0)
        if p == second_closest: color = (0, 0, 255)
        pygame.draw.circle(screen, color, p[1:], 3)
    pygame.display.flip()
save_map(save_file, vertices, edges)
