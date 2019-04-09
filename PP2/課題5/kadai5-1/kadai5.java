import pr2calc.*;
import java.io.*;

public class kadai5{
    public static void main(String[] args) {
		double[][]  m1 = { { 1.0, 2.0, 3.0 }, { 3.0, 2.0, -1.0 }, { 4.0, 2.0, 6.0 } };
		SimultaneousEquation mat1 = new SimultaneousEquation(m1);
		mat1.display("matrix");
		// System.out.println("****************");
		// mat1.display("matrix");
		System.out.println("****************");
		// mat1.normalize(2);
		mat1.subtractRowFrom(1,2);
		mat1.subtractRowFrom(1,3);
		mat1.display("matrix");
	}
}