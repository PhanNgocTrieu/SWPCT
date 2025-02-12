class Solution {
public:
    bool isPerfectSquare(int num) {
     int s=0,e=num;
     int mid=s+(e-s)/2;
    while(s<=e){
        long long square=(long long)mid*mid;
        if(square== num) return true;
        if(square >= num) e=mid-1;
        else{
            s=mid+1;
        }
       mid=s+(e-s)/2;
    }return false;
    }
};
