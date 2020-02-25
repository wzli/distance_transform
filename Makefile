BUILD_DIR ?= ./build
SRC_DIR ?= ./
INC_DIR ?= ./

SRCS := $(shell find -L $(SRC_DIR) -name "*.c")
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

$(BUILD_DIR)/test: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

INC_FLAGS := $(addprefix -I,$(INC_DIR))

COMMONFLAGS =  -Wall -Wextra -Ofast -DDEBUG

CFLAGS ?= -std=c99 $(COMMONFLAGS)
CC ?= gcc

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP 
LDLIBS += -lm

-include $(DEPS)
MKDIR_P ?= mkdir -p

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

