#ifndef __libqos_h
#define __libqos_h

#include "libqtest.h"
#include "libqos/pci.h"
#include "libqos/malloc-pc.h"

typedef struct QOSOps {
    QGuestAllocator *(*init_allocator)(QAllocOpts);
    void (*uninit_allocator)(QGuestAllocator *);
} QOSOps;

typedef struct QOSState {
    QTestState *qts;
    QGuestAllocator *alloc;
    QOSOps *ops;
} QOSState;

QOSState *qtest_vboot(QOSOps *ops, const char *cmdline_fmt, va_list ap);
QOSState *qtest_boot(QOSOps *ops, const char *cmdline_fmt, ...);
void qtest_shutdown(QOSState *qs);
void mkimg(const char *file, const char *fmt, unsigned size_mb);
void mkqcow2(const char *file, unsigned size_mb);
void prepare_blkdebug_script(const char *debug_fn, const char *event);

static inline uint64_t qmalloc(QOSState *q, size_t bytes)
{
    return guest_alloc(q->alloc, bytes);
}

static inline void qfree(QOSState *q, uint64_t addr)
{
    guest_free(q->alloc, addr);
}

#endif
