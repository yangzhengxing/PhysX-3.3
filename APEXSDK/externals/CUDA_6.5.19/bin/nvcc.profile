
TOP              = $(_HERE_)/..

NVVMIR_LIBRARY_DIR = $(TOP)/nvvm/libdevice

PATH            += $(TOP)/open64/bin;$(TOP)/nvvm/bin;$(_HERE_);$(TOP)/lib;

INCLUDES        +=  "-I$(TOP)/include" $(_SPACE_)

LIBRARIES        =+ $(_SPACE_) "/LIBPATH:$(TOP)/lib/$(_WIN_PLATFORM_)"

CUDAFE_FLAGS    +=
OPENCC_FLAGS    +=
PTXAS_FLAGS     +=
