#include "foo.h"

void sort_alg(vector<double>::iterator begin, vector<double>::iterator end) {

    int size=distance(begin,end);

    double *arr=new double[size]();
    int i=0,j=size-1;

    vector<double>::iterator mid=begin+size/2,mid2=mid,begin2=begin;

    auto s=[](vector<double>::iterator it1,vector<double>::iterator it2){
        sort(it1,it2);
    };
    auto c=[](double *p1,double *p2,vector<double>::iterator it){
        copy(p1,p2,it);
    };

    thread t1(s,begin,mid);
    thread t2(s,mid,end);

    t1.join();
    t2.join();

    auto m1=[&i,size,arr,begin,mid,end,begin2,mid2](){
        vector<double>::iterator it1=begin;
        vector<double>::iterator it2=mid;
        while((i<size/2)&&(it1!=mid2||it2!=end)){
            if((it1<mid2)&&(*it1<*it2)||(it2==end)){
                arr[i++]=*it1++;
            }
            else if(it2<end){
                arr[i++]=*it2++;
            }
        }
    };

    auto m2=[&j,size,arr,begin,mid,end,begin2,mid2](){
        vector<double>::iterator it1=mid2-1;
        vector<double>::iterator it2=end-1;
        while((j>=size/2)&&(it1!=begin2||it2!=mid2)){
            if((it1>=begin2)&&(*it1>*it2)||(it2==mid2)){
                arr[j--]=*it1--;
            }
            else if(it2>mid2){
                arr[j--]=*it2--;
            }
        }
    };

    thread t3(m1);
    thread t4(m2);

    t3.join();
    t4.join();

    thread t5(c,arr,arr+size/2,begin2);
    thread t6(c,arr+size/2,arr+size,begin2+size/2);

    t5.join();
    t6.join();

    delete[] arr;

}
