#include <filesystem>
#include <iostream>
#include <vector>

class Cipher {
	private:
		const std::string new_ext = ".ft";
		void encryptFile(std::filesystem::directory_entry &path, std::string &key);
		void decryptFile(std::filesystem::directory_entry &path, std::string &key);

	public:
		Cipher(std::vector<std::filesystem::directory_entry> &final_paths_vector, std::string &key, int &option_field);
};
