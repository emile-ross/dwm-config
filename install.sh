#!/usr/bin/sh

num_steps = 4

if [ "$EUID" -ne 0 ]
then 
	echo "Elevated privileges are needed for installing any package"
	exit 1
fi

echo -n "INFO: "
if ! command -v yay >/dev/null 2>&1 
then
	echo "yay could not be found"
	# install yay here
else
	echo "yay was found"
fi
