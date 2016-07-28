#!/bin/sh
#            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
#                    Version 2, December 2004
#
# Copyright (C) 2016 Thomas Lübking, https://github.com/luebking/nodesk
#
# Everyone is permitted to copy and distribute verbatim or modified
# copies of this script, and changing it is allowed as long
# as the name is changed.
#
#            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
#   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
#
#  0. You just DO WHAT THE FUCK YOU WANT TO.
#

LOCATION="EUR|DE|GM009|BERLIN" 	# no, I don't live there ;-P
METRIC=1 						# 1 is celsius, 0 is fahrenheit

# fetch rss from accuweather and extract the current temperatur for a give
# location, requires
#
# 1. wget
# 2. xmlstarlet
# 3. sed

wget -qO - 'http://rss.accuweather.com/rss/liveweather_rss.asp?metric='$METRIC'&locCode='"$LOCATION" | \
xmlstarlet sel -T -t -m "/rss/channel/item" -v 'description' -n | \
sed -e 's/.*: \([0-9]*\s*°.\).*/\1/g; 1q'
