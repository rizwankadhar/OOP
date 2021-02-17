#include "data.h"

void EnorData::next()
{
    string line;
    getline(_f , line);
    if( !(_end = _f.fail()) ){
        istringstream is(line);
        is >> _curr.name >> _curr.champ;
        _curr.tunas = 0;
        string fish;
        int size;
        for( is >> fish >> size ; !is.fail(); is >> fish >> size ){
            if(fish == "Tuna")
            {
                _curr.tunas++;
            }
        }
    }
}
