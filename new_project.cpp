#include<experimental/filesystem>
#include<iostream>

namespace fs = std::experimental::filesystem;

int main()
{
    std::string possible_errors = "no errors";
    int ret = 0;
    
    std::string source_path_name{"project templates/clang++ vscode project template"};

    std::string dest_path_name;

    try
    {
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

    system("pause");

    if(ret == 0)
    {
        system(("code \"" + dest_path_name + "\"").c_str());
    }

    return ret;

}