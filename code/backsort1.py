#!/usr/bin/env python
#coding: utf-8
 
import sys
 
def backsort(lines):
    pairs = []
    for line in lines:
        pairs.append(('.'.join(
            reversed(line.split('.'))), line))
    return map(lambda item: item[1],
               sorted(pairs))
 
def main():
    result = backsort(map(
               lambda line: line.rstrip('\n'),
               sys.stdin))
    for line in result:
        print(line)
 
if __name__ == '__main__':
    main()
