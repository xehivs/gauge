#!/bin/bash
make
rm -f cache/*.bmp
python generator.py > data/blurb.txt
python datastream.py > data/stream.txt
./arche 256 < data/stream.txt
kitty icat cache/0001.bmp
kitty icat cache/0002.bmp
kitty icat cache/0003.bmp
./movie.sh
# kitty icat cache/0001.bmp
# kitty icat cache/0002.bmp
# kitty icat cache/0003.bmp