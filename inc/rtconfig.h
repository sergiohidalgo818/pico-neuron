#ifndef RTCONFIG_H__
#define RTCONFIG_H__

/* Basic RT-Thread config */
#define RT_NAME_MAX 8
#define RT_ALIGN_SIZE 4
#define RT_THREAD_PRIORITY_MAX 32
#define RT_TICK_PER_SECOND 1000
#define RT_DEBUG

/* Disable components you don’t use */
#undef RT_USING_FINSH
#undef RT_USING_DEVICE
#undef RT_USING_CONSOLE

#endif /* RTCONFIG_H__ */
