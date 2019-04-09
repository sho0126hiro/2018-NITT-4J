import java.io.*;
import calc.*;

public class kadai6{
    public static final int DIM = 196;
    public static final int DATASIZE = 200;
    public static final int TARGET_START = 181;
    public static final int TARGET_END = 200;
    public static final int  CTGRY = 46;
    
    /**
     * ���̃f�[�^�ǂݍ��ݗp
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
     * path�̃t�@�C����ǂݍ��݁A�z��̑傫����DIM�́A�ꎟ���z���Ԃ��B
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


    public static void main(String[] args) {
        String fname;
        // �t�@�C���ǂݍ���
        double[][][] source = new double[CTGRY][DATASIZE][DIM];
        double[][]   average = new double[CTGRY][DIM];
        double[][]   eigenvalues = new double[CTGRY][DIM];
        double[][][] eigenvectors  = new double[CTGRY][DIM][DIM];
        for(int k=1;k<=CTGRY;k++){
            // ���f�[�^
            if(k<10)  fname = "./../data/c"+0+k+".txt";
            else fname = "./../data/c"+k+".txt";
            source[k-1] = fileRead_Source(fname);
            // ���ϒl
            if(k<10)  fname = "./../data/mean"+0+k+".txt";
            else fname = "./../data/mean"+k+".txt";
            average[k-1] = fileRead_1DIMArray(fname);
            // �ŗL�l�i�傫�����ԁj
            if(k<10)  fname = "./../eigenvalues/eigenvalues"+0+k+".txt";
            else fname = "./../eigenvalues/eigenvalues"+k+".txt";
            eigenvalues[k-1] = fileRead_1DIMArray(fname);
            // �ŗL�x�N�g��(������傫�����i��x�N�g�����ŗL�x�N�g���j�j
            if(k<10)  fname = "./../eigenvectors/eigenvectors"+0+k+".txt";
            else fname = "./../eigenvectors/eigenvectors"+k+".txt";
            eigenvectors[k-1] = fileRead_2DIMArray(fname);
        }
        double recognition_all=0;
        System.out.println("*********** ���킲�Ƃ̔F���� ***********");
        System.out.println("����ԍ�\t����\t�F����(%)");
        for(int k=0;k<CTGRY;k++){
            double recognition_ctgry=0;
            // for(int j=TARGET_START;j<=TARGET_START+1;j++){
            for(int j=TARGET_START-1;j<TARGET_END;j++){
                double dm;
                double dm_min = Double.MAX_VALUE; // �}�n���m�r�X�����̍ŏ��l������
                double dm_min2 = Double.MAX_VALUE; // 2�Ԗ�
                int dm_min_index = -1;         // �}�n���m�r�X�����̍ŏ��l�̔ԍ�������
                int dm_min_index2 = -1;         // �}�n���m�r�X�����̍ŏ��l�̔ԍ�������
                for(int i=0;i<CTGRY;i++){
                    BayesDiscriminant m = new BayesDiscriminant(source[k][j],average[i],eigenvalues[i],eigenvectors[i]);
                    dm = m.CalcBayesDiscriminant();
                    // System.out.println(dm);
                    if(dm < dm_min){
                        dm_min2 = dm_min;
                        dm_min = dm;
                        dm_min_index2 = dm_min_index;
                        dm_min_index = i;
                    }
                }
                // �����̈�v�m�F
                if(k == dm_min_index){
                    recognition_ctgry+=1;
                }else{
                    // ��v���Ă��Ȃ�������
                    System.out.println("k: "+k+ "j: "+j+"�{����\t"+moji(k+1)+"�v�����ʂ�\t"+dm_min_index+" moji: "+moji(dm_min_index+1)+", ������ "+dm_min+"��Ԗڂ�"+dm_min_index2+"moji: "+moji(dm_min_index2+1)+"������ "+dm_min2);
                }
            }
            //�������Ƃ̔F����
            recognition_all += recognition_ctgry;
            recognition_ctgry/=(TARGET_END-TARGET_START+1);
            // System.out.println(k+ "\t" +moji(k+1)+"\t"+recognition_ctgry*100);
        }
        //�@�S�̂̔F����
        System.out.println("*********** �S�̂̔F���� ***********");
        recognition_all /= CTGRY * (TARGET_END-TARGET_START+1);
        System.out.println("�S�̂̔F����(%)\t"+recognition_all*100);
    }
    
    /**
     * �����֐�
     */
    public static char moji(int n) {
        char res;
        switch(n) {
        case 1:
            res='��';
            break;
        case 2:
            res='��';
            break;
        case 3:
            res='��';
            break;
        case 4:
            res='��';
            break;
        case 5:
            res='��';
            break;
        case 6:
            res='��';
            break;
        case 7:
            res='��';
            break;
        case 8:
            res='��';
            break;
        case 9:
            res='��';
            break;
        case 10:
            res='��';
            break;
        case 11:
            res='��';
            break;
        case 12:
            res='��';
            break;
        case 13:
            res='��';
            break;
        case 14:
            res='��';
            break;
        case 15:
            res='��';
            break;
        case 16:
            res='��';
            break;
        case 17:
            res='��';
            break;
        case 18:
            res='��';
            break;
        case 19:
            res='��';
            break;
        case 20:
            res='��';
            break;
        case 21:
            res='��';
            break;
        case 22:
            res='��';
            break;
        case 23:
            res='��';
            break;
        case 24:
            res='��';
            break;
        case 25:
            res='��';
            break;
        case 26:
            res='��';
            break;
        case 27:
            res='��';
            break;
        case 28:
            res='��';
            break;
        case 29:
            res='��';
            break;
        case 30:
            res='��';
            break;
        case 31:
            res='��';
            break;
        case 32:
            res='��';
            break;
        case 33:
            res='��';
            break;
        case 34:
            res='��';
            break;
        case 35:
            res='��';
            break;
        case 36:
            res='��';
            break;
        case 37:
            res='��';
            break;
        case 38:
            res='��';
            break;
        case 39:
            res='��';
            break;
        case 40:
            res='��';
            break;
        case 41:
            res='��';
            break;
        case 42:
            res='��';
            break;
        case 43:
            res='��';
            break;
        case 44:
            res='��';
            break;
        case 45:
            res='��';
            break;
        case 46:
            res='��';
            break;
        default:
            res='E';
        }
        return res;
    }

}

/**
*********** ���킲�Ƃ̔F���� ***********
����ԍ�        ����    �F����(%)
0       ��      100.0
1       ��      100.0
2       ��      95.0
3       ��      100.0
4       ��      100.0
5       ��      100.0
6       ��      95.0
7       ��      100.0
8       ��      100.0
9       ��      95.0
10      ��      100.0
11      ��      100.0
12      ��      95.0
13      ��      100.0
14      ��      100.0
15      ��      100.0
16      ��      100.0
17      ��      90.0
18      ��      100.0
19      ��      100.0
20      ��      100.0
21      ��      100.0
22      ��      100.0
23      ��      95.0
24      ��      100.0
25      ��      95.0
26      ��      90.0
27      ��      100.0
28      ��      100.0
29      ��      100.0
30      ��      100.0
31      ��      100.0
32      ��      100.0
33      ��      95.0
34      ��      90.0
35      ��      95.0
36      ��      100.0
37      ��      95.0
38      ��      95.0
39      ��      90.0
40      ��      100.0
41      ��      100.0
42      ��      100.0
43      ��      95.0
44      ��      95.0
45      ��      100.0
*********** �S�̂̔F���� ***********
�S�̂̔F����(%) 97.82608695652173
 */