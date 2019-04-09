import pr2calc.*;
import java.io.*;

public class kadai9{
    public static void main(String[] args) {
		double x_0 = 0.0;
		NonlinearEquation eqn = new NonlinearEquation();
		eqn._solveNLEByBisectionMethod();
		if(eqn.iteration_ >= eqn.MAXIMUM_IT){
			System.out.println("âÇ™å©Ç¬Ç©ÇËÇ‹ÇπÇÒÇ≈ÇµÇΩÅB");
		}else{
			System.out.println("X = "+ eqn.answer_+ " at iteration "+eqn.iteration_+".");
		}
	}
}

/*
xMid = 2.5, f(xMid)=-0.10022377933989138, xPastMid = 0.0
xMid = 1.25, f(xMid)=0.345810309727965, xPastMid = 2.5
xMid = 1.875, f(xMid)=0.09163338899597247, xPastMid = 1.25
xMid = 2.1875, f(xMid)=-0.014397246516950494, xPastMid = 1.875
xMid = 2.03125, f(xMid)=0.036327876952067746, xPastMid = 2.1875
xMid = 2.109375, f(xMid)=0.010359664031320402, xPastMid = 2.03125
xMid = 2.1484375, f(xMid)=-0.0021740285336127904, xPastMid = 2.109375
xMid = 2.12890625, f(xMid)=0.004054472162812196, xPastMid = 2.1484375
xMid = 2.138671875, f(xMid)=9.305765474322396E-4, xPastMid = 2.12890625
xMid = 2.1435546875, f(xMid)=-6.241445899367854E-4, xPastMid = 2.138671875
xMid = 2.14111328125, f(xMid)=1.5261223601674287E-4, xPastMid = 2.1435546875
xMid = 2.142333984375, f(xMid)=-2.3591722617347872E-4, xPastMid = 2.14111328125
X = 2.1417236328125 at iteration 12.
*/