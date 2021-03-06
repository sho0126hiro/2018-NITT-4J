import pr2calc.*;
import java.io.*;

public class kadai5{
    public static void main(String[] args) {
		/*
		double[][] m1 = { { 4.0, 3.0, 2.0, 1.0,  4.0},
						  {-2.0, 4.0,-6.0, 8.0,-34.0},
						  { 3.0, 2.0,-3.0,-3.0, -4.0},
						  {12.0, 6.0, 7.0, 5.0, 18.5},
						};
		*/
		double[][] m1 = { { 2.0, 1.0, 3.0, 4.0,  2.0},
						  { 3.0, 2.0, 5.0, 2.0, 12.0},
						  { 3.0, 4.0, 1.0,-1.0,  4.0},
						  {-1.0,-3.0, 1.0, 3.0, -1.0},
						};
		SimultaneousEquation mat1 = new SimultaneousEquation(m1);
		mat1.display("matrix");
		mat1.solveByGaussJordan();
	}
}
/********************** 実行結果 ******************************
[2.0 1.0 3.0 4.0 2.0]
[3.0 2.0 5.0 2.0 12.0]
[3.0 4.0 1.0 -1.0 4.0]
[-1.0 -3.0 1.0 3.0 -1.0]

1行1列目が1となるように割り、他の行の1列目が0となるように引く
[1.0 0.5 1.5 2.0 1.0]
[0.0 0.5 0.5 -4.0 9.0]
[0.0 2.5 -3.5 -7.0 1.0]
[0.0 -2.5 2.5 5.0 0.0]

2行2列目が1となるように割り、他の行の2列目が0となるように引く
[1.0 0.0 1.0 6.0 -8.0]
[0.0 1.0 1.0 -8.0 18.0]
[0.0 0.0 -6.0 13.0 -44.0]
[0.0 0.0 5.0 -15.0 45.0]

3行3列目が1となるように割り、他の行の3列目が0となるように引く
[1.0 0.0 0.0 8.166666666666666 -15.333333333333332]
[0.0 1.0 0.0 -5.833333333333334 10.666666666666668]
[-0.0 -0.0 1.0 -2.1666666666666665 7.333333333333333]
[0.0 0.0 0.0 -4.166666666666668 8.333333333333336]

4行4列目が1となるように割り、他の行の4列目が0となるように引く
[1.0 0.0 0.0 0.0 1.0]
[0.0 1.0 0.0 0.0 -1.0]
[-0.0 -0.0 1.0 0.0 3.0]
[-0.0 -0.0 -0.0 1.0 -2.0]

Answer:
x1 = 1.0, x2 = -1.0, x3 = 3.0, x4 = -2.0.
***************************************************************/