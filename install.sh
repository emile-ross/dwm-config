#!/usr/bin/sh

print_step(){
	echo "Step $1 / 4"
}

# check for root privileges
if [ "$EUID" -ne 0 ]
then 
	echo "Elevated privileges are needed for installing any package"
	exit 1
fi

# install dependencies
print_step 1
pacman -S base-devel xorg-server libx11 libxft git

print_step 2
echo -n "INFO: "
if ! command -v yay >/dev/null 2>&1 
then
	echo "yay could not be found"
	# install yay here
else
	echo "yay was found"
fi

print_step 3
# building st & dwm
cd dwm/
make install
cd ../st/
make install

echo "exec dwm" > ~/.xinitrc
