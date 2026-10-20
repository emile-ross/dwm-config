#!/usr/bin/sh


if ! command -v yay >/dev/null 2>&1
then
    echo "yay could not be found"
    exit 1
else
	echo "yay was found"
fi
