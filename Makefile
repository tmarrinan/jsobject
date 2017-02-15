CXX= g++

INCLUDE= -I./include
LIB= 

OBJDIR= obj
SRCDIR= src

OBJS= $(addprefix $(OBJDIR)/, jsobject.o test.o)
EXEC= test


# BUILD EVERYTHING
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) -o $@ $^ $(LIB)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c -o $@ $< $(INCLUDE)

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)


# REMOVE OLD FILES
clean:
	rm -f $(OBJS) $(EXEC)
