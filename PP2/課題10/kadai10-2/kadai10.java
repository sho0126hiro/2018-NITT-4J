import pr2calc.*;
import java.io.*;

public class kadai10{
    public static void main(String[] args) {
		double x_0 = 0.0;
		NonlinearEquation eqn = new NonlinearEquation();
		eqn._solveNLEByRegulaFalsi();
		if(eqn.iteration_ >= eqn.MAXIMUM_IT){
			System.out.println("âÇ™å©Ç¬Ç©ÇËÇ‹ÇπÇÒÇ≈ÇµÇΩÅB");
		}else{
			System.out.println("X = "+ eqn.answer_+ " at iteration "+eqn.iteration_+".");
		}
	}
}

/*
xNext = 3.6283513111891135, f(xNext)=-0.10820710224503294, xPastNext = 0.0
xNext = 2.9308132021587436, f(xNext)=-0.1979876501172628, xPastNext = 3.6283513111891135
xNext = 2.04170427220361, f(xNext)=-0.1938282059324413, xPastNext = 2.9308132021587436
xNext = 1.4314437304323238, f(xNext)=-0.08329133148712527, xPastNext = 2.04170427220361
xNext = 1.209807777900147, f(xNext)=-0.02123561193022515, xPastNext = 1.4314437304323238
xNext = 1.1558219516951447, f(xNext)=-0.0045087518096415405, xPastNext = 1.209807777900147
xNext = 1.1444722193896844, f(xNext)=-9.157536207905594E-4, xPastNext = 1.1558219516951447
xNext = 1.1421716567807858, f(xNext)=-1.8426846839878023E-4, xPastNext = 1.1444722193896844
X = 1.141708923799169 at iteration 8.
*/