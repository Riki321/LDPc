
#include <bits/stdc++.h>
using namespace std;
//------------------------------
int **H;
double **create_arr(int row,int colon)
{
    double **arr;
    arr=new double*[row];
    for(int i=0;i<row;i++)
    {
        arr[i]=new double[colon];
    }
    return arr;
}
//----------------------------------------
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
//----------------------------------------

void create_Hmatrix()
{
    int m = 3792, n = 5056;
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
//----------------------------------------
void for_rand()
{
    srand(time(0));
}
//---------------------------------------
double fRand()
{
    double f = (double)rand() / RAND_MAX;
    return f;
}
double tanH(double proba_arr)
{
    double antilog=pow(2.7182,proba_arr);
    double p=1/(1+antilog);
    return (1-(2*p));
}
//-----------------------------------------------
int **check_node_eq()
{

    int **check_nodes; //int check_nodes[3792][3];
    check_nodes = new int *[3792];
    for (int i = 0; i < 3792; i++)
    {
        int k = 0;
        check_nodes[i] = new int[4];
        for (int j = 0; j < 5056; j++)
        {
            if (H[i][j] == 1)
            {
                check_nodes[i][k] = j;
                k++;
            }
        }
    }
    return check_nodes;
}
int **check_node_eq_colon()
{
    //create_Hmatrix();
    int **check_nodes; //int check_nodes[3792][3];
    check_nodes = new int *[5056];
    for (int i = 0; i < 5056; i++)
    {
        int k = 0;
        check_nodes[i] = new int[3];
        for (int j = 0; j < 3792; j++)
        {
            if (H[j][i] == 1)
            {
                check_nodes[i][k] = j;
                k++;
            }
        }
    }
    //destroy(H,3792,5056);
    return check_nodes;
}
//----------------------------------------
//--------------------------------------------
int eresure_soft(int **check_node_row,double *proba_arr,double **M,int error_massage[])
{
    int error=0;
    int decode_massage[5056];
    for(int i=0; i<5056; i++)
    {
        decode_massage[i]=error_massage[i];
    }
    double E;
    for(int q=0; q<20; q++)
    {
        for (int i = 0; i < 3792; i++)
        {
            int k = 0; //int jj=0;
            for (int j = 0; j < 5; j++)
            {
                if (M[i][check_node_row[i][j]] == 0)
                {
                    k++;
                }
            }
            if(k==1)
            {
                int pos=0;
                for(int j=0; j<5; j++)
                {
                    double sum1=1;

                    if(M[i][check_node_row[i][j]]==0)
                    {
                        pos=j;
                        for(int k=0; k<4; k++)
                        {
                            if(pos!=k)
                            {


                            double x=0;
                            x=tanH(M[i][check_node_row[i][k]]);
                            sum1*=x;
                            }
                        }
                    }
                    E=log((1+sum1)/(1-sum1));
                }

                if(E>0 && E!=0)
                {
                    decode_massage[check_node_row[i][pos]]=0;
                    M[i][check_node_row[i][pos]]=E;
                }
            }
        }
        int e=0;
        for(int i=0; i<5056; i++)
        {
            if(decode_massage[i]==-1)
            {
                e++;
            }
        }
        if(e==0)
        {
            error=0;
            break;
        }
        error=e;
    }

    return error;
}

int main()
{
    for_rand();
    create_Hmatrix();
    int **check_node_row = check_node_eq();
    int **check_node_colon=check_node_eq_colon();
    for(double proba=0; proba<=1; proba+=0.1)
    {
        int result,suscess=0,lose=0;
        for(int i=0; i<10000; i++)
        {
            int error_massage[5056]= {0};
            for(int i=0; i<5056; i++)
            {
                if(fRand()<proba)
                    error_massage[i]=-1;
            }
            double proba_arr[5056];
            double a=log((1-proba)/proba);
            for(int i=0; i<5056; i++)
            {
                if(error_massage[i]==-1)
                {
                    proba_arr[i]=0;
                }
                else if(error_massage[i]==0)
                {
                    proba_arr[i]=a;
                }
                else
                {
                    proba_arr[i]=-a;
                }
            }
            double **M=create_arr(3792,5056);
            for(int i=0; i<5056; i++)
            {
                for(int j=0; j<3; j++)
                {

                    M[check_node_colon[i][j]][i]=proba_arr[i];
                }

            }
            result=eresure_soft(check_node_row,proba_arr,M,error_massage);

            if(result==0)
            {
                suscess++;
            }
            else
            {
                lose++;
            }
            //cout<<endl;
            //cout<<endl;
            //delete[] decode_massage;
            destroy1(M,3792,5056);
        }
        cout<<"proba="<<proba<<" "<<"suscess="<<suscess<<" "<<"lose="<<lose<<" "<<"final="<<(double)suscess/10000<<endl;
        /*ofstream out;
        out.open("error_proba_X.txt",ios::app);
        out << proba << " ";
        out.close();*/
        ofstream out1;
        out1.open("Ncurr_Nsim_Y_BEC-soft.txt",ios::app);
        out1<<(double)suscess/10000<<" ";
        out1.close();
        //cout<<k<<endl;
        // proba+=0.01;



    }
    destroy(check_node_colon,5056,3);
    destroy(check_node_row,3792,5);
    destroy(H,3792,5056);
    //delete[] decode_massage;
    return 0;
}

