import pr2calc.Matrix;
import java.io.*;

public class kadai3{
    public static void main(String[] args) {
		/*
		 * main メソッド中で今回作成した内積計算メソッドや行列同士、ベクトルと行列、
		 * 行列とベクトルの積を計算するメソッドが正常に動いているかを確認せよ。
		 */

		Matrix mat11,mat12,mat21,mat22,mat31,mat32,mat41,mat42,mat51,mat52;

		double[]     v1 = { 2.0, -3.0, 7.0 },
					 v2 = {-1.0, -2.0, 2.0};

		double[][]  m21 = { { 1.0, 2.0, 3.0 }, { 3.0, 2.0, -1.0 }, { 4.0, 2.0, 6.0 } },
                    m22 = { { 5.0, 3.0, 1.0 }, { 3.0, -3.0, 2.0 }},
                    m31 = { { 3.0 }, { -2.0 }},
                    m32 = { { 3.0, 7.0, -5.0, 2.0} },
                    m41 = { { 1.0, 2.0, 3.0 }, { 3.0, 2.0, -1.0 }, { 4.0, 2.0, 6.0 } },
                    m42 = { { 8.0, 2.0 }, { -3.0, 2.0 }, { 1.0, 6.0 } },
                    m51 = { { 2.0,-3.0}, {4.0, 2.0}},
					m52 = { {-5.0,-3.0, 1.0 }, {-3.0,  3.0, 2.0}};
		
		mat11 = new Matrix(v1);
		mat12 = new Matrix(v2);
		mat21 = new Matrix(m21);
		mat22 = new Matrix(m22);
		mat31 = new Matrix(m31);
		mat32 = new Matrix(m32);
		mat41 = new Matrix(m41);
		mat42 = new Matrix(m42);
		mat51 = new Matrix(m51);
		mat52 = new Matrix(m52);

		// Q1
		System.out.println("1.x(vector)・y(vector)");
		System.out.println("x(vector):");		
		mat11.display("vector");
		System.out.println("y(vector):");
		mat12.display("vector");
		double answer1 = mat11.getInnerProduct(mat12);
		System.out.println("A. "+ answer1);
		// Q2
		System.out.println("2.x(Matrix)・y(Matrix)");
		System.out.println("x(Matrix):");		
		mat21.display("matrix");
		System.out.println("y(Matrix):");		
		mat22.display("matrix");
		Matrix answer2;
		answer2 = mat21.multiplyMatrix(mat22);
		answer2.display("matrix");
		// Q3
		System.out.println("3.x(Matrix)・y(Matrix)");
		System.out.println("x(Matrix):");		
		mat31.display("matrix");
		System.out.println("y(Matrix):");		
		mat32.display("matrix");
		System.out.println("Answer : ");		
		Matrix answer3;
		answer3 = mat31.multiplyMatrix(mat32);
		answer3.display("matrix");
		// Q4
		System.out.println("4.x(Matrix)・y(Matrix)");
		System.out.println("x(Matrix):");		
		mat41.display("matrix");
		System.out.println("y(Matrix):");		
		mat42.display("matrix");
		System.out.println("Answer : ");		
		Matrix answer4;
		answer4 = mat41.multiplyMatrix(mat42);
		answer4.display("matrix");
		// Q5
		System.out.println("5.x(Matrix)・y(Matrix)");
		System.out.println("x(Matrix):");		
		mat51.display("matrix");
		System.out.println("y(Matrix):");		
		mat52.display("matrix");
		System.out.println("Answer : ");		
		Matrix answer5;
		answer5 = mat51.multiplyMatrix(mat52);
		answer5.display("matrix");
	}
}