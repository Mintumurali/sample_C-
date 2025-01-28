#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

// XOR encryption function (simple encryption for demonstration)
std::string xorEncryptDecrypt(const std::string& data, const std::string& key) {
    std::string result = data;
    for (size_t i = 0; i < data.size(); ++i) {
        result[i] ^= key[i % key.size()];
    }
    return result;
}

// Password Manager Class
class PasswordManager {
private:
    std::unordered_map<std::string, std::string> passwords; // Store passwords in memory
    std::string masterPassword;                            // Master password for authentication
    const std::string encryptionKey = "SimpleKey123";      // Key for encryption (replace with something more secure)
    const std::string fileName = "passwords.txt";          // File to store encrypted passwords

public:
    PasswordManager(const std::string& masterPass) : masterPassword(masterPass) {
        loadPasswords();
    }

    // Add a new password
    void addPassword(const std::string& site, const std::string& password) {
        passwords[site] = xorEncryptDecrypt(password, encryptionKey);
        savePasswords();
        std::cout << "Password for " << site << " added successfully!\n";
    }

    // Retrieve a password
    void getPassword(const std::string& site) {
        if (passwords.find(site) != passwords.end()) {
            std::string decryptedPassword = xorEncryptDecrypt(passwords[site], encryptionKey);
            std::cout << "Password for " << site << ": " << decryptedPassword << "\n";
        } else {
            std::cout << "No password found for " << site << "!\n";
        }
    }

    // View all saved websites
    void viewAllWebsites() {
        std::string inputMasterPassword;
        std::cout << "Enter master password to view all websites: ";
        std::cin >> inputMasterPassword;

        if (!verifyMasterPassword(inputMasterPassword)) {
            std::cout << "Incorrect master password. Access denied.\n";
            return;
        }

        if (passwords.empty()) {
            std::cout << "No passwords saved yet.\n";
        } else {
            std::cout << "\nSaved websites:\n";
            for (const auto& entry : passwords) {
                std::cout << "- " << entry.first << "\n";
            }
        }
    }

    // Save passwords to file
    void savePasswords() {
        std::ofstream outFile(fileName, std::ios::trunc);
        if (outFile.is_open()) {
            for (const auto& entry : passwords) {
                outFile << entry.first << " " << entry.second << "\n";
            }
            outFile.close();
        } else {
            std::cerr << "Error: Unable to save passwords to file.\n";
        }
    }

    // Load passwords from file
    void loadPasswords() {
        passwords.clear();
        std::ifstream inFile(fileName);
        if (inFile.is_open()) {
            std::string site, encryptedPassword;
            while (inFile >> site >> encryptedPassword) {
                passwords[site] = encryptedPassword;
            }
            inFile.close();
        }
    }

    // Verify master password
    bool verifyMasterPassword(const std::string& inputPassword) {
        return inputPassword == masterPassword;
    }
};

int main() {
    std::string masterPass;
    std::cout << "Set your master password: ";
    std::cin >> masterPass;

    PasswordManager manager(masterPass);

    int choice;
    do {
        std::cout << "\n=== Password Manager ===\n";
        std::cout << "1. Add Password\n";
        std::cout << "2. Get Password\n";
        std::cout << "3. View All Websites\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string site, password;
            std::cout << "Enter site name: ";
            std::cin >> site;
            std::cout << "Enter password: ";
            std::cin >> password;
            manager.addPassword(site, password);
            break;
        }
        case 2: {
            std::string site;
            std::cout << "Enter site name: ";
            std::cin >> site;
            manager.getPassword(site);
            break;
        }
        case 3:
            manager.viewAllWebsites();
            break;
        case 4:
            std::cout << "Exiting Password Manager.\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
