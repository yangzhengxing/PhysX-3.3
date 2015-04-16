/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#ifndef SAMPLE_COMMANDLINE_H
#define SAMPLE_COMMANDLINE_H

#include <assert.h>

namespace SampleFramework
{

	// Container for command-line arguments.
	// This class assumes argument 0 is always the executable path!
	class SampleCommandLine
	{
	public:
		//! commandLineFilePathFallback is an optional fall-back to a configuration file containing command line arguments.
		//  Its contents are only processed and used if the other constructor arguments yield only an executable path.
		//	This is especially useful in the case of an Andriod platform, which does not support command line options.
		//  e.g. commandLineFilePathFallback = "commandline.txt"
		//  e.g. contents of commandline.txt = --argument1 --argument2

		SampleCommandLine(unsigned int argc, const char *const* argv, const char * commandLineFilePathFallback = 0);
		SampleCommandLine(const char *args, const char * commandLineFilePathFallback = 0);
		~SampleCommandLine(void);

		//! has a given command-line switch?
		//  e.g. s=="foo" checks for -foo
		bool hasSwitch(const char *s, const unsigned int argNum = invalidArgNum) const;

		//! gets the value of a switch... 
		//  e.g. s="foo" returns "bar" if '-foo=bar' is in the commandline.
		const char* getValue(const char *s, unsigned int argNum = invalidArgNum) const;

		// return how many command line arguments there are
		unsigned int getNumArgs(void) const;

		// what is the program name
		const char* getProgramName(void) const;

		// get the string that contains the unsued args
		unsigned int unusedArgsBufSize(void) const;

		// get the string that contains the unsued args
		const char* getUnusedArgs(char *buf, unsigned int bufSize) const;

		//! if the first argument is the given command.
		bool isCommand(const char *s) const;

		//! get the first argument assuming it isn't a switch.
		//  e.g. for the command-line "myapp.exe editor -foo" it will return "editor".
		const char *getCommand(void) const;

		//! get the raw command-line argument list...
		unsigned int      getArgC(void) const { return m_argc; }
		const char *const*getArgV(void) const { return m_argv; }

		//! whether or not an argument has been read already
		bool isUsed(unsigned int argNum) const;

	private:
		SampleCommandLine(const SampleCommandLine&);
		SampleCommandLine(void);
		SampleCommandLine operator=(const SampleCommandLine&);
		void initCommon(const char * commandLineFilePathFallback);
		unsigned int		m_argc;
		const char *const	*m_argv;
		void				*m_freeme;
		static const unsigned int invalidArgNum = 0xFFFFFFFFU;
		bool*				m_argUsed;
	};

} // namespace SampleFramework

#endif // SAMPLE_COMMANDLINE_H
