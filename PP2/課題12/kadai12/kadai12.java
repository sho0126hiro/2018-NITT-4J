import tsp.*;
import java.io.*;

public class kadai12{
	public static final int CITY_NUM = 5000;
	/**
     * 5000 * 5000 の都市距離データを取得
	 * 対象行列、対角の値は-1
     * @return result[CITY_NUM][CITY_NUM]
     */
    public static double[][] fileRead(String path){
		double[][] result = new double[CITY_NUM][CITY_NUM];
		String[] tmp;
        try {
            BufferedReader bufferedReader = new BufferedReader(new FileReader(path));
            for(int i=0;i<CITY_NUM;i++){
				tmp = bufferedReader.readLine().split(" ");
				result[i][i] = -1;
                for(int j=i+1;j<CITY_NUM;j++){
					result[i][j] = Double.parseDouble(tmp[j]);
				}
            }
			bufferedReader.close();
			for(int i=1;i<CITY_NUM;i++){
				for(int j=0;j<i;j++){
					result[i][j] = result[j][i];
				}
			}
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(0);
        }
        return result;
	}

	/**
	 * debug 配列の表示
     * @param data[CITY_NUM][CITY_NUM]
     */
    public static void debug_Display(double[][] data){
        for(int i=0;i<3;i++){
			for(int j=0;j<3;j++)System.out.print(data[i][j]+" ");
			System.out.printf("\n");
		}
	}
	
    public static void main(String[] args) {
		double[][] data = new double[CITY_NUM][CITY_NUM];
		data = fileRead("./data/table.dat");
		TravelingSalesmanProblem tsp = new TravelingSalesmanProblem(data);
		tsp.NearestNeibour();
		// tsp.NN_all();
		tsp.ResultPrint();
		tsp.ResultFileWrite("test.txt");
	}
}