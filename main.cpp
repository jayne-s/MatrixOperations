#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

class Matrix{
private:
vector<vector<double>> v;

public:
Matrix(){
  v = {{1,0,0},{0,1,0},{0,0,1}};
}
void show(){
  for (int row = 0; row < 3; row++){
    for (int col = 0; col < 3; col++){
      cout << fixed << setprecision(5) << this->v[row][col] << ", ";
    }
    cout << endl;
  }
}
double getValue(int row, int col){
  return this->v[row][col];
}
void setValue(int row, int col, double val){
 this->v[row][col] = val;
}
Matrix operator- (Matrix that){
  Matrix result;
  for (int row = 0; row < 3; row++){
    for(int col = 0; col < 3; col++){
     result.v[row][col] = that.v[row][col] - this->v[row][col];
    }
  }
  return result;
}

 Matrix operator* (Matrix that){
   Matrix result;
   int i,j,k;
   double sum;
   for (i = 0; i < 3; i++){
     for (j = 0; j < 3; j++){
       sum = 0.0;
       for (k = 0; k < 3; k++){
         sum = sum + this->v[i][k] * (that.v[k][j]);
       }
       result.v[i][j] = sum;
     }
   }
   return result;
 }

Matrix operator+ (Matrix that){
  Matrix result;
  for (int row = 0; row < 3; row++){
    for(int col = 0; col < 3; col++){
     result.v[row][col] = this->v[row][col] + that.v[row][col];
    }
  }
  return result;
}

double subDet(int row, int col){
  double result;

      if(row == 0 && col == 0){
        result = (this->v[1][1] * this->v[2][2]) - (this->v[1][2] * this->v[2][1]);
      }
      else if (row == 0 && col ==1){
        result = (this->v[1][0] * this->v[2][2]) - (this->v[1][2] * this->v[2][0]);
      }
      else if (row == 0 && col == 2){
        result = (this->v[1][0] * this->v[2][1]) - (this->v[1][1] * this->v[2][0]);
      }
      else if (row == 1 && col == 0){
        result = (this->v[0][1] * this->v[2][2]) - (this->v[0][2] * this->v[2][1]);
      }
      else if (row == 1 && col == 1){
        result = (this->v[0][0] * this->v[2][2]) - (this->v[1][2] * this->v[2][0]);
      }
      else if (row == 1 && col == 2){
        result = (this->v[1][1] * this->v[2][1]) - (this->v[0][1] * this->v[2][0]);
      }
      else if (row == 2 && col == 0){
        result = (this->v[0][1] * this->v[1][2]) - (this->v[0][2] * this->v[1][1]);
      }
      else if (row == 2 && col == 1){
        result = (this->v[0][0] * this->v[1][2]) - (this->v[0][2] * this->v[1][0]);
      }
      else if (row == 2 && col == 2){
        result = (this->v[0][0] * this->v[1][1]) - (this->v[0][1] * this->v[1][0]);
      }
    
  return result;
}

double Determinant(){
  double firstsubDet = this->subDet(0,0);
  double secondsubDet = this->subDet(0,1);
  double thirdsubDet = (this->subDet(0,2));
  double result = ((firstsubDet) * (this->v[0][0])) - ((secondsubDet) * (this->v[0][1])) + ((thirdsubDet) * (this->v[0][2]));
  return result;
}

Matrix CoFactor(){
  Matrix results;
  for(int row = 0; row < 3; row++){
    for(int col = 0; col < 3; col++){
      results.setValue(row, col, (this->subDet(row,col) * pow(-1, col)));
    }
  }
  return results;   
}

Matrix Adjoint(){
  Matrix resultes;
  for(int row = 0; row < 3; row++){
    for(int col = 0; col < 3; col++){
      resultes.setValue(row, col, this->v[row][col]);
    }
  }
  return resultes;
}

Matrix Inverse(){
  Matrix result1;
  double determinant = this->Determinant();
  Matrix temp1 = this->CoFactor();
  Matrix temp2 = temp1.Adjoint();
  for(int row = 0; row < 3; row++){
    for (int col = 0; col < 3; col++){
      result1.setValue(row, col, (temp2.getValue(row,col) / determinant));
    }
  }
  return result1;
}

};


int main(){
srand(time(0));
cout << "Demonstrate the Constructor" << endl;
Matrix a,b,c;
int row, col;
for(row = 0; row < 3; row++){
  for(col = 0; col < 3; col++){
    a.setValue(row,col,rand()%100);
  }
}
for(row = 0; row < 3; row++){
  for(col = 0; col < 3; col++){
     b.setValue(row,col,rand()%100);
  }
}
c.show();
cout << endl;

cout << "Demonstrate Addition" << endl;
c = a.operator+(b);
a.show();
cout << endl;
b.show();
cout << endl;
c.show();
cout << endl;

cout << "Demonstrate Subtraction" << endl;
c = b.operator-(a);
a.show();
cout << endl;
b.show();
cout << endl;
c.show();
cout << endl;

cout << "Demonstrate Inverse" << endl;
b = a.Inverse();
c = a.operator*(b);
a.show();
cout << endl;
b.show();
cout << endl;
c.show();
cout << endl;
 
  return 0;
}
