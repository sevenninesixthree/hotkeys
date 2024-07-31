CFLAGS=-g
debug:CFLAGS=-g
build:CFLAGS=

WAY:=$(realpath hotkeys)
SERV_PATH=/usr/lib/systemd/system/
TEMPLATE=hotkeys.temp
SERVICE=hotkeys.service

APPS=$(wildcard app/*.c)

all:
	@echo Please Use install

install:build service
	cp ${SERVICE} ${SERV_PATH}

ch:check.o local.o
	${CC} check.o local.o -o check

hot:hotkeys.o local.o config
	${CC} hotkeys.o local.o config.o -o hotkeys

config:
	${CC} ${CFLAGS} -c ${APPS} -o config.o

build:ch hot clean

debug:ch hot clean

clean:
	rm -f *.o

service:
	touch ${SERVICE}
	cat ${TEMPLATE} | sed -e 's\!!PATH\${WAY}\g' > ${SERVICE}

restart:build
	systemctl stop ${SERVICE}
	systemctl start ${SERVICE}
