#include<experimental/filesystem>
#include<iostream>

namespace fs = std::experimental::filesystem;

//change when you compile if you want set directories
//should end with a slash
std::string set_files_origin{/*enter path here*/ "/personal-vscode-template-project/project-template/"};
std::string set_files_destination{/*enter path here*/ ""};

int main()
{
    std::string possible_errors = "no errors";
    int ret = 0;
    
    std::string source_path_name{set_files_origin};

    std::string dest_path_name;

    try
    {
        std::cout 
        << "project destination will default to being in " << set_files_destination << "\n"
        << "unless if a full path is specified with a drive name (e.g. C:/work/somesubfolder/newprojectname)\n"
        << "or ./ is used to indicate the current directory (e.g. ./somesubfolder/newprojectname)\n"
        << "target directory:\n" << std::flush;

        std::getline(std::cin,dest_path_name);

        //if the name does not declare a drive (e.g. c: or d:)
        //and there is not a "./" at the beginning
        //then assume the folder will be in the default directory.
        if(
            (dest_path_name.size() < 2 || dest_path_name[1] != ':' )
            &&
            (!(dest_path_name.size() >= 2 && dest_path_name[0] == '.' && dest_path_name[1] == '/'))
        )
        {
            dest_path_name = set_files_destination + dest_path_name;
        }

        fs::path source_path{source_path_name};

        fs::path dest_path{dest_path_name};

        std::cout << "copying from " << source_path << " to " << dest_path << "\n" << std::flush;

        fs::copy(source_path,dest_path,fs::copy_options::recursive);
    }
    catch(std::exception caught)
    {
        possible_errors = caught.what();
        ret = -1;
    }

    std::cout << possible_errors << std::endl;

    {
        std::cout << "press enter to continue..." << std::flush;
        std::string temp;
        std::getline(std::cin,temp);
    }

    if(ret == 0)
    {
        system(("code \"" + dest_path_name + "\"").c_str());
    }

    return ret;

}