//---------------------------------------------------------------------------

#pragma hdrstop

//---------------------------------------------------------------------------

#pragma argsused
#include <string>
#include <iostream>
#include <stdio.h>
#include <dir.h>
#include "awpipl.h"
#include "fvlcore.h"

#pragma link "awpipl2b.lib"
#pragma link "FVLCB.lib"
#pragma link "awplflibb.lib"
#pragma link "JPEGLIB.lib"

using namespace std;
void usage(){
    printf( "Usage: create_tmpl [-n number of eigenvectors] [-r new_image_width new_image_hight ] from_directory to_tmpl_filename\n" );
}

int main(int argc, char* argv[])
{
    int numVect = 0;
    AWPWORD newImageHight = 56;
    AWPWORD newImageWidth = 46;
    struct ffblk filesInfo;
    int numFiles = 0;
    FvcTemplate* pTemplate = NULL;
    char* dirName;
    char* tmplFileName;
    if( argc < 3 || argc > 8 || argc == 4 || argc == 7 ){
        usage();
        return -1;
    }
    else if( argc == 5 && !strcmp( argv[1], "-n" ) ){
        sscanf( argv[2], "%d", &numVect );
        dirName = argv[3];
        tmplFileName = argv[4];
    }
    else if( argc == 6 && !strcmp( argv[1], "-r" ) ){
        sscanf( argv[2], "%hu", &newImageWidth );
        sscanf( argv[3], "%hu", &newImageHight );
        dirName = argv[4];
        tmplFileName = argv[5];
    }
    else if( argc == 8 && !strcmp( argv[1], "-n" ) && !strcmp( argv[3], "-r" ) ){
        sscanf( argv[2], "%d", &numVect );
        sscanf( argv[4], "%hu", &newImageWidth );
        sscanf( argv[5], "%hu", &newImageHight );
        dirName = argv[6];
        tmplFileName = argv[7];
    }
    else if( argc == 3 ){
        dirName = argv[1];
        tmplFileName = argv[2];
    }
    else{
        usage();
        return -1;
    }
    string path( dirName );
    path = path + "\\*.awp";
    for (int done = findfirst( path.c_str(), &filesInfo, 0 ); !done; done = findnext(&filesInfo))
        numFiles++;
    if( !numFiles ){
        cout << "Files not found" << endl;
        return -1;
    }
    awpImage** sourceImages = new awpImage* [numFiles];
    findfirst( path.c_str(), &filesInfo, 0 );
    string fileName;
    for( int i=0; i<numFiles; i++  ){
        cout << filesInfo.ff_name << endl;
        fileName = "";
        fileName.append( dirName );
        fileName += "\\";
        fileName.append( filesInfo.ff_name );
        AWPRESULT load_res = awpLoadImage( fileName.c_str(), &sourceImages[i] );
//        awpConvert(sourceImages[i], AWP_CONVERT_TO_FLOAT);
        if( load_res )
            cout << load_res;
        if( newImageHight != 56 && newImageWidth != 46){
            AWPRESULT resize_res = awpResize( sourceImages[i], newImageWidth, newImageHight );
            cout << resize_res;
//            AWPRESULT save_res = awpSaveImage( fileName.c_str(), sourceImages[i] );
        }
        findnext( &filesInfo );
    }
    int create_res = fvcCreateTemplate( &pTemplate, newImageWidth, newImageHight, numFiles, true );
    if( create_res != FVC_OK )
        cout << create_res;
    int build_res = fvcBuildTemplate(sourceImages, numFiles, pTemplate);
    if( build_res )
            cout << build_res;
    if( numVect )
        fvcResampleTemplate( pTemplate, numVect );
    int save_res = fvcSaveTemplate( tmplFileName, pTemplate );
    if( save_res )
        cout << save_res;
    int n;
    string str( tmplFileName );
    n = str.rfind( '.', str.length()-1 );
    char * imageName = new char[ n+10 ];
    memcpy( imageName, str.c_str(), n+1 );
    memcpy( imageName+n+1, "jpg\0", 4 );
    int saveIm_res = fvcSaveTemplateAsImage( imageName, pTemplate );
    if( saveIm_res )
        cout << saveIm_res;
    for( int j = 0; j < numFiles; j++ )
    {
        if( sourceImages[j] != NULL )
            awpReleaseImage( &sourceImages[j] );
    }
    fvcFreeTemplate( &pTemplate );
    delete[] sourceImages;
    delete[] imageName;
    return 0;
}
//---------------------------------------------------------------------------
