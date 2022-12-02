#!/bin/bash
pipe=/tmp/testpipe

trap "rm -f $pipe" EXIT

if [[ ! -p $pipe ]]; then
    mkfifo $pipe
fi

date=$(date +%s)
date+='.jpg'


libcamera-jpeg -o $date

echo $date > $pipe