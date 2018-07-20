#include<experimental/filesystem>
#include<iostream>

namespace fs = std::experimental::filesystem;

int main()
{
    std::string path_name{"clang++ vscode project template/"};

    std::string new_dir_name;

    std::cin >> new_dir_name;

    fs::path source_path{path_name};

    fs::path dest_path{new_dir_name};

    fs::copy(source_path,dest_path,fs::copy_options::recursive);

    char a;
    std::cin >> a;

}