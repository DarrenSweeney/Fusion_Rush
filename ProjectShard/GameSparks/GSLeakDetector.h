// Copyright 2015 GameSparks Ltd 2015, Inc. All Rights Reserved.
#ifndef GSLeakDetector_h__
#define GSLeakDetector_h__

#pragma once

#include <GameSparks/gsstl.h>

#undef GS_USE_LEAK_DETECTOR
//#define GS_USE_LEAK_DETECTOR 1

#if defined(GS_USE_LEAK_DETECTOR) && !defined(DOXYGEN)
namespace GameSparks {
    namespace Util
    {
        namespace LeakDetector
        {
            struct LeakedObjectDetectorBase
            {
                LeakedObjectDetectorBase()
                {
                    getAliveObjects().insert(this);
                }
                
                virtual ~LeakedObjectDetectorBase()
                {
                    getAliveObjects().erase(this);
                }
                
                virtual const char* getLeakedObjectClassName() const = 0;
                
                typedef gsstl::set<LeakedObjectDetectorBase*> AliveObjects;
                static AliveObjects& getAliveObjects()
                {
                    static AliveObjects aliveObjects;
                    return aliveObjects;
                }
                
                static gsstl::string getLeakedClasses()
                {
                    gsstl::string ret;
                    
                    for(AliveObjects::iterator i=getAliveObjects().begin(); i!=getAliveObjects().end(); ++i)
                    {
                        ret += gsstl::string("Leaked: ") + (*i)->getLeakedObjectClassName() + "\n";
                    }
                    
                    return ret;
                }
                
                static void Cleanup()
                {
                    getAliveObjects().clear();
                }
            };
            
            template <typename OwnerClass>
            struct LeakedObjectDetector : public LeakedObjectDetectorBase
            {
                virtual const char* getLeakedObjectClassName() const
                {
                    return OwnerClass::getLeakedObjectClassName();
                }
            };
        }
    }
}

#   define GS_LEAK_DETECTOR(OwnerClass) \
        friend struct GameSparks::Util::LeakDetector::LeakedObjectDetector<OwnerClass>; \
        static const char* getLeakedObjectClassName() { return #OwnerClass; } \
        GameSparks::Util::LeakDetector::LeakedObjectDetector<OwnerClass> _gs_leak_detector_;
#else
#   define GS_LEAK_DETECTOR(OwnerClass)
#endif /* GS_USE_LEAK_DETECTOR */

//#undef GS_USE_CODE_TIMING_ASSERTS
//#define GS_USE_CODE_TIMING_ASSERTS 1
#if defined(GS_USE_CODE_TIMING_ASSERTS) && !defined(DOXYGEN)
#include <chrono>
#include <iostream>
#include <iomanip>
#include <cassert>
namespace GameSparks {
	namespace Util
	{
		struct CodetimingAssert
		{
			CodetimingAssert(const std::string& function, const std::string& file, int line)
				:function(function)
				,file(file)
				,line(line)
				,inner_did_fail(false)
				,start(clock::now())
			{
				getStack().push_back(this);
			}

			~CodetimingAssert()
			{
				auto duration = clock::now() - start;
				if (!inner_did_fail && duration >= std::chrono::microseconds(1000000 / 30))
				{
					auto d = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
					std::clog << "************************************************************" << std::endl;
					std::clog << "************************************************************" << std::endl;
					std::clog << "***** Code timing Assert Failed:" << std::endl;
					std::clog << "in:" << std::endl << file << "(" << line << ")" << std::endl;
					std::clog << "function: " << function << std::endl;
					std::clog << "took: " << std::setw(10) << d << " us" << " (" << std::setprecision(3) << std::setw(11) << (1000000.0 / d) << " Hz" << ")" << std::endl;
					std::clog << "************************************************************" << std::endl;
					std::clog << "************************************************************" << std::endl;

					auto& outer = getStack();
					for (auto& x : outer)
					{
						x->inner_did_fail = true;
					}
				}

				assert(getStack().back() == this);
				getStack().pop_back();
			}

			private:
				const std::string function;
				const std::string file;
				int line;
				bool inner_did_fail; // indicates, that a CodetimingAssert further down the call-tree did fail
				typedef std::chrono::high_resolution_clock clock;
				clock::time_point start;

				static std::vector<CodetimingAssert*>& getStack()
				{
					static std::vector<CodetimingAssert*> stack;
					return stack;
				}
		};
	}
}
#	define GS_CODE_TIMING_ASSERT() ::GameSparks::Util::CodetimingAssert gsucta_##__line__(__FUNCTION__, __FILE__, __LINE__)
#else
#	define GS_CODE_TIMING_ASSERT()
#endif



#endif // GSLeakDetector_h__
