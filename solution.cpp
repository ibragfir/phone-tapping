#ifndef __PROGTEST__
#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;   

struct TPhone{
    unsigned int    m_TimeFrom;
    unsigned int    m_TimeTo;
    unsigned int    m_Channel;
};
#endif /* __PROGTEST__ */ 

void quicksort_f(TPhone** a, int lo, int hi){ 
    int left, right;
    unsigned int median;
    TPhone* temp;
    if( hi > lo ){ 
        left=lo; right=hi;
        median = a[lo]->m_TimeFrom; 
        while(right >= left){ 
            while(a[left]->m_TimeFrom < median) left++;
            while(a[right]->m_TimeFrom > median) right--;
            if(left > right) break;
            temp=a[left]; a[left]=a[right]; a[right]=temp;
            left++; right--;
        }
    quicksort_f(a, lo, right);// divide and conquer
    quicksort_f(a, left,  hi);
    }
}
void quicksort_t(TPhone** a, int lo, int hi){ 
    int left, right;
    unsigned int median;
    TPhone* temp;
    if( hi > lo ){ 
        left=lo; right=hi;
        median = a[lo]->m_TimeTo; 
        while(right >= left){ 
            while(a[left]->m_TimeTo < median) left++;
            while(a[right]->m_TimeTo > median) right--;
            if(left > right) break;
            temp=a[left]; a[left]=a[right]; a[right]=temp;
            left++; right--;
        }
    quicksort_t(a, lo, right);// divide and conquer
    quicksort_t(a, left,  hi);
    }
}
int Add_Channels(TPhone** From, TPhone** To, int size){
    int t  = 0;
    int f  = 0;
    int ch = 0;

    while(t != size && f != size){
        if(From[f]->m_TimeFrom <= To[t]->m_TimeTo){
            From[f]->m_Channel = ch;
            ++ch;
        }
        else{
            From[f]->m_Channel = To[t]->m_Channel;
            From[f] = To[t] = NULL;
            ++t;
        }
        ++f;
    }
    delete[] From;
    delete[] To;
    return ch;
}

int AllocChannels ( TPhone  * const * req, int reqNr ){
    if(!reqNr || !req)
        return 0;
    TPhone**        From;
    TPhone**        To;
    From = new TPhone* [reqNr];
    To   = new TPhone* [reqNr];

    for(int i = 0; i < reqNr; ++i)
        From[i] = To[i] = req[i];
    quicksort_f(From,0, reqNr-1);
    quicksort_t(To,  0, reqNr-1);
    //for(int i=0;i<reqNr;++i)
    //    cout<<From[i]->m_TimeFrom<<"  "<<To[i]->m_TimeTo<<endl;
    //cout<<endl;
    return Add_Channels(From,To,reqNr);
}                                                             

#ifndef __PROGTEST__
int main ( int argc, char * argv [] ){
    TPhone ** ptr;
    int cnt, chnl;
   
    if (!(cin >> cnt))
        return 1;
    ptr = new TPhone * [ cnt ];
    for ( int i = 0; i < cnt; i ++ ){
        TPhone * n = new TPhone;
        if ( ! (cin >> n -> m_TimeFrom >> n -> m_TimeTo) ) return 1;
        ptr[i] = n;
    }

    chnl = AllocChannels ( ptr, cnt );
    cout << chnl << endl;
    for ( int i = 0; i < cnt; i ++ ){
        cout << ptr[i] -> m_Channel << endl;
        delete ptr[i];
    }
    delete [] ptr; 
    return 0;
 }
#endif  /* __PROGTEST__ */
