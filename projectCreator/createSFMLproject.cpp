/*
*
* Добавить проверку файлов(по желанию)
* Разобраться с русскими символами как быть
*
*/

#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;
bool directory_exists(const wstring& path) {
    DWORD fattr = GetFileAttributesW(path.c_str());
    if (fattr == INVALID_FILE_ATTRIBUTES) return false;
    if (fattr & FILE_ATTRIBUTE_DIRECTORY) return true;
    return false;
}
bool is_dir(const TCHAR* dir){
    DWORD flag = GetFileAttributes(dir);
    if(flag == 0xFFFFFFFFUL){
        if(GetLastError() == ERROR_FILE_NOT_FOUND)
            return false;
    }
    if(! (flag & FILE_ATTRIBUTE_DIRECTORY))
        return false;
    return true;
}
int main()
{
    SetConsoleCP(1251); //установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL,"Russian");
    cout << "CodeBlocks project creator\n";
    //checking exists files
    cout << "Checking files OK\n";
    string pathProject;
    cout << "Input directory of project:\t";
    //cin >> pathProject;
    getline(cin,pathProject,'\n');
    if(pathProject[pathProject.size()-1]!='\\')
        pathProject = pathProject + '\\';
    string nameProject;
    cout << "Input name of project (One whole word):\t";
    cin >> nameProject;
    string fullPathProject = pathProject + nameProject;
    string fullPathProject1 = fullPathProject; /// YA USTAL BLIN(((
    if(is_dir(fullPathProject.c_str()))
    {
        cout << "Directory exists. Closing.\n";
        return 0;
    }
    if(CreateDirectory(fullPathProject.c_str(),NULL))
    {
        cout << "\nDirectory of project was created " << fullPathProject << endl;
    }/// CreateDirectory of project
    if(CopyFile(string("main.cpp").c_str(),string(fullPathProject+"\\main.cpp").c_str(),false)) /// CopyFile(Coping from Directory, coping to directory, FileExists)
        cout << "main.cpp was created\n";

    ifstream projectIs("myproject.cbp");
    ofstream project(fullPathProject + "\\" + nameProject + ".cbp");
    if(CreateDirectory(string(fullPathProject+"\\bin").c_str(),NULL))
    {
        cout << "\\bin created" << endl;
            if(CreateDirectory(string(fullPathProject+"\\bin\\Debug").c_str(),NULL))
                cout << "\\bin\\Debug created" << fullPathProject << endl;
    }
    fullPathProject += "\\bin\\Debug"; ///PLOHAYA IDEYA NO CHTO PODELAT((((((((((((((((
    if(CopyFile(string("openal32.dll").c_str(),string(fullPathProject+"\\openal32.dll").c_str(),false)) /// CopyFile(Coping from Directory, coping to directory, FileExists)
        cout << "openal32.dll was created\n";
    if(CopyFile(string("sfml-audio-2.dll").c_str(),string(fullPathProject+"\\sfml-audio-2.dll").c_str(),false)) /// CopyFile(Coping from Directory, coping to directory, FileExists)
        cout << "sfml-audio-2.dll was created\n";
    if(CopyFile(string("sfml-audio-d-2.dll").c_str(),string(fullPathProject+"\\sfml-audio-d-2.dll").c_str(),false)) /// CopyFile(Coping from Directory, coping to directory, FileExists)
        cout << "sfml-audio-d-2.dll was created\n";
    if(CopyFile(string("sfml-graphics-2.dll").c_str(),string(fullPathProject+"\\sfml-graphics-2.dll").c_str(),false)) /// CopyFile(Coping from Directory, coping to directory, FileExists)
        cout << "sfml-graphics-2.dll was created\n";
    if(CopyFile(string("sfml-graphics-d-2.dll").c_str(),string(fullPathProject+"\\sfml-graphics-d-2.dll").c_str(),false)) /// CopyFile(Coping from Directory, coping to directory, FileExists)
        cout << "sfml-graphics-d-2.dll was created\n";
    if(CopyFile(string("sfml-network-2.dll").c_str(),string(fullPathProject+"\\sfml-network-2.dll").c_str(),false)) /// CopyFile(Coping from Directory, coping to directory, FileExists)
        cout << "sfml-network-2.dll was created\n";
    if(CopyFile(string("sfml-network-d-2.dll").c_str(),string(fullPathProject+"\\sfml-network-d-2.dll").c_str(),false)) /// CopyFile(Coping from Directory, coping to directory, FileExists)
        cout << "sfml-network-d-2.dll was created\n";
    if(CopyFile(string("sfml-system-2.dll").c_str(),string(fullPathProject+"\\sfml-system-2.dll").c_str(),false)) /// CopyFile(Coping from Directory, coping to directory, FileExists)
        cout << "sfml-system-2.dll was created\n";
    if(CopyFile(string("sfml-system-d-2.dll").c_str(),string(fullPathProject+"\\sfml-system-d-2.dll").c_str(),false)) /// CopyFile(Coping from Directory, coping to directory, FileExists)
        cout << "sfml-system-d-2.dll was created\n";
    if(CopyFile(string("sfml-window-2.dll").c_str(),string(fullPathProject+"\\sfml-window-2.dll").c_str(),false)) /// CopyFile(Coping from Directory, coping to directory, FileExists)
        cout << "sfml-window-2.dll was created\n";
    if(CopyFile(string("sfml-window-d-2.dll").c_str(),string(fullPathProject+"\\sfml-window-d-2.dll").c_str(),false)) /// CopyFile(Coping from Directory, coping to directory, FileExists)
        cout << "sfml-window-d-2.dll was created\n";

    char buf;
    while(projectIs.get(buf))
    {
        if(buf=='*')
        {
            project << nameProject;
            continue;
        }
        project << buf;
    }
    project.close();
    projectIs.close();
    cout << "Project created. Open project's folder ?(y/n)";
    char yn;
    cin >> yn;
    if(yn == 'y')
        ShellExecute(NULL,NULL,"explorer.exe",fullPathProject1.c_str(),NULL,SW_SHOWNORMAL);
    system("pause");
    return 0;
}
