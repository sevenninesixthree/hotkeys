CHECK=check.c local.c
CHECK_OUT=check
HOT=hotkeys.c local.c
HOT_OUT=hotkeys
WAY=$(realpath hotkeys)
SERV_PATH=/usr/lib/systemd/system/
TEMPLATE=hotkeys.temp
SERVICE=hotkeys.service

debug:dech dehot
install:ch hot service
	cp hotkeys.service ${SERV_PATH}
dech:
	cc -g ${CHECK} -o ${CHECK_OUT}
ch:
	cc ${CHECK} -o ${CHECK_OUT}
dehot:
	cc -g ${HOT} -o ${HOT_OUT}
hot:
	cc ${HOT} -o ${HOT_OUT}
clean:
	rm ${CHECK_OUT} ${HOT_OUT} ${SERVICE}
service:
	touch ${SERVICE}
	cat ${TEMPLATE} | sed -e 's\!!PATH\${WAY}\g' > ${SERVICE}
