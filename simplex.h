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

            float pivetValue = A[pivotRow][pivotColumn];//gets the pivot value

            float pivotRowVals[cols];//the column with the pivot

            float pivotColVals[rows];//the row with the pivot

            float rowNew[cols];//the row after processing the pivot value

            maximum = maximum - (C[pivotColumn]*(B[pivotRow]/pivetValue));  //set the maximum step by step
             //get the row that has the pivot value
             for(int i=0;i<cols;i++){
                pivotRowVals[i] = A[pivotRow][i];
             }
             //get the column that has the pivot value
             for(int j=0;j<rows;j++){
                pivotColVals[j] = A[j][pivotColumn];
            }

            //set the row values that has the pivot value divided by the pivot value and put into new row
             for(int k=0;k<cols;k++){
                rowNew[k] = pivotRowVals[k]/pivetValue;
             }

            B[pivotRow] = B[pivotRow]/pivetValue;


             //process the other coefficients in the A array by subtracting
             for(int m=0;m<rows;m++){
                //ignore the pivot row as we already calculated that
                if(m !=pivotRow){
                    for(int p=0;p<cols;p++){
                        float multiplyValue = pivotColVals[m];
                        A[m][p] = A[m][p] - (multiplyValue*rowNew[p]);
                        //C[p] = C[p] - (multiplyValue*C[pivotRow]);
                        //B[i] = B[i] - (multiplyValue*B[pivotRow]);
                    }

                }
             }

            //process the values of the B array
            for(int i=0;i<B.size();i++){
                if(i != pivotRow){

                        float multiplyValue = pivotColVals[i];
                        B[i] = B[i] - (multiplyValue*B[pivotRow]);

                }
            }
                //the least coefficient of the constraints of the objective function
                float multiplyValue = C[pivotColumn];
                //process the C array
                 for(int i=0;i<C.size();i++){
                    C[i] = C[i] - (multiplyValue*rowNew[i]);

                }


             //replacing the pivot row in the new calculated A array
             for(int i=0;i<cols;i++){
                A[pivotRow][i] = rowNew[i];
             }


        }

        void print(){
            for(int i=0; i<rows;i++){
                for(int j=0;j<cols;j++){
                    cout<<A[i][j] <<" ";
                }
                cout<<""<<endl;
            }
            cout<<""<<endl;
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

        void CalculateSimplex(){
            bool end = false;

            cout<<"initial array(Not optimal)"<<endl;
            print();

            cout<<" "<<endl;
            cout<<"final array(Optimal solution)"<<endl;


            while(!end){

                bool result = simplexAlgorithmCalculataion();

                if(result==true){

                    end = true;


                    }
            }
            print();
            cout<<"Answers for the Constraints of variables"<<endl;

            for(int i=0;i< A.size(); i++){  //every basic column has the values, get it form B array
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