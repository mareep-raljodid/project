First of all edit line 1 to reflect your own boost ibrary directory.

Compile & run using the command below:
g++ main.cpp -lboost_filesystem -lpthread; ./a.out <FOLDER TO MONITOR>


It will mix up logs since this is a multithreaded application, using mutexes/semaphores here will make this worse
than a serial program, hence avoided. Once started- the program should first print all folders and their respective
files within along with dashes reflecting depth from parent directory. Once it is done printing it will 
continue to monitor for new folders and files to appear and continue above.


Complexities:

Work: O(n)
Step: O(n)
Time: O(n)
Memory: O(n)



Further ideas:
We can have a DS to track folder, their respective files and its contents to be able to
track everything in-memory.
Ideal datastructure is a tree with nodes reflecting of they are files or a folder. See below:

TreeNode* node; 

struct TreeNode
{
  vector<TreeNode*> children;
  bool isfolder = true;
  string filecontents = "":
};
