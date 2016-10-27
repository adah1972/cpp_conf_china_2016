#!/usr/bin/env python
#coding: utf-8

import sys

def cat(files):
    for fn in files:
        with open(fn) as f:
            for line in f:
                yield line.rstrip('\n')

def backsort(lines):
    result = {}
    for line in lines:
        result['.'.join(
            reversed(line.split('.')))] = line
    return map(lambda item: item[1],
               sorted(result.items()))

def main():
    if sys.argv[1:]:
        result = backsort(cat(sys.argv[1:]))
    else:
        result = backsort(map(
            lambda line: line.rstrip('\n'),
            sys.stdin))
    for line in result:
        print(line)

if __name__ == '__main__':
    main()
