#!/bin/sh
echo "From: host@mail.com" > msg.txt
echo "Subject: Public IP Update" >> msg.txt
echo "" >> msg.txt
echo "Your Public IP has been changed to: "$1 >> msg.txt
# If you use a mail client other than msmtp, modify the line below
msmtp yourmail@mail.com < msg.txt
