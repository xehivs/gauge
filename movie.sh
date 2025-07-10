#!/bin/bash
rm -f out.mp4
ffmpeg -framerate 30 -pattern_type glob -i 'cache/*.bmp' \
  -c:v libx264 -pix_fmt yuv420p out.mp4
cvlc out.mp4 --loop