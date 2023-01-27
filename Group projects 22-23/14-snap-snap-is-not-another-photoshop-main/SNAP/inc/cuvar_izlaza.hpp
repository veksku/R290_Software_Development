#pragma once

#include <chrono>
#include <memory>
#include <iostream>
#include "slika.hpp"

namespace snap {
	class cuvar_izlaza
	{
	public:
        const std::shared_ptr<GotovaSlika> slika;
        const std::chrono::time_point<std::chrono::system_clock> vreme;

        cuvar_izlaza(std::shared_ptr<GotovaSlika> slika);
	};
}

// ovo je samo nacrt da dobijete ideju kako ce ovo da izgleda - sve vristi jer jos nista nije zavrseno
