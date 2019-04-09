import java.io.*;
import calc.*;

public class kadai4{
    public static final int DIM = 196;
    public static final int DATASIZE = 200;
    public static final int TARGET_START = 181;
    public static final int TARGET_END = 200;
    public static final int  CTGRY = 46;
    
    /**
     * 元のデータ読み込み用
     * @return result[DATASIZE][DIM]
     */
    public static double[][] fileRead_Source(String path){
        double[][] result = new double[DATASIZE][DIM];
        try {
            BufferedReader bufferedReader = new BufferedReader(new FileReader(path));
            for(int i=0;i<DATASIZE;i++){
                for(int j=0;j<DIM;j++){
                    result[i][j] = Double.parseDouble(bufferedReader.readLine());
                }
            }
            bufferedReader.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(0);
        }
        return result;
    }

    /**
     * pathのファイルを読み込み、配列の大きさがDIMの、一次元配列を返す。
     * @param {String} path
     * @return {double[]} result
     */
    public static double[] fileRead_1DIMArray(String path){
        double[] result = new double[DIM];
        try {
            BufferedReader bufferedReader = new BufferedReader(new FileReader(path));
            for(int i=0;i<DIM;i++){
                result[i] = Double.parseDouble(bufferedReader.readLine());
            }
            bufferedReader.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(0);
        }
        return result;
    }
    
    public static double[][] fileRead_2DIMArray(String path){
        double[][] result = new double[DIM][DIM];
        try {
            BufferedReader bufferedReader = new BufferedReader(new FileReader(path));
            for(int i=0;i<DIM;i++){
                String[] line = bufferedReader.readLine().split("\t",0);
                for(int j=0;j<DIM;j++){
                    result[i][j] = Double.parseDouble(line[j]);
                }
            }
            bufferedReader.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(0);
        }
        return result;
    }
    public static void fileWrite(double[] input,String path){
        try {
            File file = new File(path);
            FileWriter filewriter = new FileWriter(file);
            for(int i=0;i<DIM;i++){
                filewriter.write(input[i]+"\n");                
            }
            filewriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void fileWrite(double[][] input,String path){
        try {
            File file = new File(path);
            FileWriter filewriter = new FileWriter(file);
            for(int j=0;j<DIM;j++){
                for(int i=0;i<DIM;i++){
                    filewriter.write(input[j][i]+"\t");                
                }
                filewriter.write("\n");
            }
            filewriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void printSigma(double[][] sigma){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                System.out.println(sigma[i][j]);
            }
        }
    }

    /**
     * 文字関数
     */
    public static char moji(int n) {
        char res;
        switch(n) {
        case 1:
            res='あ';
            break;
        case 2:
            res='い';
            break;
        case 3:
            res='う';
            break;
        case 4:
            res='え';
            break;
        case 5:
            res='お';
            break;
        case 6:
            res='か';
            break;
        case 7:
            res='き';
            break;
        case 8:
            res='く';
            break;
        case 9:
            res='け';
            break;
        case 10:
            res='こ';
            break;
        case 11:
            res='さ';
            break;
        case 12:
            res='し';
            break;
        case 13:
            res='す';
            break;
        case 14:
            res='せ';
            break;
        case 15:
            res='そ';
            break;
        case 16:
            res='た';
            break;
        case 17:
            res='ち';
            break;
        case 18:
            res='つ';
            break;
        case 19:
            res='て';
            break;
        case 20:
            res='と';
            break;
        case 21:
            res='な';
            break;
        case 22:
            res='に';
            break;
        case 23:
            res='ぬ';
            break;
        case 24:
            res='ね';
            break;
        case 25:
            res='の';
            break;
        case 26:
            res='は';
            break;
        case 27:
            res='ひ';
            break;
        case 28:
            res='ふ';
            break;
        case 29:
            res='へ';
            break;
        case 30:
            res='ほ';
            break;
        case 31:
            res='ま';
            break;
        case 32:
            res='み';
            break;
        case 33:
            res='む';
            break;
        case 34:
            res='め';
            break;
        case 35:
            res='も';
            break;
        case 36:
            res='や';
            break;
        case 37:
            res='ゆ';
            break;
        case 38:
            res='よ';
            break;
        case 39:
            res='ら';
            break;
        case 40:
            res='り';
            break;
        case 41:
            res='る';
            break;
        case 42:
            res='れ';
            break;
        case 43:
            res='ろ';
            break;
        case 44:
            res='わ';
            break;
        case 45:
            res='を';
            break;
        case 46:
            res='ん';
            break;
        default:
            res='E';
        }
        return res;
    }

    public static void main(String[] args) {
        String fname;
        // ファイル読み込み
        double[][][] source = new double[CTGRY][DATASIZE][DIM];
        double[][]   average = new double[CTGRY][DIM];
        double[][]   eigenvalues = new double[CTGRY][DIM];
        double[][][] eigenvectors  = new double[CTGRY][DIM][DIM];
        for(int k=1;k<=CTGRY;k++){
            // 元データ
            if(k<10)  fname = "./../data/c"+0+k+".txt";
            else fname = "./../data/c"+k+".txt";
            source[k-1] = fileRead_Source(fname);
            // 平均値
            if(k<10)  fname = "./../data/mean"+0+k+".txt";
            else fname = "./../data/mean"+k+".txt";
            average[k-1] = fileRead_1DIMArray(fname);
            // 固有値（大きい順番）
            if(k<10)  fname = "./../eigenvalues/eigenvalues"+0+k+".txt";
            else fname = "./../eigenvalues/eigenvalues"+k+".txt";
            eigenvalues[k-1] = fileRead_1DIMArray(fname);
            // 固有ベクトル(左から大きい順（列ベクトルが固有ベクトル））
            if(k<10)  fname = "./../eigenvectors/eigenvectors"+0+k+".txt";
            else fname = "./../eigenvectors/eigenvectors"+k+".txt";
            eigenvectors[k-1] = fileRead_2DIMArray(fname);
        }
        double recognition_all=0;
        System.out.println("*********** 字種ごとの認識率 ***********");
        System.out.println("字種番号\t字種\t認識率(%)");
        for(int k=0;k<CTGRY;k++){
            double recognition_ctgry=0;
            // for(int j=TARGET_START;j<=TARGET_START+1;j++){
            for(int j=TARGET_START-1;j<TARGET_END;j++){
                double dm;
                double dm_min = Double.MAX_VALUE; // マハラノビス距離の最小値が入る
                double dm_min_index = -1;         // マハラノビス距離の最小値の番号が入る
                for(int i=0;i<CTGRY;i++){
                    Mahalanobis m = new Mahalanobis(source[k][j],average[i],eigenvalues[i],eigenvectors[i]);
                    dm = m.CalcMahalanobisDistance();
                    // System.out.println(dm);
                    if(dm < dm_min){
                        dm_min = dm;
                        dm_min_index = i;
                    }
                }
                // 文字の一致確認
                if(k == dm_min_index){
                    recognition_ctgry+=1;
                }
            }
            //文字ごとの認識率
            recognition_all += recognition_ctgry;
            recognition_ctgry/=(TARGET_END-TARGET_START+1);
            System.out.println(k+ "\t" +moji(k+1)+"\t"+recognition_ctgry*100);
        }
        //　全体の認識率
        System.out.println("*********** 全体の認識率 ***********");
        recognition_all /= CTGRY * (TARGET_END-TARGET_START+1);
        System.out.println("全体の認識率(%)\t"+recognition_all*100);
	}
}
