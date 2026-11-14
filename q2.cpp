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

node* minnode(node* r){
    while(r->left)r=r->left;
    return r;
}

node* del(node* r,int k){
    if(!r)return nullptr;
    if(k<r->key)r->left=del(r->left,k);
    else if(k>r->key)r->right=del(r->right,k);
    else{
        if(!r->left){
            node* t=r->right;
            delete r;
            return t;
        }
        if(!r->right){
            node* t=r->left;
            delete r;
            return t;
        }
        node* s=minnode(r->right);
        r->key=s->key;
        r->right=del(r->right,s->key);
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
    int a[]={50,30,70,20,40,60,80,35,45};
    for(int v:a)root=insert(root,v);
    int d[]={20,30,50};
    for(int k:d){
        root=del(root,k);
        cout<<"after deleting "<<k<<": ";
        inorder(root);
        cout<<endl;
    }
}
