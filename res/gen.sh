#!/bin/sh

set -e

bin2c *.png -C res.cpp -H res.h --wxbitmap
