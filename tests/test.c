#include <np.h>
#include "test.h"

static void test_simple(void)
{
	int r;

	r = myatoi("42");
	NP_ASSERT_EQUAL(r, 42);
}
