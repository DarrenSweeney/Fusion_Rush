#include "./Thread.hpp"

// || defined(ANDROID)
#if (defined(__linux__) || defined(__APPLE__)) && !(defined(ANDROID) || defined(IW_SDK))
#   define HAVE_PTHREAD 1
#   include <pthread.h>
#elif defined(ANDROID)
#   include <sys/prctl.h>
#else
#   define HACE_PTHREAD 0
//#   warning "Thread::SetName / GetName not implemented"
#endif

namespace System { namespace Threading {

void Thread::SetName(std::string name) {
    #if HAVE_PTHREAD
    //while(name.size() > 15) name.pop_back(); // pthread_setname_np only accepts 16 chars on some platforms
    pthread_setname_np(name.c_str());
    #elif defined (ANDROID)
    prctl(PR_SET_NAME, (unsigned long) name.c_str(), 0, 0, 0);
    #else
    #endif
}

std::string Thread::GetName() {
#if HAVE_PTHREAD
    char buffer[16];
    pthread_getname_np(
            pthread_self(),
            buffer,
            sizeof(buffer)
    );
    return buffer;
#else
    return "Thread";
#endif
}

struct _init_main_thread_name_
{
    _init_main_thread_name_(){ Thread::SetName("Main Thread"); }
} _init_main_thread_name__;

}} /* namespace System.Threading */
