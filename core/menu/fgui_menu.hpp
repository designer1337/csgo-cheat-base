#pragma once
#include "../..//dependencies/common_includes.hpp"
#include "FGUI/FGUI.hh"

namespace gui {
	void initialize();
}

namespace vars {
	inline std::unordered_map<std::string, std::shared_ptr<fgui::button>> button;
	inline std::unordered_map<std::string, std::shared_ptr<fgui::checkbox>>
		checkbox;
	inline std::unordered_map<std::string, std::shared_ptr<fgui::colorlist>>
		colorlist;
	inline std::unordered_map<std::string, std::shared_ptr<fgui::colorpicker>>
		colorpicker;
	inline std::unordered_map<std::string, std::shared_ptr<fgui::combobox>>
		combobox;
	inline std::unordered_map<std::string, std::shared_ptr<fgui::container>>
		container;
	inline std::unordered_map<std::string, std::shared_ptr<fgui::keybinder>>
		keybinder;
	inline std::unordered_map<std::string, std::shared_ptr<fgui::label>> label;
	inline std::unordered_map<std::string, std::shared_ptr<fgui::listbox>> listbox;
	inline std::unordered_map<std::string, std::shared_ptr<fgui::multibox>>
		multibox;
	inline std::unordered_map<std::string, std::shared_ptr<fgui::slider>> slider;
	inline std::unordered_map<std::string, std::shared_ptr<fgui::spinner>> spinner;
	inline std::unordered_map<std::string, std::shared_ptr<fgui::tabs>> tabs;
	inline std::unordered_map<std::string, std::shared_ptr<fgui::textbox>> textbox;
}