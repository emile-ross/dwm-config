#!/usr/bin/sh


if [ "$EUID" -ne 0 ]
then 
	echo "Elevated privileges are needed for installing any package"
	exit 1
fi

# step 1
# install dependencies
pacman -S base-devel xorg-server libx11 libxft git

echo "exec dwm" > ~/.xinitrc

echo -n "INFO: "
if ! command -v yay >/dev/null 2>&1 
then
	echo "yay could not be found"
	# install yay here
else
	echo "yay was found"
fi

cd dwm/
make install
cd ../st/
make install


