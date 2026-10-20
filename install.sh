#!/usr/bin/sh

print_step(){
	echo "Step $1 / 4"
build(){
	cd $2
	make install
	if [ $? -eq 0 ]
	then
		echo "${bold}${undr}Compiled $1 successfully${ends}"
	else
		echo "${bold}${undr}Errors during $1 compilation. Check the compilation log.${ends}"
		cd ..
		exit
	fi
	cd ..
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
build dwm dwm/
build st st/

echo "exec dwm" > ~/.xinitrc
