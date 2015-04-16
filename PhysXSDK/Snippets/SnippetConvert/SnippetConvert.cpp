/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
// Copyright (c) 2004-2008 AGEIA Technologies, Inc. All rights reserved.
// Copyright (c) 2001-2004 NovodeX AG. All rights reserved.  


// ***********************************************************************************************
// This snippet illustrates how to convert PhysX 3 serialized binary files from one platform to
// another. The conversion requires three input files:
// 
// 1. A metadata file that was created on the source platform. This file specifies the 
//   source platform as well as the layout of PhysX data structures on the source platform.
// 2. A metadata file that was created on the target platform. This file specifies the target 
//   (destination) platform as well as the layout of PhysX data structures on the target platform. 
// 3. A source file containing a binary serialized collection. The platform this file was created
//   on needs to match with the platform the source metadata file has been created on.
//
// A set of pre-built binary metadata files for various platforms is included with the PhysX SDK 
// at [path to installed PhysX SDK]/Tools/BinaryMetaData.
//
// Optionally this snippet allows to create a example file with binary serialized data for the 
// platform the snippet runs on.
//
// The conversion snippet only compiles and runs on authoring platforms (windows, osx and linux).
//
// SnippetConvert is a simple command-line tool supporting the following options::
//
//  --srcMetadata=<filename>         Specify the source metadata (and the source platform)
//  --dstMetadata=<filename>         Specify the target metadata (and the target platform)
//  --srcBinFile=<filename>          Source binary file to convert (serialized on target platform)
//  --dstBinFile=<filename>          Outputs target binary file
//  --generateExampleFile=<filename> Generates an example file
//  --verbose                        Enables verbose mode
//
// ***********************************************************************************************

#include "PxPhysicsAPI.h"

#include "../SnippetCommon/SnippetPrint.h"
#include "../SnippetUtils/SnippetUtils.h"

#include <iostream>



using namespace physx;
PxDefaultAllocator		 gAllocator;
PxDefaultErrorCallback	 gErrorCallback;

PxFoundation*			 gFoundation = NULL;
PxPhysics*				 gPhysics	= NULL;
PxSerializationRegistry* gSerializationRegistry = NULL;


struct CmdLineParameters
{
	bool			verbose;
	const char*		srcMetadata;		
	const char*		dstMetadata;			
	const char*		srcBinFile;		
	const char*		dstBinFile;		
	const char*		exampleFile;		

	CmdLineParameters()
		: verbose(false)
		, srcMetadata(NULL)
		, dstMetadata(NULL)
		, srcBinFile(NULL)
		, dstBinFile(NULL)
		, exampleFile(NULL)
	{
	}
};

static bool match(const char* opt, const char* ref)
{
	std::string s1(opt);
	std::string s2(ref);
	return !s1.compare(0, s2.length(), s2);
}

static void printHelpMsg()
{
	printf("SnippetConvert usage:\n"
		"SnippetConvert "
		"--srcMetadata=<filename> "
		"--dstMetadata=<filename> "
		"--srcBinFile=<filename> "
		"--dstBinFile=<filename> "
		"--generateExampleFile=<filename> "		
	    "--verbose \n"
		"A set of pre-built binary metadata is included with the PhysX SDK "
		"at [path to installed PhysX SDK]/Tools/BinaryMetaData.\n");

	printf("--srcMetadata=<filename>\n");
	printf("  Defines source metadata file\n");

	printf("--dstMetadata=<filename>\n");
	printf("  Defines target metadata file\n");

	printf("--srcBinFile=<filename>\n");
	printf("  Source binary file to convert\n");

	printf("--dstBinFile=<filename>\n");
	printf("  Outputs target binary file\n");

	printf("--generateExampleFile=<filename>\n");
	printf("  Generates an example file\n");

	printf("--verbose\n");
	printf("  Enables verbose mode\n");
}

static bool parseCommandLine(CmdLineParameters& result, int argc, const char *const*argv)
{
	if( argc <= 1 )
    {
        printHelpMsg();
        return false;
    }
	
#define GET_PARAMETER(v, s)                                             \
    {                                                                   \
	   v = argv[i] + strlen(s);										    \
	   if( v == NULL )													\
	   {																\
	    printf("[ERROR] \"%s\" should have extra parameter\n", argv[i]);\
	    printHelpMsg();													\
	    return false;													\
	  }																	\
	}

	for(int i = 0; i < argc; ++i)
	{
		if(argv[i][0] != '-' || argv[i][1] != '-')
		{
			if( i > 0 )
			{
				printf( "[ERROR] Unknown command line parameter \"%s\"\n", argv[i] );
				printHelpMsg();
				return false;
			}

			continue;
		}
		
		if(match(argv[i], "--verbose"))
		{
			result.verbose = true;
		}
		else if(match(argv[i], "--srcMetadata="))
		{
			GET_PARAMETER(result.srcMetadata, "--srcMetadata=");
		}
		else if(match(argv[i], "--dstMetadata="))
		{
			GET_PARAMETER(result.dstMetadata, "--dstMetadata=");
		}
		else if(match(argv[i], "--srcBinFile="))
		{
			GET_PARAMETER(result.srcBinFile, "--srcBinFile=");
		}
		else if(match(argv[i], "--dstBinFile="))
		{
			GET_PARAMETER(result.dstBinFile, "--dstBinFile=");
		}
		else if(match(argv[i], "--generateExampleFile="))
		{
			GET_PARAMETER(result.exampleFile, "--generateExampleFile=");
			break;
		}
		else
		{
			printf( "[ERROR] Unknown command line parameter \"%s\"\n", argv[i] );
			printHelpMsg();
			return false;
		}
	}
	
	if( result.exampleFile )
		return true;

	if( !result.srcMetadata || !result.dstMetadata || !result.srcBinFile || !result.dstBinFile)
	{
		printf("[ERROR] Missed args!! \n");      
		printHelpMsg();													
	    return false;													
	}
	return true;
}

static bool generateExampleFile(const char* filename)
{
	PxCollection* collection = PxCreateCollection();
	PX_ASSERT( collection );
	
	PxMaterial *material = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
	PX_ASSERT( material );
	PxShape* shape = gPhysics->createShape(PxBoxGeometry(2.f, 2.f, 2.f), *material);
	PxRigidStatic* theStatic = PxCreateStatic(*gPhysics, PxTransform(PxIdentity), *shape);
	
	collection->add(*material);
	collection->add(*shape);
	collection->add(*theStatic);

	PxDefaultFileOutputStream s(filename);
	bool bret = PxSerialization::serializeCollectionToBinary(s, *collection, *gSerializationRegistry);	
	collection->release();
	return bret;
}

static void initPhysics()
{
	gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);
	
	PxProfileZoneManager* profileZoneManager = &PxProfileZoneManager::createProfileZoneManager(gFoundation);
	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,profileZoneManager);
	
	gSerializationRegistry = PxSerialization::createSerializationRegistry(*gPhysics);	
}

static void cleanupPhysics()
{
	gSerializationRegistry->release();
	
	PxProfileZoneManager* profileZoneManager = gPhysics->getProfileZoneManager();
	gPhysics->release();
	profileZoneManager->release();
	gFoundation->release();

	printf("SnippetConvert done.\n");
}

int snippetMain(int argc, const char *const*argv)
{
	CmdLineParameters result;
	if(!parseCommandLine(result, argc, argv))
		return 1;

	bool bret = false;
	initPhysics();
	if(result.exampleFile)
	{
		bret = generateExampleFile(result.exampleFile);
	}
	else
	{
		PxBinaryConverter* binaryConverter = PxSerialization::createBinaryConverter();
		if(result.verbose)
			binaryConverter->setReportMode(PxConverterReportMode::eVERBOSE);
		else
			binaryConverter->setReportMode(PxConverterReportMode::eNORMAL);

		
		PxDefaultFileInputData srcMetaDataStream(result.srcMetadata);
		PxDefaultFileInputData dstMetaDataStream(result.dstMetadata);
		bret = binaryConverter->setMetaData(srcMetaDataStream, dstMetaDataStream);
		if(!bret)
		{
			printf("setMetaData failed\n");
		}
		else
		{
			PxDefaultFileInputData  srcBinaryDataStream(result.srcBinFile);
			PxDefaultFileOutputStream dstBinaryDataStream(result.dstBinFile);
			binaryConverter->convert(srcBinaryDataStream, srcBinaryDataStream.getLength(), dstBinaryDataStream);
		}

		binaryConverter->release();
	}

	cleanupPhysics();
	
	return !bret;
}
