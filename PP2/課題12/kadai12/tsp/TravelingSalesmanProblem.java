package tsp;
import java.io.*;

public class TravelingSalesmanProblem{
    public int[] _answer_route; // 都市ルート番号が開始点から順番に入る
    public double _answer_distance; // 最適解の距離
    public double[] _distance_process; // ノード間の距離が代入される(debug用)
    public static final int CITY_NUM=5000; // 都市数

    protected double[][] _data; // 元データ
    protected int _now_index; // 次のノードの検索をしているindex 
    protected boolean[] _visited; // 訪問されているか
    protected int _searchCount; // 求めた次のノード数

    /**
     * constructor
     * 開始点を指定しない場合、index=0から探索をする。
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
     * constructor(開始点指定の場合)
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
     * nowIndexから一番近いノードindexを求め、
     * 距離とルートに値を代入する。
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
     * NearestNeibour法を使って解く
     */
    public void NearestNeibour(){
        int first=this._now_index;
        this._answer_route[this._searchCount] = this._now_index;
        this._distance_process[this._searchCount] = 0;
        this._visited[this._now_index] = true;
        for(int i=0;i<CITY_NUM-1;i++){
            this._now_index = this._NNgetNextIndex(this._now_index);
        }
        // 出発地に戻す
        this._answer_distance += this._data[this._now_index][first];
        this._answer_route[this._searchCount+1] = first;
        this._distance_process[this._searchCount+1] = this._data[this._now_index][first];
    }

    /**
     * すべての都市を初期値とし、NearestNeibour法を用いて解く。
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
     * 結果の表示
     */
    public void ResultPrint(){
        for(int i=0;i<CITY_NUM-1;i++){
            // System.out.println((i+1)+"番目に通る都市番号："+this._answer_route[i]);
        }
        System.out.println("総距離："+this._answer_distance);
    } 

    /**
     * 実行結果：ファイル出力
     */
    public void ResultFileWrite(String path){
        try {
            File file = new File(path);
            FileWriter filewriter = new FileWriter(file);
            filewriter.write("試行回数\tノード\tノード間距離\n");                
            for(int i=0;i<CITY_NUM+1;i++){
                filewriter.write(i+"\t"+this._answer_route[i]+"\t"+this._distance_process[i]+"\n");                
            }
            filewriter.write("総距離："+this._answer_distance);                
            filewriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}