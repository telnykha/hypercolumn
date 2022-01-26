/*
    awpmain.c
*/
#define _CRT_SECURE_NO_WARNINGS
#include "../include/awpipl.h"
#include "stdlib.h"

#define CHECK_RESULT  \
	if(res!=AWP_OK){ \
		printf("ERROR CODE:%i", res);\
		exit(-1); \
	}\

#define _CHECK\
	if (k != 8)\
	{\
		printf("invalid draw params = %s\n", argv[idx2]);\
		exit(-1);\
	}\

#define _CHECK2\
	if (k != 6)\
	{\
		printf("invalid draw params = %s\n", argv[idx2]);\
		exit(-1);\
	}\

#define _CHECK3\
	if (k != 9) {\
printf("invalid draw params = %s\n", argv[idx2]);\
exit(-1);\
	}\

#define __GET_IDX__ \
int idx0 = InputKey(argc, argv, "-i");\
int idx1 = InputKey(argc, argv, "-o");\
int idx2 = InputKey(argc, argv, "-p");\
if (idx0 < 2)\
	exit(-1);\
	

int InputKey(int argc, char **argv, const char* key)
{
	int i = 0;
	int result = -1;
	for (i = 2; i < argc; i++)
	{
		if (strcmp(argv[i], key) == 0)
		{
			result = i + 1;
			break;
		}
	}
	if (result < 0)
	{
		printf("cannot find key %s.\n", key);
		exit(-1);
	}
		
	return result;
}


awpImage* __LoadImage(const char* lpFileName)
{
	awpImage* img = NULL;
	if (awpLoadImage(lpFileName, &img) != AWP_OK)
	{
		printf("cannot load image %s\n", lpFileName);
		exit(-1);
	}
	return img;
}

void __SaveImage(const char* lpFileName, awpImage* img)
{
	if (awpSaveImage(lpFileName, img) != AWP_OK)
	{
		printf("cannot save image %s\n", lpFileName);
		exit(-1);
	}
}


void Help(int argc, char **argv)
{
	printf("--help \n");
	printf("--info -i filename\n");
	printf("--flip -i filename -o outfile -p mode [mode = r - right, l - left, v - vertical, h - horizontal]\n");
	printf("--resize -i filename -o outfile -p width:height:mode [mode = r - fast, b - bilinear, n - not in place]\n");
	printf("--rescale -i filename -o outfile -p width:height\n");
	printf("--rotate -i filename -o outfile -p angle:mode [mode = r - fast, b - bilinear]\n");
	printf("--rotatecenter -i filename -o outfile -p angle:x:y\n");
	printf("--calc -i filename -i1 - filename2 -p mode [mode = and,or,xor,add,sub,mlt,div,min,max,avg] -o outfile \n");
	printf("--crop -i filename -o outfile -p left:top:right:bottom\n");
	printf("--filter -p mode [mode = b,bm,s,sm,se,fe,fe1,en,eno,eo,eso,es,esw,ew,enw,pv,ph,sv,sh] -i filename -o outfile\n");
	printf("--contrast -i filename -o outfile -p mode [mode = a - autolevels, h - histogramm equalize]\n");
	printf("--stat -i namefile\n");
	printf("--convert -i filename -o outfile\n");
	printf("--draw -i file name -o outfile -f mode [mode = line,rect,point,cross,ellipse,ellipse2] -p x1:x2:y1:y2:r:g:b:rd \n");
	printf("--blob -p draw_cp:draw_contour:draw_rect:draw_axis:draw_ellipce -i filename -o outfile\n");
	printf("--detect \n");
	printf("--bacrproject \n");
	printf("--camera \n");
}
void Blob(int argc, char** argv)
{
	awpImage* img = NULL;
	AWPBYTE threshold;
	int draw_cp, draw_contour, draw_rect, draw_axis, draw_ellipce;
	int k;
	awpImage* res = NULL;

	__GET_IDX__
		k = sscanf(argv[idx2], "%i:%i:%i:%i:%i", &draw_cp, &draw_contour, &draw_rect, &draw_axis, &draw_ellipce);
	if (k != 5)
	{
		printf("invalid blob params = %s\n", argv[idx2]);
		exit(-1);
	}
	awpImage* dst = NULL;
	img = __LoadImage(argv[idx0]);
	//awpCopyImage(img, &dst);
	awpConvert(img, AWP_CONVERT_3TO1_BYTE);

	AWPINT num = 0;
	awpStrokeObj* strokes = NULL;
	awpCreateImage(&dst, img->sSizeX, img->sSizeY, 3, AWP_BYTE);
	awpGetStrokes(img, &num, &strokes, 128, NULL);
#ifdef _DEBUG 
	printf("Number of binary objects: %i\n", num);
#endif 
	AWPINT square;
	awpContour* c = NULL;
	awpRect r;
	awpRect cross;
	awpPoint p;
	AWPDOUBLE perim = 0;
	FILE * pFile;
	pFile = fopen("c:\\_alt\\_proj\\awpipl2\\file.txt", "w+t");
	for (int i = 0; i < num; i++)
	{
		awpStrObjSquare(&strokes[i], &square);
		memset(&p, 0, sizeof(awpPoint));
		AWPRESULT res = awpGetObjCentroid(img, &strokes[i], &p);
#ifdef _DEBUG
		printf("awpGetObjCentroid result = %i\n", res);
#endif 
		awpCalcObjRect(&strokes[i], &r);
		awpCreateContour(&c, strokes[i].Num * 2, TRUE);
		awpGetObjCountour(&strokes[i], c);
		awpGetContPerim(c, &perim);
		fprintf(pFile,
			"a. %i\nb. X = %i; Y = %i\nc. bottom = %hi; left = %hi; right = %hi; top = %hi\nd. -\ne. direction = %i; num = %i\nf. %f\n",
			square, p.X, p.Y,
			r.bottom, r.left, r.right, r.top,
			c->Direction, c->NumPoints, perim);

		if (draw_cp)
		{
			cross.left = p.X - 4;
			cross.right = p.X + 4;
			cross.bottom = p.Y - 4;
			cross.top = p.Y + 4;

			awpDrawCCross(dst, &cross, 0, 0, 255, 1);
		}
		if (draw_contour)
			awpDrawPolygon(dst, c, 1, 255, 1);
		if (draw_rect)
			awpDrawCRect(dst, &r, 255, 0, 0, 1);
		if (draw_axis)
		{
			AWPDOUBLE theta = 0;
			AWPDOUBLE mi = 0;
			AWPDOUBLE ma = 0;

			awpGetObjOrientation(img, &strokes[i], &theta, &mi, &ma);
			theta += 90;
#ifdef _DEBUG
			printf("theta = %lf\n", theta);
#endif 
			awpDrawCEllipse2(dst, p, ma, mi, theta, 255, 0, 0, 1);
			awpDrawCEllipseCross(dst, p, ma, mi, theta, 255, 0, 0, 1);
		}
	}
	fclose(pFile);
	__SaveImage(argv[idx1], dst);
	_AWP_SAFE_RELEASE_(img);
	_AWP_SAFE_RELEASE_(dst);
	awpFreeContour(&c);
	awpFreeStrokes(num, &strokes);
}
void Convert(int argc, char** argv) {
	awpImage* img = NULL;
	__GET_IDX__
	
		
		img = __LoadImage(argv[idx0]);
	if (strcmp(argv[idx2], "c") == 0) {
		awpConvert(img, AWP_CONVERT_TO_BYTE_WITH_NORM);

	}

	__SaveImage(argv[idx1], img);
	_AWP_SAFE_RELEASE_(img);
}
void Draw(int argc, char** argv) {
	awpImage* img = NULL;
	AWPDOUBLE r = 0, g = 0, b = 0 , angle = 0;
	AWPWORD w= 0, h= 0;
	int rd =1;
	awpRect a;
	int k = 0 , left = 0, top = 0, right = 0, bottom = 0;;
	int idx3 = InputKey(argc, argv, "-f");
	awpPoint p1;
	awpPoint p2;
	__GET_IDX__

		img = __LoadImage(argv[idx0]);
	if (strcmp(argv[idx3], "line") == 0){
		k = sscanf(argv[idx2], "%hi:%hi:%hi:%hi:%lf:%lf:%lf:%i", &p1.X, &p1.Y, &p2.X, &p2.Y, &r, &g, &b, &rd);
			_CHECK
			awpDrawCLine(img, p1, p2, r, g, b, rd);}

	else if (strcmp(argv[idx3], "rect") == 0){
		k = sscanf(argv[idx2], "%i:%i:%i:%i:%lf:%lf:%lf:%i", &left,&top,&bottom,&right,&r, &g, &b, &rd);
			_CHECK
		a.left = left;
		a.bottom = bottom;
		a.right = right;
		a.top = top;
			awpDrawCRect(img, &a, r, g, b, rd);}

	else if (strcmp(argv[idx3], "point") == 0){
		k = sscanf(argv[idx2], "%hi:%hi:%lf:%lf:%lf:%i", &p1.X, &p1.Y, &r, &g, &b, &rd);
			_CHECK2
			awpDrawCPoint(img, p1, r, g, b, rd);}

	else if (strcmp(argv[idx3], "cross") == 0){
		k = sscanf(argv[idx2], "%i:%i:%i:%i:%lf:%lf:%lf:%i", &left, &top, &bottom, &right, &r, &g, &b, &rd);
			_CHECK
		a.left = left;
		a.bottom = bottom;
		a.right = right;
		a.top = top;
			awpDrawCCross(img, &a, r, g, b, rd);}

	else if (strcmp(argv[idx3], "ellipse") == 0) {
		k = sscanf(argv[idx2], "%hi:%hi:%hi:%hi:%lf:%lf:%lf:%lf:%i", &p1.X, &p1.Y, &w, &h, &angle, &r, &g, &b, &rd);
			_CHECK3
			awpDrawCEllipse(img, p1, w, h, angle, r, g, b, rd);}

	else if (strcmp(argv[idx3], "ellipse2") == 0) {
		k = sscanf(argv[idx2], "%hi:%hi:%hi:%hi:%lf:%lf:%lf:%lf:%i", &p1.X, &p1.Y, &w, &h, &angle, &r, &g, &b, &rd);
			_CHECK3
	}

	else{
			printf("unknown draw option %s\n", argv[idx2]);
			exit(-1);}

			__SaveImage(argv[idx1], img);
			_AWP_SAFE_RELEASE_(img);
}
void Calc(int argc,char** argv) {
	awpImage* img = NULL;
	awpImage* img2 = NULL;
	awpImage* img3 = NULL;
	int res = AWP_OK;
	__GET_IDX__
		int idx3 = InputKey(argc, argv, "-i1");
		img = __LoadImage(argv[idx0]);
		img2 = __LoadImage(argv[idx3]);
		if (strcmp(argv[idx2], "and") == 0) {
			res=awpCalcImage(img, img2, &img3, AWP_CALC_ANDIMAGES, AWP_CALC_OUTPLACE);
			CHECK_RESULT
		}
		else if (strcmp(argv[idx2], "or") == 0){
			res=awpCalcImage(img, img2, &img3, AWP_CALC_ORIMAGES, AWP_CALC_OUTPLACE);
			CHECK_RESULT
		}
		else if (strcmp(argv[idx2], "xor") == 0)	{
			res = awpCalcImage(img, img2, &img3, AWP_CALC_XORIMAGES, AWP_CALC_OUTPLACE);
			CHECK_RESULT
		}
		else if (strcmp(argv[idx2], "add") == 0) {
			res = awpCalcImage(img, img2, &img3, AWP_CALC_ADDIMAGES, AWP_CALC_OUTPLACE);
			CHECK_RESULT
		}
		else if (strcmp(argv[idx2], "sub") == 0) {
			res = awpCalcImage(img, img2, &img3, AWP_CALC_SUBIMAGES, AWP_CALC_OUTPLACE);
			CHECK_RESULT
		}
		else if (strcmp(argv[idx2], "mlt") == 0) {
			res = awpCalcImage(img, img2, &img3, AWP_CALC_MLTIMAGES, AWP_CALC_OUTPLACE);
			CHECK_RESULT
		}
		else if (strcmp(argv[idx2], "div") == 0) {
			res = awpCalcImage(img, img2, &img3, AWP_CALC_DIVIMAGES, AWP_CALC_OUTPLACE);
			CHECK_RESULT
		}
		else if (strcmp(argv[idx2], "min") == 0) {
			res = awpCalcImage(img, img2, &img3, AWP_CALC_MINIMAGES, AWP_CALC_OUTPLACE);
			CHECK_RESULT
		}
		else if (strcmp(argv[idx2], "max") == 0) {
			res = awpCalcImage(img, img2, &img3, AWP_CALC_MAXIMAGES, AWP_CALC_OUTPLACE);
			CHECK_RESULT
		}
		else if (strcmp(argv[idx2], "avg") == 0) {
			res = awpCalcImage(img, img2, &img3, AWP_CALC_AVGIMAGES, AWP_CALC_OUTPLACE);
			CHECK_RESULT
		}
		else {
			printf("unknown calc option %s\n", argv[idx2]);
			exit(-1);
		}
		awpConvert(img3, AWP_CONVERT_TO_BYTE_WITH_NORM);
		__SaveImage(argv[idx1], img3);
		_AWP_SAFE_RELEASE_(img3);
}
void Info(int argc, char **argv)
{
	awpImage* img = NULL;
	int idx = InputKey(argc, argv, "-i");
	if (idx < 2)
		exit(-1);
	img = __LoadImage(argv[idx]);
	printf("width = %d\n", img->sSizeX);
	printf("height = %d\n", img->sSizeY);
	printf("channels = %d\n", img->bChannels);
	printf("type = %d\n", img->dwType);
	FILE* f = fopen(argv[idx], "rb");
	if (f != NULL)
	{
		fseek(f, 0, SEEK_END); // seek to end of file 
		long size = ftell(f); // get current file pointer 
		fseek(f, 0, SEEK_SET);
		printf("size = %d\n", size);
		fclose(f);
	}
	else
	{
		printf("cannot open file.\n");
	}
	_AWP_SAFE_RELEASE_(img);
}
void Stat(int argc, char** argv) {
	int idx = InputKey(argc, argv, "-i");
	FILE * stat = fopen("result.txt", "w");
	FILE * ht = fopen("hst.txt", "w");
	awpImage* img = NULL; 
	awpImage* hst = NULL; 
	awpImage* mean = NULL;
	awpImage *median = NULL;
	awpImage *entropy = NULL;
	awpImage *StdDev = NULL;
	AWPDOUBLE *a = NULL;
	AWPDOUBLE *b = NULL;
	int   res = AWP_OK;
	
	img = __LoadImage(argv[idx]);
	double w = (double)img->sSizeX;
	double y = (double)img->sSizeY;

	fprintf(stat,"width = %lf\n",w);
	fprintf(stat, "height = %lf\n", y);

	res=awpGetHst(img, &hst, 0);
	CHECK_RESULT
	double *d = (double*)hst->pPixels;
	for (int i = 0; i < hst->sSizeX; i++){
	for (int g = 0; g < hst->bChannels; g++){
	fprintf(stat, "%lf\t", d[i*hst->bChannels+g + hst->bChannels*hst->sSizeX]);}
	fprintf(stat, "\n");}
	
					
	awpCreateImage(&mean, 1, 1, hst->bChannels, hst->dwType);
	awpCreateImage(&median, 1, 1, hst->bChannels, hst->dwType);
	awpCreateImage(&StdDev, 1, 1, hst->bChannels, hst->dwType);
	awpCreateImage(&entropy, 1, 1, hst->bChannels, hst->dwType);

	res=awpMinMax(img, &a, &b);
	CHECK_RESULT
	fprintf(stat, "min:\t");
	for (int  f = 0; f < img->bChannels; f++){
	fprintf(stat, "ch%i = %lf\t",f,a[f]);}
	fprintf(stat, "\n");
	fprintf(stat, "max:\t");
	for (int f = 0; f < img->bChannels; f++){
	fprintf(stat, "ch%i = %lf\t ",f,b[f]);}
	free(a);
	free(b);

	res=awpGetHstMean(hst, mean);
	CHECK_RESULT
	double *men = (double*)mean->pPixels;
	fprintf(stat, "\n");
	fprintf(stat, "mean:\t");
	for (int h = 0; h<hst->bChannels; h++){
	fprintf(stat, "ch%i = %lf\t", h, men[h]);}
	fprintf(stat, "\n");
	
	res=awpGetMedian(img, median);
	CHECK_RESULT
	double *medin = (double*)median->pPixels;
	fprintf(stat, "median:\t");
	for (int i  = 0; i <hst->bChannels; i++){
	fprintf(stat, "ch%i = %lf\t",i, medin[i]);}
	fprintf(stat, "\n");

	res=awpGetHstStdDev(hst, StdDev);
	CHECK_RESULT
	double *q = (double*)StdDev->pPixels;
	fprintf(stat, "stddev:\t");
	for (int i= 0; i < hst->bChannels; i++){
	fprintf(stat, "ch%i %lf\t",i,q[i]);}
	fprintf(stat, "\n");

	res=awpGetHstEntropy(hst, entropy);
	CHECK_RESULT
	double *ent = (double*)entropy->pPixels; 
	fprintf(stat, "entropy:");
	for (int i = 0; i < hst->bChannels; i++){
	fprintf(stat, "ch%i %lf\t",i, ent[i]);}
	fprintf(stat, "\n");
	
	fclose(stat); 
}


void Flip(int argc, char **argv)
{
	awpImage* img = NULL;
	int res = AWP_OK;

	__GET_IDX__

	img = __LoadImage(argv[idx0]);
	printf("width = %d height = %d\n", img->sSizeX, img->sSizeY);
	if (strcmp(argv[idx2], "r") == 0)
	{
		res = awpFlip(&img, AWP_FLIP_RGHT);
		CHECK_RESULT
	}
	else if (strcmp(argv[idx2], "l") == 0)
	{
		res = awpFlip(&img, AWP_FLIP_LEFT);
		CHECK_RESULT
	}
	else if (strcmp(argv[idx2], "v") == 0)
	{
		res = awpFlip(&img, AWP_FLIP_VERT);
		CHECK_RESULT
	}
	else if (strcmp(argv[idx2], "h") == 0)
	{
		res = awpFlip(&img, AWP_FLIP_HRZT);
		CHECK_RESULT
	}
	else
	{
		printf("unknown flip option %s\n", argv[idx2]);
		exit(-1);
	}

	__SaveImage(argv[idx1], img);
	_AWP_SAFE_RELEASE_(img);
}
void Resize(int argc, char **argv)
{
	awpImage* img = NULL;
	awpImage* imgo = NULL;
	int w;
	int h;
	char key;
	int k,res;
	__GET_IDX__
	k = sscanf(argv[idx2], "%i:%i:%c", &w, &h, &key);
	if (k != 3)
	{
		printf("invalid resize params = %s\n", argv[idx2]);
		exit(-1);
	}
	img = __LoadImage(argv[idx0]);

	if (key == 'r')
	{
		res=awpResize(img, w, h);
		CHECK_RESULT
	}
	else if (key == 'b')
	{
		res=awpResizeBilinear(img, w, h);
		CHECK_RESULT
	}
	else if (key == 'n')
	{
		res=awpResizeNip(img, &imgo, w, h);
		CHECK_RESULT
		_AWP_SAFE_RELEASE_(img);
		img = imgo;
	}
	else
	{
		printf("invalid resize params = %s\n", argv[idx2]);
		exit(-1);
	}

    __SaveImage(argv[idx1], img);
	_AWP_SAFE_RELEASE_(img);
}
void Rescale(int argc, char **argv)
{
	awpImage* img = NULL;
	float w;
	float h;
	int k , res;
	__GET_IDX__
		k = sscanf(argv[idx2], "%f:%f", &w, &h);
	if (k != 2)
	{
		printf("invalid rescale params = %s\n", argv[idx2]);
		exit(-1);
	}
	img = __LoadImage(argv[idx0]);

	res=awpRescale(img, w, h);
	CHECK_RESULT
	__SaveImage(argv[idx1], img);
	_AWP_SAFE_RELEASE_(img);
}
void Rotate(int argc, char **argv)
{
	awpImage* img = NULL;
	int angle;
	char key;
	int k;
	int res;
	__GET_IDX__
		k = sscanf(argv[idx2], "%i:%c", &angle, &key);
	if (k != 2)
	{
		printf("invalid rotate params = %s\n", argv[idx2]);
		exit(-1);
	}
	img = __LoadImage(argv[idx0]);
	if (key == 'r')
	{
		res=awpRotate(img, angle);
		CHECK_RESULT
	}
	else if (key == 'b')
	{
		res=awpRotateBilinear(img, angle);
		CHECK_RESULT
	}
	else
	{
		printf("invalid rotate params = %s\n", argv[idx2]);
		exit(-1);
	}
	__SaveImage(argv[idx1], img);
	_AWP_SAFE_RELEASE_(img);
}
void RotateCenter(int argc, char **argv)
{
	awpImage* img = NULL;
	int angle;
	int x;
	int y;
	int k,res;
	__GET_IDX__
		k = sscanf(argv[idx2], "%i:%i:%i", &angle, &x, &y);
	if (k != 3)
	{
		printf("invalid rotate params = %s\n", argv[idx2]);
		exit(-1);
	}
	img = __LoadImage(argv[idx0]);
		
	res=awpRotateCenter(img, angle, x, y);
	CHECK_RESULT

	__SaveImage(argv[idx1], img);
	_AWP_SAFE_RELEASE_(img);
}

void Crop(int argc, char **argv)
{
	awpImage* img = NULL;
	awpImage* imgo = NULL;
	awpRect* rect = NULL;
	rect = (awpRect*)malloc(sizeof(awpRect));
	int left = 0;// rect->left;
	int top = 0;// rect->top;
	int right = 0;// rect->right;
	int bottom = 0;// rect->bottom;
	int k;
	__GET_IDX__
			k = sscanf(argv[idx2], "%i:%i:%i:%i", &left, &top, &right, &bottom);
		if (k != 4)
		{
			printf("invalid crop params = %s\n", argv[idx2]);
			exit(-1);
		}
	rect->left = left;
	rect->top = top;
	rect->right = right;
	rect->bottom = bottom;
	img = __LoadImage(argv[idx0]);
	if (awpCopyRect(img, &imgo, rect) == AWP_OK)
	{	
		__SaveImage(argv[idx1], imgo);
		_AWP_SAFE_RELEASE_(imgo);
	}
	else
	{
		printf("invalid rect %s\n", argv[idx2]);
		exit(-1);
	}
	free(rect);
	_AWP_SAFE_RELEASE_(img);
}
void Contrast(int argc, char **argv)
{
	awpImage* img = NULL;
	__GET_IDX__

	img = __LoadImage(argv[idx0]);
	if (strcmp(argv[idx2], "a") == 0)
	{
		AWPRESULT res = AWP_OK;
		res = awpAutoLevels(img);
		CHECK_RESULT
	}
	else if (strcmp(argv[idx2], "h") == 0)
	{
		AWPRESULT res = AWP_OK;
		res = awpHistogrammEqualize(img);
		CHECK_RESULT
	}
	else
	{
		printf("unknown contrast option %s\n", argv[idx2]);
		exit(-1);
	}
	__SaveImage(argv[idx1], img);
	_AWP_SAFE_RELEASE_(img);
}
void Filter(int argc, char **argv)
{
	int res;
	awpImage* img = NULL;
	awpImage* dst = NULL;
	__GET_IDX__

		img = __LoadImage(argv[idx0]);
	awpCopyImage(img, &dst);
	if (strcmp(argv[idx2], "b") == 0)
	{
		res=awpFilter(img, dst, AWP_BLUR);
		CHECK_RESULT
	}
	else if (strcmp(argv[idx2], "bm") == 0)
	{
		res=awpFilter(img, dst, AWP_BLUR_MORE);
		CHECK_RESULT
	}
	else if (strcmp(argv[idx2], "s") == 0)
	{
		res=awpFilter(img, dst, AWP_SHARPEN);
		CHECK_RESULT
	}
	else if (strcmp(argv[idx2], "sm") == 0)
	{
		res=awpFilter(img, dst, AWP_SHARPEN_MORE);
		CHECK_RESULT
	}
	else if (strcmp(argv[idx2], "se") == 0)
	{
		res=awpFilter(img, dst, AWP_SHARPEN_EDGES);
		CHECK_RESULT
	}
	else if (strcmp(argv[idx2], "fe") == 0)
	{
		res=awpFilter(img, dst, AWP_FIND_EDGES);
		CHECK_RESULT
	}
	else if (strcmp(argv[idx2], "fe1") == 0)
	{
		res=awpFilter(img, dst, AWP_FIND_EDGES1);
		CHECK_RESULT
	}
	else if (strcmp(argv[idx2], "en") == 0)
	{
		res=awpFilter(img, dst, AWP_EMBOSS_NORTH);
		CHECK_RESULT
	}
	else if (strcmp(argv[idx2], "eno") == 0)
	{
		res=awpFilter(img, dst, AWP_EMBOSS_NORTH_OST);
		CHECK_RESULT
	}
	else if (strcmp(argv[idx2], "eo") == 0)
	{
		res=awpFilter(img, dst, AWP_EMBOSS_OST);
		CHECK_RESULT
	}
	else if (strcmp(argv[idx2], "eso") == 0)
	{
		res=awpFilter(img, dst, AWP_EMBOSS_SOUTH_OST);
		CHECK_RESULT
	}
	else if (strcmp(argv[idx2], "es") == 0)
	{
		res=awpFilter(img, dst, AWP_EMBOSS_SOUTH);
		CHECK_RESULT
	}
	else if (strcmp(argv[idx2], "esw") == 0)
	{
		res=awpFilter(img, dst, AWP_EMBOSS_SOUTH_WEST);
		CHECK_RESULT
	}
	else if (strcmp(argv[idx2], "ew") == 0)
	{
		res=awpFilter(img, dst, AWP_EMBOSS_WEST);
		CHECK_RESULT
	}
	else if (strcmp(argv[idx2], "enw") == 0)
	{
		res=awpFilter(img, dst, AWP_EMBOSS_NORTH_WEST);
		CHECK_RESULT
	}
	else if (strcmp(argv[idx2], "pv") == 0)
	{
		res=awpFilter(img, dst, AWP_PREWITT_V);
		CHECK_RESULT
	}
	else if (strcmp(argv[idx2], "ph") == 0)
	{
		res=awpFilter(img, dst, AWP_PREWITT_H);
		CHECK_RESULT
	}
	else if (strcmp(argv[idx2], "sv") == 0)
	{
		res=awpFilter(img, dst, AWP_SOBEL_V);
		CHECK_RESULT
	}
	else if (strcmp(argv[idx2], "sh") == 0)
	{
		res=awpFilter(img, dst, AWP_SOBEL_H);
		CHECK_RESULT
	}
	else
	{
		printf("unknown filter option %s\n", argv[idx2]);
		exit(-1);
	}
	__SaveImage(argv[idx1], dst);
	_AWP_SAFE_RELEASE_(img);
	_AWP_SAFE_RELEASE_(dst);
}
int main (int argc, char **argv)
{
  int i = 0;
  if (argc < 2)
  {
	  return -1;
  }
   char* arg1 = argv[1];
   if (strcmp(arg1, "--help") == 0)
   {
	   Help(argc, argv);
   }
   else if (strcmp(arg1, "--info") == 0)
   {
	   Info(argc, argv);
   }
   else if (strcmp(arg1, "--flip") == 0)
   {
	   Flip(argc, argv);
   }
   else if (strcmp(arg1, "--resize") == 0)
   {
	   Resize(argc, argv);
   }
   else if (strcmp(arg1, "--rescale") == 0)
   {
	   Rescale(argc, argv);
   }
   else if (strcmp(arg1, "--rotate") == 0)
   {
	   Rotate(argc, argv);
   }
   else if (strcmp(arg1, "--rotatecenter") == 0)
   {
	   RotateCenter(argc, argv);
   }
   else if (strcmp(arg1, "--calc") == 0)
   {
	   Calc(argc, argv);
   }
   else if (strcmp(arg1, "--crop") == 0)
   {
	   Crop(argc, argv);
   }
   else if (strcmp(arg1, "--filter") == 0)
   {
	   Filter(argc, argv);
   }
   else if (strcmp(arg1, "--contrast") == 0)
   {
	   Contrast(argc, argv);
   }
   else if (strcmp(arg1, "--stat") == 0)
   {
	   Stat(argc, argv);
   }
   else if (strcmp(arg1, "--convert") == 0)
   {
	   Convert(argc, argv);
   }
   else if (strcmp(arg1, "--draw") == 0)
   {
	   Draw(argc, argv);
   }
   else if (strcmp(arg1, "--blob") == 0)
   {
	   Blob(argc, argv);
	   // Binary objects analysis 
   }
   else if (strcmp(arg1, "--detect") == 0)
   {
	   // object detection 
   }
   else if (strcmp(arg1, "--backproject") == 0)
   {
	   // 
   }
   else if (strcmp(arg1, "--camera") == 0)
   {
	   // 
   }
   return 0;
}