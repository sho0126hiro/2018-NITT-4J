import pr2calc.Matrix;
import java.io.*;

public class kadai4{
    public static void main(String[] args) {
		/*
		 * main ���\�b�h���ō���쐬�������όv�Z���\�b�h��s�񓯎m�A�x�N�g���ƍs��A
		 * �s��ƃx�N�g���̐ς��v�Z���郁�\�b�h������ɓ����Ă��邩���m�F����B
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