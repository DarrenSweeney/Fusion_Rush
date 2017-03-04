#include <GameSparks/gsstl.h>
#include <GameSparks/GSPlatformDeduction.h>

#if defined(__APPLE__)
#include <TargetConditionals.h>
#endif

#if GS_TARGET_PLATFORM == GS_PLATFORM_IOS
#	import <UIKit/UIKit.h>

	gsstl::string gs_ios_get_writeable_base_path()
	{
	    NSString *libraryPath = [NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES) lastObject];

	    return [libraryPath UTF8String];
	}


	gsstl::string get_ios_device_id()
	{
		static gsstl::string device_id;

		if(device_id.empty())
		{
			#if (TARGET_OS_SIMULATOR)
				// when running the test-suite in the iOS simulator from the command line via xcrun simctl
				// the test hangs in [UIDevice identifierForVendor]. So we just return a hard-coded device id
				// in the simulator for now.
				device_id = "IOS-SIMULATOR-DEVICE-ID";
			#else
				UIDevice *device = [UIDevice currentDevice];
			    #pragma clang diagnostic ignored "-Wundeclared-selector"
			    if ([UIDevice instancesRespondToSelector:@selector(identifierForVendor)]) {
			        device_id = [[[device identifierForVendor] UUIDString] UTF8String];
			    } else {
			        #pragma clang diagnostic push
			        #pragma clang diagnostic ignored "-Wdeprecated-declarations"
			        device_id = [[device performSelector:@selector(uniqueIdentifier)] UTF8String];
			    
			    }
			    #pragma clang diagnostic pop
			#endif
		}

	    return device_id;
	}

#elif GS_TARGET_PLATFORM == GS_PLATFORM_MAC
#	import <Foundation/Foundation.h>

	gsstl::string get_osx_device_id()
	{
		static gsstl::string device_id;

		if (device_id.empty())
		{
			NSArray * args = @[@"-rd1", @"-c", @"IOPlatformExpertDevice", @"|", @"grep", @"model"];
			NSTask * task = [NSTask new];
			[task setLaunchPath:@"/usr/sbin/ioreg"];
			[task setArguments:args];

			NSPipe * pipe = [NSPipe new];
			[task setStandardOutput:pipe];
			[task launch];

			NSArray * args2 = @[@"/IOPlatformUUID/ { split($0, line, \"\\\"\"); printf(\"%s\\n\", line[4]); }"];
			NSTask * task2 = [NSTask new];
			[task2 setLaunchPath:@"/usr/bin/awk"];
			[task2 setArguments:args2];

			NSPipe * pipe2 = [NSPipe new];
			[task2 setStandardInput:pipe];
			[task2 setStandardOutput:pipe2];
			NSFileHandle * fileHandle2 = [pipe2 fileHandleForReading];
			[task2 launch];

			NSData * data = [fileHandle2 readDataToEndOfFile];
			NSString * uuid = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];

			device_id = [uuid UTF8String];
		}

		return device_id;
	}

#endif
