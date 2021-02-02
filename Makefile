BUILD  := build
SRCDIR := src
INCDIR := inc
LIBDIR := lib
DEPDIR := .d

RM     := rm -rf
MKDIR  := mkdir -p
TARGET := $(BUILD)/SDL_GUI
SRCSALL      := $(patsubst ./%, %, $(shell find -name "*.cc" -o -name "*.h"))
SRCSCC       := $(filter %.cc, $(SRCSALL))
SRCH         := $(filter %.h, $(SRCSALL))
OBJS         := $(patsubst $(SRCDIR)/%.cc, $(BUILD)/%.o, $(SRCSCC))
DEPS         := $(patsubst $(SRCDIR)/%.cc, $(DEPDIR)/%.d, $(SRCSCC))


CXXFLAGS     := -std=c++2a -Wall -Wextra -Wpedantic -ggdb -O0 `sdl2-config --cflags`
CXXFLAGS     += -I$(INCDIR)

DEPFLAGS     += -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

CXXFLAGSTAGS := -I/home/morion/.vim/tags

LIBS         := -lSDL2 -lSDL2_gfx -lSDL2_ttf -lSDL2_image -lfontconfig

# create directories
$(foreach dirname,$(dir $(OBJS)) $(dir $(DEPS)),$(shell $(MKDIR) $(dirname)))

.PHONY: all
#all: CXXFLAGS += -fsanitize=address
#all: LIBS += -fsanitize=address
all: $(TARGET)

.PHONY: run
run: all
	$(TARGET)

.PHONY: clean
clean:
	$(RM) $(BUILD)
	$(RM) $(DEPDIR)

.PHONY: sure
sure: clean
	@$(MAKE) --no-print-directory

.PHONY: debug
debug:
	@echo $(OBJS)

.PHONY: lib
#lib: CXXFLAGS += -fsanitize=address
#lib: LIBS += -fsanitize=address
lib: $(TARGET).a

tags: $(SRCSCC)
	$(CXX) $(CXXFLAGSTAGS) $(CXXFLAGS) -M $(SRCSCC) | sed -e 's/[\\ ]/\n/g' | \
	sed -e '/^$$/d' -e '/\.o:[ \t]*$$/d' | \
	ctags -L - --c++-kinds=+p --fields=+iaS --extra=+q -o "tags" --language-force=C++

$(OBJS): $(BUILD)/%.o: $(SRCDIR)/%.cc $(DEPDIR)/%.d | $(DEPDIR)
	$(CXX) $(DEPFLAGS) $(CXXFLAGS) -c -o $@ $<

$(DEPDIR): ; @mkdir -p $@

$(DEPS):

$(TARGET): $(BUILD)/main.o $(TARGET).a
	$(CXX) -o $@ $< $(TARGET).a $(LIBS)

$(TARGET).a: $(filter-out $(BUILD)/main.o, $(OBJS))
	$(AR) rvs $@ $^

$(LIBRARIES): $(LIBDIR)/%.a: $(LIBDIR)/%/
	$(MAKE) -C $(LIBDIR)/$* lib
	ln -fs $(CURDIR)/$(LIBDIR)/$*/build/$*.a $(LIBDIR)/$*.a

-include $(wildcard $(DEPS))
