### 2022-10-01 K.OHWADA

JAVAC= javac
JAVA_FLAGS=-d class

TARGET1=server
SRCS1= EchoServerSingle.java EchoServerWorker.java EchoUtil.java
TARGET2=client
SRCS2=EchoClientOne.java EchoUtil.java


$(TARGET1): $(SRCS1)
	$(JAVAC)  $(SRCS1) $(JAVA_FLAGS)


$(TARGET2): $(SRCS2)
	$(JAVAC)  $(SRCS2) $(JAVA_FLAGS)


clean:
	rm -rf class/*
