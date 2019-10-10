PROJECT_NAME=	Buhlmann

all: $(PROJECT_NAME)

MYCODE_SOURCE=	$(shell find src -type f -name "*.c")
MYCODE_OBJS=	$(MYCODE_SOURCE:.c=.o)

CFLAGS= -g -I./include/
CLIBS= -lrt -lm

$(PROJECT_NAME): $(MYCODE_OBJS)
	$(CC) $(CFLAGS) -o $(PROJECT_NAME) $(MYCODE_OBJS) $(CLIBS)

clean:
	$(RM) $(MYCODE_OBJS) $(MYTEST_OBJS)
