import pr2calc.*;
import java.io.*;

public class kadai8{
    public static void main(String[] args) {
		double x_0 = 0.0;
		NonlinearEquation eqn = new NonlinearEquation(x_0);
		eqn._solveNLEByLinearIteration();
		if(eqn.iteration_ >= eqn.MAXIMUM_IT){
			System.out.println("‰ğ‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ‚Å‚µ‚½B");
		}else{
			System.out.println("X = "+ eqn.answer_+ " at iteration "+eqn.iteration_+".");
		}
	}
}