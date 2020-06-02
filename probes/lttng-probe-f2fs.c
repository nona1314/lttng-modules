#include <linux/module.h>
#include <linux/fs.h>
#include <linux/f2fs_fs.h>
#include <../fs/f2fs/f2fs.h>
#include <../fs/f2fs/segment.h>
#include <lttng-tracer.h>

#include <trace/events/f2fs.h>

#define LTTNG_PACKAGE_BUILD
#define CREATE_TRACE_POINTS
#define TRACE_INCLUDE_PATH instrumentation/events/lttng-module

#include <instrumentation/events/lttng-module/f2fs.h>

MODULE_LICENSE("GPL and additional rights");
MODULE_AUTHOR("Changgyu Lee <changgyuu.lee@gmail.com>");
MODULE_DESCRIPTION("LTTng f2fs probes");
MODULE_VERSION(__stringify(LTTNG_MODULES_MAJOR_VERSION) "."
        __stringify(LTTNG_MODULES_MINOR_VERSION) "."
        __stringify(LTTNG_MODULES_PATCHLEVEL_VERSION)
        LTTNG_MODULES_EXTRAVERSION);
