#!/usr/bin/bash

sudo stty -F /dev/ttyACM0 speed 9600
sudo cat /dev/ttyACM0
