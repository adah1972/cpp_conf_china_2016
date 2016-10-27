#!/usr/bin/env python
#coding: utf-8

def gen_pythagorean_triple():
    z = 1
    while True:
        z += 1
        yield [(x, y, z) for x in range(1, z)
                         for y in range(x, z)
                         if x**2 + y**2 == z**2]

def main():
    generator = gen_pythagorean_triple()
    triples = []
    while len(triples) < 10:
        triples += next(generator);
    print(triples)

if __name__ == '__main__':
    main()
