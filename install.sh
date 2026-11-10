#!/usr/bin/env bash

bold=$(tput bold)
undr=$(tput smul)
ends=$(tput sgr0)

# TODO: make a printing function with the standard format used
# ( simplifies the program with less variables {bold} & {ends} )

print_step(){
	echo "${bold}${undr}Step $1 / 3${ends}"
}

# compiles a program using the makefile
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
	echo "${bold}${undr}Elevated privileges are needed for installing any package${ends}"
	exit 1
fi

# install dependencies
print_step 1
pacman -S base-devel xorg-server libx11 libxft git xorg-xinit xdg-desktop-portal-gtk obs-studio pipewire wireplumber xdg-desktop-portal xdg-desktop-portal-wlr slurp

print_step 2
echo -n "INFO: "
if ! command -v yay >/dev/null 2>&1 
then
	echo -e "${bold}${undr}yay could not be found\nInstalling yay...${ends}"
	# install yay here
	git clone https://aur.archlinux.org/yay.git
	cd yay/
	makepkg -si
	cd ..
else
	echo "${bold}${undr}yay was found${ends}"
fi

print_step 3
# building st & dwm
build dwm dwm/
build st st/

# building dwl
mkdir -p /etc/ly/custom-sessions
build dwl dwl/
# add custom dwl launcher to ly boot menu
cp dwl/dwl.desktop /etc/ly/custom-sessions/dwl-custom.desktop

# get the username and convert it to a home directory
USER_HOME=$(getent passwd "$SUDO_USER" | cut -d: -f6)
cp dwl/other_configs/startup-dwl.sh "$USER_HOME/.local/bin/dwl-startup"
mkdir -p "$USER_HOME/.config/xdg-desktop-portal"
cp dwl/other_configs/portals.conf "$USER_HOME/.config/xdg-desktop-portal/portals.conf"

# enable pipewire & wireplumber
su $SUDO_USER
systemctl --user enable --now pipewire.service
systemctl --user enable --now wireplumber.service

echo "Installation is complete"

