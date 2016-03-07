#ifndef __STATIC_ASSERT_H__
#define __STATIC_ASSERT_H__

/* static assert */
#define static_assert(x) const unsigned int static_assert_arr[x ? -1 : 1];

#endif