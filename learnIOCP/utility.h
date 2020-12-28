#pragma once
#include <vector>
#include <string>
#include <stdio.h>
#include <direct.h>
#include <io.h>

using std::string;
using std::vector;

//https://blog.csdn.net/hust_bochu_xuchao/article/details/53418197
//���ұ�Ŀ¼����Ŀ¼�µ������ļ���TODO ��� mainDir ʹ�����·�������
void cf_findFileFromDir(string mainDir, vector<string> &files)
{
    files.clear();
    const char *dir = mainDir.c_str();
    _chdir(dir);
    long hFile;
    _finddata_t fileinfo;

    if ((hFile = _findfirst("*.*", &fileinfo)) != -1)
    {
        do
        {
            if ((fileinfo.attrib & _A_SUBDIR))//�ҵ��ļ���
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                {
                    char subdir[_MAX_PATH];
                    strcpy_s(subdir, dir);
                    strcat_s(subdir, "\\");
                    strcat_s(subdir, fileinfo.name);
                    string temDir = subdir;
                    vector<string> temFiles;
                    cf_findFileFromDir(temDir, temFiles);
                    for (vector<string>::iterator it = temFiles.begin(); it < temFiles.end(); it++)
                    {
                        files.push_back(*it);
                    }
                }
            }
            else//ֱ���ҵ��ļ�
            {
                char filename[_MAX_PATH];
                strcpy_s(filename, dir);
                strcat_s(filename, "\\");
                strcat_s(filename, fileinfo.name);
                string temfilename = filename;
                files.push_back(temfilename);
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

