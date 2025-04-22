//
// Created by alexa on 3/9/2025.
// Moved to shell-game repo on 4/21/2025
//
#include <filesystem>
#include <iostream>
#include <vector>
#include <algorithm>

namespace fs = std::filesystem;

int main() {
    /* fs::path workingDir = "/"; // Set the working directory to the root of the filesystem
     * fs::path someFile = workingDir / "a.out"; // someFile is now the path "/a.out"
     * fs::path otherFile = workingDir / "tmp" / "a.out"; // otherFile is the path "/tmp/a.out"
     *
     * workingDir = fs::canonical("/var/tmp/../log"); // workingDir is the path "/var/log" (canonical)
     */
    std::string cmd;
    fs::path workingDir = "/";

    std::cout << "Welcome to ElbeeShell" << std::endl;
    while (cmd != "exit") {
        std::cout << "\n" << workingDir.string() << " $ ";
        std::getline(std::cin, cmd);
        // Commands
        if (cmd == "workingdir") {
            std::cout << "Working directory: " << workingDir.string() << std::endl;
        }
        else if (cmd.substr(0, 3) == "cd ") {
            const fs::path path = cmd.substr(3, cmd.length()-3);
            // Check if path exists
            if (exists(path) || exists(workingDir / path)) {
                if (path.string()[0] == '/') {
                    workingDir = path; // Absolute
                }
                else {
                    workingDir /= path; // Relative
                }
                workingDir = fs::canonical(workingDir);
            }
            // Print path nonexistence
            else {
                std::cout << "Path " << path << " does not exist." << std::endl;
            }
        }
        else if (cmd == "list") {
            // Lists directories then files alphabetically
            std::vector<fs::path> dirs;
            std::vector<fs::path> files;

            // Separates directories and files
            for (const auto &entry : fs::directory_iterator(workingDir)) {
                if (entry.is_directory()) {
                    dirs.push_back(entry.path());
                }
                else {
                    files.push_back(entry.path());
                }
            }

            // Sorts both directories and files alphabetically
            std::sort(dirs.begin(), dirs.end());
            std::sort(files.begin(), files.end());

            // Prints all directories
            for (const auto &dir : dirs) {
                const std::string dirTemp = dir.string();
                const int currentDirPos = dirTemp.find_last_of('/');
                std::cout << dirTemp.substr(currentDirPos+1, dirTemp.size()-currentDirPos) << " (Directory)" << std::endl;
            }
            // Prints all files
            for (const auto &file : files) {
                const std::string fileTemp = file.string();
                const int currentDirPos = fileTemp.find_last_of('/');
                std::cout << fileTemp.substr(currentDirPos+1, fileTemp.size()-currentDirPos) << std::endl;
            }
        }

    }

}