CXX= g++

INCLUDE= -I./include
LIB= 

OBJDIR= example/obj
SRCDIR= example/src
BINDIR= example/bin

OBJS= $(addprefix $(OBJDIR)/, example.o)
EXEC= $(addprefix $(BINDIR)/, example)

mkdirs := $(shell mkdir -p $(OBJDIR) $(BINDIR))


# BUILD EVERYTHING
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) -o $@ $^ $(LIB)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c -o $@ $< $(INCLUDE)


# REMOVE OLD FILES
clean:
	rm -f $(OBJS) $(EXEC)
