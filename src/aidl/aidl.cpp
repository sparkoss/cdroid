
#include "aidl_language.h"
#include "options.h"
#include "caidl.h"
#include "jaidl.h"
#include "generate_java.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/param.h>
#include <sys/stat.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>

#ifdef HAVE_MS_C_RUNTIME
#include <io.h>
#include <sys/stat.h>
#endif

#ifndef O_BINARY
#  define O_BINARY  0
#endif


using namespace std;

// ==========================================================
static int
compile_aidl(Options& options)
{
    int err = 0;

    if(options.lang == TARGET_CPP) {
        err = ccompile_aidl(options);
    }
    else if(options.lang == TARGET_JAVA) {
        err = ccompile_aidl(options);
    }

    return err;
}

static int
preprocess_aidl(const Options& options)
{
    int err;
    if(options.lang == TARGET_CPP) {
        err = cpreprocess_aidl(options);
    }
    else if(options.lang == TARGET_JAVA) {
        err = jpreprocess_aidl(options);
    }

    return err;
}

// ==========================================================
int
main(int argc, const char **argv)
{
    Options options;
    int result = parse_options(argc, argv, &options);
    if (result) {
        return result;
    }

    switch (options.task)
    {
        case COMPILE_AIDL:
            return compile_aidl(options);
        case PREPROCESS_AIDL:
            return preprocess_aidl(options);
    }
    fprintf(stderr, "aidl: internal error\n");
    return 1;
}
