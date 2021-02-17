#include "Angler.h"

void EnorAngler::next()
{
    if (!(_end = _ED.end())){
        _cur.name = _ED.current().name;
        _cur.tuna_cnt = 0;
        for(; !_ED.end() && _ED.current().name == _cur.name; _ED.next() )
        {
                _cur.tuna_cnt = _cur.tuna_cnt + _ED.current().tunas;
        }
        }
}
