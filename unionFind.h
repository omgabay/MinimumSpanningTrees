//
// Created by omerg on 4/15/2022.
//

#ifndef SPANNING_TREES_UNIONFIND_H
#define SPANNING_TREES_UNIONFIND_H

struct Set{
    int group_id;
    unsigned int groupSize = 1;
};
class unionFind {
private:
    Set *sets;
    int arrSize;
    int setsCount;
public:
    unionFind(int numOfSets):arrSize(numOfSets){
        sets = new Set[numOfSets];
        setsCount = numOfSets;
        for(auto i=0; i<numOfSets; i++)
            sets[i].group_id = i;
    };
    int Find(int s){
        if(s >= arrSize || s<0){
            return -1;
        }else if(s == sets[s].group_id){
            return s;
        }
        int res = Find(sets[s].group_id);
        sets[s].group_id = res;
        return res;
    }

    bool Union(int s1, int s2){
        int smallSetID, biggerSetID;
        if(s1>=arrSize || s2>=arrSize || s1<0 || s2<0 || s1==s2)
            return false;

        int rep1 = this->Find(s1);
        int rep2 = this->Find(s2);
        if(rep1 == rep2)
            return false;

        if(sets[rep1].groupSize > sets[rep2].groupSize){
            smallSetID = rep2;
            biggerSetID = rep1;
        }else{
            smallSetID = rep1;
            biggerSetID = rep2;
        }
        sets[smallSetID].group_id = biggerSetID;  // union by setting group-id to the bigger group
        setsCount--;
        return true;
    }
    bool isConnected() const{
        return setsCount == 1;
    }
    unsigned int getNumberOfComponents(){
        return setsCount;
    }

};


#endif //SPANNING_TREES_UNIONFIND_H
