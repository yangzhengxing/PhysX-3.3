# Makefile generated by XPJ for osx32
-include Makefile.custom
ProjectName = PxTask
PxTask_custom_cflags := -isysroot $(APPLE_OSX_SDK_CURRENT_VERSION)
PxTask_custom_lflags := -isysroot $(APPLE_OSX_SDK_CURRENT_VERSION)
PxTask_cppfiles   += ./../../pxtask/src/CudaWrapper.cpp
PxTask_cppfiles   += ./../../pxtask/src/TaskManager.cpp

PxTask_cpp_debug_dep    = $(addprefix $(DEPSDIR)/PxTask/debug/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.P, $(PxTask_cppfiles)))))
PxTask_cc_debug_dep    = $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.debug.P, $(PxTask_ccfiles)))))
PxTask_c_debug_dep      = $(addprefix $(DEPSDIR)/PxTask/debug/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.P, $(PxTask_cfiles)))))
PxTask_debug_dep      = $(PxTask_cpp_debug_dep) $(PxTask_cc_debug_dep) $(PxTask_c_debug_dep)
-include $(PxTask_debug_dep)
PxTask_cpp_checked_dep    = $(addprefix $(DEPSDIR)/PxTask/checked/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.P, $(PxTask_cppfiles)))))
PxTask_cc_checked_dep    = $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.checked.P, $(PxTask_ccfiles)))))
PxTask_c_checked_dep      = $(addprefix $(DEPSDIR)/PxTask/checked/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.P, $(PxTask_cfiles)))))
PxTask_checked_dep      = $(PxTask_cpp_checked_dep) $(PxTask_cc_checked_dep) $(PxTask_c_checked_dep)
-include $(PxTask_checked_dep)
PxTask_cpp_profile_dep    = $(addprefix $(DEPSDIR)/PxTask/profile/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.P, $(PxTask_cppfiles)))))
PxTask_cc_profile_dep    = $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.profile.P, $(PxTask_ccfiles)))))
PxTask_c_profile_dep      = $(addprefix $(DEPSDIR)/PxTask/profile/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.P, $(PxTask_cfiles)))))
PxTask_profile_dep      = $(PxTask_cpp_profile_dep) $(PxTask_cc_profile_dep) $(PxTask_c_profile_dep)
-include $(PxTask_profile_dep)
PxTask_cpp_release_dep    = $(addprefix $(DEPSDIR)/PxTask/release/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.P, $(PxTask_cppfiles)))))
PxTask_cc_release_dep    = $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.release.P, $(PxTask_ccfiles)))))
PxTask_c_release_dep      = $(addprefix $(DEPSDIR)/PxTask/release/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.P, $(PxTask_cfiles)))))
PxTask_release_dep      = $(PxTask_cpp_release_dep) $(PxTask_cc_release_dep) $(PxTask_c_release_dep)
-include $(PxTask_release_dep)
PxTask_debug_hpaths    := 
PxTask_debug_hpaths    += ./../../../Include/foundation
PxTask_debug_hpaths    += ./../../foundation/include
PxTask_debug_hpaths    += ./../../../Include/physxprofilesdk
PxTask_debug_hpaths    += ./../../../Include/physxvisualdebuggersdk
PxTask_debug_hpaths    += ./../../../Include
PxTask_debug_hpaths    += ./../../../Include/pxtask
PxTask_debug_lpaths    := 
PxTask_debug_defines   := $(PxTask_custom_defines)
PxTask_debug_defines   += PX_SUPPORT_VISUAL_DEBUGGER
PxTask_debug_defines   += PX_PHYSX_STATIC_LIB
PxTask_debug_defines   += _DEBUG
PxTask_debug_defines   += PX_DEBUG
PxTask_debug_defines   += PX_CHECKED
PxTask_debug_defines   += PX_PHYSX_DLL_NAME_POSTFIX=DEBUG
PxTask_debug_libraries := 
PxTask_debug_common_cflags	:= $(PxTask_custom_cflags)
PxTask_debug_common_cflags    += -MMD
PxTask_debug_common_cflags    += $(addprefix -D, $(PxTask_debug_defines))
PxTask_debug_common_cflags    += $(addprefix -I, $(PxTask_debug_hpaths))
PxTask_debug_cflags	:= $(PxTask_debug_common_cflags)
PxTask_debug_cflags  += -arch i386
PxTask_debug_cflags  += -pipe -mmacosx-version-min=10.5 -msse2 -ffast-math -fno-exceptions -fno-rtti -fvisibility=hidden -fvisibility-inlines-hidden -Werror
PxTask_debug_cflags  += -Wall -Wextra -Wstrict-aliasing=2 -Weverything
PxTask_debug_cflags  += -Wno-pedantic -Wno-unknown-warning-option
PxTask_debug_cflags  += -Wno-long-long -Wno-newline-eof -Wno-extended-offsetof
PxTask_debug_cflags  += -Wno-float-equal -Wno-documentation-deprecated-sync -Wno-conversion -Wno-weak-vtables -Wno-unreachable-code -Wno-format-nonliteral -Wno-cast-align -Wno-documentation -Wno-covered-switch-default -Wno-documentation-unknown-command -Wno-padded
PxTask_debug_cflags  += -Wno-unknown-pragmas -Wno-invalid-offsetof
PxTask_debug_cflags  += -Wno-unused-parameter
PxTask_debug_cflags  += -Wno-global-constructors -Wno-exit-time-destructors -Wno-weak-template-vtables -Wno-shift-sign-overflow -Wno-missing-noreturn -Wno-missing-variable-declarations -Wno-switch-enum -Wno-undef -Wno-unused-macros -Wno-c99-extensions -Wno-missing-prototypes -Wno-shadow -Wno-unused-member-function -Wno-used-but-marked-unused -Wno-header-hygiene -Wno-variadic-macros -Wno-old-style-cast
PxTask_debug_cflags  += -g3 -gdwarf-2 -O0
PxTask_debug_cppflags	:= $(PxTask_debug_common_cflags)
PxTask_debug_cppflags  += -arch i386
PxTask_debug_cppflags  += -pipe -mmacosx-version-min=10.5 -msse2 -ffast-math -fno-exceptions -fno-rtti -fvisibility=hidden -fvisibility-inlines-hidden -Werror
PxTask_debug_cppflags  += -Wall -Wextra -Wstrict-aliasing=2 -Weverything
PxTask_debug_cppflags  += -Wno-pedantic -Wno-unknown-warning-option
PxTask_debug_cppflags  += -Wno-long-long -Wno-newline-eof -Wno-extended-offsetof
PxTask_debug_cppflags  += -Wno-float-equal -Wno-documentation-deprecated-sync -Wno-conversion -Wno-weak-vtables -Wno-unreachable-code -Wno-format-nonliteral -Wno-cast-align -Wno-documentation -Wno-covered-switch-default -Wno-documentation-unknown-command -Wno-padded
PxTask_debug_cppflags  += -Wno-unknown-pragmas -Wno-invalid-offsetof
PxTask_debug_cppflags  += -Wno-unused-parameter
PxTask_debug_cppflags  += -Wno-global-constructors -Wno-exit-time-destructors -Wno-weak-template-vtables -Wno-shift-sign-overflow -Wno-missing-noreturn -Wno-missing-variable-declarations -Wno-switch-enum -Wno-undef -Wno-unused-macros -Wno-c99-extensions -Wno-missing-prototypes -Wno-shadow -Wno-unused-member-function -Wno-used-but-marked-unused -Wno-header-hygiene -Wno-variadic-macros -Wno-old-style-cast
PxTask_debug_cppflags  += -g3 -gdwarf-2 -O0
PxTask_debug_lflags    := $(PxTask_custom_lflags)
PxTask_debug_lflags    += $(addprefix -L, $(PxTask_debug_lpaths))
PxTask_debug_lflags  += $(addprefix -l, $(PxTask_debug_libraries))
PxTask_debug_lflags  += -arch i386
PxTask_debug_objsdir  = $(OBJS_DIR)/PxTask_debug
PxTask_debug_cpp_o    = $(addprefix $(PxTask_debug_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.o, $(PxTask_cppfiles)))))
PxTask_debug_cc_o    = $(addprefix $(PxTask_debug_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.o, $(PxTask_ccfiles)))))
PxTask_debug_c_o      = $(addprefix $(PxTask_debug_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.o, $(PxTask_cfiles)))))
PxTask_debug_obj      = $(PxTask_debug_cpp_o) $(PxTask_debug_cc_o) $(PxTask_debug_c_o)
PxTask_debug_bin      := ./../../../Lib/osx32/libPxTaskDEBUG.a

clean_PxTask_debug: 
	@$(ECHO) clean PxTask debug
	@$(RMDIR) $(PxTask_debug_objsdir)
	@$(RMDIR) $(PxTask_debug_bin)
	@$(RMDIR) $(DEPSDIR)/PxTask/debug

build_PxTask_debug: postbuild_PxTask_debug
postbuild_PxTask_debug: mainbuild_PxTask_debug
mainbuild_PxTask_debug: prebuild_PxTask_debug $(PxTask_debug_bin)
prebuild_PxTask_debug:

$(PxTask_debug_bin): $(PxTask_debug_obj) 
	mkdir -p `dirname ./../../../Lib/osx32/libPxTaskDEBUG.a`
	@$(AR) rcs $(PxTask_debug_bin) $(PxTask_debug_obj)
	$(ECHO) building $@ complete!

PxTask_debug_DEPDIR = $(dir $(@))/$(*F)
$(PxTask_debug_cpp_o): $(PxTask_debug_objsdir)/%.o:
	$(ECHO) PxTask: compiling debug $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxTask_debug_objsdir),, $@))), $(PxTask_cppfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(PxTask_debug_cppflags) -c $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxTask_debug_objsdir),, $@))), $(PxTask_cppfiles)) -o $@
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/PxTask/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxTask_debug_objsdir),, $@))), $(PxTask_cppfiles))))))
	cp $(PxTask_debug_DEPDIR).d $(addprefix $(DEPSDIR)/PxTask/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxTask_debug_objsdir),, $@))), $(PxTask_cppfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(PxTask_debug_DEPDIR).d >> $(addprefix $(DEPSDIR)/PxTask/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxTask_debug_objsdir),, $@))), $(PxTask_cppfiles))))).P; \
	  rm -f $(PxTask_debug_DEPDIR).d

$(PxTask_debug_cc_o): $(PxTask_debug_objsdir)/%.o:
	$(ECHO) PxTask: compiling debug $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxTask_debug_objsdir),, $@))), $(PxTask_ccfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(PxTask_debug_cppflags) -c $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxTask_debug_objsdir),, $@))), $(PxTask_ccfiles)) -o $@
	mkdir -p $(dir $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxTask_debug_objsdir),, $@))), $(PxTask_ccfiles))))))
	cp $(PxTask_debug_DEPDIR).d $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxTask_debug_objsdir),, $@))), $(PxTask_ccfiles))))).debug.P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(PxTask_debug_DEPDIR).d >> $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxTask_debug_objsdir),, $@))), $(PxTask_ccfiles))))).debug.P; \
	  rm -f $(PxTask_debug_DEPDIR).d

$(PxTask_debug_c_o): $(PxTask_debug_objsdir)/%.o:
	$(ECHO) PxTask: compiling debug $(filter %$(strip $(subst .c.o,.c, $(subst $(PxTask_debug_objsdir),, $@))), $(PxTask_cfiles))...
	mkdir -p $(dir $(@))
	$(CC) $(PxTask_debug_cflags) -c $(filter %$(strip $(subst .c.o,.c, $(subst $(PxTask_debug_objsdir),, $@))), $(PxTask_cfiles)) -o $@ 
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/PxTask/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(PxTask_debug_objsdir),, $@))), $(PxTask_cfiles))))))
	cp $(PxTask_debug_DEPDIR).d $(addprefix $(DEPSDIR)/PxTask/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(PxTask_debug_objsdir),, $@))), $(PxTask_cfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(PxTask_debug_DEPDIR).d >> $(addprefix $(DEPSDIR)/PxTask/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(PxTask_debug_objsdir),, $@))), $(PxTask_cfiles))))).P; \
	  rm -f $(PxTask_debug_DEPDIR).d

PxTask_checked_hpaths    := 
PxTask_checked_hpaths    += ./../../../Include/foundation
PxTask_checked_hpaths    += ./../../foundation/include
PxTask_checked_hpaths    += ./../../../Include/physxprofilesdk
PxTask_checked_hpaths    += ./../../../Include/physxvisualdebuggersdk
PxTask_checked_hpaths    += ./../../../Include
PxTask_checked_hpaths    += ./../../../Include/pxtask
PxTask_checked_lpaths    := 
PxTask_checked_defines   := $(PxTask_custom_defines)
PxTask_checked_defines   += PX_SUPPORT_VISUAL_DEBUGGER
PxTask_checked_defines   += PX_PHYSX_STATIC_LIB
PxTask_checked_defines   += NDEBUG
PxTask_checked_defines   += PX_CHECKED
PxTask_checked_defines   += PX_PHYSX_DLL_NAME_POSTFIX=CHECKED
PxTask_checked_libraries := 
PxTask_checked_common_cflags	:= $(PxTask_custom_cflags)
PxTask_checked_common_cflags    += -MMD
PxTask_checked_common_cflags    += $(addprefix -D, $(PxTask_checked_defines))
PxTask_checked_common_cflags    += $(addprefix -I, $(PxTask_checked_hpaths))
PxTask_checked_cflags	:= $(PxTask_checked_common_cflags)
PxTask_checked_cflags  += -arch i386
PxTask_checked_cflags  += -pipe -mmacosx-version-min=10.5 -msse2 -ffast-math -fno-exceptions -fno-rtti -fvisibility=hidden -fvisibility-inlines-hidden -Werror
PxTask_checked_cflags  += -Wall -Wextra -Wstrict-aliasing=2 -Weverything
PxTask_checked_cflags  += -Wno-pedantic -Wno-unknown-warning-option
PxTask_checked_cflags  += -Wno-long-long -Wno-newline-eof -Wno-extended-offsetof
PxTask_checked_cflags  += -Wno-float-equal -Wno-documentation-deprecated-sync -Wno-conversion -Wno-weak-vtables -Wno-unreachable-code -Wno-format-nonliteral -Wno-cast-align -Wno-documentation -Wno-covered-switch-default -Wno-documentation-unknown-command -Wno-padded
PxTask_checked_cflags  += -Wno-unknown-pragmas -Wno-invalid-offsetof
PxTask_checked_cflags  += -Wno-unused-parameter
PxTask_checked_cflags  += -Wno-global-constructors -Wno-exit-time-destructors -Wno-weak-template-vtables -Wno-shift-sign-overflow -Wno-missing-noreturn -Wno-missing-variable-declarations -Wno-switch-enum -Wno-undef -Wno-unused-macros -Wno-c99-extensions -Wno-missing-prototypes -Wno-shadow -Wno-unused-member-function -Wno-used-but-marked-unused -Wno-header-hygiene -Wno-variadic-macros -Wno-old-style-cast
PxTask_checked_cflags  += -g3 -gdwarf-2 -O3 -fno-strict-aliasing
PxTask_checked_cppflags	:= $(PxTask_checked_common_cflags)
PxTask_checked_cppflags  += -arch i386
PxTask_checked_cppflags  += -pipe -mmacosx-version-min=10.5 -msse2 -ffast-math -fno-exceptions -fno-rtti -fvisibility=hidden -fvisibility-inlines-hidden -Werror
PxTask_checked_cppflags  += -Wall -Wextra -Wstrict-aliasing=2 -Weverything
PxTask_checked_cppflags  += -Wno-pedantic -Wno-unknown-warning-option
PxTask_checked_cppflags  += -Wno-long-long -Wno-newline-eof -Wno-extended-offsetof
PxTask_checked_cppflags  += -Wno-float-equal -Wno-documentation-deprecated-sync -Wno-conversion -Wno-weak-vtables -Wno-unreachable-code -Wno-format-nonliteral -Wno-cast-align -Wno-documentation -Wno-covered-switch-default -Wno-documentation-unknown-command -Wno-padded
PxTask_checked_cppflags  += -Wno-unknown-pragmas -Wno-invalid-offsetof
PxTask_checked_cppflags  += -Wno-unused-parameter
PxTask_checked_cppflags  += -Wno-global-constructors -Wno-exit-time-destructors -Wno-weak-template-vtables -Wno-shift-sign-overflow -Wno-missing-noreturn -Wno-missing-variable-declarations -Wno-switch-enum -Wno-undef -Wno-unused-macros -Wno-c99-extensions -Wno-missing-prototypes -Wno-shadow -Wno-unused-member-function -Wno-used-but-marked-unused -Wno-header-hygiene -Wno-variadic-macros -Wno-old-style-cast
PxTask_checked_cppflags  += -g3 -gdwarf-2 -O3 -fno-strict-aliasing
PxTask_checked_lflags    := $(PxTask_custom_lflags)
PxTask_checked_lflags    += $(addprefix -L, $(PxTask_checked_lpaths))
PxTask_checked_lflags  += $(addprefix -l, $(PxTask_checked_libraries))
PxTask_checked_lflags  += -arch i386
PxTask_checked_objsdir  = $(OBJS_DIR)/PxTask_checked
PxTask_checked_cpp_o    = $(addprefix $(PxTask_checked_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.o, $(PxTask_cppfiles)))))
PxTask_checked_cc_o    = $(addprefix $(PxTask_checked_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.o, $(PxTask_ccfiles)))))
PxTask_checked_c_o      = $(addprefix $(PxTask_checked_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.o, $(PxTask_cfiles)))))
PxTask_checked_obj      = $(PxTask_checked_cpp_o) $(PxTask_checked_cc_o) $(PxTask_checked_c_o)
PxTask_checked_bin      := ./../../../Lib/osx32/libPxTaskCHECKED.a

clean_PxTask_checked: 
	@$(ECHO) clean PxTask checked
	@$(RMDIR) $(PxTask_checked_objsdir)
	@$(RMDIR) $(PxTask_checked_bin)
	@$(RMDIR) $(DEPSDIR)/PxTask/checked

build_PxTask_checked: postbuild_PxTask_checked
postbuild_PxTask_checked: mainbuild_PxTask_checked
mainbuild_PxTask_checked: prebuild_PxTask_checked $(PxTask_checked_bin)
prebuild_PxTask_checked:

$(PxTask_checked_bin): $(PxTask_checked_obj) 
	mkdir -p `dirname ./../../../Lib/osx32/libPxTaskCHECKED.a`
	@$(AR) rcs $(PxTask_checked_bin) $(PxTask_checked_obj)
	$(ECHO) building $@ complete!

PxTask_checked_DEPDIR = $(dir $(@))/$(*F)
$(PxTask_checked_cpp_o): $(PxTask_checked_objsdir)/%.o:
	$(ECHO) PxTask: compiling checked $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxTask_checked_objsdir),, $@))), $(PxTask_cppfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(PxTask_checked_cppflags) -c $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxTask_checked_objsdir),, $@))), $(PxTask_cppfiles)) -o $@
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/PxTask/checked/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxTask_checked_objsdir),, $@))), $(PxTask_cppfiles))))))
	cp $(PxTask_checked_DEPDIR).d $(addprefix $(DEPSDIR)/PxTask/checked/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxTask_checked_objsdir),, $@))), $(PxTask_cppfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(PxTask_checked_DEPDIR).d >> $(addprefix $(DEPSDIR)/PxTask/checked/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxTask_checked_objsdir),, $@))), $(PxTask_cppfiles))))).P; \
	  rm -f $(PxTask_checked_DEPDIR).d

$(PxTask_checked_cc_o): $(PxTask_checked_objsdir)/%.o:
	$(ECHO) PxTask: compiling checked $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxTask_checked_objsdir),, $@))), $(PxTask_ccfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(PxTask_checked_cppflags) -c $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxTask_checked_objsdir),, $@))), $(PxTask_ccfiles)) -o $@
	mkdir -p $(dir $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxTask_checked_objsdir),, $@))), $(PxTask_ccfiles))))))
	cp $(PxTask_checked_DEPDIR).d $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxTask_checked_objsdir),, $@))), $(PxTask_ccfiles))))).checked.P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(PxTask_checked_DEPDIR).d >> $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxTask_checked_objsdir),, $@))), $(PxTask_ccfiles))))).checked.P; \
	  rm -f $(PxTask_checked_DEPDIR).d

$(PxTask_checked_c_o): $(PxTask_checked_objsdir)/%.o:
	$(ECHO) PxTask: compiling checked $(filter %$(strip $(subst .c.o,.c, $(subst $(PxTask_checked_objsdir),, $@))), $(PxTask_cfiles))...
	mkdir -p $(dir $(@))
	$(CC) $(PxTask_checked_cflags) -c $(filter %$(strip $(subst .c.o,.c, $(subst $(PxTask_checked_objsdir),, $@))), $(PxTask_cfiles)) -o $@ 
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/PxTask/checked/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(PxTask_checked_objsdir),, $@))), $(PxTask_cfiles))))))
	cp $(PxTask_checked_DEPDIR).d $(addprefix $(DEPSDIR)/PxTask/checked/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(PxTask_checked_objsdir),, $@))), $(PxTask_cfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(PxTask_checked_DEPDIR).d >> $(addprefix $(DEPSDIR)/PxTask/checked/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(PxTask_checked_objsdir),, $@))), $(PxTask_cfiles))))).P; \
	  rm -f $(PxTask_checked_DEPDIR).d

PxTask_profile_hpaths    := 
PxTask_profile_hpaths    += ./../../../Include/foundation
PxTask_profile_hpaths    += ./../../foundation/include
PxTask_profile_hpaths    += ./../../../Include/physxprofilesdk
PxTask_profile_hpaths    += ./../../../Include/physxvisualdebuggersdk
PxTask_profile_hpaths    += ./../../../Include
PxTask_profile_hpaths    += ./../../../Include/pxtask
PxTask_profile_lpaths    := 
PxTask_profile_defines   := $(PxTask_custom_defines)
PxTask_profile_defines   += PX_SUPPORT_VISUAL_DEBUGGER
PxTask_profile_defines   += PX_PHYSX_STATIC_LIB
PxTask_profile_defines   += NDEBUG
PxTask_profile_defines   += PX_PROFILE
PxTask_profile_defines   += PX_PHYSX_DLL_NAME_POSTFIX=PROFILE
PxTask_profile_libraries := 
PxTask_profile_common_cflags	:= $(PxTask_custom_cflags)
PxTask_profile_common_cflags    += -MMD
PxTask_profile_common_cflags    += $(addprefix -D, $(PxTask_profile_defines))
PxTask_profile_common_cflags    += $(addprefix -I, $(PxTask_profile_hpaths))
PxTask_profile_cflags	:= $(PxTask_profile_common_cflags)
PxTask_profile_cflags  += -arch i386
PxTask_profile_cflags  += -pipe -mmacosx-version-min=10.5 -msse2 -ffast-math -fno-exceptions -fno-rtti -fvisibility=hidden -fvisibility-inlines-hidden -Werror
PxTask_profile_cflags  += -Wall -Wextra -Wstrict-aliasing=2 -Weverything
PxTask_profile_cflags  += -Wno-pedantic -Wno-unknown-warning-option
PxTask_profile_cflags  += -Wno-long-long -Wno-newline-eof -Wno-extended-offsetof
PxTask_profile_cflags  += -Wno-float-equal -Wno-documentation-deprecated-sync -Wno-conversion -Wno-weak-vtables -Wno-unreachable-code -Wno-format-nonliteral -Wno-cast-align -Wno-documentation -Wno-covered-switch-default -Wno-documentation-unknown-command -Wno-padded
PxTask_profile_cflags  += -Wno-unknown-pragmas -Wno-invalid-offsetof
PxTask_profile_cflags  += -Wno-unused-parameter
PxTask_profile_cflags  += -Wno-global-constructors -Wno-exit-time-destructors -Wno-weak-template-vtables -Wno-shift-sign-overflow -Wno-missing-noreturn -Wno-missing-variable-declarations -Wno-switch-enum -Wno-undef -Wno-unused-macros -Wno-c99-extensions -Wno-missing-prototypes -Wno-shadow -Wno-unused-member-function -Wno-used-but-marked-unused -Wno-header-hygiene -Wno-variadic-macros -Wno-old-style-cast
PxTask_profile_cflags  += -O3 -fno-strict-aliasing
PxTask_profile_cppflags	:= $(PxTask_profile_common_cflags)
PxTask_profile_cppflags  += -arch i386
PxTask_profile_cppflags  += -pipe -mmacosx-version-min=10.5 -msse2 -ffast-math -fno-exceptions -fno-rtti -fvisibility=hidden -fvisibility-inlines-hidden -Werror
PxTask_profile_cppflags  += -Wall -Wextra -Wstrict-aliasing=2 -Weverything
PxTask_profile_cppflags  += -Wno-pedantic -Wno-unknown-warning-option
PxTask_profile_cppflags  += -Wno-long-long -Wno-newline-eof -Wno-extended-offsetof
PxTask_profile_cppflags  += -Wno-float-equal -Wno-documentation-deprecated-sync -Wno-conversion -Wno-weak-vtables -Wno-unreachable-code -Wno-format-nonliteral -Wno-cast-align -Wno-documentation -Wno-covered-switch-default -Wno-documentation-unknown-command -Wno-padded
PxTask_profile_cppflags  += -Wno-unknown-pragmas -Wno-invalid-offsetof
PxTask_profile_cppflags  += -Wno-unused-parameter
PxTask_profile_cppflags  += -Wno-global-constructors -Wno-exit-time-destructors -Wno-weak-template-vtables -Wno-shift-sign-overflow -Wno-missing-noreturn -Wno-missing-variable-declarations -Wno-switch-enum -Wno-undef -Wno-unused-macros -Wno-c99-extensions -Wno-missing-prototypes -Wno-shadow -Wno-unused-member-function -Wno-used-but-marked-unused -Wno-header-hygiene -Wno-variadic-macros -Wno-old-style-cast
PxTask_profile_cppflags  += -O3 -fno-strict-aliasing
PxTask_profile_lflags    := $(PxTask_custom_lflags)
PxTask_profile_lflags    += $(addprefix -L, $(PxTask_profile_lpaths))
PxTask_profile_lflags  += $(addprefix -l, $(PxTask_profile_libraries))
PxTask_profile_lflags  += -arch i386
PxTask_profile_objsdir  = $(OBJS_DIR)/PxTask_profile
PxTask_profile_cpp_o    = $(addprefix $(PxTask_profile_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.o, $(PxTask_cppfiles)))))
PxTask_profile_cc_o    = $(addprefix $(PxTask_profile_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.o, $(PxTask_ccfiles)))))
PxTask_profile_c_o      = $(addprefix $(PxTask_profile_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.o, $(PxTask_cfiles)))))
PxTask_profile_obj      = $(PxTask_profile_cpp_o) $(PxTask_profile_cc_o) $(PxTask_profile_c_o)
PxTask_profile_bin      := ./../../../Lib/osx32/libPxTaskPROFILE.a

clean_PxTask_profile: 
	@$(ECHO) clean PxTask profile
	@$(RMDIR) $(PxTask_profile_objsdir)
	@$(RMDIR) $(PxTask_profile_bin)
	@$(RMDIR) $(DEPSDIR)/PxTask/profile

build_PxTask_profile: postbuild_PxTask_profile
postbuild_PxTask_profile: mainbuild_PxTask_profile
mainbuild_PxTask_profile: prebuild_PxTask_profile $(PxTask_profile_bin)
prebuild_PxTask_profile:

$(PxTask_profile_bin): $(PxTask_profile_obj) 
	mkdir -p `dirname ./../../../Lib/osx32/libPxTaskPROFILE.a`
	@$(AR) rcs $(PxTask_profile_bin) $(PxTask_profile_obj)
	$(ECHO) building $@ complete!

PxTask_profile_DEPDIR = $(dir $(@))/$(*F)
$(PxTask_profile_cpp_o): $(PxTask_profile_objsdir)/%.o:
	$(ECHO) PxTask: compiling profile $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxTask_profile_objsdir),, $@))), $(PxTask_cppfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(PxTask_profile_cppflags) -c $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxTask_profile_objsdir),, $@))), $(PxTask_cppfiles)) -o $@
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/PxTask/profile/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxTask_profile_objsdir),, $@))), $(PxTask_cppfiles))))))
	cp $(PxTask_profile_DEPDIR).d $(addprefix $(DEPSDIR)/PxTask/profile/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxTask_profile_objsdir),, $@))), $(PxTask_cppfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(PxTask_profile_DEPDIR).d >> $(addprefix $(DEPSDIR)/PxTask/profile/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxTask_profile_objsdir),, $@))), $(PxTask_cppfiles))))).P; \
	  rm -f $(PxTask_profile_DEPDIR).d

$(PxTask_profile_cc_o): $(PxTask_profile_objsdir)/%.o:
	$(ECHO) PxTask: compiling profile $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxTask_profile_objsdir),, $@))), $(PxTask_ccfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(PxTask_profile_cppflags) -c $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxTask_profile_objsdir),, $@))), $(PxTask_ccfiles)) -o $@
	mkdir -p $(dir $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxTask_profile_objsdir),, $@))), $(PxTask_ccfiles))))))
	cp $(PxTask_profile_DEPDIR).d $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxTask_profile_objsdir),, $@))), $(PxTask_ccfiles))))).profile.P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(PxTask_profile_DEPDIR).d >> $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxTask_profile_objsdir),, $@))), $(PxTask_ccfiles))))).profile.P; \
	  rm -f $(PxTask_profile_DEPDIR).d

$(PxTask_profile_c_o): $(PxTask_profile_objsdir)/%.o:
	$(ECHO) PxTask: compiling profile $(filter %$(strip $(subst .c.o,.c, $(subst $(PxTask_profile_objsdir),, $@))), $(PxTask_cfiles))...
	mkdir -p $(dir $(@))
	$(CC) $(PxTask_profile_cflags) -c $(filter %$(strip $(subst .c.o,.c, $(subst $(PxTask_profile_objsdir),, $@))), $(PxTask_cfiles)) -o $@ 
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/PxTask/profile/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(PxTask_profile_objsdir),, $@))), $(PxTask_cfiles))))))
	cp $(PxTask_profile_DEPDIR).d $(addprefix $(DEPSDIR)/PxTask/profile/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(PxTask_profile_objsdir),, $@))), $(PxTask_cfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(PxTask_profile_DEPDIR).d >> $(addprefix $(DEPSDIR)/PxTask/profile/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(PxTask_profile_objsdir),, $@))), $(PxTask_cfiles))))).P; \
	  rm -f $(PxTask_profile_DEPDIR).d

PxTask_release_hpaths    := 
PxTask_release_hpaths    += ./../../../Include/foundation
PxTask_release_hpaths    += ./../../foundation/include
PxTask_release_hpaths    += ./../../../Include/physxprofilesdk
PxTask_release_hpaths    += ./../../../Include/physxvisualdebuggersdk
PxTask_release_hpaths    += ./../../../Include
PxTask_release_hpaths    += ./../../../Include/pxtask
PxTask_release_lpaths    := 
PxTask_release_defines   := $(PxTask_custom_defines)
PxTask_release_defines   += PX_SUPPORT_VISUAL_DEBUGGER
PxTask_release_defines   += PX_PHYSX_STATIC_LIB
PxTask_release_defines   += NDEBUG
PxTask_release_libraries := 
PxTask_release_common_cflags	:= $(PxTask_custom_cflags)
PxTask_release_common_cflags    += -MMD
PxTask_release_common_cflags    += $(addprefix -D, $(PxTask_release_defines))
PxTask_release_common_cflags    += $(addprefix -I, $(PxTask_release_hpaths))
PxTask_release_cflags	:= $(PxTask_release_common_cflags)
PxTask_release_cflags  += -arch i386
PxTask_release_cflags  += -pipe -mmacosx-version-min=10.5 -msse2 -ffast-math -fno-exceptions -fno-rtti -fvisibility=hidden -fvisibility-inlines-hidden -Werror
PxTask_release_cflags  += -Wall -Wextra -Wstrict-aliasing=2 -Weverything
PxTask_release_cflags  += -Wno-pedantic -Wno-unknown-warning-option
PxTask_release_cflags  += -Wno-long-long -Wno-newline-eof -Wno-extended-offsetof
PxTask_release_cflags  += -Wno-float-equal -Wno-documentation-deprecated-sync -Wno-conversion -Wno-weak-vtables -Wno-unreachable-code -Wno-format-nonliteral -Wno-cast-align -Wno-documentation -Wno-covered-switch-default -Wno-documentation-unknown-command -Wno-padded
PxTask_release_cflags  += -Wno-unknown-pragmas -Wno-invalid-offsetof
PxTask_release_cflags  += -Wno-unused-parameter
PxTask_release_cflags  += -Wno-global-constructors -Wno-exit-time-destructors -Wno-weak-template-vtables -Wno-shift-sign-overflow -Wno-missing-noreturn -Wno-missing-variable-declarations -Wno-switch-enum -Wno-undef -Wno-unused-macros -Wno-c99-extensions -Wno-missing-prototypes -Wno-shadow -Wno-unused-member-function -Wno-used-but-marked-unused -Wno-header-hygiene -Wno-variadic-macros -Wno-old-style-cast
PxTask_release_cflags  += -O3 -fno-strict-aliasing
PxTask_release_cppflags	:= $(PxTask_release_common_cflags)
PxTask_release_cppflags  += -arch i386
PxTask_release_cppflags  += -pipe -mmacosx-version-min=10.5 -msse2 -ffast-math -fno-exceptions -fno-rtti -fvisibility=hidden -fvisibility-inlines-hidden -Werror
PxTask_release_cppflags  += -Wall -Wextra -Wstrict-aliasing=2 -Weverything
PxTask_release_cppflags  += -Wno-pedantic -Wno-unknown-warning-option
PxTask_release_cppflags  += -Wno-long-long -Wno-newline-eof -Wno-extended-offsetof
PxTask_release_cppflags  += -Wno-float-equal -Wno-documentation-deprecated-sync -Wno-conversion -Wno-weak-vtables -Wno-unreachable-code -Wno-format-nonliteral -Wno-cast-align -Wno-documentation -Wno-covered-switch-default -Wno-documentation-unknown-command -Wno-padded
PxTask_release_cppflags  += -Wno-unknown-pragmas -Wno-invalid-offsetof
PxTask_release_cppflags  += -Wno-unused-parameter
PxTask_release_cppflags  += -Wno-global-constructors -Wno-exit-time-destructors -Wno-weak-template-vtables -Wno-shift-sign-overflow -Wno-missing-noreturn -Wno-missing-variable-declarations -Wno-switch-enum -Wno-undef -Wno-unused-macros -Wno-c99-extensions -Wno-missing-prototypes -Wno-shadow -Wno-unused-member-function -Wno-used-but-marked-unused -Wno-header-hygiene -Wno-variadic-macros -Wno-old-style-cast
PxTask_release_cppflags  += -O3 -fno-strict-aliasing
PxTask_release_lflags    := $(PxTask_custom_lflags)
PxTask_release_lflags    += $(addprefix -L, $(PxTask_release_lpaths))
PxTask_release_lflags  += $(addprefix -l, $(PxTask_release_libraries))
PxTask_release_lflags  += -arch i386
PxTask_release_objsdir  = $(OBJS_DIR)/PxTask_release
PxTask_release_cpp_o    = $(addprefix $(PxTask_release_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.o, $(PxTask_cppfiles)))))
PxTask_release_cc_o    = $(addprefix $(PxTask_release_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.o, $(PxTask_ccfiles)))))
PxTask_release_c_o      = $(addprefix $(PxTask_release_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.o, $(PxTask_cfiles)))))
PxTask_release_obj      = $(PxTask_release_cpp_o) $(PxTask_release_cc_o) $(PxTask_release_c_o)
PxTask_release_bin      := ./../../../Lib/osx32/libPxTask.a

clean_PxTask_release: 
	@$(ECHO) clean PxTask release
	@$(RMDIR) $(PxTask_release_objsdir)
	@$(RMDIR) $(PxTask_release_bin)
	@$(RMDIR) $(DEPSDIR)/PxTask/release

build_PxTask_release: postbuild_PxTask_release
postbuild_PxTask_release: mainbuild_PxTask_release
mainbuild_PxTask_release: prebuild_PxTask_release $(PxTask_release_bin)
prebuild_PxTask_release:

$(PxTask_release_bin): $(PxTask_release_obj) 
	mkdir -p `dirname ./../../../Lib/osx32/libPxTask.a`
	@$(AR) rcs $(PxTask_release_bin) $(PxTask_release_obj)
	$(ECHO) building $@ complete!

PxTask_release_DEPDIR = $(dir $(@))/$(*F)
$(PxTask_release_cpp_o): $(PxTask_release_objsdir)/%.o:
	$(ECHO) PxTask: compiling release $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxTask_release_objsdir),, $@))), $(PxTask_cppfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(PxTask_release_cppflags) -c $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxTask_release_objsdir),, $@))), $(PxTask_cppfiles)) -o $@
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/PxTask/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxTask_release_objsdir),, $@))), $(PxTask_cppfiles))))))
	cp $(PxTask_release_DEPDIR).d $(addprefix $(DEPSDIR)/PxTask/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxTask_release_objsdir),, $@))), $(PxTask_cppfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(PxTask_release_DEPDIR).d >> $(addprefix $(DEPSDIR)/PxTask/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxTask_release_objsdir),, $@))), $(PxTask_cppfiles))))).P; \
	  rm -f $(PxTask_release_DEPDIR).d

$(PxTask_release_cc_o): $(PxTask_release_objsdir)/%.o:
	$(ECHO) PxTask: compiling release $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxTask_release_objsdir),, $@))), $(PxTask_ccfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(PxTask_release_cppflags) -c $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxTask_release_objsdir),, $@))), $(PxTask_ccfiles)) -o $@
	mkdir -p $(dir $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxTask_release_objsdir),, $@))), $(PxTask_ccfiles))))))
	cp $(PxTask_release_DEPDIR).d $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxTask_release_objsdir),, $@))), $(PxTask_ccfiles))))).release.P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(PxTask_release_DEPDIR).d >> $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxTask_release_objsdir),, $@))), $(PxTask_ccfiles))))).release.P; \
	  rm -f $(PxTask_release_DEPDIR).d

$(PxTask_release_c_o): $(PxTask_release_objsdir)/%.o:
	$(ECHO) PxTask: compiling release $(filter %$(strip $(subst .c.o,.c, $(subst $(PxTask_release_objsdir),, $@))), $(PxTask_cfiles))...
	mkdir -p $(dir $(@))
	$(CC) $(PxTask_release_cflags) -c $(filter %$(strip $(subst .c.o,.c, $(subst $(PxTask_release_objsdir),, $@))), $(PxTask_cfiles)) -o $@ 
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/PxTask/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(PxTask_release_objsdir),, $@))), $(PxTask_cfiles))))))
	cp $(PxTask_release_DEPDIR).d $(addprefix $(DEPSDIR)/PxTask/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(PxTask_release_objsdir),, $@))), $(PxTask_cfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(PxTask_release_DEPDIR).d >> $(addprefix $(DEPSDIR)/PxTask/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(PxTask_release_objsdir),, $@))), $(PxTask_cfiles))))).P; \
	  rm -f $(PxTask_release_DEPDIR).d

clean_PxTask:  clean_PxTask_debug clean_PxTask_checked clean_PxTask_profile clean_PxTask_release
	rm -rf $(DEPSDIR)

export VERBOSE
ifndef VERBOSE
.SILENT:
endif