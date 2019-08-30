PROJECT_NAME=	Buhlmann

all: $(PROJECT_NAME)


MYCODE_SOURCE=	$(shell find src -type f -name "*.c")
MYCODE_OBJS=	$(MYCODE_SOURCE:.c=.o)
MYLIB_OBJS=	$(filter-out src/main.o, $(MYCODE_OBJS))

MYTEST_SOURCE=	$(shell find tests -type f -name "*.c")
MYTEST_OBJS=	$(MYTEST_SOURCE:.c=.o)

NOVAPROVA_CFLAGS= $(shell pkg-config --cflags novaprova) -no-pie -gdwarf-2
NOVAPROVA_LIBS= $(shell pkg-config --libs novaprova)

CFLAGS= -g $(NOVAPROVA_CFLAGS) -I./include/

testlib.a: $(MYLIB_OBJS)
	ar ruv $@ $(MYLIB_OBJS)
	ranlib $@

$(PROJECT_NAME): $(MYCODE_OBJS)
	$(CC) $(CFLAGS) -o $(PROJECT_NAME) $(MYCODE_OBJS) $(CLIBS)

clean:
	$(RM) test $(MYCODE_OBJS) testlib.a $(MYTEST_OBJS)

testrunner: $(MYTEST_OBJS) testlib.a
	$(LINK.c) -o $@ $(MYTEST_OBJS) testlib.a $(NOVAPROVA_LIBS)

check: testrunner
	./testrunner
