#!/bin/sh

find . -regex ".*\.[ch][p]*" | xargs ctags

