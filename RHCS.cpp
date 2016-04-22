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
    long int sample = 1000000;
    long int numoftrips;
    int done=0;
    vector< vector<int> > Triples;    // Declare two dimensional vector of vectors
    vector< vector<int> > se, re;
    vector<int> A, B, C, D;
    vector< vector<int> >::iterator iter_ii;
    vector<int>::iterator iter_jj;
    vector<int> cnt, dsp;
    vector<int> ele;
    int arraysize = 1000000000;
    int n,count,j,i,k,num,entered;
    j=i=k=count=0;
    triples = (int*) calloc (arraysize, sizeof(int));
    if(triples==NULL) exit(1);
    
    
    //(below) Read t#xx.txt into Triples-----------------------------------------------------------------------
    if (argc == 0){
        fprintf(stderr,"Usage: ./rhcs file n\n");
        exit(1);
    }
    int max_clique = 300; //FIXME
    
    if (argc == 3){
        max_clique = atoi(argv[2]);
    }
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
    
    indata >> num; // read in t1xx.txt
    i=0;
    while(!indata.eof()){
        triples[i]=num;
       	i++;
        indata >> num; // sets EOF flag if no value found
    }
    indata.close();
    nt=i;
    numoftrips=nt/3;
    cout << nt << " " << numoftrips << " Triples Have Been Read" <<endl;
    
    for(i=0;i<nt;i+=3){
        D.clear();
        D.push_back(triples[i]);
        D.push_back(triples[i+1]);
        D.push_back(triples[i+2]);
        Triples.push_back(D);
    }
    
    if(0){
        cout << endl << "Triples:";
        for(iter_ii=Triples.begin(); iter_ii!=Triples.end(); iter_ii++)
        {
            printf("\n");
            for(iter_jj=(*iter_ii).begin(); iter_jj!=(*iter_ii).end(); iter_jj++)
            {
                printf("%d\t",*iter_jj);
            }
        }
        cout << endl;
    }
    
    int TMAX = *max_element(D.begin(), D.end()) + 1;//Idependent of base index 0 or 1!
    cout << "Table: " << TMAX << endl;
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
    
    double timea, timeb;
    timea = clock();
    
    srand ( time(NULL) );//initialize random seed
    int MMAX,NMAX,max,csize,r1,r2,cs;
    
    
    se.reserve(sample);   //This informs the vector of a planned increase in size, although notice that the parameter n informs of a minimum, so the resulting capacity may be any capacity equal or larger than this.
    
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
            r2=rand() % MMAX;
            set_union(se[r1].begin(), se[r1].end(), Triples[r2].begin(), Triples[r2].end(), back_inserter(C));
            cs = csl(C, ele, cnt, dsp, TMAX);
            
            if(cs==1){
                re.push_back(C);
                csize=C.size();
                
                if(csize>max) max = csize;
                
                if(csize>=max_clique){
                    cout << "Solution found of length " << csize << "!" << endl;
                    for(iter_jj=C.begin(); iter_jj!=C.end(); iter_jj++) cout << *iter_jj << " ";
                    cout << endl;
                    Needed++;}
                
                if(csize>=max_clique){done = 1; break;}
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
        
        cout << "done = " << done << "  se.size = " << se.size() << "  max = " << max << endl;
        
    }//end while loop
    timeb = clock();
    cout << "Time: " << (timeb - timea)/CLOCKS_PER_SEC << endl;
    
    return 0;
    
}//end of main
