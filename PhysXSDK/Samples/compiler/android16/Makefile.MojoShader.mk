# Makefile generated by XPJ for android16
-include Makefile.custom
ProjectName = MojoShader
MojoShader_cfiles   += ./../../../externals/mojoshader/1067/mojoshader.c
MojoShader_cfiles   += ./../../../externals/mojoshader/1067/mojoshader_assembler.c
MojoShader_cfiles   += ./../../../externals/mojoshader/1067/mojoshader_common.c
MojoShader_cfiles   += ./../../../externals/mojoshader/1067/mojoshader_compiler.c
MojoShader_cfiles   += ./../../../externals/mojoshader/1067/mojoshader_effects.c
MojoShader_cfiles   += ./../../../externals/mojoshader/1067/mojoshader_lexer.c
MojoShader_cfiles   += ./../../../externals/mojoshader/1067/mojoshader_opengl.c
MojoShader_cfiles   += ./../../../externals/mojoshader/1067/mojoshader_preprocessor.c

MojoShader_cpp_debug_dep    = $(addprefix $(DEPSDIR)/MojoShader/debug/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.P, $(MojoShader_cppfiles)))))
MojoShader_cc_debug_dep    = $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.debug.P, $(MojoShader_ccfiles)))))
MojoShader_c_debug_dep      = $(addprefix $(DEPSDIR)/MojoShader/debug/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.P, $(MojoShader_cfiles)))))
MojoShader_debug_dep      = $(MojoShader_cpp_debug_dep) $(MojoShader_cc_debug_dep) $(MojoShader_c_debug_dep)
-include $(MojoShader_debug_dep)
MojoShader_cpp_release_dep    = $(addprefix $(DEPSDIR)/MojoShader/release/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.P, $(MojoShader_cppfiles)))))
MojoShader_cc_release_dep    = $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.release.P, $(MojoShader_ccfiles)))))
MojoShader_c_release_dep      = $(addprefix $(DEPSDIR)/MojoShader/release/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.P, $(MojoShader_cfiles)))))
MojoShader_release_dep      = $(MojoShader_cpp_release_dep) $(MojoShader_cc_release_dep) $(MojoShader_c_release_dep)
-include $(MojoShader_release_dep)
MojoShader_cpp_checked_dep    = $(addprefix $(DEPSDIR)/MojoShader/checked/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.P, $(MojoShader_cppfiles)))))
MojoShader_cc_checked_dep    = $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.checked.P, $(MojoShader_ccfiles)))))
MojoShader_c_checked_dep      = $(addprefix $(DEPSDIR)/MojoShader/checked/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.P, $(MojoShader_cfiles)))))
MojoShader_checked_dep      = $(MojoShader_cpp_checked_dep) $(MojoShader_cc_checked_dep) $(MojoShader_c_checked_dep)
-include $(MojoShader_checked_dep)
MojoShader_cpp_profile_dep    = $(addprefix $(DEPSDIR)/MojoShader/profile/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.P, $(MojoShader_cppfiles)))))
MojoShader_cc_profile_dep    = $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.profile.P, $(MojoShader_ccfiles)))))
MojoShader_c_profile_dep      = $(addprefix $(DEPSDIR)/MojoShader/profile/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.P, $(MojoShader_cfiles)))))
MojoShader_profile_dep      = $(MojoShader_cpp_profile_dep) $(MojoShader_cc_profile_dep) $(MojoShader_c_profile_dep)
-include $(MojoShader_profile_dep)
MojoShader_debug_hpaths    := 
MojoShader_debug_hpaths    += ./../../../externals/android-ndk-r9d/sources/cxx-stl/gnu-libstdc++/include
MojoShader_debug_hpaths    += ./../../../externals/android-ndk-r9d/sources/cxx-stl/gnu-libstdc++/libs/armeabi-v7a/include
MojoShader_debug_lpaths    := 
MojoShader_debug_defines   := $(MojoShader_custom_defines)
MojoShader_debug_defines   += ANDROID
MojoShader_debug_defines   += GLES2
MojoShader_debug_defines   += __ARM_ARCH_5__
MojoShader_debug_defines   += __ARM_ARCH_5T__
MojoShader_debug_defines   += __ARM_ARCH_5E__
MojoShader_debug_defines   += __ARM_ARCH_5TE__
MojoShader_debug_defines   += _DEBUG
MojoShader_debug_defines   += PX_CHECKED
MojoShader_debug_libraries := 
MojoShader_debug_common_cflags	:= $(MojoShader_custom_cflags)
MojoShader_debug_common_cflags    += -MMD
MojoShader_debug_common_cflags    += $(addprefix -D, $(MojoShader_debug_defines))
MojoShader_debug_common_cflags    += $(addprefix -I, $(MojoShader_debug_hpaths))
MojoShader_debug_common_cflags  += -fpic -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=softfp -mthumb-interwork -fno-exceptions
MojoShader_debug_common_cflags  += -Wno-unknown-pragmas -Wno-psabi
MojoShader_debug_common_cflags  += -isysroot ../../../externals/android-ndk-r9d/platforms/android-16/arch-arm
MojoShader_debug_common_cflags  += -g3 -gdwarf-2
MojoShader_debug_cflags	:= $(MojoShader_debug_common_cflags)
MojoShader_debug_cppflags	:= $(MojoShader_debug_common_cflags)
MojoShader_debug_lflags    := $(MojoShader_custom_lflags)
MojoShader_debug_lflags    += $(addprefix -L, $(MojoShader_debug_lpaths))
MojoShader_debug_lflags    += -Wl,--start-group $(addprefix -l, $(MojoShader_debug_libraries)) -Wl,--end-group
MojoShader_debug_objsdir  = $(OBJS_DIR)/MojoShader_debug
MojoShader_debug_cpp_o    = $(addprefix $(MojoShader_debug_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.o, $(MojoShader_cppfiles)))))
MojoShader_debug_cc_o    = $(addprefix $(MojoShader_debug_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.o, $(MojoShader_ccfiles)))))
MojoShader_debug_c_o      = $(addprefix $(MojoShader_debug_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.o, $(MojoShader_cfiles)))))
MojoShader_debug_obj      = $(MojoShader_debug_cpp_o) $(MojoShader_debug_cc_o) $(MojoShader_debug_c_o)
MojoShader_debug_bin      := ./../../../externals/mojoshader/1067/lib/android16/libMojoShaderDEBUG.a

clean_MojoShader_debug: 
	@$(ECHO) clean MojoShader debug
	@$(RMDIR) $(MojoShader_debug_objsdir)
	@$(RMDIR) $(MojoShader_debug_bin)
	@$(RMDIR) $(DEPSDIR)/MojoShader/debug

build_MojoShader_debug: postbuild_MojoShader_debug
postbuild_MojoShader_debug: mainbuild_MojoShader_debug
mainbuild_MojoShader_debug: prebuild_MojoShader_debug $(MojoShader_debug_bin)
prebuild_MojoShader_debug:

$(MojoShader_debug_bin): $(MojoShader_debug_obj) 
	mkdir -p `dirname ./../../../externals/mojoshader/1067/lib/android16/libMojoShaderDEBUG.a`
	@$(AR) rcs $(MojoShader_debug_bin) $(MojoShader_debug_obj)
	$(ECHO) building $@ complete!

MojoShader_debug_DEPDIR = $(dir $(@))/$(*F)
$(MojoShader_debug_cpp_o): $(MojoShader_debug_objsdir)/%.o:
	$(ECHO) MojoShader: compiling debug $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(MojoShader_debug_objsdir),, $@))), $(MojoShader_cppfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(MojoShader_debug_cppflags) -c $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(MojoShader_debug_objsdir),, $@))), $(MojoShader_cppfiles)) -o $@
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/MojoShader/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(MojoShader_debug_objsdir),, $@))), $(MojoShader_cppfiles))))))
	cp $(MojoShader_debug_DEPDIR).d $(addprefix $(DEPSDIR)/MojoShader/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(MojoShader_debug_objsdir),, $@))), $(MojoShader_cppfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(MojoShader_debug_DEPDIR).d >> $(addprefix $(DEPSDIR)/MojoShader/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(MojoShader_debug_objsdir),, $@))), $(MojoShader_cppfiles))))).P; \
	  rm -f $(MojoShader_debug_DEPDIR).d

$(MojoShader_debug_cc_o): $(MojoShader_debug_objsdir)/%.o:
	$(ECHO) MojoShader: compiling debug $(filter %$(strip $(subst .cc.o,.cc, $(subst $(MojoShader_debug_objsdir),, $@))), $(MojoShader_ccfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(MojoShader_debug_cppflags) -c $(filter %$(strip $(subst .cc.o,.cc, $(subst $(MojoShader_debug_objsdir),, $@))), $(MojoShader_ccfiles)) -o $@
	mkdir -p $(dir $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(MojoShader_debug_objsdir),, $@))), $(MojoShader_ccfiles))))))
	cp $(MojoShader_debug_DEPDIR).d $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(MojoShader_debug_objsdir),, $@))), $(MojoShader_ccfiles))))).debug.P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(MojoShader_debug_DEPDIR).d >> $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(MojoShader_debug_objsdir),, $@))), $(MojoShader_ccfiles))))).debug.P; \
	  rm -f $(MojoShader_debug_DEPDIR).d

$(MojoShader_debug_c_o): $(MojoShader_debug_objsdir)/%.o:
	$(ECHO) MojoShader: compiling debug $(filter %$(strip $(subst .c.o,.c, $(subst $(MojoShader_debug_objsdir),, $@))), $(MojoShader_cfiles))...
	mkdir -p $(dir $(@))
	$(CC) $(MojoShader_debug_cflags) -c $(filter %$(strip $(subst .c.o,.c, $(subst $(MojoShader_debug_objsdir),, $@))), $(MojoShader_cfiles)) -o $@ 
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/MojoShader/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(MojoShader_debug_objsdir),, $@))), $(MojoShader_cfiles))))))
	cp $(MojoShader_debug_DEPDIR).d $(addprefix $(DEPSDIR)/MojoShader/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(MojoShader_debug_objsdir),, $@))), $(MojoShader_cfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(MojoShader_debug_DEPDIR).d >> $(addprefix $(DEPSDIR)/MojoShader/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(MojoShader_debug_objsdir),, $@))), $(MojoShader_cfiles))))).P; \
	  rm -f $(MojoShader_debug_DEPDIR).d

MojoShader_release_hpaths    := 
MojoShader_release_hpaths    += ./../../../externals/android-ndk-r9d/sources/cxx-stl/gnu-libstdc++/include
MojoShader_release_hpaths    += ./../../../externals/android-ndk-r9d/sources/cxx-stl/gnu-libstdc++/libs/armeabi-v7a/include
MojoShader_release_lpaths    := 
MojoShader_release_defines   := $(MojoShader_custom_defines)
MojoShader_release_defines   += ANDROID
MojoShader_release_defines   += GLES2
MojoShader_release_defines   += __ARM_ARCH_5__
MojoShader_release_defines   += __ARM_ARCH_5T__
MojoShader_release_defines   += __ARM_ARCH_5E__
MojoShader_release_defines   += __ARM_ARCH_5TE__
MojoShader_release_defines   += NDEBUG
MojoShader_release_libraries := 
MojoShader_release_common_cflags	:= $(MojoShader_custom_cflags)
MojoShader_release_common_cflags    += -MMD
MojoShader_release_common_cflags    += $(addprefix -D, $(MojoShader_release_defines))
MojoShader_release_common_cflags    += $(addprefix -I, $(MojoShader_release_hpaths))
MojoShader_release_common_cflags  += -fpic -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=softfp -mthumb-interwork -fno-exceptions
MojoShader_release_common_cflags  += -Wno-unknown-pragmas -Wno-psabi
MojoShader_release_common_cflags  += -isysroot ../../../externals/android-ndk-r9d/platforms/android-16/arch-arm
MojoShader_release_common_cflags  += -O3 -fno-strict-aliasing
MojoShader_release_common_cflags  += -ffunction-sections -funwind-tables -fstack-protector
MojoShader_release_common_cflags  += -fomit-frame-pointer -funswitch-loops -finline-limit=300
MojoShader_release_cflags	:= $(MojoShader_release_common_cflags)
MojoShader_release_cppflags	:= $(MojoShader_release_common_cflags)
MojoShader_release_lflags    := $(MojoShader_custom_lflags)
MojoShader_release_lflags    += $(addprefix -L, $(MojoShader_release_lpaths))
MojoShader_release_lflags    += -Wl,--start-group $(addprefix -l, $(MojoShader_release_libraries)) -Wl,--end-group
MojoShader_release_objsdir  = $(OBJS_DIR)/MojoShader_release
MojoShader_release_cpp_o    = $(addprefix $(MojoShader_release_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.o, $(MojoShader_cppfiles)))))
MojoShader_release_cc_o    = $(addprefix $(MojoShader_release_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.o, $(MojoShader_ccfiles)))))
MojoShader_release_c_o      = $(addprefix $(MojoShader_release_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.o, $(MojoShader_cfiles)))))
MojoShader_release_obj      = $(MojoShader_release_cpp_o) $(MojoShader_release_cc_o) $(MojoShader_release_c_o)
MojoShader_release_bin      := ./../../../externals/mojoshader/1067/lib/android16/libMojoShader.a

clean_MojoShader_release: 
	@$(ECHO) clean MojoShader release
	@$(RMDIR) $(MojoShader_release_objsdir)
	@$(RMDIR) $(MojoShader_release_bin)
	@$(RMDIR) $(DEPSDIR)/MojoShader/release

build_MojoShader_release: postbuild_MojoShader_release
postbuild_MojoShader_release: mainbuild_MojoShader_release
mainbuild_MojoShader_release: prebuild_MojoShader_release $(MojoShader_release_bin)
prebuild_MojoShader_release:

$(MojoShader_release_bin): $(MojoShader_release_obj) 
	mkdir -p `dirname ./../../../externals/mojoshader/1067/lib/android16/libMojoShader.a`
	@$(AR) rcs $(MojoShader_release_bin) $(MojoShader_release_obj)
	$(ECHO) building $@ complete!

MojoShader_release_DEPDIR = $(dir $(@))/$(*F)
$(MojoShader_release_cpp_o): $(MojoShader_release_objsdir)/%.o:
	$(ECHO) MojoShader: compiling release $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(MojoShader_release_objsdir),, $@))), $(MojoShader_cppfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(MojoShader_release_cppflags) -c $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(MojoShader_release_objsdir),, $@))), $(MojoShader_cppfiles)) -o $@
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/MojoShader/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(MojoShader_release_objsdir),, $@))), $(MojoShader_cppfiles))))))
	cp $(MojoShader_release_DEPDIR).d $(addprefix $(DEPSDIR)/MojoShader/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(MojoShader_release_objsdir),, $@))), $(MojoShader_cppfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(MojoShader_release_DEPDIR).d >> $(addprefix $(DEPSDIR)/MojoShader/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(MojoShader_release_objsdir),, $@))), $(MojoShader_cppfiles))))).P; \
	  rm -f $(MojoShader_release_DEPDIR).d

$(MojoShader_release_cc_o): $(MojoShader_release_objsdir)/%.o:
	$(ECHO) MojoShader: compiling release $(filter %$(strip $(subst .cc.o,.cc, $(subst $(MojoShader_release_objsdir),, $@))), $(MojoShader_ccfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(MojoShader_release_cppflags) -c $(filter %$(strip $(subst .cc.o,.cc, $(subst $(MojoShader_release_objsdir),, $@))), $(MojoShader_ccfiles)) -o $@
	mkdir -p $(dir $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(MojoShader_release_objsdir),, $@))), $(MojoShader_ccfiles))))))
	cp $(MojoShader_release_DEPDIR).d $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(MojoShader_release_objsdir),, $@))), $(MojoShader_ccfiles))))).release.P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(MojoShader_release_DEPDIR).d >> $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(MojoShader_release_objsdir),, $@))), $(MojoShader_ccfiles))))).release.P; \
	  rm -f $(MojoShader_release_DEPDIR).d

$(MojoShader_release_c_o): $(MojoShader_release_objsdir)/%.o:
	$(ECHO) MojoShader: compiling release $(filter %$(strip $(subst .c.o,.c, $(subst $(MojoShader_release_objsdir),, $@))), $(MojoShader_cfiles))...
	mkdir -p $(dir $(@))
	$(CC) $(MojoShader_release_cflags) -c $(filter %$(strip $(subst .c.o,.c, $(subst $(MojoShader_release_objsdir),, $@))), $(MojoShader_cfiles)) -o $@ 
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/MojoShader/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(MojoShader_release_objsdir),, $@))), $(MojoShader_cfiles))))))
	cp $(MojoShader_release_DEPDIR).d $(addprefix $(DEPSDIR)/MojoShader/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(MojoShader_release_objsdir),, $@))), $(MojoShader_cfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(MojoShader_release_DEPDIR).d >> $(addprefix $(DEPSDIR)/MojoShader/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(MojoShader_release_objsdir),, $@))), $(MojoShader_cfiles))))).P; \
	  rm -f $(MojoShader_release_DEPDIR).d

MojoShader_checked_hpaths    := 
MojoShader_checked_hpaths    += ./../../../externals/android-ndk-r9d/sources/cxx-stl/gnu-libstdc++/include
MojoShader_checked_hpaths    += ./../../../externals/android-ndk-r9d/sources/cxx-stl/gnu-libstdc++/libs/armeabi-v7a/include
MojoShader_checked_lpaths    := 
MojoShader_checked_defines   := $(MojoShader_custom_defines)
MojoShader_checked_defines   += ANDROID
MojoShader_checked_defines   += GLES2
MojoShader_checked_defines   += __ARM_ARCH_5__
MojoShader_checked_defines   += __ARM_ARCH_5T__
MojoShader_checked_defines   += __ARM_ARCH_5E__
MojoShader_checked_defines   += __ARM_ARCH_5TE__
MojoShader_checked_defines   += NDEBUG
MojoShader_checked_defines   += PX_CHECKED
MojoShader_checked_libraries := 
MojoShader_checked_common_cflags	:= $(MojoShader_custom_cflags)
MojoShader_checked_common_cflags    += -MMD
MojoShader_checked_common_cflags    += $(addprefix -D, $(MojoShader_checked_defines))
MojoShader_checked_common_cflags    += $(addprefix -I, $(MojoShader_checked_hpaths))
MojoShader_checked_common_cflags  += -fpic -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=softfp -mthumb-interwork -fno-exceptions
MojoShader_checked_common_cflags  += -Wno-unknown-pragmas -Wno-psabi
MojoShader_checked_common_cflags  += -isysroot ../../../externals/android-ndk-r9d/platforms/android-16/arch-arm
MojoShader_checked_common_cflags  += -O3 -fno-strict-aliasing
MojoShader_checked_common_cflags  += -g3 -gdwarf-2 -O3 -fno-strict-aliasing
MojoShader_checked_common_cflags  += -ffunction-sections -funwind-tables -fstack-protector
MojoShader_checked_common_cflags  += -fomit-frame-pointer -funswitch-loops -finline-limit=300
MojoShader_checked_cflags	:= $(MojoShader_checked_common_cflags)
MojoShader_checked_cppflags	:= $(MojoShader_checked_common_cflags)
MojoShader_checked_lflags    := $(MojoShader_custom_lflags)
MojoShader_checked_lflags    += $(addprefix -L, $(MojoShader_checked_lpaths))
MojoShader_checked_lflags    += -Wl,--start-group $(addprefix -l, $(MojoShader_checked_libraries)) -Wl,--end-group
MojoShader_checked_objsdir  = $(OBJS_DIR)/MojoShader_checked
MojoShader_checked_cpp_o    = $(addprefix $(MojoShader_checked_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.o, $(MojoShader_cppfiles)))))
MojoShader_checked_cc_o    = $(addprefix $(MojoShader_checked_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.o, $(MojoShader_ccfiles)))))
MojoShader_checked_c_o      = $(addprefix $(MojoShader_checked_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.o, $(MojoShader_cfiles)))))
MojoShader_checked_obj      = $(MojoShader_checked_cpp_o) $(MojoShader_checked_cc_o) $(MojoShader_checked_c_o)
MojoShader_checked_bin      := ./../../../externals/mojoshader/1067/lib/android16/libMojoShaderCHECKED.a

clean_MojoShader_checked: 
	@$(ECHO) clean MojoShader checked
	@$(RMDIR) $(MojoShader_checked_objsdir)
	@$(RMDIR) $(MojoShader_checked_bin)
	@$(RMDIR) $(DEPSDIR)/MojoShader/checked

build_MojoShader_checked: postbuild_MojoShader_checked
postbuild_MojoShader_checked: mainbuild_MojoShader_checked
mainbuild_MojoShader_checked: prebuild_MojoShader_checked $(MojoShader_checked_bin)
prebuild_MojoShader_checked:

$(MojoShader_checked_bin): $(MojoShader_checked_obj) 
	mkdir -p `dirname ./../../../externals/mojoshader/1067/lib/android16/libMojoShaderCHECKED.a`
	@$(AR) rcs $(MojoShader_checked_bin) $(MojoShader_checked_obj)
	$(ECHO) building $@ complete!

MojoShader_checked_DEPDIR = $(dir $(@))/$(*F)
$(MojoShader_checked_cpp_o): $(MojoShader_checked_objsdir)/%.o:
	$(ECHO) MojoShader: compiling checked $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(MojoShader_checked_objsdir),, $@))), $(MojoShader_cppfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(MojoShader_checked_cppflags) -c $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(MojoShader_checked_objsdir),, $@))), $(MojoShader_cppfiles)) -o $@
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/MojoShader/checked/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(MojoShader_checked_objsdir),, $@))), $(MojoShader_cppfiles))))))
	cp $(MojoShader_checked_DEPDIR).d $(addprefix $(DEPSDIR)/MojoShader/checked/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(MojoShader_checked_objsdir),, $@))), $(MojoShader_cppfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(MojoShader_checked_DEPDIR).d >> $(addprefix $(DEPSDIR)/MojoShader/checked/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(MojoShader_checked_objsdir),, $@))), $(MojoShader_cppfiles))))).P; \
	  rm -f $(MojoShader_checked_DEPDIR).d

$(MojoShader_checked_cc_o): $(MojoShader_checked_objsdir)/%.o:
	$(ECHO) MojoShader: compiling checked $(filter %$(strip $(subst .cc.o,.cc, $(subst $(MojoShader_checked_objsdir),, $@))), $(MojoShader_ccfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(MojoShader_checked_cppflags) -c $(filter %$(strip $(subst .cc.o,.cc, $(subst $(MojoShader_checked_objsdir),, $@))), $(MojoShader_ccfiles)) -o $@
	mkdir -p $(dir $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(MojoShader_checked_objsdir),, $@))), $(MojoShader_ccfiles))))))
	cp $(MojoShader_checked_DEPDIR).d $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(MojoShader_checked_objsdir),, $@))), $(MojoShader_ccfiles))))).checked.P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(MojoShader_checked_DEPDIR).d >> $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(MojoShader_checked_objsdir),, $@))), $(MojoShader_ccfiles))))).checked.P; \
	  rm -f $(MojoShader_checked_DEPDIR).d

$(MojoShader_checked_c_o): $(MojoShader_checked_objsdir)/%.o:
	$(ECHO) MojoShader: compiling checked $(filter %$(strip $(subst .c.o,.c, $(subst $(MojoShader_checked_objsdir),, $@))), $(MojoShader_cfiles))...
	mkdir -p $(dir $(@))
	$(CC) $(MojoShader_checked_cflags) -c $(filter %$(strip $(subst .c.o,.c, $(subst $(MojoShader_checked_objsdir),, $@))), $(MojoShader_cfiles)) -o $@ 
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/MojoShader/checked/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(MojoShader_checked_objsdir),, $@))), $(MojoShader_cfiles))))))
	cp $(MojoShader_checked_DEPDIR).d $(addprefix $(DEPSDIR)/MojoShader/checked/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(MojoShader_checked_objsdir),, $@))), $(MojoShader_cfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(MojoShader_checked_DEPDIR).d >> $(addprefix $(DEPSDIR)/MojoShader/checked/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(MojoShader_checked_objsdir),, $@))), $(MojoShader_cfiles))))).P; \
	  rm -f $(MojoShader_checked_DEPDIR).d

MojoShader_profile_hpaths    := 
MojoShader_profile_hpaths    += ./../../../externals/android-ndk-r9d/sources/cxx-stl/gnu-libstdc++/include
MojoShader_profile_hpaths    += ./../../../externals/android-ndk-r9d/sources/cxx-stl/gnu-libstdc++/libs/armeabi-v7a/include
MojoShader_profile_lpaths    := 
MojoShader_profile_defines   := $(MojoShader_custom_defines)
MojoShader_profile_defines   += ANDROID
MojoShader_profile_defines   += GLES2
MojoShader_profile_defines   += __ARM_ARCH_5__
MojoShader_profile_defines   += __ARM_ARCH_5T__
MojoShader_profile_defines   += __ARM_ARCH_5E__
MojoShader_profile_defines   += __ARM_ARCH_5TE__
MojoShader_profile_defines   += NDEBUG
MojoShader_profile_defines   += PX_PROFILE
MojoShader_profile_libraries := 
MojoShader_profile_common_cflags	:= $(MojoShader_custom_cflags)
MojoShader_profile_common_cflags    += -MMD
MojoShader_profile_common_cflags    += $(addprefix -D, $(MojoShader_profile_defines))
MojoShader_profile_common_cflags    += $(addprefix -I, $(MojoShader_profile_hpaths))
MojoShader_profile_common_cflags  += -fpic -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=softfp -mthumb-interwork -fno-exceptions
MojoShader_profile_common_cflags  += -Wno-unknown-pragmas -Wno-psabi
MojoShader_profile_common_cflags  += -isysroot ../../../externals/android-ndk-r9d/platforms/android-16/arch-arm
MojoShader_profile_common_cflags  += -O3 -fno-strict-aliasing
MojoShader_profile_common_cflags  += -ffunction-sections -funwind-tables -fstack-protector
MojoShader_profile_common_cflags  += -fomit-frame-pointer -funswitch-loops -finline-limit=300
MojoShader_profile_cflags	:= $(MojoShader_profile_common_cflags)
MojoShader_profile_cppflags	:= $(MojoShader_profile_common_cflags)
MojoShader_profile_lflags    := $(MojoShader_custom_lflags)
MojoShader_profile_lflags    += $(addprefix -L, $(MojoShader_profile_lpaths))
MojoShader_profile_lflags    += -Wl,--start-group $(addprefix -l, $(MojoShader_profile_libraries)) -Wl,--end-group
MojoShader_profile_objsdir  = $(OBJS_DIR)/MojoShader_profile
MojoShader_profile_cpp_o    = $(addprefix $(MojoShader_profile_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.o, $(MojoShader_cppfiles)))))
MojoShader_profile_cc_o    = $(addprefix $(MojoShader_profile_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.o, $(MojoShader_ccfiles)))))
MojoShader_profile_c_o      = $(addprefix $(MojoShader_profile_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.o, $(MojoShader_cfiles)))))
MojoShader_profile_obj      = $(MojoShader_profile_cpp_o) $(MojoShader_profile_cc_o) $(MojoShader_profile_c_o)
MojoShader_profile_bin      := ./../../../externals/mojoshader/1067/lib/android16/libMojoShaderPROFILE.a

clean_MojoShader_profile: 
	@$(ECHO) clean MojoShader profile
	@$(RMDIR) $(MojoShader_profile_objsdir)
	@$(RMDIR) $(MojoShader_profile_bin)
	@$(RMDIR) $(DEPSDIR)/MojoShader/profile

build_MojoShader_profile: postbuild_MojoShader_profile
postbuild_MojoShader_profile: mainbuild_MojoShader_profile
mainbuild_MojoShader_profile: prebuild_MojoShader_profile $(MojoShader_profile_bin)
prebuild_MojoShader_profile:

$(MojoShader_profile_bin): $(MojoShader_profile_obj) 
	mkdir -p `dirname ./../../../externals/mojoshader/1067/lib/android16/libMojoShaderPROFILE.a`
	@$(AR) rcs $(MojoShader_profile_bin) $(MojoShader_profile_obj)
	$(ECHO) building $@ complete!

MojoShader_profile_DEPDIR = $(dir $(@))/$(*F)
$(MojoShader_profile_cpp_o): $(MojoShader_profile_objsdir)/%.o:
	$(ECHO) MojoShader: compiling profile $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(MojoShader_profile_objsdir),, $@))), $(MojoShader_cppfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(MojoShader_profile_cppflags) -c $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(MojoShader_profile_objsdir),, $@))), $(MojoShader_cppfiles)) -o $@
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/MojoShader/profile/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(MojoShader_profile_objsdir),, $@))), $(MojoShader_cppfiles))))))
	cp $(MojoShader_profile_DEPDIR).d $(addprefix $(DEPSDIR)/MojoShader/profile/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(MojoShader_profile_objsdir),, $@))), $(MojoShader_cppfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(MojoShader_profile_DEPDIR).d >> $(addprefix $(DEPSDIR)/MojoShader/profile/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(MojoShader_profile_objsdir),, $@))), $(MojoShader_cppfiles))))).P; \
	  rm -f $(MojoShader_profile_DEPDIR).d

$(MojoShader_profile_cc_o): $(MojoShader_profile_objsdir)/%.o:
	$(ECHO) MojoShader: compiling profile $(filter %$(strip $(subst .cc.o,.cc, $(subst $(MojoShader_profile_objsdir),, $@))), $(MojoShader_ccfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(MojoShader_profile_cppflags) -c $(filter %$(strip $(subst .cc.o,.cc, $(subst $(MojoShader_profile_objsdir),, $@))), $(MojoShader_ccfiles)) -o $@
	mkdir -p $(dir $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(MojoShader_profile_objsdir),, $@))), $(MojoShader_ccfiles))))))
	cp $(MojoShader_profile_DEPDIR).d $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(MojoShader_profile_objsdir),, $@))), $(MojoShader_ccfiles))))).profile.P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(MojoShader_profile_DEPDIR).d >> $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(MojoShader_profile_objsdir),, $@))), $(MojoShader_ccfiles))))).profile.P; \
	  rm -f $(MojoShader_profile_DEPDIR).d

$(MojoShader_profile_c_o): $(MojoShader_profile_objsdir)/%.o:
	$(ECHO) MojoShader: compiling profile $(filter %$(strip $(subst .c.o,.c, $(subst $(MojoShader_profile_objsdir),, $@))), $(MojoShader_cfiles))...
	mkdir -p $(dir $(@))
	$(CC) $(MojoShader_profile_cflags) -c $(filter %$(strip $(subst .c.o,.c, $(subst $(MojoShader_profile_objsdir),, $@))), $(MojoShader_cfiles)) -o $@ 
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/MojoShader/profile/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(MojoShader_profile_objsdir),, $@))), $(MojoShader_cfiles))))))
	cp $(MojoShader_profile_DEPDIR).d $(addprefix $(DEPSDIR)/MojoShader/profile/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(MojoShader_profile_objsdir),, $@))), $(MojoShader_cfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(MojoShader_profile_DEPDIR).d >> $(addprefix $(DEPSDIR)/MojoShader/profile/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(MojoShader_profile_objsdir),, $@))), $(MojoShader_cfiles))))).P; \
	  rm -f $(MojoShader_profile_DEPDIR).d

clean_MojoShader:  clean_MojoShader_debug clean_MojoShader_release clean_MojoShader_checked clean_MojoShader_profile
	rm -rf $(DEPSDIR)

export VERBOSE
ifndef VERBOSE
.SILENT:
endif
