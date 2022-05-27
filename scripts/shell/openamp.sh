#!/bin/sh

STATE=0
remoteproc_state_check() {
    STATE=$(cat /sys/class/remoteproc/remoteproc0/state)
    echo $STATE
    if [ "$STATE" = "running" ];then
	return 1
    fi
    return 0
}

start_char_f() {
    mkdir -p /lib/firmware
    cp OpenAMP_raw.elf /lib/firmware/tih_ccore

    echo tih_ccore > /sys/class/remoteproc/remoteproc0/firmware
    echo start > /sys/class/remoteproc/remoteproc0/state
    
    ./rpmsg_client_char_one_ep_test   1000 # 1000 times
    
    echo stop > /sys/class/remoteproc/remoteproc0/state
}

start_mul_char_f() {
    mkdir -p /lib/firmware
    cp OpenAMP_raw.elf /lib/firmware/tih_ccore
    echo -n tih_ccore > /sys/class/remoteproc/remoteproc0/firmware
    echo start > /sys/class/remoteproc/remoteproc0/state
    
    ./rpmsg_client_char_multi_eps_test 2 100 # 2--channels(max 2) 1000--times
    echo stop > /sys/class/remoteproc/remoteproc0/state
}

start_new_mul_char_f() {
    mkdir -p /lib/firmware
    cp OpenAMP_raw_CCore.elf /lib/firmware/tih_ccore
    echo -n tih_ccore > /sys/class/remoteproc/remoteproc0/firmware
    echo start > /sys/class/remoteproc/remoteproc0/state
    
    ./rpmsg_client_char_multi_eps_test 2 100 # 2--channels(max 2) 1000--times
    echo stop > /sys/class/remoteproc/remoteproc0/state
}

start_aio_char_f() {
    mkdir -p /lib/firmware
    cp OpenAMP_raw.elf /lib/firmware/tih_ccore
    echo -n tih_ccore > /sys/class/remoteproc/remoteproc0/firmware
    echo start > /sys/class/remoteproc/remoteproc0/state
    
    ./rpmsg_client_char_aio_test 100 # 1000 times
    echo stop > /sys/class/remoteproc/remoteproc0/state
}

start_tty_f() {
    mkdir -p /lib/firmware
    cp OpenAMP_tty_echo.elf /lib/firmware/tih_ccore
    echo -n tih_ccore > /sys/class/remoteproc/remoteproc0/firmware
    echo start > /sys/class/remoteproc/remoteproc0/state
   
    ./rpmsg_client_tty_one_channel_test 100 # 1000-times
    echo stop > /sys/class/remoteproc/remoteproc0/state
}

start_mul_tty_f() {
    mkdir -p /lib/firmware

    cp OpenAMP_tty_echo.elf /lib/firmware/tih_ccore
    echo -n tih_ccore > /sys/class/remoteproc/remoteproc0/firmware
    echo start > /sys/class/remoteproc/remoteproc0/state
    ./rpmsg_client_tty_multi_channels_test 0 10
    ./rpmsg_client_tty_multi_channels_test 1 10

    ./rpmsg_client_tty_multi_channels_test 0 10 &
    ./rpmsg_client_tty_multi_channels_test 1 10 &
    ./rpmsg_client_tty_multi_channels_test 2 10 &
    ./rpmsg_client_tty_multi_channels_test 3 10 &
    ./rpmsg_client_tty_multi_channels_test 4 10 &
    ./rpmsg_client_tty_multi_channels_test 5 10 &
    ./rpmsg_client_tty_multi_channels_test 6 10 &
    ./rpmsg_client_tty_multi_channels_test 7 10 &
    wait
    sleep 3
    
    echo stop > /sys/class/remoteproc/remoteproc0/state
}

start_new_mul_tty_f() {
    mkdir -p /lib/firmware

    cp OpenAMP_tty_echo_CCore.elf /lib/firmware/tih_ccore
    echo -n tih_ccore > /sys/class/remoteproc/remoteproc0/firmware
    echo start > /sys/class/remoteproc/remoteproc0/state
    # ./rpmsg_client_tty_multi_channels_test 0 10
    # ./rpmsg_client_tty_multi_channels_test 1 10
    
    ./rpmsg_client_tty_multi_channels_test 0 10 &
    ./rpmsg_client_tty_multi_channels_test 1 10 &
    ./rpmsg_client_tty_multi_channels_test 2 10 &
    ./rpmsg_client_tty_multi_channels_test 3 10 &
    ./rpmsg_client_tty_multi_channels_test 4 10 &
    ./rpmsg_client_tty_multi_channels_test 5 10 &
    ./rpmsg_client_tty_multi_channels_test 6 10 &
    ./rpmsg_client_tty_multi_channels_test 7 10 &
    wait
    sleep 5
    
    echo stop > /sys/class/remoteproc/remoteproc0/state
}

start_char_tty_f() {
    mkdir -p /lib/firmware
    cp OpenAMP_Char_TTy.elf /lib/firmware/tih_ccore
    echo -n tih_ccore > /sys/class/remoteproc/remoteproc0/firmware
    echo start > /sys/class/remoteproc/remoteproc0/state
    
    # ./rpmsg_client_char_tty_test 2 10
    ./rpmsg_client_test
    sleep 5
    echo stop > /sys/class/remoteproc/remoteproc0/state
}

start_drv_rpmsg_client_f() {
    mkdir -p /lib/firmware
    cp  OpenAMP_drv_raw.elf /lib/firmware/tih_ccore
    echo -n tih_ccore > /sys/class/remoteproc/remoteproc0/firmware
    echo start > /sys/class/remoteproc/remoteproc0/state

    insmod drv_rpmsg_client.ko

    sleep 10
    echo stop > /sys/class/remoteproc/remoteproc0/state
    rmmod drv_rpmsg_client.ko
}

trace_f() {
      echo -n 'file virtio_rpmsg_bus.c +p' > /sys/kernel/debug/dynamic_debug/control
      echo -n 'file tih_remoteproc.c +p' > /sys/kernel/debug/dynamic_debug/control
      echo -n 'file remoteproc*.c +p' > /sys/kernel/debug/dynamic_debug/control  
}

stop_f() {
     echo stop > /sys/class/remoteproc/remoteproc0/state
}

start_f() {
    mkdir -p /lib/firmware
    cp OpenAMP_tty_echo.elf /lib/firmware/tih_ccore

    echo  tih_ccore > /sys/class/remoteproc/remoteproc0/firmware
    echo start > /sys/class/remoteproc/remoteproc0/state
}

ssh_f() {
    ifconfig eth0 192.168.100.249
    sleep 3
    dropbear -E
    sleep 1    
}

time_start_f(){
    startTime=`date +%Y%m%d-%H:%M:%S`
    startTime_s=`date +%s`
}

time_stop_f(){
    endTime=`date +%Y%m%d-%H:%M:%S`
    endTime_s=`date +%s`
    sumTime=$[ $endTime_s - $startTime_s ]
    echo "$startTime ---> $endTime" "Totl:$sumTime seconds" 
}

rpmsg_verify_parse_cmd_line() {
    case "$1" in
	start_char)
	    start_char_f 
	    ;;
	start_aio_char)
	    start_aio_char_f
	    ;;
	start_tty)
	    start_tty_f
	    ;;
	start_mul_tty)
	    start_mul_tty_f
	    ;;
	start_mul_char)
	    start_mul_char_f
	    ;;
	start_char_tty)
	    start_char_tty_f    
	    ;;
	trace)
	    trace_f
	    ;;
	stop)
	    stop_f
	    ;;
	start)
	    start_f
	    ;;
	start_all)
           time_start_f 
           start_mul_char_f
           start_mul_tty_f
	   start_new_mul_char_f
           start_new_mul_tty_f
           start_tty_f
           start_aio_char_f
           start_char_f
	   time_stop_f
	    ;;
	ssh)
	    ssh_f
	    ;;
	start_new_mul_char)
	    start_new_mul_char_f
	    ;;
	start_new_mul_tty)
	    start_new_mul_tty_f
	    ;;
	start_drv_rpmsg_client)
	    start_drv_rpmsg_client_f
	    ;;
	# --help)
	#     help_f
	    # ;;
    esac
}

     ################# main ################

     RET=0     # this is a global as we can have a function main(), see #705. Should we toss then all local $ret?
     
     remoteproc_state_check
     RET=$? 
     if [ $RET -eq 0 ] || [ "$1" = "stop" ] || [ "$1" = "start" ]; then
	 echo "offline or stop will come here!"
	 rpmsg_verify_parse_cmd_line "$1"
     fi
     












