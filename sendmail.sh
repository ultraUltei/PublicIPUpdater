#!/bin/sh
echo "From: host@mail.com" > msg.txt
echo "Subject: Public IP Update" >> msg.txt
echo "" >> msg.txt
echo "Your Public IP has been changed to: "$1 >> msg.txt
msmtp yourmail@mail.com < msg.txt  #change this line if needed
