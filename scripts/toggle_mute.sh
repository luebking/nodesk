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


# If your alsa Master does not toggle, you can use this script instead.
# Also uses the OSD script to display the state

# Requires
# 1. A retarded soundchip where Master cannot be toggled ...
# 2. amixer
# 3. the OSD script

FILE="/tmp/.$USER.alsa.volume"
VOLUME="`amixer sget Master |  grep -oE "[[:digit:]]*%"`"
if [ $VOLUME = "0%" ] && [ -e "$FILE" ]; then
    VOLUME="`cat "$FILE"`"
    OSD % `amixer sset Master "$VOLUME" | sed -e '/[[:digit:]]*%/!d; s/.*\[\([[:digit:]]*\)%\].*/\1/g'` 1
    rm "$FILE"
else
    echo "$VOLUME" > "$FILE"
    amixer -q sset Master 0
    OSD "" "Muted" 1
fi
