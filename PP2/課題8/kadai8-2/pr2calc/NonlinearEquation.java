package pr2calc;
import java.lang.Math;

public class NonlinearEquation{
    public static final double EPSILON = 0.001;
    public static final int MAXIMUM_IT = 100;
    public static final double ALPHA   = 2.0; // f(x)�Ɋ܂܂��alpha
    
    public double initialValue_;
    public double answer_;
    public int iteration_;
    
    // constructor
    public NonlinearEquation(double initV){
        this.initialValue_ = initV;
        this.iteration_ = 0;
    }

    public double function(double x){
        double y = Math.sqrt(10 + ALPHA + x);
        return y;
    }

    public void _solveNLEByLinearIteration(){
        double value;      // x_k �ɑΉ�
        double pastValue;  // x_{k-1} �ɑΉ��i�����pastValue = x_0�Ƃ���j
        pastValue = this.initialValue_;
        while(true){
            value = function(pastValue);
            System.out.println("value = " + value + " , pastValue = " + pastValue);
            this.iteration_ += 1;
            if(Math.abs(value - pastValue) < EPSILON || this.iteration_ >= MAXIMUM_IT){
                this.answer_ = value;
                break;
            }
            pastValue = value;
        }
    }
}