BUILD = build
ifneq ($(notdir $(CURDIR)),$(BUILD))

.SUFFIXES:
OBJDIR := $(CURDIR)/build
DEPDIR := $(CURDIR)/.d
INCDIR := $(CURDIR)/inc
SRCDIR := $(CURDIR)/src

RM     := rm -rf
MKDIR  := mkdir -p

SRCSALL      := $(shell find $(CURDIR) -name "*.cc" -o -name "*.h")
SRCSCCABS    := $(filter %.cc, $(SRCSALL))
SRCSCC       := $(patsubst $(SRCDIR)/%,%,$(SRCSCCABS))

# create directories
$(foreach dirname,$(dir $(SRCSCC)),$(shell $(MKDIR) $(DEPDIR)/$(dirname)))
$(foreach dirname,$(dir $(SRCSCC)),$(shell $(MKDIR) $(OBJDIR)/$(dirname)))

.PHONY: $(all)
all:
	+@$(MAKE) --no-print-directory -C $(OBJDIR) -f $(CURDIR)/Makefile \
	 SRCDIR=$(SRCDIR) INCDIR=$(INCDIR) DEPDIR=$(DEPDIR) ROOTDIR=$(CURDIR) \
	 $(MAKECMDGOALS)

Makefile : ;

% :: all ;

.PHONY: clean
clean:
	$(RM) $(OBJDIR)
	$(RM) $(DEPDIR)

.PHONY: sure
sure: clean
	+@$(MAKE) --no-print-directory

else

TARGET       := SDL_GUI

SRCSALL      := $(shell find $(ROOTDIR) -name "*.cc" -o -name "*.h")
SRCSCCABS    := $(filter %.cc, $(SRCSALL))
SRCSCC       := $(patsubst $(SRCDIR)/%,%,$(SRCSCCABS))
SRCHABS      := $(filter %.h, $(SRCSALL))
SRCSH        := $(patsubst $(INCDIR)/%,%,$(SRCSHABS))
OBJS         := $(SRCSCC:.cc=.o)
DEPS         := $(addprefix $(patsubst $(ROOTDIR)/%,%,$(DEPDIR))/,$(SRCSCC:.cc=.d))

CXXFLAGS     := -std=c++17 -Wall -Wextra -Wpedantic -g -O0 `sdl2-config --cflags`
CXXFLAGS     += -I$(INCDIR)

CXXFLAGSTAGS := -I/home/manuel/.vim/tags

LIBS         := -lSDL2 -lSDL2_gfx -lSDL2_ttf

vpath %.h $(dir $(SRCSHABS))
vpath %.cc $(dir $(SRCSCCABS))
vpath %.d $(dir $(addprefix $(DEPDIR)/, $(DEPS)))

.PHONY: all
all: $(TARGET)

.PHONY: tags
tags: $(ROOTDIR)/tags

.PHONY: sanitized
sanitized: CXXFLAGS += -fsanitize=address
sanitized: LIBS += -fsanitize=address
sanitized: all

.PHONY: effective
effective: CXXFLAGS += -Weffc++
effective: all

.PHONY: makefile-debug
makefile-debug:
	@echo $(dir $(SRCSCC))

.PHONY: lib
lib: $(filter-out main.o, $(OBJS))
	$(AR) rvs $(TARGET).a $(filter-out main.o, $^)

$(TARGET): lib main.o
	$(CXX) -o $@ main.o $@.a $(LIBS)

$(DEPDIR)/%.d: %.cc
	$(CXX) $(CXXFLAGS) -MM -o $@ $<

$(ROOTDIR)/tags: $(SRCSCC)
	$(CXX) $(CXXFLAGSTAGS) $(CXXFLAGS) -M $(SRCSCCABS) | sed -e 's/[\\ ]/\n/g' | \
	sed -e '/^$$/d' -e '/\.o:[ \t]*$$/d' | \
	ctags -L - --c++-kinds=+p --fields=+iaS --extras=+q -o "$(ROOTDIR)/tags" --language-force=C++

-include $(DEPS)

endif
