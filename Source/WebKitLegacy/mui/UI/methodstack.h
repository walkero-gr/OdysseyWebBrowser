#ifndef MUI_METHODSTACK_H
#define MUI_METHODSTACK_H
/*
 * Copyright 2009 Ilkka Lehtoranta <ilkleht@isoveli.org>
 *
 * This file is part of NetSurf, http://www.netsurf-browser.org/
 *
 * NetSurf is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * NetSurf is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#if defined(__cplusplus)
extern "C" {
#endif

// #if !defined(__AROS__)
// #define AROS_PP_VARIADIC_CAST2IPTR(x) x
// #endif

void methodstack_init(void);
void methodstack_cleanup(void);
void methodstack_cleanup_flush(void);


#if defined(__AROS__)
void methodstack_push_A(APTR obj, ULONG cnt, IPTR *args);
ULONG methodstack_push_sync_A(APTR obj, ULONG cnt, IPTR *args);

#define methodstack_push(obj, cnt, ...)                             \
    ({                                                              \
        IPTR __args[] = {AROS_PP_VARIADIC_CAST2IPTR(__VA_ARGS__)};  \
        methodstack_push_A((obj), (cnt), __args);                   \
    })

#define methodstack_push_sync(obj, cnt, ...)                        \
    ({                                                              \
        IPTR __args[] = {AROS_PP_VARIADIC_CAST2IPTR(__VA_ARGS__)};  \
        methodstack_push_sync_A((obj), (cnt), __args);              \
    })
#else
void methodstack_push(APTR obj, ULONG cnt, ...);
ULONG methodstack_push_sync(APTR obj, ULONG cnt, ...);
#endif

void methodstack_check(void);

#if defined(__cplusplus)
}
#endif
#endif /* MUI_METHODSTACK_H */
