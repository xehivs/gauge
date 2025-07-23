#!/bin/bash
rm -rf gear.mp4
ffmpeg -framerate 14 -pattern_type glob -i 'gear/*.png' \
  -c:v mpeg4 -qscale:v 1 -pix_fmt yuv420p gear.mp4
cvlc gear.mp4 --loop