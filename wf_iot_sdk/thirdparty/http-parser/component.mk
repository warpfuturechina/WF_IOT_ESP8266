#
# Component Makefile
#

COMPONENT_ADD_INCLUDEDIRS := .

COMPONENT_SRCDIRS := http-parser

COMPONENT_OBJEXCLUDE := http-parser/bench.o
COMPONENT_OBJEXCLUDE += http-parser/test.o
COMPONENT_OBJEXCLUDE += contrib/http-parser/parsertrace.o
COMPONENT_OBJEXCLUDE += contrib/http-parser/url_parser.o