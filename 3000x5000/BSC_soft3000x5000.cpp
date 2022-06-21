#include <bits/stdc++.h>
using namespace std;
int **H;
/*double **create_array(int row,int colon)
{
    double **arr;
    arr=new double*[row];
    for(int i=0;i<row;i++)
    {
        arr[i]=new double[colon];
    }
    return arr;
}*/
void destroy(int ** ptr, int row, int col)
{
    for(int i = 0; i < row; i++)
    {
        delete [] ptr[i];
    }
    delete [] ptr;
}
void destroy1(double ** ptr, int row, int col)
{
    for(int i = 0; i < row; i++)
    {
        delete [] ptr[i];
    }
    delete [] ptr;
}
//---------------------------------------------
void create_Hmatrix()
{
    int m = 3000, n = 5000;
    H = new int *[m];

    for (int i = 0; i < m; i++)
        H[i] = new int[n];
    ifstream in;
    in.open("Hmatrix2.txt");
    if (!in)
    {
        cout << "Cannot open tHe file" << endl;
        exit(0);
    }

    int row = 0, col = 0;
    char data;
    while (!in.eof()) // Here I want to fill tHe H matrix witH values given in text file,
        //keeping in mind tHe size of eacH row and column of H
    {
        in >> data;
        if (data != ',')
        {
            if (col == n)
            {

                col = 0;
                row++;
            }

            H[row][col] = data - 48;
            col++;

            if (row == m - 1 && col == n)
                break;
        }
    }
    in.close();
}
//---------------------------------------------
void for_rand()
{
    srand(time(0));
}
double fRand()
{
    //for_rand();
    double f = (double)rand() / RAND_MAX;
    return f;
}
double tanH(double proba_arr)
{
    double antilog=pow(2.7182,proba_arr);
    double p=1/(1+antilog);
    return (1-(2*p));
}
int **check_node_eq_row()
{
    //create_Hmatrix();
    int **check_nodes; //int check_nodes[3000][3];
    check_nodes = new int *[3000];
    for (int i = 0; i < 3000; i++)
    {
        int k = 0;
        check_nodes[i] = new int[5];
        for (int j = 0; j < 5000; j++)
        {
            if (H[i][j] == 1)
            {
                check_nodes[i][k] = j;
                k++;
            }
        }
    }
    //destroy(H,3000,5000);
    return check_nodes;
}
int **check_node_eq_colon()
{
    //create_Hmatrix();
    int **check_nodes; //int check_nodes[3000][3];
    check_nodes = new int *[5000];
    for (int i = 0; i < 5000; i++)
    {
        int k = 0;
        check_nodes[i] = new int[3];
        for (int j = 0; j < 3000; j++)
        {
            if (H[j][i] == 1)
            {
                check_nodes[i][k] = j;
                k++;
            }
        }
    }
    //destroy(H,3000,5000);
    return check_nodes;
}
int sum_product_algo(int **check_node_row,int **check_node_colon,vector<vector<double>>M,double proba_arr[])
{
    int error=0;
    int decode_massage[5000]= {0};
    //double **E=create_array(3000,5000);
    int m=3000,n=5000;
    vector<vector<double>> E( m, vector<double> (n, 0));
    for(int itr=0; itr<30; itr++)
    {
        for (int i = 0; i < 3000; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                double sum1 = 1;
                for (int k = 0; k < 5; k++)
                {
                    if (j != k)
                    {
                        double x=0;
                        x=tanH(M[i][check_node_row[i][k]]);
                        sum1*=x;
                    }
                }
                E[i][check_node_row[i][j]] = log((1+sum1)/(1-sum1));
            }
        }
        int e=0;
        for(int i=0; i<5000; i++)
        {
            double temp=0;
            double x=0;
            for(int j=0; j<3; j++)
            {
                temp+=E[check_node_colon[i][j]][i];
            }
            x=temp+proba_arr[i];
            if(x<0)
            {
                decode_massage[i]=1;
            }
            else
            {
                decode_massage[i]=0;
            }
        }
        for(int i=0; i<5000; i++)
        {
            if(decode_massage[i]!=0)
            {
                e++;
            }
        }
        if(e==0)
        {
            //cout<<"booom"<<endl;
            error=0;
            break;
        }
        else
        {
            for(int i=0; i<5000; i++)
            {
                for(int j=0; j<3; j++)
                {
                    double sum=0;
                    for(int k=0; k<3; k++)
                    {
                        if(j!=k)
                        {
                            sum+=E[check_node_colon[i][k]][i];
                        }
                    }
                    M[check_node_colon[i][j]][i]=sum+proba_arr[i];
                }
            }
            error=e;
            //cout<<"e="<<error<<" ";
        }
    }
    //destroy1(E,3000,5000);
    return error;
}
int main()
{
    for_rand();
    create_Hmatrix();
    //int origal_massage[5000]= {0};

    int **check_node_row=check_node_eq_row();
    int **check_node_colon = check_node_eq_colon();
    for(double proba=0; proba<=1.0; proba+=0.1)
    {
        int result,suscess=0,lose=0;
        for(int i=0; i<10000; i++)
        {
            int error_massage[5000]= {0};
            for(int i=0; i<5000; i++)
            {
                if(fRand()<proba)
                    error_massage[i]=1;
            }
            double proba_arr[5000];
            double a=log((1-proba)/proba);
            for(int i=0; i<5000; i++)
            {
                if(error_massage[i]==1)
                {
                    proba_arr[i]=(-a);
                }
                else
                {
                    proba_arr[i]=a;
                }
            }
            //double **M=create_array(3000,5000);
            int m=3000,n=5000;
            vector<vector<double>> M( m, vector<double> (n, 0));
            for(int i=0; i<5000; i++)
            {
                for(int j=0; j<3; j++)
                {

                    M[check_node_colon[i][j]][i]=proba_arr[i];
                }

            }
            //double *proba_arr=BSC_channal(origal_massage,proba);
            result=sum_product_algo(check_node_row,check_node_colon,M,proba_arr);
            if(result==0)
            {
                suscess++;
            }
            else
            {
                lose++;
            }
            //destroy1(M,3000,5000);
            //delete[] proba_arr;
            //delete[] decode_massage;
        }
        cout<<"proba="<<proba<<" "<<"suscess="<<suscess<<" "<<"lose="<<lose<<" "<<"final="<<(double)suscess/10000<<endl;
        /*ofstream out;
        out.open("error_proba_X.txt",ios::app);
        out << proba << " ";
        out.close();*/
        ofstream out1;
        out1.open("Ncurr_Nsim_Y_BSC-soft.txt",ios::app);
        out1<<(double)suscess/10000<<" ";
        out1.close();
    }
    destroy(check_node_colon,5000,3);
    destroy(check_node_row,3000,5);
    destroy(H,3000,5000);
    //destroy1(E,3000,5000);
    return 0;
}
