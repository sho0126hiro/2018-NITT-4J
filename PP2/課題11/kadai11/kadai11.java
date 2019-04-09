import pr2calc.*;
import java.io.*;

public class kadai11{
    public static void main(String[] args) {
		double x_0 = 0.0;
		NonlinearEquation eqn = new NonlinearEquation();
		eqn._solveNLEByNewton();
		if(eqn.iteration_ >= eqn.MAXIMUM_IT){
			System.out.println("解が見つかりませんでした。");
		}else{
			System.out.println("X = "+ eqn.answer_+ " at iteration "+eqn.iteration_+".");
		}
	}
}

/*
微分の式について、手計算の式を用いた場合
xNext = 1.8528040594471646, f(xNext)=-0.16942257287404386
xNext = 1.5867621726391166, f(xNext)=-0.12005559975566239
xNext = 1.4799718266340227, f(xNext)=-0.09539117818313993
xNext = 1.4613243208825182, f(xNext)=-0.09080681532456922
X = 1.4607668922568422 at iteration 4.
微分の式について、中心差分の考え方を適用した場合
xNext = 1.8524810361582826, f(xNext)=-0.1693732488385101
xNext = 1.586627040834545, f(xNext)=-0.12002611741869254
xNext = 1.4799488981992903, f(xNext)=-0.09538559155781044
xNext = 1.461325855078881, f(xNext)=-0.09080719585133039
X = 1.4607669834535368 at iteration 4.
*/