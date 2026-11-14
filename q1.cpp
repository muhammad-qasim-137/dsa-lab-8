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

void preorder(node* r){
    if(!r)return;
    cout<<r->key<<" ";
    preorder(r->left);
    preorder(r->right);
}

void inorder(node* r){
    if(!r)return;
    inorder(r->left);
    cout<<r->key<<" ";
    inorder(r->right);
}

void postorder(node* r){
    if(!r)return;
    postorder(r->left);
    postorder(r->right);
    cout<<r->key<<" ";
}

int countone(node* r){
    if(!r)return 0;
    int c=((r->left==nullptr)!=(r->right==nullptr))?1:0;
    return c+countone(r->left)+countone(r->right);
}

int counttwo(node* r){
    if(!r)return 0;
    int c=(r->left&&r->right)?1:0;
    return c+counttwo(r->left)+counttwo(r->right);
}

int height(node* r){
    if(!r)return -1;
    int a=height(r->left),b=height(r->right);
    return 1+(a>b?a:b);
}

int main(){
    node* root=nullptr;
    int a[]={45,25,65,15,35,55,75,30};
    for(int v:a)root=insert(root,v);
    cout<<"preorder: ";
    preorder(root);
    cout<<endl<<"inorder: ";
    inorder(root);
    cout<<endl<<"postorder: ";
    postorder(root);
    cout<<endl;
    cout<<"nodes with one child: "<<countone(root)<<endl;
    cout<<"nodes with two children: "<<counttwo(root)<<endl;
    cout<<"height (edges): "<<height(root)<<endl;
}
