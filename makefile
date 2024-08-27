# ----------------------------
# Makefile Options
# ----------------------------

NAME = flexCE
ICON = icon.png
DESCRIPTION = "raycaster"
COMPRESSED = NO
ARCHIVED = YES

CFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
