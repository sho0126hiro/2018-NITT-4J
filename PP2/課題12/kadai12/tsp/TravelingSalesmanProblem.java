package tsp;
import java.io.*;

public class TravelingSalesmanProblem{
    public int[] _answer_route; // �s�s���[�g�ԍ����J�n�_���珇�Ԃɓ���
    public double _answer_distance; // �œK���̋���
    public double[] _distance_process; // �m�[�h�Ԃ̋�������������(debug�p)
    public static final int CITY_NUM=5000; // �s�s��

    protected double[][] _data; // ���f�[�^
    protected int _now_index; // ���̃m�[�h�̌��������Ă���index 
    protected boolean[] _visited; // �K�₳��Ă��邩
    protected int _searchCount; // ���߂����̃m�[�h��

    /**
     * constructor
     * �J�n�_���w�肵�Ȃ��ꍇ�Aindex=0����T��������B
     */
    public TravelingSalesmanProblem(double[][] data){
        this._distance_process = new double[CITY_NUM+1];
        this._answer_route = new int[CITY_NUM+1];
        this._data = new double[CITY_NUM][CITY_NUM];
        this._visited = new boolean[CITY_NUM];
        this._now_index = 0;
        this._answer_distance = 0.0;
        this._searchCount = 0;
        for(int i=0;i<data.length;i++){
            for(int j=0;j<data.length;j++){
                this._data[i][j] = data[i][j];
            }
            this._visited[i] = false;
        }

    }
    /**
     * constructor(�J�n�_�w��̏ꍇ)
     */
    public TravelingSalesmanProblem(double[][] data,int startIndex){
        this._distance_process = new double[CITY_NUM+1];
        this._answer_distance = 0.0;
        this._answer_route = new int[CITY_NUM+1];
        this._data = new double[CITY_NUM][CITY_NUM];
        this._visited = new boolean[CITY_NUM];
        this._now_index = startIndex;
        this._searchCount = 0;

        for(int i=0;i<data.length;i++){
            for(int j=0;j<data.length;j++){
                this._data[i][j] = data[i][j];
            }
            this._visited[i] = false;
        }
    }

    /**
     * nowIndex�����ԋ߂��m�[�hindex�����߁A
     * �����ƃ��[�g�ɒl��������B
     * @param {int} nowIndex
     * @return {int} nextIndex
     */
    protected int _NNgetNextIndex(int nowIndex){
        int i,j,nextIndex=-1;
        double min_distance = Double.MAX_VALUE; 
        for(i=0;i<CITY_NUM;i++){
            if(this._visited[i] || (this._data[nowIndex][i] == -1.0))continue;
            if(min_distance > this._data[nowIndex][i]){
                min_distance = this._data[nowIndex][i];
                nextIndex = i;
            }
        }
        this._searchCount++;
        this._distance_process[this._searchCount] = min_distance;
        this._answer_distance += min_distance;
        this._visited[nextIndex] = true;
        this._answer_route[this._searchCount] = nextIndex;
        return nextIndex;
    }

    /**
     * NearestNeibour�@���g���ĉ���
     */
    public void NearestNeibour(){
        int first=this._now_index;
        this._answer_route[this._searchCount] = this._now_index;
        this._distance_process[this._searchCount] = 0;
        this._visited[this._now_index] = true;
        for(int i=0;i<CITY_NUM-1;i++){
            this._now_index = this._NNgetNextIndex(this._now_index);
        }
        // �o���n�ɖ߂�
        this._answer_distance += this._data[this._now_index][first];
        this._answer_route[this._searchCount+1] = first;
        this._distance_process[this._searchCount+1] = this._data[this._now_index][first];
    }

    /**
     * ���ׂĂ̓s�s�������l�Ƃ��ANearestNeibour�@��p���ĉ����B
     */
    public void NN_all(){
        double min_distance = Double.MAX_VALUE;
        int[] min_route = new int[CITY_NUM+1];
        double[] min_process = new double[CITY_NUM+1];
        for(int i=0;i<CITY_NUM;i++){
            this._answer_distance = 0.0;
            this._searchCount = 0;
            this._now_index = i;
            for(int j=0;j<CITY_NUM;j++) this._visited[j] = false;
            this.NearestNeibour();
            System.out.println(this._answer_distance);
            if(min_distance > this._answer_distance){
                min_distance = this._answer_distance;
                for(int j=0;j<CITY_NUM+1;j++){
                    min_route[j] = this._answer_route[j];
                    min_process[j] = this._distance_process[j];
                }
            }
        }
        this._answer_distance = min_distance;
        for(int i=0;i<CITY_NUM;i++){
            this._answer_route[i] = min_route[i];
            this._distance_process[i] = min_process[i];
        }
    }
    
    /**
     * ���ʂ̕\��
     */
    public void ResultPrint(){
        for(int i=0;i<CITY_NUM-1;i++){
            // System.out.println((i+1)+"�Ԗڂɒʂ�s�s�ԍ��F"+this._answer_route[i]);
        }
        System.out.println("�������F"+this._answer_distance);
    } 

    /**
     * ���s���ʁF�t�@�C���o��
     */
    public void ResultFileWrite(String path){
        try {
            File file = new File(path);
            FileWriter filewriter = new FileWriter(file);
            filewriter.write("���s��\t�m�[�h\t�m�[�h�ԋ���\n");                
            for(int i=0;i<CITY_NUM+1;i++){
                filewriter.write(i+"\t"+this._answer_route[i]+"\t"+this._distance_process[i]+"\n");                
            }
            filewriter.write("�������F"+this._answer_distance);                
            filewriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}