#!/bin/bash
make
rm -f cache/*.bmp
python generator.py >data/blurb.txt
python datastream.py >data/stream.txt
./arche 256 <data/blurb.txt
./movie.sh
