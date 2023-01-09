#ifndef CE_CONFIG_HPP
#define CE_CONFIG_HPP

#include "key.hpp"
#include "style.hpp"
#include "plug.hpp"

namespace CE {

class Config {
	Habit *$habits;
	Plug *$plugs;
	Style $style;
	Keymap $keymap;

public:
	Bool $load();
	Bool $unload();
};

}

#endif // CE_CONFIG_HPP
