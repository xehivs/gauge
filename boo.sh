#!/bin/bash
make
rm -f cache/*.bmp
./arche 32 < data/blurb.txt
kitty icat cache/0001.bmp
kitty icat cache/0002.bmp
kitty icat cache/0003.bmp
./movie.sh
kitty icat cache/0001.bmp
kitty icat cache/0002.bmp
kitty icat cache/0003.bmp