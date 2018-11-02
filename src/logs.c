#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "logs.h"

static ZNPStatusString _status_list[] =
{
    {ZSUCCESS , "ZNP COMMAND SUCCESS"},
    {ZFAILURE , "ZNP failure"},
    {ZINVALIDPARAMETER , "ZNP invalid parameter"},
    {NV_ITEM_UNINIT, "ZNP NV item is not intialized"},
    {NV_OPER_FAILED , "ZNP NV operation is not valid"},
    {NV_BAD_ITEM_LEN , "ZNP NV item length is invalid"},
    {ZMEMERROR , "ZNP memory error"},
    {ZBUFFERFULL , "ZNP buffer is full"},
    {ZUNSUPPORTEDMODE , "ZNP unsupported mode"},
    {ZMACMEMERROR , "ZNP MAC memory error"},
    {ZDOINVALIDREQUESTTYPE , "ZNP ZDO request is invalid"},
    {ZDODEVICENOTFOUND , "ZNP ZDO device not found"},
    {ZDOINVALIDENDPOINT , "ZNP ZDO request on invalid endpoint"},
    {ZDOUNSUPPORTED , "ZNP ZDO command is not supported"},
    {ZDOTIMEOUT , "ZNP ZDO timeout"},
    {ZDONOMATCH , "ZNP ZDO found no match"},
    {ZDOTABLEFULL , "ZNP ZDO table is full"},
    {ZDONOBINDENTRY , "ZNP ZDO found no bind entry"},
    {ZSECNOKEY , "ZNP found no security key"},
    {ZSECMAXFRMCOUNT , "ZNP security max frame count reached"},
    {ZAPSFAIL , "ZNP APS failed"},
    {ZAPSTABLEFULL , "ZNP APS table is full"},
    {ZAPSILLEGALREQUEST , "ZNP APS illegal request"},
    {ZAPSINVALIDBINDING , "ZNP APS binding is invalid"},
    {ZAPSUNSUPPORTEDATTRIB , "ZNP APS unsupported attribute"},
    {ZAPSNOTSUPPORTED , "ZNP APS operation not supported"},
    {ZAPSNOACK , "ZNP APS no acknowledgement received"},
    {ZAPSDUPLICATEENTRY , "ZNP APS duplicate entry"},
    {ZAPSNOBOUNDDEVICE , "ZNP APS no bound device found"},
    {ZNWKINVALIDPARAM , "ZNP APS invalid parameter"},
    {ZNWKINVALIDREQUEST , "ZNP APS invalid request"},
    {ZNWKNOTPERMITTED , "ZNP APS operation not permitted"},
    {ZNWKSTARTUPFAILURE , "ZNP NWK startup failure"},
    {ZNWKTABLEFULL , "ZNP NWK Table is full"},
    {ZNWKUNKNOWNDEVICE , "ZNP NWK unkown device"},
    {ZNWKUNSUPPORTEDATTRIBUTE , "ZNP NWM unsupported attribute"},
    {ZNWKNONETWORKS , "ZNP NWK no network available"},
    {ZNWKLEAVEUNCONFIRMED , "ZNP NWK Leave command unconfirmed"},
    {ZNWKNOACK , "ZNP NWK No Acknowledgement received"},
    {ZNWKNOROUTE , "ZNP NWK no route found"},
    {ZMACNOACK , "ZNP MAC no acknowledgemeent received"}
};
static uint8_t _status_list_len = sizeof(_status_list)/sizeof(ZNPStatusString);
static uint8_t _loglevel = -1;

void zg_logs_init()
{

    char *tmp = getenv("ZP_LOG_LEVEL");
    if (tmp)
    {
        _loglevel = atoi(tmp);
    }
    else
    {
        _loglevel = ZP_LOG_LEVEL_NONE;
    }}

int zg_logs_domain_register(const char *name __attribute__((unused)),  const char *color __attribute__((unused)))
{
    return 1;
}

void zg_logs_shutdown()
{

}

const char *zg_logs_znp_strerror(ZNPStatus status)
{
    int index = 0;
    for(index = 0; index < _status_list_len; index++)
    {
        if(_status_list[index].status == status)
            return _status_list[index].string;
    }
    return NULL;
}

void zp_log_print(int level, const char *file, int line, const char *format, ...)
{
    va_list va;

    static const char *const c[] =
    {
        [ZP_LOG_LEVEL_EVENT]     = ZG_COLOR_WHITE,
        [ZP_LOG_LEVEL_DEBUG]     = ZG_COLOR_BLUE,
        [ZP_LOG_LEVEL_INFO]      = ZG_COLOR_LIGHTBLUE,
        [ZP_LOG_LEVEL_WARNING]   = ZG_COLOR_YELLOW,
        [ZP_LOG_LEVEL_ERROR]     = ZG_COLOR_LIGHTRED,
        [ZP_LOG_LEVEL_CRITICAL]  = ZG_COLOR_RED,
    };

    static const char *const l[] =
    {
        [ZP_LOG_LEVEL_EVENT]    = "event",
        [ZP_LOG_LEVEL_DEBUG]    = "debug",
        [ZP_LOG_LEVEL_INFO]     = "info",
        [ZP_LOG_LEVEL_WARNING]  = "warning",
        [ZP_LOG_LEVEL_ERROR]    = "error",
        [ZP_LOG_LEVEL_CRITICAL] = "critical",
    };

    /* no log => return */
    if (_loglevel == ZP_LOG_LEVEL_NONE)
    {
        return;
    }

    if (level < _loglevel)
    {
        return;
    }

    va_start (va, format);
    fprintf (stderr, ZG_FORMAT_BOLD "[%s:%d] %s%s" ZG_FORMAT_NORMAL ": ", file, line, c[level], l[level]);
    vfprintf (stderr, format, va);
    fprintf (stderr, "\n");
    va_end (va);
}
