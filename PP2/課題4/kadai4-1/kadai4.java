import pr2calc.Matrix;
import java.io.*;

public class kadai4{
    public static void main(String[] args) {
		/*
		 * main メソッド中で今回作成した内積計算メソッドや行列同士、ベクトルと行列、
		 * 行列とベクトルの積を計算するメソッドが正常に動いているかを確認せよ。
		 */

		Matrix mat1,mat2,mat1_t,mat2_t;

		double[][]  m1 = { { 1.0, 2.0, 3.0 }, { 3.0, 2.0, -1.0 }, { 4.0, 2.0, 6.0 } },
                    m2 = { { 5.0, 3.0, 1.0 }, { 3.0, -3.0, 2.0 }};
		mat1 = new Matrix(m1);
		mat2 = new Matrix(m2);
		// mat1 -> transpose
		/*
		System.out.println("1.x(matrix)");
		mat1.display("matrix");
		System.out.println("x >> transpose:");
		mat1_t = mat1.transpose();
		mat1_t.display("matrix");
		*/
		// mat2 -> transpose
		System.out.println("2.x(Matrix)");
		mat2.display("matrix");
		System.out.println("x >> transpose:");
		mat2.transpose().display("matrix");
		// mat2_t = mat2.transpose();
		// mat2_t.display("matrix");
	}
}