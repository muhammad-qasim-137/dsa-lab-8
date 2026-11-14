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

int maxval(node* r){
    while(r->right)r=r->right;
    return r->key;
}

void printgreater(node* r,double t){
    if(!r)return;
    printgreater(r->left,t);
    if(r->key>t)cout<<r->key<<" ";
    printgreater(r->right,t);
}

int counttwo(node* r){
    if(!r)return 0;
    int c=(r->left&&r->right)?1:0;
    return c+counttwo(r->left)+counttwo(r->right);
}

int ht(node* r){
    if(!r)return 0;
    int a=ht(r->left),b=ht(r->right);
    return 1+(a>b?a:b);
}

void printpath(node* r){
    while(r){
        cout<<r->key<<" ";
        r=ht(r->left)>=ht(r->right)?r->left:r->right;
    }
    cout<<endl;
}

bool skewed(node* r){
    if(!r)return true;
    if(r->left&&r->right)return false;
    return skewed(r->left)&&skewed(r->right);
}

node* delone(node* r,int& cnt){
    if(!r)return nullptr;
    bool one=(r->left==nullptr)!=(r->right==nullptr);
    r->left=delone(r->left,cnt);
    r->right=delone(r->right,cnt);
    if(one){
        cnt++;
        return del(r,r->key);
    }
    return r;
}

node* kthnode(node* r,int& c,int k){
    if(!r)return nullptr;
    node* a=kthnode(r->left,c,k);
    if(a)return a;
    c++;
    if(c==k)return r;
    return kthnode(r->right,c,k);
}

int main(){
    node* root=nullptr;
    root=insert(root,45);
    root=insert(root,25);
    root=insert(root,65);
    root=insert(root,15);
    root=insert(root,35);
    root=insert(root,55);
    root=insert(root,75);
    root=insert(root,10);
    root=insert(root,30);
    root=insert(root,40);
    root=insert(root,60);
    root=insert(root,80);
    root=insert(root,32);
    root=insert(root,33);
    int k;
    cin>>k;
    cout<<"original inorder: ";
    inorder(root);
    cout<<endl;
    int lo=minnode(root)->key,hi=maxval(root);
    double t=(lo+hi)/2.0;
    cout<<"min: "<<lo<<" max: "<<hi<<" threshold: "<<t<<endl;
    cout<<"greater than threshold: ";
    printgreater(root,t);
    cout<<endl;
    cout<<"two children: "<<counttwo(root)<<endl;
    cout<<"longest path: ";
    printpath(root);
    cout<<"skewed: "<<(skewed(root)?"yes":"no")<<endl;
    int cnt=0;
    root=delone(root,cnt);
    cout<<"deleted: "<<cnt<<endl;
    cout<<"final inorder: ";
    inorder(root);
    cout<<endl;
    int c=0;
    node* r=kthnode(root,c,k);
    cout<<k<<"th smallest: "<<(r?r->key:-1)<<endl;
}
