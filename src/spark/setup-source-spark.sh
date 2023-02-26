#!/bin/bash
root=$1
mkdir -p /tmp/apps
mkdir -p /tmp/data
cp $root/*.py /tmp/apps
cp $root/*.txt /tmp/data
cp $root/*.csv /tmp/data