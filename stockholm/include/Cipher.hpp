#include <filesystem>
#include <iostream>
#include <vector>

class Cipher {
	private:
		const std::string new_ext = ".ft";
	public:
		Cipher(std::vector<std::filesystem::directory_entry> &final_paths_vector, std::string &key);
};
