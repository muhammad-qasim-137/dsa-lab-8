#include <iostream>
using namespace std;

struct node{
    int key;
    node* left;
    node* right;
    node(int k){key=k;left=nullptr;right=nullptr;}
};

node* insert(node* r,int k){
    if(!r)return new node(k);
    if(k<r->key)r->left=insert(r->left,k);
    else if(k>r->key)r->right=insert(r->right,k);
    return r;
}

void inrange(node* r,int lo,int hi){
    if(!r)return;
    if(r->key>lo)inrange(r->left,lo,hi);
    if(r->key>=lo&&r->key<=hi)cout<<r->key<<" ";
    if(r->key<hi)inrange(r->right,lo,hi);
}

int countrange(node* r,int lo,int hi){
    if(!r)return 0;
    if(r->key<lo)return countrange(r->right,lo,hi);
    if(r->key>hi)return countrange(r->left,lo,hi);
    return 1+countrange(r->left,lo,hi)+countrange(r->right,lo,hi);
}

node* trim(node* r,int lo,int hi){
    if(!r)return nullptr;
    r->left=trim(r->left,lo,hi);
    r->right=trim(r->right,lo,hi);
    if(r->key<lo){
        node* t=r->right;
        delete r;
        return t;
    }
    if(r->key>hi){
        node* t=r->left;
        delete r;
        return t;
    }
    return r;
}

void inorder(node* r){
    if(!r)return;
    inorder(r->left);
    cout<<r->key<<" ";
    inorder(r->right);
}

int main(){
    node* root=nullptr;
    int a[]={50,25,75,10,30,60,90,20,40,70,80};
    for(int v:a)root=insert(root,v);
    int lo=25,hi=70;
    cout<<"ids in range: ";
    inrange(root,lo,hi);
    cout<<endl;
    cout<<"count: "<<countrange(root,lo,hi)<<endl;
    root=trim(root,lo,hi);
    cout<<"after deleting outside range: ";
    inorder(root);
    cout<<endl;
}
