/*

author : Yekuuun
github : https://github.com/yekuuun


contains all logs function to keep trace of data received.

*/

#include "logs.hpp"

std::string current_date_string() {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);

    // Create a std::stringstream for formatting
    std::stringstream ss;
    ss << std::setfill('0');
    ss << std::setw(4) << (tm.tm_year + 1900) << "-";
    ss << std::setw(2) << (tm.tm_mon + 1) << "-";
    ss << std::setw(2) << tm.tm_mday;

    return ss.str();
}

int create_logs(const std::string& folderPath, const char *data){
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);

    // Créer un std::stringstream pour le formatage du nom de fichier
    std::stringstream filename;
    filename << folderPath << "\\";
    filename << std::setw(2) << tm.tm_mday << "-";
    filename << std::setw(2) << (tm.tm_mon + 1) << "-";
    filename << (tm.tm_year + 1900);
    filename << ".txt";

    std::string filePath = filename.str();

    // Ouvrir le fichier en mode écriture (crée le fichier s'il n'existe pas)
    std::ofstream outputFile(filePath, std::ios::app);

    if (outputFile.is_open()) {
        outputFile << "----" << current_date_string() << "---\n" << data << std::endl;
        
        outputFile.close();
        return 0;
        
    } else {
        std::cerr << "[ERROR] while trying to open file " << filePath << std::endl;
        return 1;
    }
}


