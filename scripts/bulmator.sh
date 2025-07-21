#!/bin/bash
scp -r ./*.mp4 bulma.local:/share/Trunks/gauge/
cvlc -LZ /mnt/trunks/gauge
