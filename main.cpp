#include "/Users/rajdeepbandopadhyay/boost_1_81_0/boost/filesystem.hpp"
#include <iostream>
#include <unordered_map>
#include <thread>

void recursive_handler (std::unordered_map< std::string, bool >& dirdata, 
                        std::unordered_map< std::string, bool >& filedata, std::string folderpath, 
                        std::string& level, std::vector<std::thread>& thrds) {
    if (folderpath.length() <2) return ;

    level = level + " --";

    dirdata[folderpath] = true;

    for ( boost::filesystem::recursive_directory_iterator end, dir(folderpath); 
                                                                dir != end; 
                                                                ++dir ) 
    {   

        if(is_directory(*dir) && !dirdata[dir->path().string()])  
        {
            std:: cout << "Folder: " << level << " " << dir->path().string() << std::endl;

            auto thrd = [&]{
                recursive_handler(std::ref(dirdata), std::ref(filedata), std::ref(dir->path().string()), std::ref(level), thrds);
            };
            std::thread t1(thrd);
            thrds.push_back(std::move(t1));

        }
        if(is_regular_file(*dir))  
        {
            std::string temp = dir->path().string();
            if (filedata.find(temp) == filedata.end())
                filedata[temp] = false;
            if (filedata[temp] == false)
            {
                std:: cout << "File:   " << level << " " << dir->path().string() << std::endl;
                filedata[temp] = true;
            }
        }
    }

    level = level.substr(0, level.size()-2);
}

int main(int argc, char** argv)
{
    std::unordered_map< std::string, bool > filedata, dirdata;
    std::vector<std::thread> thrds;
    std::string t = "";

    while (true)
    {
        recursive_handler (dirdata, filedata, argv[1], t, thrds);
        for (std::thread & th : thrds)
        {
            if (th.joinable())
                th.join();
        }
    }
}
