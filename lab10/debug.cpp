#include"debug.h"

bool Debug::session = false;
string Debug::debugFile = "debug.txt";

void Debug::write(string content)
{   
    ofstream writer;
      
    if(!Debug::session)
    {
        Debug::session = true;
        writer.open(Debug::debugFile.c_str());  
    }else
    {
        writer.open(Debug::debugFile.c_str(), ios::app);  
    }
           
    writer << content << endl;
    
    writer.close();
}

void Debug::writeTitle(string title)
{
    Debug::write("\n--------------------------------------------------------");
    Debug::write("-------------------------"+title+"-------------------------");
    Debug::write("--------------------------------------------------------");
}
