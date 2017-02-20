#include "embeddedPy.h"
#include "config.h"

//PythonLibs
#include <python.h>
// c lib
#include <stdlib.h>
// stl
#include <iostream>
using namespace std;




static wchar_t* charToWChar(const char* text)
{
    const size_t size = strlen(text) + 1;
    wchar_t* wText = new wchar_t[size];
    mbstowcs(wText, text, size);
    return wText;
}


embPy::embPy()
{

}

void embPy::action(const int & i, const std::string & s)
{
    cout << "Not implemented yet!"<<endl;
}


void embPyFunc(const int & i, const std::string &s)
{

    cout<<pythonpath <<endl;
    cout<<pythonhome <<endl;
    cout<<pythonscripts <<endl;
    Py_SetPythonHome(charToWChar(pythonhome.c_str()));
 //   Py_SetPath(charToWChar("T:/Informatique/dev/qt-python-app/lib;T:/Informatique/dev/qt-python-app/scripts"));
    Py_SetPath(charToWChar(pythonpath.c_str()));
  //  Py_SetPath(charToWChar(pythonscripts.c_str()));

    Py_Initialize();
        PyObject* module = PyImport_ImportModule("python_script");
          if(module == NULL){
              cout<<"FATAL ERROR: python_script not loaded."<<endl;
              throw(-1);
          }

          PyObject* args = Py_BuildValue("(i,s)", i, s.c_str());
          PyObject* funct=PyObject_GetAttrString(module, "instant_dump");
          PyObject* funcCall = PyObject_CallObject(funct,args );

          Py_Finalize();
}


