CHECK=check.c local.c
CHECK_OUT=check
HOT=hotkeys.c local.c
HOT_OUT=hotkeys

debug:ch hot

ch:
	cc -g ${CHECK} -o ${CHECK_OUT}
hot:
	cc -g ${HOT} -o ${HOT_OUT}
clean:
	rm ${CHECK_OUT} ${HOT_OUT}
