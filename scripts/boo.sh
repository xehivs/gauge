#!/bin/bash
make
rm -f cache/*.bmp
kitty icat docs/foo.bmp
python drivers/generator.py >tracks/blurb.txt
python drivers/datastream.py > tracks/stream.txt
./arche 256 <tracks/blurb.txt
./scripts/movie.sh
