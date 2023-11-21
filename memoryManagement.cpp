#include <bits/stdc++.h>


using namespace std;

class mm{
  vector<int> blocks;
  vector<int> flagforblocks; // initially all should be zero
  vector<int> processes;
  
  public:
  int prev = 0;
  void input(){
      cout<<"sizes bol"<<endl;
      int bs;
      int ps;
      cin>>bs>>ps;
      blocks.resize(bs);
      flagforblocks.resize(bs); 
      processes.resize(ps);
      
      for(int i = 0;i<bs;i++){
          cout<<"block ka size bolo"<<endl;
          cin>>blocks[i];
          flagforblocks[i] = 0;
      }
      for(int i = 0;i<ps;i++){
          cin>>processes[i];
      }
  }
  
  void firstfit(){
      input();
      
    vector<int> allocation(processes.size(),-1);
    
    for(int i = 0;i<processes.size();i++){
        for(int j = 0;j<blocks.size();j++){
            if(blocks[j] >= processes[i] && flagforblocks[j] == 0){
                allocation[i] = j;// block no.
                blocks[j] -= processes[i];
                flagforblocks[j] = 1;
                break;
            }
        }
    }
    
     cout << "\nProcess No.\tProcess Size\tBlock no." << endl;
    for (int i = 0; i < processes.size(); i++)
    {
            cout << i + 1 << "\t\t" << processes[i] << "\t\t";
            if (allocation[i] != -1)
                cout << allocation[i] + 1;
            else
                cout << "Not Allocated";
            cout << endl;
    }
    
  }
  
  void bestfit(){
      input();
      
      vector<int> allo(processes.size(),-1);
      
      for(int i = 0;i<processes.size();i++){
          int bestIndex = -1;
          for(int j = 0;j<blocks.size();j++){
              if(blocks[j] >= processes[i] && flagforblocks[j] == 0){
                  if(bestIndex == -1){ bestIndex = j;}
                  else if(blocks[bestIndex] > blocks[j]){
                      bestIndex = j;
                     
                  }
              }
          }
          if(bestIndex != -1){
              allo[i] = bestIndex;
              blocks[bestIndex] -= processes[i];
              flagforblocks[bestIndex] = 1;
          }
      }
      
      cout << "\nProcess No.\tProcess Size\tBlock no." << endl;
        for (int i = 0; i < processes.size(); i++)
        {
            cout << i + 1 << "\t\t" << processes[i] << "\t\t";
            if (allo[i] != -1)
                cout << allo[i] + 1;
            else
                cout << "Not Allocated";
            cout << endl;
        }
    }
    
    void nextfit(){
        input();
        
        vector<int> allo(processes.size(),-1);
        for(int i = 0;i<processes.size();i++){
            // cout<<"prev - "<<prev<<endl;
            // if(prev == blocks.size()) break;
            for(int j = prev;j<blocks.size();j++){
                // cout<<"j - "<<j<<endl;
                if(blocks[j] >= processes[i] && flagforblocks[j] == 0){
                    // cout<<"ghussa hua j - "<<j<<endl;
                    allo[i] = j;
                    blocks[j] -= processes[i];
                    flagforblocks[j] = 1;
                    prev = j;
                    break;
                }
            }
        }
        
         cout << "\nProcess No.\tProcess Size\tBlock no." << endl;
        for (int i = 0; i < processes.size(); i++)
        {
            cout << i + 1 << "\t\t" << processes[i] << "\t\t";
            if (allo[i] != -1)
                cout << allo[i] + 1;
            else
                cout << "Not Allocated";
            cout << endl;
        }
    }
    
    void  worstfit(){
      input();
      
      vector<int> allo(processes.size(),-1);
      
      for(int i = 0;i<processes.size();i++){
          int bestIndex = -1;
          for(int j = 0;j<blocks.size();j++){
              if(blocks[j] >= processes[i] && flagforblocks[j] == 0){
                  if(bestIndex == -1){ bestIndex = j;}
                  else if(blocks[bestIndex] < blocks[j]){
                      bestIndex = j;
                     
                  }
              }
          }
          if(bestIndex != -1){
              allo[i] = bestIndex;
              blocks[bestIndex] -= processes[i];
              flagforblocks[bestIndex] = 1;
          }
      }
      
      cout << "\nProcess No.\tProcess Size\tBlock no." << endl;
        for (int i = 0; i < processes.size(); i++)
        {
            cout << i + 1 << "\t\t" << processes[i] << "\t\t";
            if (allo[i] != -1)
                cout << allo[i] + 1;
            else
                cout << "Not Allocated";
            cout << endl;
        }
    }
    
    
  
  
};
int main()
{
    mm mp;
    // mp.input();
    bool repeat = true;
    int choice;

    while(repeat) {
        cout<<"### MENU ###"<<endl;
        cout<<"1. First Fit"<<endl;
        cout<<"2. Best Fit"<<endl;
        cout<<"3. Next Fit"<<endl;
        cout<<"4. Worst Fit"<<endl;
        cout<<"5. Exit"<<endl;
        cout<<endl;
        cout<<"Enter your choice:";
        cin>>choice;
        cout<<endl;

        switch(choice) {
            case 1:
            cout<<"First Fit Algorithm"<<endl;
            mp.firstfit();
            break;

            case 2:
            cout<<"Best Fit ALgorithm"<<endl;
            mp.bestfit();
            break;

            case 3:
            cout<<"Next Fit Algorithm"<<endl;
            mp.nextfit();
            break;

            case 4:
            cout<<"Worst Fit Algorithm"<<endl;
            mp.worstfit();
            break;

            default:
            cout<<"Exiting the code"<<endl;
            repeat = false;
            break;
        }
    }

    return 0;
}