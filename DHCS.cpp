#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

int csl(vector<int> &a, vector<int> &t, vector<int> &cnt, vector<int> &dsp, int size)
{
	int n = a.size();
	for(int i = 0; i < n - 2; i++)
	{
		int ai = a[i];
		for(int j = i + 1; j < n - 1; j++)
		{
			int aj = a[j];
			int m = cnt[ai * size + aj];
			int l = dsp[ai * size + aj];
			m += l;
			for(int k = j + 1; k < n; k++)
			{
				int ak = a[k];
				bool found = false;
				while(l < m)
				{
					if(ak == t[l++])
					{
						found = true;
						break;
					}
				}
				if(!found) return 0;
			}
		}
	}
	return 1;
}

bool compare(vector<int> a, vector<int> b)
{
	return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
}

bool equal_vector(vector<int> a, vector<int> b)
{
	if(a.size() != b.size()) return false;
	for(int i = 0; i < a.size(); i++) if(a[i] != b[i]) return false;
	return true;
}
double scale(int i)
{
	return (3.0 + sqrt(1.0 + 8.0 * (double)i))/2.0;
}

bool tally(vector<int> &e, vector<int> &t, int m)
{
	static bool seed = true;

	int tsize = t.size(), esize = e.size();
	for(int i = 0; i < tsize; i++) t[i] = 0;
	for(int i = 0; i < esize; i++) t[e[i]]++;
	if(seed)
	{
		for(int i = 0; i < tsize; i++)
		{
			if(t[i] < (m - 1)*(m - 2)/2) t[i] = 0;
			seed = false;
		}
	}

	int n = 0;
	int min = esize;
	for(int i = 0; i < tsize; i++)
	{
		int t0 = t[i];
		if(t0 != 0)
		{
			if(min > t0) min = t0;
			n++;
		}
	}
	int max = (n - 1)*(n - 2)/2;
    cout << "min: " << scale(min) << " max: " << scale(max) <<endl;
    if(min == max) return false;
	for(int i = 0; i < tsize; i++) if(t[i] == min) {t[i] = 0; break;}

	int j = 0;
	for(int i = 0; i < esize; i+=3)
	{
		int e0 = e[i+0], e1 = e[i+1], e2 = e[i+2];
		if(t[e0] != 0 && t[e1] != 0 && t[e2] != 0)
		{
			e[j+0] = e0; e[j+1] = e1; e[j+2] = e2;
			j+=3;
		}
	}
	e.resize(j);
    return true;
}

int main(int argc, char *argv[])
{

//STEP 1: READ IN TRIPLES
//	 Result: One dimensional array of size nt starting from 1
unsigned long int nt=0;
int *triples;
int *doubles;
const char* file;
char ac[256];
int Needed = 1;
long int sample = 100000;
long int numoftrips;
int done=0;
vector< vector<int> > se, re;
vector<int> A, B, C, D;
vector< vector<int> > Triples;    // Declare two dimensional vector of vectors
vector< vector<int> >::iterator iter_ii;
vector<int>::iterator iter_jj;
vector<int> cnt, dsp;
vector<int> ele;


size_t arraysize = 1024000000;
unsigned int n,count,j,i,k,num,entered;
j=i=k=count=0;

triples = (int*) calloc (arraysize, sizeof(int));
//doubles = (int*) calloc (arraysize, sizeof(int));
//if(triples==NULL || doubles==NULL) exit(1);


//(below) Read t#xx.txt into Triples-----------------------------------------------------------------------
if (argc == 0){
	fprintf(stderr,"Usage: ./dhcs file\n");
   exit(1);
}

//int max_clique = 300; //TODO
ifstream is(argv[1]);
if(!is.good()) {
	cout << "Error: file could not be opened" << endl;
	exit(1);
}

ifstream indata;
indata.open(argv[1]);
if(!indata) {
  cerr << "Error: file could not be opened" << endl;
  exit(1);
}

//      indata >> num; // read in t1xx.txt
      i=0;
      while(!indata.eof()){
		char line[255];
		indata.getline(line, 255);
		string sline(line);
		if(sline.empty()) continue;
		istringstream iss(sline);
		iss >> triples[i+0];
      	iss >> triples[i+1];
      	iss >> triples[i+2];
       	i+=3;
       }
       indata.close();
	   nt=i;numoftrips=nt/3;
cout << nt << " " << numoftrips << " Triples Have Been Read" <<endl;

Triples.clear();
Triples.reserve(nt);
for(i=0;i<nt;i+=3){
D.clear();
D.push_back(triples[i]);
D.push_back(triples[i+1]);
D.push_back(triples[i+2]);
Triples.push_back(D);
}
cout << D[0] << " " << D[1] << " " << D[2] << endl;
//UNCOMMENT BELOW TO PRINT Triples
	//   cout << endl << "Triples:";
	//   for(iter_ii=Triples.begin(); iter_ii!=Triples.end(); iter_ii++)
	//   {
	//   	  printf("\n");
	//      for(iter_jj=(*iter_ii).begin(); iter_jj!=(*iter_ii).end(); iter_jj++)
	//      {
	//         printf("%d\t",*iter_jj);
	//      }
	//   }
	//   cout << endl;
//UNCOMMENT ABOVE TO PRINT Triples

//(above) Input t1#.txt into Triples-----------------------------------------------------------------------

#if 1
double ta, tb;

int edges = nt;
int m = Needed;
vector<int> e(edges);
for(int i = 0; i < edges; i++) e[i] = triples[i] - 1;
int nodes = *max_element(e.begin(), e.end()) + 1;
vector<int> v(nodes);
vector<int> t(nodes);

ta = clock();
while(tally(e, t, m));// cout << "Edges: " << e.size() << " Nodes: " << v.size() << endl;
tb = clock();

int l = 0;
for(int i = 0; i < nodes; i++) if(t[i] != 0) v[l++] = i;
v.resize(l);

cout << endl;
cout << "Clique: " << v.size() << " | ";
for(int i = 0; i < v.size(); i++) cout << v[i] + 1 << " ";
cout << endl;

cout << "Time: " << (tb - ta)/CLOCKS_PER_SEC << endl;

return 0;

#else
//STEP 2: DO THE WHILE LOOP IN Hypergrpah.nb
//
//  Note 1 : The outer union in "Union[Array[Union @@ RandomSample[t, l] &, m]]"
//  		 is not implemented since I don't know how to union two vector of vectors
//
//  Note 2 : In my RandomSample equivalent we are not assured that we are not getting
//			 repeats!
//

int TMAX = *max_element(D.begin(), D.end()) + 1;//Idependent of base index 0 or 1!
cout << "Table: " << TMAX - 1 << endl;
cnt.resize(TMAX * TMAX, 0);
dsp.resize(TMAX * TMAX, 0);
for(int i = 0; i < Triples.size(); i++) cnt[Triples[i][0] * TMAX + Triples[i][1]]++;
for(int t = 0, i = 0; i < TMAX * TMAX; i++)
{
	dsp[i] = t;
	t += cnt[i];
}
ele.resize(Triples.size());
for(int i = 0; i < Triples.size(); i++) ele[i] = Triples[i][2];
vector<int> wgh;
wgh.resize(TMAX, 0);
for(int i = 0; i < Triples.size(); i++) wgh[Triples[i][0]]++;
for(int i = 0; i < Triples.size(); i++) wgh[Triples[i][1]]++;
for(int i = 0; i < Triples.size(); i++) wgh[Triples[i][2]]++;
for(iter_jj=wgh.begin(); iter_jj!=wgh.end(); iter_jj++) cout << *iter_jj << " ";
cout << endl;

double timea, timeb;
timea = clock();

srand ( time(NULL) );//initialize random seed
int MMAX,NMAX,max,csize,r1,r2,cs;


se.reserve(sample);
se.assign(Triples.begin(), Triples.end());
re.reserve(sample);
re.clear();

while(done==0 && se.size()>1){
MMAX = Triples.size();
NMAX = se.size();
max=0;

	for(j=0;j<sample;j++){

	C.clear();
	r1=rand() % NMAX;
	//r2=rand() % NMAX;
	//set_union(se[r1].begin(), se[r1].end(), se[r2].begin(), se[r2].end(), back_inserter(C));
	r2=rand() % MMAX;
	set_union(se[r1].begin(), se[r1].end(), Triples[r2].begin(), Triples[r2].end(), back_inserter(C));
	cs = csl(C, ele, cnt, dsp, TMAX);
	/*
		cout << endl << "C:";
		for(iter_jj=C.begin(); iter_jj!=C.end(); iter_jj++) cout << *iter_jj << " ";
		cout << endl << cs <<endl;
	*/
		if(cs==1){
			//if(!binary_search(se.begin(), se.end(), C))
			re.push_back(C);
			csize=C.size();
			if(csize>max)max=csize;
			if(csize>=Needed){
				cout << "!!!!!!!!! Solution found of length " << C.size() << " !!!!!!!!!" << endl;
      			for(iter_jj=C.begin(); iter_jj!=C.end(); iter_jj++) cout << *iter_jj << "(" << wgh[*iter_jj] << ") ";
   				cout << endl;
   				done =1;
				break;}
		}//end if

	}//end for loop
#if 1
/*
    vector<bool> rf(re.size());
    for(int i = 0; i < re.size(); i++)
    {
        bool rb = true;
        for(int j = 0; j < re.size(); j++)
        {
            C.clear();
            set_intersection(re[i].begin(), re[i].end(), re[j].begin(), re[j].end(), back_inserter(C));
            if((re[i] != re[j]) && (C.size() == re[i].size())) {rb = false; break;}
        }
        rf[i] = rb;
    }
    int l = 0;
    for(int i = 0; i < re.size(); i++)
    {
        if(rf[i] == true)
        {
            re[l] = re[i]; l++;
        }
    }
    re.resize(l);
*/
    //set< vector<int> > rs(re.begin(), re.end());
    //rs.insert(re.begin(), re.end());
    //se.assign(rs.begin(), rs.end());

	//rs.clear();

    se.assign(re.begin(), re.end());
	re.clear();
#else

    vector<bool> rf(re.size());
    for(int i = 0; i < re.size(); i++)
    {
		bool rb = true;
        for(int j = 0; j < re.size(); j++)
        {
            C.clear();
            set_intersection(re[i].begin(), re[i].end(), re[j].begin(), re[j].end(), back_inserter(C));
            if((re[i] != re[j]) && (C.size() == re[i].size())) {rb = false; break;}
        }
		rf[i] = rb;
    }
    int l = 0;
    for(int i = 0; i < re.size(); i++)
    {
        if(rf[i] == true)
        {
            re[l] = re[i]; l++;
        }
    }
    re.resize(l);
	set< vector<int> > rs(re.begin(), re.end());
	re.assign(rs.begin(), rs.end());

	vector<bool> sf(se.size());
	for(int i = 0; i < se.size(); i++)
	{
		bool sb = true;
		for(int j = 0; j < re.size(); j++)
		{
			C.clear();
			set_intersection(se[i].begin(), se[i].end(), re[j].begin(), re[j].end(), back_inserter(C));
			if(C.size() == se[i].size()) {sb = false; break;}
		}
		sf[i] = sb;
	}
	int k = 0;
	for(int i = 0; i < se.size(); i++)
	{
		if(sf[i] == true)
		{
			se[k] = se[i]; k++;
		}
	}
	se.resize(k);
	for(int i = 0; i < re.size(); i++)
	{
		se.push_back(re[i]);
	}
#endif

cout << "done=" << done << "  se.size=" << se.size() << "  max=" << max << endl;
}//end while loop
timeb = clock();
cout << "Time: " << (timeb - timea)/CLOCKS_PER_SEC << endl;

return 0;
#endif
}//end of main
