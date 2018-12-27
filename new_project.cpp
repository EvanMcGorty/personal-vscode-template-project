#include<experimental/filesystem>
#include<iostream>

namespace fs = std::experimental::filesystem;

//change when you compile if you want set directories
std::string set_files_origin{""};
std::string set_files_destination{""};

int main()
{
    std::string possible_errors = "no errors";
    int ret = 0;
    
    std::string source_path_name{set_files_origin + "project templates/clang++ vscode project template"};

    std::string dest_path_name;

    try
    {
        std::cout << "target directory:\n" << std::flush;

        std::getline(std::cin,dest_path_name);

        //if the name does not declare a drive (e.g. c: or d:) then assume the folder will be in work.
        if(dest_path_name.size() < 2 || dest_path_name[1] != ':')
        {
            dest_path_name = set_files_destination + dest_path_name;
        }

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