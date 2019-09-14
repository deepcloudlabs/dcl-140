# Makefile for SMS project

TGT = sms_server

all:	$(TGT)

SRC = 			\
	sms_server.c	\
	disconnect.c	\
	garbo.c		\
	get_stale.c	\
	list_conn.c	\
	list_stats.c	\
	listen_port.c	\
	menu.c		\
	serve_client.c	\
	zap_servlet.c	\
	zap_stale.c	\
	zero_stats.c

OBJ = $(SRC:.c=.o)

LIBS = -lnsl -lpthread

$(OBJ) : sms.h

$(TGT) : $(OBJ)
	cc -o $(TGT) $(OBJ) $(LIBS)

clean :
	@rm -f $(OBJ)
