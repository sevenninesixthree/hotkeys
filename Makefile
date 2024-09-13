CFLAGS=-g
debug:CFLAGS=-g
build:CFLAGS=

WAY:=$(realpath hotkeys)
SERV_PATH=/usr/lib/systemd/system/
TEMPLATE=hotkeys.temp
SERVICE=hotkeys.service

APPS:=$(wildcard app/*.c)
APPS:=$(APPS:%.c=%.o)

all:
	@echo ${APPS}

install:build service
	cp ${SERVICE} ${SERV_PATH}

check:check.o local.o
	${CC} check.o local.o -o check

hotkeys:hotkeys.o local.o ${APPS}
	${CC} hotkeys.o local.o ${APPS} -o hotkeys

build:check hotkeys

debug:check hotkeys

clean:
	rm -f *.o ${APPS}

service:
	touch ${SERVICE}
	cat ${TEMPLATE} | sed -e 's\!!PATH\${WAY}\g' > ${SERVICE}

restart:build
	systemctl stop ${SERVICE}
	systemctl start ${SERVICE}
