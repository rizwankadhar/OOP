#ifndef OUTFILE_H
#define OUTFILE_H

#include <iostream>
#include <fstream>
#include <stdlib.h>

class Outfile
{
    public:
        enum Error{OPEN_ERROR};
        Outfile(const std::string &filename);
        void write(Cactus &c);
        ~Outfile();


    private:
        std::ofstream _f;

#endif // OUTFILE_H
