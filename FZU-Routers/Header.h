#pragma warning(disable: 4786)

#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <VECTOR>
#include <SET>
#include <MAP>
#include <utility> //pair
#include <QUEUE>
#include <string>
using namespace std;

/*#define INPUT_FILE "1.txt"
#define OUTPUT_FILE "std_1_out.txt"
#define RECORD_FILE "std_1_record_p.txt"*/

int test_num = 11; //the number of benchmark circuits   //测试的基准电路的编号

char INPUT_FILE[30];    //测试的基准电路的编号  ----------> 存到INPUT_FILE
char OUTPUT_FILE[30];

const bool calc_std = false; //	whether consider the std in the fitness function

const int X_MAX = 324; //	the maximum of X_coordinate
const int Y_MAX = 324; //	the maximum of y_coordinate
const int XYMAX = X_MAX * Y_MAX; // 网格大小
const int record_p_num = X_MAX * Y_MAX + 2; //	initialize the size of the array record_p
int record_p[record_p_num][4]; //	record the actual routes //	record the points with smaller number in its four directions (total 8 directions)
int net_num; //	the total number of net
int min_tree[20000]; //	store the minimal spanning tree
int vertice;
int big_net_num;
typedef struct Net
{
	char name[10]; //	the name of net
	int serial_num; //	the seral number of net
	int pin_sum; //	the number of pins in each net
	int layer; //	the layer which the pin located
	//double pin[150][3]; //	the number of pins and  the layer which the pin located of each net
	vector< vector<int> > pin;
    //double graphw[150][150]; // record the distance between each pin_pair
    vector< vector<double> > graphw;
    //int osmt[460]; //	record the OSMT of each net
    vector<int> osmt;
	double fit_value;//	fitness value
    set< pair<int, int> > unconnected; // store the unconnected pin_pairs
    set< int > point_edge; //	store the connected pin_pairs which stores the serial_number of pins and four directions?????????????
} Net;
Net line_net[3000000];
int ver; //	intermediate variable, used to record the current routed net and  facilitated the construction of SMT
double totalwl=0;
const int popsize=10; //	population size
const int evaluations=10; // the maximal evaluation
const int endeval=evaluations;
const double w_start=0.95;
const double w_end=0.4;
const int w_varyfor=evaluations;
double w_now;
const double inerdec=(w_start-w_end)/w_varyfor;
const double c1_start=0.9;
const double c1_end=0.15;
const int c1_varyfor=evaluations;
double c1_now;
double c2_now;
const double c1_dec=(c1_start-c1_end)/c1_varyfor;
const double P=0.7071;//record the value of sqrt(2)/2 and is used in the rotation of xsegment, ysegment
struct Pop_osmt
{
	int edge[20000];
	double fit_value;
} pop_osmt[popsize+1],pbest[popsize+1],gbest; // population, particle best, global best

int max_h; //the maximal of H, horizontal, 0
int max_v; //the maximal of V, vertical, 2
int max_x45; //the maximal of X45, 45 segment, 1
int max_x135; //the maximal of X135, 135 segment, 3
int max_line[4]; //the maximal of 4 edges ??????????????????

typedef struct Point {
    int x, y; // x_coordinate y_coordinate
    bool operator< (const Point& rhs) const {//先比y,再比x
		return y < rhs.y || (y == rhs.y && x < rhs.x);
        //return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
	bool operator== (const Point& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
    Point& operator=(const Point& rhs) {
        x = rhs.x;
        y = rhs.y;
        return *this;
    }
} Point;

int box[4]; // the top, bottom, left, right of the extended box
typedef struct ExpandNode {
    int pa_id, pb_id;
    int net_id;
	int cnt;
    bool operator< (const ExpandNode& rhs) const {
        return net_id < rhs.net_id ||
            (net_id == rhs.net_id && (pa_id < rhs.pa_id ||
            (pa_id == rhs.pa_id || pb_id < rhs.pb_id)));
    }
} ExpandNode;
vector<ExpandNode> ilp_extend_point_vec;
vector<ExpandNode> ilp_extend_point_vec2;
vector<ExpandNode> ilp_extend_point_vec3;
set<ExpandNode> extend_unconnect; // record the pins which cannot route

/************************************************************************/
/* the parameter setting of ilp pso                                               */
/************************************************************************/
const int popsize_ilp=20; //the population size
const int evaluations_ilp=20; //the maximal of evaluations
const int endeval_ilp=evaluations_ilp;
const double w_start_ilp=0.95;
const double w_end_ilp=0.4;
const int w_varyfor_ilp=evaluations_ilp;
double w_now_ilp;
const double inerdec_ilp=(w_start_ilp-w_end_ilp)/w_varyfor_ilp;
const double c1_start_ilp=0.9;
const double c1_end_ilp=0.15;
const int c1_varyfor_ilp=evaluations_ilp;
double c1_now_ilp;
double c2_now_ilp;
const double c1_dec_ilp=(c1_start_ilp-c1_end_ilp)/c1_varyfor_ilp;
typedef struct Pop
{
    vector<bool> sol;
	vector<int> cnt;
    double fit_value;
    bool operator< (const Pop& rhs) const {
        return this->fit_value < rhs.fit_value;
    }
} Pop;
Pop pop_ilp[popsize_ilp],pbest_ilp[popsize_ilp],gbest_ilp; //	population, particle best, global best


FILE *out_file_p;

//double __std_deviation;

int maxline[(X_MAX + 5)*(Y_MAX + 5)][5];
int changenum;

int netvnum, nethnum, netx45num, netx135num;

int xnum;
int lnum;

double alltime;
