#!/usr/bin/env python
#coding: utf-8

import sys

def main():
    for line in sys.stdin:
        print(line.rstrip('\n'))

if __name__ == '__main__':
    main()
