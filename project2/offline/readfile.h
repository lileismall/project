#pragma once
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <vector>
using namespace std;

/***** Global Variables *****/
char dirr[100] = "./rss源语料";
int const MAX_STR_LEN = 200;

/* Show all files under dir_name , do not show directories ! */
vector<string> getAllFilesName( const char * dir_name  )
{
    //check the parameter !
        if( NULL == dir_name  )
        {
            cout<<" dir_name is null ! "<<endl;
            return vector<string>();
        }

    // check if dir_name is a valid dir
    struct stat s;
    lstat( dir_name , &s  );
    if( ! S_ISDIR( s.st_mode  )  )
    {
        cout<<"dir_name is not a valid directory !"<<endl;
        return vector<string>();
    }

    struct dirent * filename;    // return value for readdir()
    DIR * dir;                   // return value for opendir()
    dir = opendir( dir_name  );
    if( NULL == dir  )
    {
        cout<<"Can not open dir "<<dir_name<<endl;
        return vector<string>();
    }
    cout<<"Successfully opened the dir !"<<endl;

    /* read all the files in the dir ~ */
    vector<string> path;
    while( ( filename = readdir(dir)  ) != NULL  )
    {
        /* int len = sizeof(filename->d_name); */
        /* cout << len << endl; */
        /* char *str = filename->d_name + len - 4; */
        /* puts(str); */
        // get rid of "." and ".."
        if( strcmp( filename->d_name , "."  ) == 0 || 
            strcmp( filename->d_name , ".." ) == 0    )
            continue;
        char strpath[100] = {0};
        sprintf(strpath,"%s%s%s",dirr,"/",filename->d_name);
        /* path.push_back(filename->d_name); */
        path.push_back(strpath);
        /* cout<<filename ->d_name <<endl; */
    }

    /* cout << "rss源语料文件名：" << endl; */
    /* for(auto &s : path) */
    /* { */
    /*     cout << s << endl; */
    /* } */

    return path;
} 

/* int main() */
/* { */
/*     // 测试 */
/*     showAllFiles( dir  ); */
/*     return 0; */
/* } */
