//	g++ -Wall -O2 -L/usr/X11R6/lib -lm -lpthread -lX11
//	g++ cluster.cpp -o cluster.exe -Wall -O2 -L/usr/X11R6/lib -lm -lpthread -lX11 ; ./cluster.exe -DD_T=2.e-0 -DMAX_T=2.e2
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <cstring>

#define yaoCImg

#ifdef yaoCImg
#include "CImg.h"
using namespace cimg_library;
#endif

/***********************************	类型声明定义	*************************************/
//	粒子密度：d	格点网络大小：L*L  粒子数目：N=L*L*d	leader比例：yita
#ifndef L
#define L	193
#endif
#ifndef d
#define d	0.3
#endif

const int	LL = L * L, N = static_cast<int>(LL * d + 0.5);
double	g = 1., v0 = 100.;	//	速度转移概率系数g   位置转移概率系数v0
unsigned	seed = 0;	//	随机数种子
double	MAX_T = 2.e1, D_T = 2.e-1;
double	yita = 0.;

//	方向
const int	EMPTY = 00, UP = 01, LEFT = 02, RIGHT = 03, DOWN = 04, DIR_SIZE = 5;
inline int R_DIR(const int dir)
{
	return 5-dir;
}
const char	EMPTY_CHAR = '.', UP_CHAR = '^', DOWN_CHAR = 'v', LEFT_CHAR = '<', RIGHT_CHAR = '>';
const char	dirOut[DIR_SIZE] = {EMPTY_CHAR, UP_CHAR, LEFT_CHAR, RIGHT_CHAR, DOWN_CHAR};

//	位置类
class Pos
{
public:
	int	x, y;
	Pos& move(const int dir);
	Pos& print(void);
};
const int	LEnd = L - 1;
Pos& Pos::move(const int dir)
{
	switch(dir) {
	case UP:
		if(x > 0)	--x;
		else	x = LEnd;
		break;
	case DOWN:
		if(x < LEnd)	++x;
		else	x = 0;
		break;
	case LEFT:
		if(y > 0)	--y;
		else	y = LEnd;
		break;
	case RIGHT:
		if(y < LEnd)	++y;
		else	y = 0;
		break;
	case EMPTY:
	default:
		break;
	}
	return *this;
}
Pos& Pos::print(void)
{
	printf("( %3d , %3d )", x, y);
	return *this;
}

//  粒子类
class Par
{
public:
	//	位置pos	方向dir	能否移动moveFlag	邻居方向在各维度的数目dup,dlr
	//	按变化概率处于状态sta[staId][staId2],sta[STA_SIZE-1][staMvId]	转移概率pt:{EMPTY,UP,LEFT,RIGHT,DOWN}
	Pos	pos;
	int	dir;
	bool	moveFlag;
	int	dud, dlr;
	int	staId, staId2, staMvId;
} ;
extern Par par[N+1];	//	给粒子从1开始编号至N(0号不用)，数组par[N+1]保存粒子参数


/***********************************	函数声明、全局变量定义	*************************************/

//	功能函数模块声明

void ptPrint(void);	//	输出各状态对应概率
void latDirPrint(void);	//	输出网格格点粒子方向
#ifdef yaoCImg
void latDirImg(void);	//	输出网格格点粒子方向
#endif
void latParPrint(void);	//	输出网格格点粒子编号
void parPrint(void);	//	输出所有粒子状态
void staPrint(void);	//	按状态输出所有粒子编号
void saveData(char path[], char count[]);	//	保存数据

void MainInit(int argc, char* argv[]);		//	系统初始化
void MainExit(void);	//	结束程序，系统回收资源
void parInit(void);	//	生成所有粒子
void parRand(int *const pNum, int *const pDir, double *const tao);	//	返回随机的改变状态的粒子编号及方向
void parTran(const int num, const int dir);	//	粒子变方向或位置
void staUpdate(const int num);			//	更新编号为num粒子的概率队列状态


//	全局变量定义

int	lat[L][L];	//	各格点状态lat[L][L]:占据的粒子编号，0为空
Par	par[N+1];	//	给粒子从1开始编号至N(0号不用)，数组par[1..N]保存粒子参数
int	N0, dirNum[DIR_SIZE] = {0};	//	N0：leader数目	dirNum粒子在各方向的数目

//	用sta[stId][N+1]数组保存各种类粒子的编号,sta[*][0]为长度,sta[0]为移动概率
#define STA_SIZE	16
#define STA_MOVE	(STA_SIZE-1)
#define STA_NULL	(-1)
#define STA_SIZE2	(N+1)
int	sta[STA_SIZE][STA_SIZE2];	//	sta：按状态用队列保存粒子编号
#define STA_DIR_SIZE (2*DIR_SIZE-1)
double	pt[STA_SIZE], ptDir[STA_DIR_SIZE][STA_DIR_SIZE][DIR_SIZE];	//	按各粒子总概率pt可分为staSize种粒子，相应概率为pt	prDir[ud][lr][toDir]
int	ptId[DIR_SIZE][DIR_SIZE];	//	对应状态编号为ptId[ud][lr]
double	staPtSum[STA_SIZE];		//	各状态粒子的概率和

char	dirName[128] = "", fileName[128] = "", logName[128] = "";
FILE	*fpLog;
double	t = 0.;
long long unsigned	tCount = 0, moveCount = 0, tCountD, moveCountD;	//	移动的次数

#ifdef yaoCImg
CImg<unsigned char>	img(L,L,1,3);
#ifdef yaoDisplay
static CImgDisplay	main_window(img,"Dir");
#endif
unsigned char	white[] = {255,255,255}, black[] = {0,0,0};
unsigned char	red[] = {255,0,0}, green[] = {0,255,0}, blue[] = {0,0,255}, yellow[] = {255,255,0};
unsigned char	*color[DIR_SIZE] = {white, red, green, blue, yellow}, *colorLeader[DIR_SIZE] = {white, red, green, blue, yellow};
#endif

/***********************************	功能函数模块定义	*************************************/

//	输出各状态对应概率
void ptPrint(void)
{
	double	*p = pt;
	int	i;
	printf("pt	size:	%d\n", STA_SIZE);
	printf("No.	pt\n");
	for(i = 0;	i < STA_SIZE;	++i) {
		printf("%d	%lf\n", i, *p++);
	}
	return;
}

//	输出网格格点粒子方向
void latDirPrint(void)
{
	int	(*p1)[L] = lat, *p2, i, j;
	printf("lat::dir	size:	%d\nNo.	dir\n", L);
	for(i = 0;	i < L;	++i, ++p1) {
		printf("%d\t", i);
		for(p2 = *p1, j = 0;	j < L;	++j)
			printf("%c", dirOut[par[*p2++].dir]);
		printf("\n");
	}
	return;
}
#ifdef yaoCImg
void latDirImg(void)
{
	int	i;
	Par	*pPar;
	img.fill(255);
	for(i = 1, pPar = par + i;	i <= N0;	++i)
		img.draw_point(pPar->pos.y, pPar->pos.x, colorLeader[pPar++->dir]);
	for(;	i <= N;	++i)
		img.draw_point(pPar->pos.y, pPar->pos.x, color[pPar++->dir]);
	#ifdef yaoDisplay
	img.display(main_window);
	#endif
	return;
}
#endif

//	输出网格格点粒子编号
void latParPrint(void)
{
	int		(*p1)[L] = lat, *p2, i, j;
	printf("lat::ParNo.	size:	%d\nNo.	parId\n", L);
	for(j = 0;	j < L;	++j)
		printf("\t%d", j);
	printf("\n");
	for(i = 0;	i < L;	++i, ++p1) {
		printf("%d", i);
		for(p2 = *p1, j = 0;	j < L;	++j,++p2)
			printf("\t%4d %c", *p2, dirOut[par[*p2].dir]);
		printf("\n");
	}
	return;
}

//	输出所有粒子状态
void parPrint(void)
{
	Par	*p = par + 1;
	int i;
	double	*pp;
	printf("par	size:	%d\n", N);
	printf("No.	pos:x,y	  dir	mvFlg	staMvId	dud	dlr	staId	staId2	pt %c	pt %c	pt %c	pt %c\n",
	       dirOut[1], dirOut[2], dirOut[3], dirOut[4]);
	for(i = 1;	i <= N;	++i, ++p) {
		pp = ptDir[p->dud+DIR_SIZE-1][p->dlr+DIR_SIZE-1];
		printf("%d	%3d,%3d	  %c	%d	%d	%d	%d	%d	%d	%6.2lf	%6.2lf	%6.2lf	%6.2lf\n", i, p->pos.x, p->pos.y, dirOut[p->dir],
		       p->moveFlag, p->staMvId, p->dud, p->dlr, p->staId, p->staId2, pp[1], pp[2], pp[3], pp[4]);
	}
	return;
}

//	按状态输出所有粒子编号
void staPrint(void)
{
	int	(*p1)[1+N] = sta, *p2, i, j;
	printf("sta	size:	%d\n", STA_SIZE);
	printf("No.	pt	size	parId\n");
	for(i = 0;	i < STA_SIZE;	++i, ++p1) {
		printf("%d	%6.2lf	%d\t", i, pt[i], **p1);
		for(p2 = *p1, j = 0;	j < **p1;	++j)
			printf(" %-3d", *++p2);
		printf("\n");
	}
	return;
}

//	保存数据
void saveData(char path[], char name[])
{
	double	m, mMove;	//	序参量: m = | Sum(vi) | / N	移动率mMove
	if(tCountD > 0)
                mMove = static_cast<double>(moveCountD) / tCountD;
        else
                mMove = 0.;
        m = sqrt((dirNum[UP] - dirNum[DOWN]) * (dirNum[UP] - dirNum[DOWN]) + (dirNum[LEFT] - dirNum[RIGHT]) * (dirNum[LEFT] - dirNum[RIGHT])) / N;
        printf("%g	%g	%g	%llu	%llu	%d	%d	%d	%d\n", t, m, mMove, tCount, moveCount, dirNum[UP], dirNum[LEFT], dirNum[RIGHT], dirNum[DOWN]);
        if(fpLog != NULL)
                fprintf(fpLog, "%g	%g	%g	%llu	%llu	%d	%d	%d	%d\n", t, m, mMove, tCount, moveCount, dirNum[UP], dirNum[LEFT], dirNum[RIGHT], dirNum[DOWN]);
        sprintf(fileName, "%s%g", "t_", t);

#ifdef yaoCImg
	latDirImg();
	char	imgName[128] = "";
	sprintf(imgName, "%s/%s%s", path, name, ".bmp");
	img.save(imgName);
#endif
	char	files[DIR_SIZE][128] = {""};
	FILE	*fps[DIR_SIZE];
	sprintf(files[UP],	"%s/%s%s", path, name, "_UP.dat");
	sprintf(files[LEFT],	"%s/%s%s", path, name, "_LEFT.dat");
	sprintf(files[RIGHT],	"%s/%s%s", path, name, "_RIGHT.dat");
	sprintf(files[DOWN],	"%s/%s%s", path, name, "_DOWN.dat");
	fps[UP]		= fopen(files[UP],	"w");
	fps[LEFT]	= fopen(files[LEFT],	"w");
	fps[RIGHT]	= fopen(files[RIGHT],	"w");
	fps[DOWN]	= fopen(files[DOWN],	"w");
	if(fps[UP] == NULL || fps[LEFT] == NULL || fps[RIGHT] == NULL || fps[DOWN] == NULL) {
		printf("Couldn't open data files!\n");
		if(fpLog != NULL)
			fprintf(fpLog, "Couldn't open data files!\n");
	} else {
		fprintf(fps[UP],	"x	UP	No.\n");
		fprintf(fps[LEFT],	"x	LEFT	No.\n");
		fprintf(fps[RIGHT],	"x	RIGHT	No.\n");
		fprintf(fps[DOWN],	"x	DOWN	No.\n");
		Par	*pPar = par + 1;
		for(int i = 1;	i <= N;	++i,++pPar) {
			fprintf(fps[pPar->dir], "%d	%d	%d\n", pPar->pos.x, pPar->pos.y, i);
		}
	}
	if(fps[UP] != NULL)	fclose(fps[UP]);
	if(fps[LEFT] != NULL)	fclose(fps[LEFT]);
	if(fps[RIGHT] != NULL)	fclose(fps[RIGHT]);
	if(fps[DOWN] != NULL)	fclose(fps[DOWN]);

	return;
}

//	系统初始化
void MainInit(int argc, char* argv[])
{
	int	i, j;

	for(i = 1;	i < argc;	++i) {
		if(0 == strcmp(argv[i], "--help") || 0 == strcmp(argv[i], "-help") || 0 == strcmp(argv[i], "--h") || 0 == strcmp(argv[i], "-h")) {
			printf("%s\n", argv[0]);
			printf("%s\n", "options usage:	[-option arg]	or	[--option arg]");
			printf("	-seed	unsigned((0,%u], %u)\n", RAND_MAX, seed);
			printf("	-yita	double([0., 1.], %g)\n", yita);
			printf("	-MAX_T	double([0.,inf), %g)\n", MAX_T);
			printf("	-D_T	double((0.,inf), %g)\n", D_T);
			printf("	-v0	double([0.,inf), %g)\n", v0);
			printf("	-g	double((-inf,inf), %g)\n", g);
			MainExit();
			exit(0);
		} else if(0 == strcmp(argv[i], "--yita") || 0 == strcmp(argv[i], "-yita")) {
			sscanf(argv[++i], "%lf", &yita);
			if(yita < 0.)	yita = 0.;
			else if(yita > 1.)	yita = 1.;
		} else if(0 == strcmp(argv[i], "--MAX_T") || 0 == strcmp(argv[i], "-MAX_T")) {
			sscanf(argv[++i], "%lf", &MAX_T);
			if(MAX_T < 0.)	MAX_T = 0.;
		} else if(0 == strcmp(argv[i], "--D_T") || 0 == strcmp(argv[i], "-D_T")) {
			sscanf(argv[++i], "%lf", &D_T);
			if(D_T <= 0.)	D_T = 1.;
		} else if(0 == strcmp(argv[i], "--seed") || 0 == strcmp(argv[i], "-seed")) {
			sscanf(argv[++i], "%u", &seed);
			if(seed <= 0)	seed = 1;
		} else if(0 == strcmp(argv[i], "--g") || 0 == strcmp(argv[i], "-g")) {
			sscanf(argv[++i], "%lf", &g);
		} else if(0 == strcmp(argv[i], "--v0") || 0 == strcmp(argv[i], "-v0")) {
			sscanf(argv[++i], "%lf", &v0);
			if(v0 < 0)	v0 = 0.;
		}
	}
	N0 = static_cast<int>(N * yita + 0.5);

	if(seed <= 0)	 seed = (unsigned) time(NULL);
	srand(seed);

	for(i = 0;	i < L;	++i) {
		for(j = 0;	j < L;	++j)
			lat[i][j] = 0;
	}

	par[0].dir = EMPTY;
	par[0].dud = par[0].dlr = 0;
	par[0].moveFlag = false;
	par[0].pos.x = par[0].pos.y = -1;
	par[0].staId = STA_NULL;
	par[0].staId2 = 0;
	par[0].staMvId = 0;

	int	num;
	num = 0;
	for(i = 0;	i < DIR_SIZE;	++i) {
		for(j = 0;	j < DIR_SIZE - i;	++j) {
			ptId[i][j] = num;
			pt[num] = exp(i * g) + exp(-i * g) + exp(j * g) + exp(-j * g);
			++num;
		}
	}
	pt[STA_MOVE] = v0;

	double	*p;
	int	ud, lr;
	for(i = 0;	i < STA_DIR_SIZE;	++i) {
		ud = i - (DIR_SIZE - 1);
		for(j = 0;	j < STA_DIR_SIZE;	++j) {
			lr = j - (DIR_SIZE - 1);
			p = ptDir[i][j];
			p[UP] = exp(g * ud);
			p[DOWN] = exp(-g * ud);
			p[LEFT] = exp(g * lr);
			p[RIGHT] = exp(-g * lr);
		}
	}

	for(i = 0;	i < STA_SIZE;	++i)
		sta[i][0] = 0;

	char	cmdName[128] = "";
	sprintf(dirName, "./data/L_%d_d_%g_N_%d_N0_%d_g_%g_seed_%u", L, d, N, N0, g, seed);
	sprintf(cmdName, "mkdir %s", dirName);
	std::system(cmdName);
	sprintf(logName, "%s%s", dirName, ".log");
	if((fpLog	= fopen(logName, "w")) == NULL)
		printf("Couldn't open logfile : %s\n", logName);
	printf("L=%d	LL=%d	d=%g	N=%d	N0=%d	g=%g	seed=%u\ndirname : %s\n", L, LL, d, N, N0, g, seed, dirName);
	printf("t	m	mMove	tCount	moveCount	UP	LEFT	RIGHT	DOWN\n");
	if(fpLog != NULL)
		fprintf(fpLog, "L=%d	LL=%d	d=%g	N=%d	N0=%d	g=%g	seed=%u\ndirname : %s\n%s\n",
			 L, LL, d, N, N0, g, seed, dirName,
			 "t	m	mMove	tCount	moveCount	UP	LEFT	RIGHT	DOWN\n");

	return;
}
void MainExit(void)
{
	if(fpLog != NULL)
		fclose(fpLog);
	return;
}

//  生成所有粒子
void parInit(void)
{
	int	ll = LL, iRandNum, i, r, randNum[LL], *pRandNum = randNum, num;
	Par	*pPar;
	int	dir;
	Pos	pos;
	for(i = 0;	i < LL;	++i)
		*pRandNum++ = i;
	for(i = 1, pPar = par + i;	i <= N;	++i, ++pPar) {
		r = rand() % ll;
		iRandNum = randNum[r];
		randNum[r] = randNum[--ll];
		randNum[ll] = iRandNum;
		pPar->pos.x = iRandNum / L;
		pPar->pos.y = iRandNum % L;
		pPar->dir = rand() % (DIR_SIZE - 1) + 1;
		pPar->moveFlag = false;
		pPar->staId = STA_NULL;
		pPar->dud = pPar->dlr = 0;
		lat[pPar->pos.x][pPar->pos.y] = i;
		++dirNum[pPar->dir];
	}

	for(i = 1, pPar = par + i;	i <= N;	++i, ++pPar) {
		for(dir = 1;	dir < DIR_SIZE;	++dir) {
			pos = pPar->pos;
			pos.move(dir);
			if((num = lat[pos.x][pos.y])) {
				switch(par[num].dir) {
				case UP:
					++pPar->dud;
					break;
				case DOWN:
					--pPar->dud;
					break;
				case LEFT:
					++pPar->dlr;
					break;
				case RIGHT:
					--pPar->dlr;
					break;
				}
			}
		}
	}

	for(i = 1;	i <= N;	++i)
		staUpdate(i);
	return;
}

//	按概率计算粒子状态
void staUpdate(const int num)
{
	Par	*pPar = par + num;
	int	num2;
	Pos	p;
	if(num <= 0)	return;

	if(pPar->moveFlag) {
		num2 = sta[STA_MOVE][pPar->staMvId] = sta[STA_MOVE][sta[STA_MOVE][0]--];
		par[num2].staMvId = pPar->staMvId;
	}

	p = pPar->pos;
	p.move(pPar->dir);
	if((pPar->moveFlag = (lat[p.x][p.y] == 0)))
		sta[STA_MOVE][pPar->staMvId = ++sta[STA_MOVE][0]] = num;

	if(num <= N0) {
		return;
	}

	if(pPar->staId != STA_NULL) {
		num2 = sta[pPar->staId][pPar->staId2] = sta[pPar->staId][sta[pPar->staId][0]--];
		par[num2].staId2 = pPar->staId2;
	}

	pPar->staId = ptId[abs(pPar->dud)][abs(pPar->dlr)];
	sta[pPar->staId][pPar->staId2 = ++sta[pPar->staId][0]] = num;

	return;
}

//	返回随机的改变状态的粒子编号及方向
void  parRand(int *const pNum, int *const pDir, double *const tao)
{
	double	r, *p = staPtSum, *ppt = pt;
	int	head, tail, mid, num, (*psta)[STA_SIZE2] = sta;
	*p = *ppt++ * **psta++;
	for (int i = 1;	i < STA_SIZE;	++i,++p)
		p[1] = *p + *ppt++ * **psta++;
	*tao = log(static_cast<double>(RAND_MAX) / rand()) / staPtSum[STA_SIZE-1];
	do {
		head = 0;
		tail = STA_SIZE-1;
		r = staPtSum[STA_SIZE-1] * rand() / RAND_MAX;
		while(head < tail) {
			mid = (head + tail) >> 1;
			if( r > staPtSum[mid] )
				head = mid + 1;
			else
				tail = mid;
		}
	} while(sta[head][0] == 0);
	if(head)	r -= staPtSum[head-1];
	num = (int)(r / pt[head]) + 1;
	if(num > sta[head][0])	num = sta[head][0];
	else if(num <= 0)	num = 1;
	r -= (num - 1) * pt[head];
	*pNum = sta[head][num];

	if(head == STA_MOVE) {
		*pDir = EMPTY;
		return;
	}

	Par	*pPar = par + *pNum;
	p = ptDir[DIR_SIZE-1+pPar->dud][DIR_SIZE-1+pPar->dlr] + 1;
	for ( *pDir = 1;	*pDir < DIR_SIZE - 1;	++*pDir) {
		if(r > *p)
			r -= *p++;
		else
			break;
	}

	return;
}

//	粒子变方向或位置
void parTran(const int num, const int dir)
{
	Pos	pos;
	Par	*pPar = par + num;
	int	iDir, num2, dud, dlr;
	if(pPar->dir == dir)
		return;
	if(dir) {
		//	改变方向
		dud = dlr = 0;
		switch(pPar->dir) {
		case UP:
			--dud;
			break;
		case DOWN:
			++dud;
			break;
		case LEFT:
			--dlr;
			break;
		case RIGHT:
			++dlr;
			break;
		}
		--dirNum[pPar->dir];
		switch(pPar->dir = dir) {
		case UP:
			++dud;
			break;
		case DOWN:
			--dud;
			break;
		case LEFT:
			++dlr;
			break;
		case RIGHT:
			--dlr;
			break;
		}
		++dirNum[pPar->dir];
		for(iDir = 1;	iDir < DIR_SIZE;	++iDir) {
			pos = pPar->pos;
			pos.move(iDir);
			if((num2 = lat[pos.x][pos.y])) {
				par[num2].dud += dud;
				par[num2].dlr += dlr;
				staUpdate(num2);
			}
		}
		staUpdate(num);
	} else {
		//	移动
		lat[pPar->pos.x][pPar->pos.y] = 0;
		dud = dlr = 0;
		switch(pPar->dir) {
		case UP:
			--dud;
			break;
		case DOWN:
			++dud;
			break;
		case LEFT:
			--dlr;
			break;
		case RIGHT:
			++dlr;
			break;
		}
		for(iDir = 1;	iDir < DIR_SIZE;	++iDir) {
			pos = pPar->pos;
			pos.move(iDir);
			if((num2 = lat[pos.x][pos.y])) {
				par[num2].dud += dud;
				par[num2].dlr += dlr;
				staUpdate(num2);
			}
		}

		pPar->pos.move(pPar->dir);
		++moveCountD;
		lat[pPar->pos.x][pPar->pos.y] = num;
		dud = -dud;
		dlr = -dlr;
		pPar->dud = pPar->dlr = 0;
		for(iDir = 1;	iDir < DIR_SIZE;	++iDir) {
			pos = pPar->pos;
			pos.move(iDir);
			if((num2 = lat[pos.x][pos.y])) {
				par[num2].dud += dud;
				par[num2].dlr += dlr;
				staUpdate(num2);
				switch(par[num2].dir) {
				case UP:
					++pPar->dud;
					break;
				case DOWN:
					--pPar->dud;
					break;
				case LEFT:
					++pPar->dlr;
					break;
				case RIGHT:
					--pPar->dlr;
					break;
				}
			}
		}
		staUpdate(num);
	}

	return;
}

/***********************************	主函数	*************************************/
int main(int argc, char* argv[])
{

	//	系统初始化
	MainInit(argc, argv);


	//  生成所有粒子
	parInit();
#ifdef yaoCImg
	latDirImg();
#endif

	//  开始迭代、输出结果
	double	tao, time;
	int	num, dir;
	for(time = 0., tCountD = 0, moveCountD = 0;	time <= MAX_T;	time += D_T) {
		for(;	t < time;) {
			++tCountD;
			parRand(&num, &dir, &tao);
			parTran(num, dir);
			t += tao;
		}
		tCount += tCountD;
		moveCount += moveCountD;
		saveData(dirName, fileName);
	}

	//	结束
	MainExit();
	return 0;
}
/************************************************************************/
