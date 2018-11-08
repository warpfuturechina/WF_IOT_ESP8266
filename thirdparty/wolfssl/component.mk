#
# Component Makefile
#

COMPONENT_ADD_INCLUDEDIRS := port wolfssl

COMPONENT_SRCDIRS := wolfssl/src wolfssl/wolfcrypt/src

COMPONENT_OBJEXCLUDE := wolfssl/wolfcrypt/src/aes_asm.o
COMPONENT_OBJEXCLUDE += wolfssl/wolfcrypt/src/evp.o
COMPONENT_OBJEXCLUDE += wolfssl/src/bio.o