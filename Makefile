BUILD     := build
SRCDIR    := src
INCDIR    := inc
EXTDIR    := ext
LIBDIR    := $(EXTDIR)/lib
LIBINCDIR := $(EXTDIR)/inc
DEPDIR    := .d

RM         := rm -rf
MKDIR      := mkdir -p
TARGET     := $(BUILD)/SDL_GUI
LIB_TARGET := $(BUILD)/libSDL_GUI.a
SRCSALL      := $(patsubst ./%, %, $(shell find -name "*.cc" -o -name "*.h"))
SRCSCC       := $(filter %.cc, $(SRCSALL))
SRCH         := $(filter %.h, $(SRCSALL))
OBJS         := $(patsubst $(SRCDIR)/%.cc, $(BUILD)/%.o, $(SRCSCC))
DEPS         := $(patsubst $(SRCDIR)/%.cc, $(DEPDIR)/%.d, $(SRCSCC))


CXXFLAGS     := -std=c++2a -Wall -Wextra -Wpedantic -ggdb -O0 `sdl2-config --cflags`
CXXFLAGS     += -I$(INCDIR) -I$(LIBINCDIR)

DEPFLAGS     += -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

CXXFLAGSTAGS := -I/home/morion/.vim/tags


RAPIDXML_INCDIR  := $(LIBINCDIR)/rapidxml
RAPIDXML_EXTDIR  := $(EXTDIR)/rapidxml
RAPIDXML_HEADERS := $(RAPIDXML_EXTDIR)

SDL2_GFX_LIB      := $(LIBDIR)/libSDL2_gfx.a
SDL2_GFX_INCDIR   := $(LIBINCDIR)/SDL2_gfx
SDL2_GFX_EXTDIR   := $(EXTDIR)/SDL2_gfx
SDL2_GFX_HEADERS  := $(patsubst ./%, %, $(shell find $(SDL2_GFX_EXTDIR) -name "*.h"))
SDL2_GFX_INCLUDES := $(SDL2_GFX_HEADERS:$(SDL2_GFX_EXTDIR)%=$(SDL2_GFX_INCDIR)%)

LIBRARIES   := $(SDL2_GFX_LIB)
LIB_HEADERS := $(RAPIDXML_INCDIR) $(SDL2_GFX_INCLUDES)
DYN_LIBS    := -lSDL2 -lSDL2_ttf -lSDL2_image -lfontconfig
EXPORT_LIBS := $(LIBRARIES:$(LIBDIR)%=$(BUILD)%)

# create directories
$(foreach dirname,$(dir $(OBJS)) $(dir $(DEPS)),$(shell $(MKDIR) $(dirname)))

.PHONY: all
#all: CXXFLAGS += -fsanitize=address
#all: LIBS += -fsanitize=address
all: $(TARGET)

.PHONY: libheaders
libheaders: $(LIB_HEADERS)

.PHONY: run
run: all
	$(TARGET)

.PHONY: clean
clean:
	$(RM) $(BUILD)
	$(RM) $(DEPDIR)
	$(RM) $(LIBDIR)
	$(RM) $(LIBINCDIR)

.PHONY: sure
sure: clean
	@$(MAKE) --no-print-directory

.PHONY: debug
debug:
	@echo $(OBJS)

.PHONY: lib
#lib: CXXFLAGS += -fsanitize=address
#lib: LIBS += -fsanitize=address
lib: $(LIB_TARGET) $(EXPORT_LIBS)

$(EXPORT_LIBS): $(BUILD)/%.a: $(LIBDIR)/%.a
	ln -fs "$(CURDIR)/$<" $@

.PHONY: tags
tags: $(SRCSCC)
	$(CXX) $(CXXFLAGSTAGS) $(CXXFLAGS) -M $(SRCSCC) | sed -e 's/[\\ ]/\n/g' | \
	sed -e '/^$$/d' -e '/\.o:[ \t]*$$/d' | \
	ctags -L - --c++-kinds=+p --fields=+iaS --extra=+q -o "tags" --language-force=C++

$(OBJS): $(BUILD)/%.o: $(SRCDIR)/%.cc $(LIB_HEADERS) $(DEPDIR)/%.d | $(DEPDIR)/
	$(CXX) $(DEPFLAGS) $(CXXFLAGS) -c -o $@ $<

%/:
	$(MKDIR) $@

$(DEPS):

$(TARGET): $(BUILD)/main.o $(LIB_TARGET) $(LIBRARIES)
	$(CXX) -o $@ $^ $(DYN_LIBS)

$(LIB_TARGET): $(filter-out $(BUILD)/main.o, $(OBJS))
	$(AR) rvs $@ $^

$(SDL2_GFX_EXTDIR)/.libs/libSDL2_gfx.a:
	cd $(SDL2_GFX_EXTDIR); ./configure -q --disable-shared
	$(MAKE) -C $(SDL2_GFX_EXTDIR)

$(SDL2_GFX_LIB): $(SDL2_GFX_EXTDIR)/.libs/libSDL2_gfx.a
	ln -fs "$(CURDIR)/$<" $@


$(RAPIDXML_INCDIR): $(RAPIDXML_HEADERS)

$(SDL2_GFX_INCLUDES): $(SDL2_GFX_INCDIR)/%.h: $(SDL2_GFX_EXTDIR)/%.h

$(LIBRARIES): | $(LIBDIR)/

.SECONDEXPANSION:

$(LIB_HEADERS): | $(LIBINCDIR)/ $$(@D)/
	ln -fs "$(CURDIR)/$<" $@

-include $(wildcard $(DEPS))
