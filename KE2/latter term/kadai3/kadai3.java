import java.io.*;
import calc.*;

public class kadai3{
    public static final int DIM = 196;
    public static final int DATASIZE = 180;
    public static final int  CTGRY = 46;
    

    public static double[][] fileRead_sigma(String path){
        double[][] sigma = new double[DIM][DIM];
        try {
            // BufferedReaderクラスのreadLineメソッドを使って1行ずつ読み込み表示する
            System.out.println(path);
            BufferedReader bufferedReader = new BufferedReader(new FileReader(path));
            for(int i=0;i<DIM;i++){
                String[] line = bufferedReader.readLine().split("\t",0);
                for(int j=0;j<DIM;j++){
                    sigma[i][j] = Double.parseDouble(line[j]);
                }
            }
            bufferedReader.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(0);
        }
        return sigma;
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

    public static void Exchange(double[] target,int i,int j){
        double tmp;
        tmp       = target[i];
        target[i] = target[j];
        target[j] = tmp;
    }

    public static void sort(double[] eigenvalues,double[][] eigenvectors){
        int i,j,k;
	    for(i=0;i<DIM;i++){
		    for(j=0;j<DIM-i-1;j++){
		    	if(eigenvalues[j]<eigenvalues[j+1]){
                    Exchange(eigenvalues,j,j+1);
                    for(k=0;k<DIM;k++){
                        double tmp = eigenvectors[k][j+1];
                        eigenvectors[k][j+1] = eigenvectors[k][j];
                        eigenvectors[k][j] = tmp;
                    }
                }
            }
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
        
        for(int i=1;i<=CTGRY;i++){
            String fname;
            if(i<10)  fname= "./../sigma/sigma"+0+i+".txt";
            else fname = "./../sigma/sigma"+i+".txt";
            double[][] sigma =fileRead_sigma(fname);
            // printSigma(sigma);
            Jacobi matA = new Jacobi(sigma);
            matA.JacobiMethod();
            // MatA :固有値
            double[] eigenvalues = matA.getEigenvalues();
            sort(eigenvalues,matA.ResultP);
            if(i<10)  fname= "./../eigenvalues/eigenvalues"+0+i+".txt";
            else fname = "./../eigenvalues/eigenvalues"+i+".txt";
            fileWrite(eigenvalues,fname);
            if(i<10)  fname= "./../eigenvectors/eigenvectors"+0+i+".txt";
            else fname = "./../eigenvectors/eigenvectors"+i+".txt";
            fileWrite(matA.ResultP,fname);
            System.out.println(i+" success!");
            
        }
        
	}
}
