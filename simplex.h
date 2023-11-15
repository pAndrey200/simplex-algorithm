#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class Simplex{

    private:
        int rows, cols;
        std::vector <std::vector<float> > A;
        std::vector<float> B;
        std::vector<float> C;

        float maximum;

        bool isUnbounded;
        bool simplexAlgorithmCalculataion(){
            if(checkOptimality()){
			    return true;
            }

            int pivotColumn = findPivotColumn();
            int pivotRow = findPivotRow(pivotColumn);

            if(isUnbounded == true){
                cout<<"Error unbounded"<<endl;
			    return true;
            }

            doPivotting(pivotRow,pivotColumn);

            return false;
        }

        bool checkOptimality(){
            for(int i=0; i<C.size();i++){
                if(C[i] < 0){
                    return false;
                }
            }
            return true;
        }

        void doPivotting(int pivotRow, int pivotColumn){
            maximum = maximum - (C[pivotColumn]*(B[pivotRow]/A[pivotRow][pivotColumn]));
            for(int i = 0; i < rows;i++){
                for(int j = 0;j<cols;++j){
                    if(i == pivotRow || j == pivotColumn){
                        continue;
                    }
                    else{
                        A[i][j] -= A[pivotRow][j] * A[i][pivotColumn] / A[pivotRow][pivotColumn];
                    }
                }
            }
            for(int i = 0; i < rows;i++){
                if(i != pivotRow){
                    B[i] -= B[pivotRow] * A[i][pivotColumn] / A[pivotRow][pivotColumn];
                }
            }
            B[pivotRow]/=A[pivotRow][pivotColumn];
            for(int i = 0; i < cols;i++){
                if(i != pivotColumn){
                    C[i] -= A[pivotRow][i] * C[pivotColumn] / A[pivotRow][pivotColumn];
                }
            }
            C[pivotColumn] = 0;
            for(int i = 0; i < rows;i++){
                if(i != pivotRow){
                    A[i][pivotColumn] = 0;
                }
            }
            int pivotPoint = A[pivotRow][pivotColumn];
            for(int i = 0; i < cols;i++){
                A[pivotRow][i]/=pivotPoint;
            }
            
        }

        void print(){
            for(int i=0; i<rows;i++){
                for(int j=0;j<cols;j++){
                    cout<<A[i][j] <<" ";
                }
                cout<<endl;
            }
            cout<<endl;
            for(int i=0; i<rows;i++){
                cout << B[i] << "  ";
            }
            cout<<endl;
            for(int i=0; i<cols;i++){
                cout << C[i] << "  ";
            }
            cout <<endl << endl;
        }

        int findPivotColumn(){

            int location = 0;
            float minm = C[0];
            for(int i=1;i<C.size();i++){
                if(C[i]<minm){
                    minm = C[i];
                    location = i;
                }
            }
            return location;

        }

        int findPivotRow(int pivotColumn){

            int negativeValueCount = 0;

            for(int i=0;i<rows;i++){
                if(A[i][pivotColumn]<0){
                    negativeValueCount++;
                }
            }

            if(negativeValueCount==rows){
                isUnbounded = true;
                return 0;
            }
            
            float minimum = 99999999;
            int location = 0;
            for(int i=0;i<rows;i++){
                if(A[i][pivotColumn]<=0) continue;
                
                if(B[i]/A[i][pivotColumn]<minimum){
                    minimum = B[i]/A[i][pivotColumn];
                    location = i;
                }
                
            }
            return location;

        }

        

    public:
        Simplex(std::vector <std::vector<float> > matrix,std::vector<float> b ,std::vector<float> c){
            maximum = 0;
            isUnbounded = false;
            rows = matrix.size();
            cols = matrix[0].size();
            A.resize( rows , vector<float>( cols , 0 ) );
            B.resize(b.size());
            C.resize(c.size());

            for(int i= 0;i<rows;i++){            
                for(int j= 0; j< cols;j++ ){
                    A[i][j] = matrix[i][j];

                }
            }

            for(int i=0; i< c.size() ;i++ ){    
                C[i] = c[i] ;
            }
            for(int i=0; i< b.size();i++ ){      
                B[i] = b[i];
            }
        }
        void CalculateSimplex(){
            bool end = false;

            cout<<"initial array(Not optimal)"<<endl;
            print();

            cout<<" "<<endl;
            cout<<"final array(Optimal solution)"<<endl;


            while(!simplexAlgorithmCalculataion()){}
            print();
            cout<<"Answers for the Constraints of variables"<<endl;

            for(int i=0;i< cols; i++){  //every basic column has the values, get it form B array
                int count0 = 0;
                int index = 0;
                for(int j=0; j< rows; j++){
                    if(A[j][i]==0.0){
                        count0 += 1;
                    }
                    else if(A[j][i]==1){
                        index = j;
                    }

                }

                if(count0 == rows -1 ){

                    cout<<"variable"<<index+1<<": "<<B[index]<<endl;  //every basic column has the values, get it form B array
                }
                else{
                    cout<<"variable"<<index+1<<": "<<0<<endl;

                }

            }

           cout<<""<<endl;
           cout<<"maximum value: "<<maximum<<endl;  //print the maximum values

        }

};