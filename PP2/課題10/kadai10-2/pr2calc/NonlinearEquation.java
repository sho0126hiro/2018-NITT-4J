package pr2calc;
import java.lang.Math;

public class NonlinearEquation{
    public static final double EPSILON = 0.001;
    public static final int MAXIMUM_IT = 100; // �ő厎�s��
    public static final double ALPHA   = 2.0; // f(x)�Ɋ܂܂��alpha (kadai8)
    public static final double ALPHA2  = 2.0; //  f2(x)�Ɋ܂܂��alpha (kadai9-kadai10)
    public static final double POSITIVE_MAX = 4.0;
    public static final double NEGATIVE_MAX = 0.0;

    public double initialValue_;
    public double answer_;
    public int iteration_;
    
    // constructor
    public NonlinearEquation(double initV){
        this.initialValue_ = initV;
        this.iteration_ = 0;
    }
    public NonlinearEquation(){
        this.iteration_ = 0;
    }

    public double function(double x){
        double y = Math.sqrt(10 + ALPHA + x);
        return y;
    }

    /**
     * ���`�����@�ɂ���Ĕ���`������������
     */
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

    /**
     * kadai9�ŗ^����ꂽ�֐�
     */
    public double function2(double x){
        if(x == -1*ALPHA2) return 1.0;
        return (Math.sin(x + ALPHA2))/ (x + ALPHA2);
    }
    
    /**
     * �����𔻒肷��
     * @return 1 : �� , -1 : �� , 0 : �[�� >> �I��
     */
    public int checkSign(double fx){
        if(fx<0)         return -1;
        else if(fx == 0) return  0;
        else             return  1; 
    }
    /**
     * �񕪖@�ɂ���Ĕ���`������������
     */
    public void _solveNLEByBisectionMethod(){
        double value_max;      // x_k �ɑΉ�
        double value_min;      // x_{k-1} �ɑΉ��i�����pastValue = x_0�Ƃ���j
        double nextValue;
        double xPastMid = 0.0; // �O��̒����l���i�[����i�\���p�j
        value_min = NEGATIVE_MAX;
        value_max     = POSITIVE_MAX;
        while(true){
            nextValue = 0.5*(value_min+value_max);
            if(checkSign(function2(nextValue))==0){
                this.answer_ = nextValue;
                break;
            }
            if(Math.abs(nextValue - value_min) < EPSILON || this.iteration_ >= MAXIMUM_IT){
                this.answer_ = nextValue;
                break;
            }
            // xMid = 3.0, f(xMid)=0.0470400026866224, xPastMid = 0.0
            System.out.println("xMid = "+nextValue + ", f(xMid)="+function2(nextValue)+", xPastMid = "+xPastMid);
            if(checkSign(function2(value_min)) == checkSign(function2(nextValue))){
            // fx0�Ɠ�����
                value_min = nextValue;
            }else if(checkSign(function2(value_max)) == checkSign(function2(nextValue))){
            // fx1�Ɠ�����
                value_max = nextValue;
            }
            xPastMid = nextValue;
            this.iteration_ += 1;
        }
    }
    /**
     * �͂��݂����@�ɂ���Ĕ���`������������
     */
    public void _solveNLEByRegulaFalsi(){
        double value_max;      // x_k �ɑΉ�
        double value_min;      // x_{k-1} �ɑΉ��i�����pastValue = x_0�Ƃ���j
        double nextValue;
        double xPast = 0.0; // �O���nextValue�����߂�
        value_min = NEGATIVE_MAX;
        value_max     = POSITIVE_MAX;
        while(true){
            nextValue = (value_min * function2(value_max) - value_max * function2(value_min)) / (function2(value_max)-function2(value_min)); 
            // ������0�Ȃ�I��
            if(function2(nextValue)== 0){
                this.answer_ = nextValue;
                break;
            }
            // �I������
            if(Math.abs(nextValue - value_min) < EPSILON || Math.abs(value_max-nextValue)<EPSILON || this.iteration_ >= MAXIMUM_IT){
                this.answer_ = nextValue;
                break;
            }
            System.out.println("xNext = "+nextValue + ", f(xNext)="+function2(nextValue)+", xPastNext = "+xPast);
            if(checkSign(function2(value_min)) == checkSign(function2(nextValue))){
            // fx0�Ɠ�����
                value_min = nextValue;
            }else if(checkSign(function2(value_max)) == checkSign(function2(nextValue))){
            // fx1�Ɠ�����
                value_max = nextValue;
            }
            xPast = nextValue;
            this.iteration_ += 1;
        }
    }
}