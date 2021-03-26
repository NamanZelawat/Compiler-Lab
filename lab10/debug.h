#ifndef debugH
#define debugH

#include<bits/stdc++.h>

using namespace std;

class Debug
{
    private :
        static string debugFile;
        static bool session;

    public :
        Debug() {}
        static void write(string);
        static void writeTitle(string title);
};

#endif