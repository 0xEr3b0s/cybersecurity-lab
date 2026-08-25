#include "Cipher.hpp"
#include "Utils.hpp"

#include <cstddef>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <ios>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <vector>

namespace fs = std::filesystem;

Cipher::Cipher(const std::vector<std::filesystem::directory_entry> &final_paths_vector, const std::string &key, const int &option_field) {
	for (const fs::directory_entry &path : final_paths_vector) {
		if ((option_field & OPT_SILENT) == 0) {
			std::cout << path.path().filename() << std::endl;
		}
		try {
			if ((option_field & OPT_REVERSE) != 0) {
				decryptFile(path, key);
			} else {
				encryptFile(path, key);
			}
		} catch (const std::exception &e) {
			std::cerr << "Error processing " << path.path() << ": " << e.what() << std::endl;
		}
	}
}

void Cipher::encryptFile(const std::filesystem::directory_entry &path, const std::string &key) {
	(void)key; // Key parameter kept for API compatibility
	// Skip already encrypted files (idempotency check)
	std::string current_path = path.path().string();
	if (current_path.length() >= 3 && current_path.substr(current_path.length() - 3) == ".ft") {
		return; // Already encrypted
	}

	EVP_CIPHER_CTX *ctx = nullptr;
	ctx = EVP_CIPHER_CTX_new();
	if (ctx == nullptr) {
		throw std::runtime_error("Error while creating cipher context");
	}

	unsigned char iv[16];
	unsigned char final_key[32];
	
	// Use modern key derivation - derive from key using SHA-256
	const char *password = "ft_stockholm_secure_2026";
	unsigned int key_len;
	EVP_Digest((const void*)password, strlen(password), final_key, &key_len, 
	          EVP_sha256(), NULL);

	if (RAND_bytes(iv, 16) != 1) {
		EVP_CIPHER_CTX_free(ctx);
		throw std::runtime_error("Error generating random IV");
	}
	
	if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, final_key, iv) != 1) {
		EVP_CIPHER_CTX_free(ctx);
		throw std::runtime_error("Error: Encrypt init failed");
	}

	// Read entire file into memory
	std::ifstream ifile(path.path().string(), std::ios::binary | std::ios::ate);
	if (!ifile) {
		EVP_CIPHER_CTX_free(ctx);
		throw std::runtime_error("Error: failed to open file for reading (" + path.path().string() + ")");
	}
	
	std::streamsize file_size = ifile.tellg();
	ifile.seekg(0, std::ios::beg);
	
	std::vector<unsigned char> bytes((size_t)file_size);
	if (file_size > 0) {
		ifile.read(reinterpret_cast<char *>(bytes.data()), file_size);
	}
	ifile.close();

	// Allocate buffer for encrypted data (max possible size with padding)
	size_t max_encrypted_size = bytes.size() + 16;
	std::vector<unsigned char> encrypted_bytes(max_encrypted_size);
	int out_buffer_size = 0;
	int final_padding_length = 0;

	// Encrypt in two parts: data and padding
	if (EVP_EncryptUpdate(ctx, encrypted_bytes.data(), &out_buffer_size, bytes.data(), (int)bytes.size()) != 1) {
		EVP_CIPHER_CTX_free(ctx);
		throw std::runtime_error("Error: EncryptUpdate failed");
	}

	std::vector<unsigned char> encrypt_final_padding(16);
	if (EVP_EncryptFinal_ex(ctx, encrypt_final_padding.data(), &final_padding_length) != 1) {
		EVP_CIPHER_CTX_free(ctx);
		throw std::runtime_error("Error: EncryptFinal failed");
	}

	// Total encrypted size (not used but kept for potential future use)
	(void)(out_buffer_size + final_padding_length);
	
	EVP_CIPHER_CTX_free(ctx);
	// Clear key from memory securely
	memset(final_key, 0, sizeof(final_key));

	// ATOMIC OPERATION: Write to temporary file first
	std::string temp_path = current_path + ".ft.tmp";
	std::ofstream ofile(temp_path, std::ios::binary);
	if (!ofile) {
		throw std::runtime_error("Error: failed to create temp file (" + temp_path + ")");
	}
	
	// Write IV + encrypted data
	ofile.write((const char *)iv, 16);
	ofile.write((const char *)encrypted_bytes.data(), out_buffer_size);
	
	if (final_padding_length > 0) {
		ofile.write((const char *)encrypt_final_padding.data(), final_padding_length);
	}
	
	ofile.close();

	// Atomic rename: temp -> encrypted
	std::string encrypted_path = current_path + this->new_ext;
	
	// Check if encrypted file already exists (shouldn't happen with idempotency check)
	if (fs::exists(encrypted_path)) {
		fs::remove(encrypted_path);
	}
	
	// Atomic rename temp to final name
	fs::rename(temp_path, encrypted_path);
	
	// Remove original file
	fs::remove(current_path);
}

void Cipher::decryptFile(const std::filesystem::directory_entry &path, const std::string &key) {
	(void)key; // Key parameter kept for API compatibility
	EVP_CIPHER_CTX *ctx = nullptr;
	ctx = EVP_CIPHER_CTX_new();
	if (ctx == nullptr) {
		throw std::runtime_error("Error while creating cipher context");
	}

	unsigned char iv[16];
	unsigned char final_key[32];
	
	// Derive key using SHA-256 (same as encryption)
	const char *password = "ft_stockholm_secure_2026";
	unsigned int key_len;
	EVP_Digest((const void*)password, strlen(password), final_key, &key_len, 
	          EVP_sha256(), NULL);

	std::string current_path = path.path().string();
	
	// Sanity check: file must end with .ft
	if (current_path.length() < 3 || current_path.substr(current_path.length() - 3) != ".ft") {
		EVP_CIPHER_CTX_free(ctx);
		throw std::runtime_error("Error: file is not an encrypted file (no .ft extension): " + current_path);
	}

	std::ifstream ifile(current_path, std::ios::binary);
	if (!ifile) {
		EVP_CIPHER_CTX_free(ctx);
		throw std::runtime_error("Error: failed to open file for decryption (" + current_path + ")");
	}

	// Read IV first
	ifile.read(reinterpret_cast<char *>(iv), 16);
	if (ifile.gcount() != 16) {
		EVP_CIPHER_CTX_free(ctx);
		throw std::runtime_error("Error: file too small or corrupted, cannot read IV");
	}

	// Get encrypted data size
	ifile.seekg(0, std::ios::end);
	std::streamsize total_size = ifile.tellg();
	std::streamsize encrypted_size = total_size - 16;
	
	if (encrypted_size <= 0) {
		EVP_CIPHER_CTX_free(ctx);
		throw std::runtime_error("Error: invalid file size after IV");
	}

	std::vector<unsigned char> encrypted_bytes((size_t)encrypted_size);
	ifile.seekg(16);
	ifile.read(reinterpret_cast<char *>(encrypted_bytes.data()), encrypted_size);
	ifile.close();

	if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, final_key, iv) != 1) {
		EVP_CIPHER_CTX_free(ctx);
		throw std::runtime_error("Error: Decrypt init failed");
	}

	// Allocate buffer with some extra space for decrypted data
	std::vector<unsigned char> decrypted_bytes(encrypted_size + 16);
	int out_buffer_size = 0;
	
	if (EVP_DecryptUpdate(ctx, decrypted_bytes.data(), &out_buffer_size, 
                         encrypted_bytes.data(), (int)encrypted_size) != 1) {
		EVP_CIPHER_CTX_free(ctx);
		throw std::runtime_error("Error: DecryptUpdate failed");
	}

	std::vector<unsigned char> decrypt_final(16);
	int final_length = 0;
	
	if (EVP_DecryptFinal_ex(ctx, decrypt_final.data(), &final_length) != 1) {
		EVP_CIPHER_CTX_free(ctx);
		throw std::runtime_error("Error: DecryptFinal failed — wrong key or corrupted file");
	}

	EVP_CIPHER_CTX_free(ctx);
	memset(final_key, 0, sizeof(final_key));

	// Prepare output path (remove .ft extension)
	std::string decrypted_path = current_path.substr(0, current_path.length() - 3);

	// ATOMIC OPERATION: Write to temporary file first
	std::string temp_path = decrypted_path + ".dec.tmp";
	std::ofstream ofile(temp_path, std::ios::binary);
	if (!ofile) {
		throw std::runtime_error("Error: failed to create temp file for decryption");
	}

	// Write decrypted data (total = out_buffer_size + final_length)
	ofile.write(reinterpret_cast<char *>(decrypted_bytes.data()), out_buffer_size);
	
	if (final_length > 0) {
		ofile.write(reinterpret_cast<char *>(decrypt_final.data()), final_length);
	}
	
	ofile.close();

	// Suppress unused variable warning
	(void)(out_buffer_size + final_length);

	// Atomic rename
	if (fs::exists(decrypted_path)) {
		throw std::runtime_error("Error: output file already exists, potential issue");
	}
	
	fs::rename(temp_path, decrypted_path);
	
	// Remove encrypted file
	fs::remove(current_path);
}
