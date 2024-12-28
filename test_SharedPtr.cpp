#define SHARED_PTR_IMPL
#include "SharedPtr.h"

#include <cassert>

int main() {
    SharedPtr<int> sptr(new int);
    SharedPtr<int> sptr2(sptr);
    SharedPtr<int> sptr3 = sptr;

    assert(sptr.get() == sptr2.get());
    assert(sptr.get() == sptr3.get());

    *sptr = 10;

    assert(*sptr == 10);
    assert(*sptr2 == 10);
    assert(*sptr3 == 10);

    auto sptr4 = make_shared<char>('a');

    assert(*sptr4 == 'a');

    return 0;
}