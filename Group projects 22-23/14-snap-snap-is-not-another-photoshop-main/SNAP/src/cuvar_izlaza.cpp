#include "../inc/cuvar_izlaza.hpp"

namespace snap {
    cuvar_izlaza::cuvar_izlaza(std::shared_ptr<GotovaSlika> slika)
        : slika(slika), vreme(std::chrono::system_clock::now()) {
            std::cout << "CUVAR IZLAZA :: CUVAR IZLAZA" << std::endl;
        }
}


