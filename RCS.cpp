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
using namespace std;

int csl(vector<int> &a, vector<int> &cnt, int size)
{
	int n = a.size();
	for(int i = 0; i < n - 1; i++)
	{
		int ai = a[i];
		for(int j = i + 1; j < n; j++)
		{
			int aj = a[j];
			int m = cnt[ai * size + aj];
			if(m == 0) return 0;
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

int main(int argc, char *argv[])
{
//Read file into Triples-----------------------------------------------------------------------
if (argc != 4)
   {fprintf(stderr,"Usage: ./rcs file samples clique\n");
   exit(1);}

	int sample = atoi(argv[2]);
	int max_clique = atoi(argv[3]);
	ifstream is(argv[1]);
	if(!is.good()) {
		cout << "Error: file could not be opened" << endl;
		exit(1);
	}

	vector< vector<int> > tr;
	tr.clear();
	vector<int> t(2, -1);

	int vertex = 0;
	int edge = 0;
	int i = 0;
	while(!is.eof())
	{
		char c = is.peek();
		if(c == 'p')
		{
			string str;
			is >> c;
			is >> str;
			is >> vertex;
			is >> edge;
			tr.reserve(edge);
		}
		if(c == 'e')
		{
			int v, v1, v2;
			is >> c;
			is >> v1;
			is >> v2;
			if(v1 > v2)
			{
				v = v1; v1 = v2; v2 = v;
			}
			if(v1 > vertex || v1 <= 0) cout << "*";
			if(v2 > vertex || v2 <= 0) cout << "+";
			t[0] = v1;
			t[1] = v2;
			tr.push_back(t);
			i++;;
		}
		else
		{
			char cc[256];
			is.getline(cc, 256);
		}
	}
	is.close();
	if(edge == i) cout << "OK! " << edge << " Pairs Have Been Read" <<endl;

	vector< vector<int> >::iterator iter_ii;
	vector<int>::iterator iter_jj;





	int TMAX = 0;
	for(int i = 0; i < tr.size(); i++)
	{
		int j = tr[i][0];
		int k = tr[i][1];
		if(j > TMAX) TMAX = j;
		if(k > TMAX) TMAX = k;
	}
	cout << "Table: " << TMAX << endl;
	TMAX++;//Idependent of base index 0 or 1!

	vector<int> cnt;
	cnt.resize(TMAX * TMAX, 0);
	for(int i = 0; i < tr.size(); i++) cnt[tr[i][0] * TMAX + tr[i][1]]++;

	double timea, timeb;
	timea = clock();
	srand ( time(NULL) );//initialize random seed

	int MMAX,NMAX,max,csize,r1,r2,cs;
	vector< vector<int> > se, re;
	vector<int> C;

	se.reserve(sample);
	se.assign(tr.begin(), tr.end());
	re.reserve(sample);
	re.clear();

	int done=0;
	while(done==0 && se.size()>1){
	MMAX = tr.size();
	NMAX = se.size();
	max=0;

	for(int j = 0; j < sample; j++){
		C.clear();
		r1=rand() % NMAX;
		//r2=rand() % NMAX;
		//set_union(se[r1].begin(), se[r1].end(), se[r2].begin(), se[r2].end(), back_inserter(C));
		r2=rand() % MMAX;
		set_union(se[r1].begin(), se[r1].end(), tr[r2].begin(), tr[r2].end(), back_inserter(C));
		cs = csl(C, cnt, TMAX);

		if(cs==1){
			re.push_back(C);
			csize=C.size();
			if(csize>max)max=csize;
			if(csize>=max_clique){
				cout << "!!!!!!!!! Solution found of length " << C.size() << " !!!!!!!!!" << endl;
      			for(iter_jj=C.begin(); iter_jj!=C.end(); iter_jj++) cout << *iter_jj << " ";
   				cout << endl;
   				done =1;
				break;}
		}
	}
#if 1
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
}//end of main
