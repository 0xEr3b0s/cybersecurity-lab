#pragma once

#include <filesystem>
#include <iostream>
#include <vector>

class Discovering {
	private:
		const std::string home = "HOME";
		const std::string infection_folder_name = "/infection";
		char *getenv_result;
		std::string complete_path;
		std::vector<std::filesystem::directory_entry> final_paths_vector;

	public:
		Discovering(int &option_field);
		std::vector<std::filesystem::directory_entry> getFinalPaths(void);
};
