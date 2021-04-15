#include <iostream>
#include <Eigen/Eigen>
#include <Eigen/Core>
int main(){
    Eigen::Vector3f v[3] = {{1,1,1},{8,1,1},{8,9,0}};
    Eigen::Vector3f p = {7,2,0};
    bool op[3] = {true,true,true};
    for(int i=0;i<3;++i){
        int j = (i+1)%3;
        Eigen::Vector3f temp1 = v[i]-v[j];
        Eigen::Vector3f temp2 = p-v[j];
        if(temp1.cross(temp2)[2]<0){
            op[i] = false;
        }
    }
    std::cout<< (op[0]==op[1] && op[1]==op[2]);
    return 0;
}