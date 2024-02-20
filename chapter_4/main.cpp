#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <typeinfo>
#include "second_class.hpp"
using namespace std;
int main(){
    /*取空指针类型异常处理*/
    // second_class* base_one = nullptr;
    // try{
    //     cout<< typeid(*base_one).name()<<endl;
    // }catch(const exception& e){
    //     cerr<< e.what()<<endl;
    // }
    /*转型失败异常处理测试*/
    // try{
    //     second_class* base_one = new second_class(10);//已经指向了基类
    //     //base_one = new first_child(20);//如果没有这句类型转换，会抛出相应异常
    //     first_child* child_one = new first_child(20);
    //     first_child& child_two = dynamic_cast<first_child&>(*base_one);
    // }catch(const exception& e){
    //     cerr<<"HERE is an error!: "<<e.what()<<endl;
    // }
    /*范围溢出异常处理测试*/
    // try{
    //     int* a=new int[100000000000000000];//bad_alloc异常处理
    //     //int a[10]={0};
    //     // int i=10;
    //     // if(i>9||i<0){//一般来说自定义
    //     //     throw out_of_range("Index is out of range");
    //     // }
    // }catch(const exception& e){
    //     cout<<"HEY! here is an error: "<<e.what()<<endl;
    // }
    //cout<<a[1]<<endl;  //try内的作用域不会延伸到全局

    /*文件读写测试*/
    // fstream out;
    // out.open("test.txt",ios::in);
    // if(!out.is_open()){
    //     cerr<<"ERROR: can't open the file"<<endl;
    //     return 1;
    // }
    // //out.seekg(0, ios::beg);//文件位置指针：从开头位置偏移0个字节开始
    // char data[100];
    // string line;
    // out>> data;
    // cout<<"the data from the file: "<<data<<endl;
    // // out<<"\n here add the number: "<<10;
    // out>> line;
    // cout<<"the first line from the file: "<<line<<endl;//只能读取一个char
    // int i=0;
    // while(getline(out,line)){
    //     cout<<"the"<<" line from the file: "<<line<<endl;
    // }
    // out.close();
    return 0;
}