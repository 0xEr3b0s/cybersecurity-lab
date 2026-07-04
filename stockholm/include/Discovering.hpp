#pragma once

#include <iostream>

class Discovering {
	private:
		const std::string home = "HOME";
		const std::string infection_folder_name = "/infection";
		char *getenv_result;
		std::string complete_path;

	public:
		void discover();
};
