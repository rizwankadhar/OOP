#include <iostream>
#include "filesystem.h"

using namespace std;

int main()
{
    FileSystem* sys = new FileSystem;

    sys->add(new File(2));

    Folder* f = new Folder();
    sys->add(f);
    f->add(new File(20));
    f->add(new File(10));

    Folder* ff = new Folder();
    f->add(ff);
    ff->add(new File(100));

    sys->add(new File(3));

    cout << "Size: " << sys->getSize() << endl;

    delete sys;

    return 0;
}
