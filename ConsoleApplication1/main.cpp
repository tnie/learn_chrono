//#ifdef _DEBUG
//#undef _DEBUG   /*ȱʧ Python Debug Binary*/
//#include <python.h>
//#define _DEBUG
//#else
#include <python.h>
//#endif

#include <iostream>

using namespace std;

int main()
{
    //ȷ����ͷ�ļ������ļ�����Դһ��
    Py_SetPythonHome(L"C:/Users/nielo/anaconda3");
    if (auto ptr = Py_GetPythonHome())
    {
        wcout << L"PythonHome is: " << ptr << endl;
    }
    else
    {
        wcerr << L"PythonHome is: NULL" << endl;
    }
    Py_SetProgramName(L"main");
    Py_Initialize();
    PyRun_SimpleString("print('Hello Python!')");
    Py_Finalize();
    return 0;
}