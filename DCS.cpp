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

double scale(int i)
{
    return (1.0 + (double)i);
}
bool tally(vector<int> &e, vector<int> &t)
{
    int tsize = t.size(), esize = e.size();
    for(int i = 0; i < tsize; i++) t[i] = 0;
    for(int i = 0; i < esize; i++) t[e[i]]++;
    
    int n = 0;
    int min = tsize;
    for(int i = 0; i < tsize; i++)
    {
        int t0 = t[i];
        if(t0 != 0)
        {
            if(min > t0) min = t0;
            n++;
        }
    }
    int max = (n - 1);
    //cout << "min: " << scale(min) << " max: " << scale(max) <<endl;
    if(min == max) return false;
    for(int i = 0; i < tsize; i++) if(t[i] == min) {t[i] = 0; break;}
    
    int j = 0;
    for(int i = 0; i < esize; i+=2)
    {
        int e0 = e[i+0], e1 = e[i+1];
        if(t[e0] != 0 && t[e1] != 0)
        {
            e[j+0] = e0; e[j+1] = e1;
            j+=2;
        }
    }
    e.resize(j);
    return true;
}

int main(int argc, char *argv[])
{
    //STEP 1: READ IN PAIRS
    
    //Read file into Triples-----------------------------------------------------------------------
    if (argc != 4)
    {fprintf(stderr,"Usage: ./dcs file samples clique\n");
        exit(1);}
    
    int sample = atoi(argv[2]);
    int max_clique = atoi(argv[3]);
    ifstream is(argv[1]);
    if(!is.good()) {
        cout << "Error: file could not be opened" << endl;
        exit(1);
    }
    /*
     is.seekg (0, ios::end);
     int length = is.tellg();
     is.seekg (0, ios::beg);
     */
    vector< vector<int> > tr;
    tr.clear();
    vector<int> tt(2, -1);
    
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
            //tr.resize(edge);
            tr.reserve(edge);
        }
        if(c == 'e')
        {
            int v, v1 = -1, v2 = -1;
            is >> c;
            is >> v1;
            is >> v2;
            if(v1 > v2)
            {
                v = v1; v1 = v2; v2 = v;
            }
            if(v1 > vertex || v1 <= 0) cout << "*";
            if(v2 > vertex || v2 <= 0) cout << "+";
            tt[0] = v1;
            tt[1] = v2;
            //tr[i] = t;
            tr.push_back(tt);
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
    //sort(tr.begin(), tr.end(), compare);
    cout << tr[edge-1][0] << " " << tr[edge-1][1] << endl;
    
    vector< vector<int> >::iterator iter_ii;
    vector<int>::iterator iter_jj;
    if(0){
        cout << endl << "Pairs:" << tr.size();
        for(iter_ii=tr.begin(); iter_ii!=tr.end(); iter_ii++)
        {
            cout << endl;
            for(iter_jj=(*iter_ii).begin(); iter_jj!=(*iter_ii).end(); iter_jj++) cout << *iter_jj << " ";
        }
        cout << endl;
    }
    
#if 1
    srand(time(NULL));
    double ta, tb;
    
    int edges = 2 * edge;
    vector<int> e(edges);
    for(int i = 0; i < edges; i++) e[i] = tr[i/2][i%2] - 1;
    int nodes = *max_element(e.begin(), e.end()) + 1;
    vector<int> v(nodes);
    vector<int> t(nodes);
    
    ta = clock();
    while(tally(e, t));// cout << "Edges: " << e.size() << " Nodes: " << v.size() << endl;
    tb = clock();
    
    int l = 0;
    for(int i = 0; i < t.size(); i++)
    {
        if(t[i] != 0)
        {
            v[l] = i;
            l++;
        }
    }
    v.resize(l);
    
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
    
    //int TMAX = *max_element(triples, triples + nt) + 1;//Idependent of base index 0 or 1!
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
    
    vector<int> cnt;//, dsp, ele;
    cnt.resize(TMAX * TMAX, 0);
    //dsp.resize(TMAX * TMAX, 0);
    for(int i = 0; i < tr.size(); i++) cnt[tr[i][0] * TMAX + tr[i][1]]++;
    //for(int t = 0, i = 0; i < TMAX * TMAX; i++)
    //{
    //	dsp[i] = t;
    //	t += cnt[i];
    //}
    //ele.resize(tr.size());
    //for(int i = 0; i < tr.size(); i++) ele[i] = tr[i][2];
    vector<int> wgh;
    wgh.resize(TMAX, 0);
    for(int i = 0; i < tr.size(); i++) wgh[tr[i][0]]++;
    for(int i = 0; i < tr.size(); i++) wgh[tr[i][1]]++;
    //for(int i = 0; i < wgh.size(); i++) wgh[i]>>=1;
    for(iter_jj=wgh.begin(); iter_jj!=wgh.end(); iter_jj++) cout << *iter_jj << " ";
    cout << endl;
    
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
            while(se[r1].size() >= wgh[tr[r2][0]] || se[r1].size() >= wgh[tr[r2][1]]) r2 = rand() % MMAX;
            set_union(se[r1].begin(), se[r1].end(), tr[r2].begin(), tr[r2].end(), back_inserter(C));
            cs = csl(C, cnt, TMAX);
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
                if(csize>=max_clique){
                    cout << "!!!!!!!!! Solution found of length " << C.size() << " !!!!!!!!!" << endl;
                    for(iter_jj=C.begin(); iter_jj!=C.end(); iter_jj++) cout << *iter_jj << " ";
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
