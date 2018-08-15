#include<experimental/filesystem>
#include<iostream>

namespace fs = std::experimental::filesystem;

int main()
{
    std::string possible_errors = "no errors";
    int ret = 0;

    try
    {
        std::string source_path_name{"project templates/clang++ vscode project template"};

        std::string dest_path_name;

        std::cout << "target directory:\n" << std::flush;

        std::getline(std::cin,dest_path_name);

        fs::path source_path{source_path_name};

        fs::path dest_path{dest_path_name};

        fs::copy(source_path,dest_path,fs::copy_options::recursive);
    }
    catch(std::exception caught)
    {
        possible_errors = caught.what();
        ret = -1;
    }

    std::cout << possible_errors << std::endl;

    std::cout << "press enter to continue..." << std::flush;
    std::string in;
    std::getline(std::cin,in);

    return ret;

}