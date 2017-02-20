#include <string>
using std::string;

//#include <unistd.h>
#ifdef _WIN32
// http://stackoverflow.com/questions/875249/how-to-get-current-directory

#include <windows.h>
string ExePath() {
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    string::size_type pos = string( buffer ).find_last_of( "\\/" );
    return string( buffer ).substr( 0, pos);
}
#endif



string pythonpath = ExePath()+string(";")+ExePath()+string("/../lib;")+ExePath()+string("/../scripts");
string pythonscripts=ExePath()+string("/../scripts");
string pythonhome=ExePath();
