#!/bin/sh
#\
exec /usr/bin/expect -- "$0" ${1+"$@"}
#
#
set roc $argv 
spawn /bin/tcsh
send \r\r
expect clon
puts $roc
send "ssh $roc\r"
send "\r"
send "coda_roc_gef -s clashps -o \"$roc TS\" \r"
send "\r"
interact