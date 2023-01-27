#pragma once
#include <Magick++.h>
#include <string>

namespace snap {
    class GotovaSlika {
    public:
        // TODO: da li bi bilo bolje da ovaj metod vraca Qt::QImage ?
        virtual Magick::Image dohvati_sliku() = 0 ;
        virtual bool sacuvajNaDisku() = 0;
        virtual bool sacuvajNaDisku(std::string &path) = 0;

    };
}