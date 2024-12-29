#include "UniquePtr.h"

#include <utility>
#include <cassert>

int main() {
    UniquePtr<int> sptr(new int);
    UniquePtr<int> sptr2(std::move(sptr));
    UniquePtr<int> sptr3 = std::move(sptr2);

    *sptr3 = 10;
    assert(*sptr3 == 10);

    auto sptr4 = make_unique<char>('a');

    assert(*sptr4 == 'a');

    return 0;
}