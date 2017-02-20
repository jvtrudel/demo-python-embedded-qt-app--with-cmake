
#include <string>
using std::string;



static wchar_t* charToWChar(const char* text);

class embPy{
public:
    embPy();
    void action(const int&, const string&);
};

void embPyFunc(const int&, const string&);
