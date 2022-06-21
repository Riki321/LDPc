
#include <bits/stdc++.h>
using namespace std;
//------------------------------
int **H;
//----------------------------------------
void destroy(int ** ptr, int row, int col)
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
    int m = 9, n = 12;
    H = new int *[m];

    for (int i = 0; i < m; i++)
        H[i] = new int[n];
    ifstream in;
    in.open("Hmatrix3.txt");
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
//----------------------------------------------------
/*int *BSC_channal(int origal_massage[], double proba)
{
    int arr[12]= {0};
    int massage[12];
    for(int i=0; i<12; i++)
    {
        cout<<massage[i]<<" ";
    }
    cout<<endl;
    for (int i = 0; i < 12; i++)
    {
        if (fRand() > proba)
        {
            if (origal_massage[i] == 0)
            {
                massage[i] = 1;
            }
            else
            {
                massage[i] = 0;
            }
        }
    }
    return massage;
}*/
//----------------------------------------------
//-----------------------------------------------
int **check_node_eq()
{
    create_Hmatrix();
    int **check_nodes; //int check_nodes[3000][3];
    check_nodes = new int *[9];
    for (int i = 0; i < 9; i++)
    {
        int k = 0;
        check_nodes[i] = new int[4];
        for (int j = 0; j < 12; j++)
        {
            if (H[i][j] == 1)
            {
                check_nodes[i][k] = j;
                k++;
            }
        }
    }
    //delete(check_nodes);
    destroy(H,9,12);
    return check_nodes;
}
int **check_node_eq_colon()
{
    create_Hmatrix();
    int **check_nodes;
    check_nodes = new int *[12];
    for (int i = 0; i < 12; i++)
    {
        int k = 0;
        check_nodes[i] = new int[3];
        for (int j = 0; j < 9; j++)
        {
            if (H[j][i] == 1)
            {
                check_nodes[i][k] = j;
                k++;
            }
        }
    }
    destroy(H,9,12);
    return check_nodes;
}
//--------------------------------------------
int massage_pass(int **check_node,/*int **check_node_colon,*/int error_massage[])
{
    int error=0;
    int decode_massage[12];
    //int **E;
    //int *decode_massage = BSC_channal(origal_massage, proba);
    for(int i=0; i<12; i++)
    {
        decode_massage[i]=error_massage[i];
    }
    //int E[9][12]= {0};
    for(int q=0; q<200; q++)
    {
        for (int i = 0; i < 9; i++)
        {
            int k = 0; //int jj=0;
            for (int j = 0; j < 4; j++)
            {
                if (decode_massage[check_node[i][j]] == -1)
                {
                    k++;
                }
            }
            if(k==1)
            {
                int sum=0,pos=0;
                for(int j=0;j<4;j++)
                {
                    if(decode_massage[check_node[i][j]]==-1)
                    {
                        pos=j;
                    }
                    else
                    {
                        sum+=decode_massage[check_node[i][j]];
                    }
                }
                decode_massage[check_node[i][pos]]=sum%2;
            }
        }
        int e=0;
        for(int i=0; i<12; i++)
        {
            if(decode_massage[i]==-1)
            {
                e++;
            }
        }
        error=e;
    }

    return error;
}

int main()
{
    for_rand();

    int **check_node = check_node_eq();
    for(double proba=0; proba<=1; proba+=0.1)
    {


        int result,suscess=0,lose=0;
        for(int i=0; i<10000; i++)
        {
            int massage[12]= {0};
            for (int i = 0; i < 12; i++)
            {
                if (fRand() < proba)
                {
                    massage[i]=-1;
                }
            }

            result=massage_pass(check_node,massage);

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
        }
        cout<<"proba="<<proba<<" "<<"suscess="<<suscess<<" "<<"lose="<<lose<<" "<<"final="<<(double)suscess/10000<<endl;
        /*ofstream out;
        out.open("error_proba_X.txt",ios::app);
        out << proba << " ";
        out.close();*/
        ofstream out1;
        out1.open("Ncurr_Nsim_Y_BEC-hard.txt",ios::app);
        out1<<(double)suscess/10000<<" ";
        out1.close();
        //cout<<k<<endl;
        // proba+=0.01;
    }

    //destroy(check_node_colon,5000,3);
    destroy(check_node,3000,5);
    //delete[] decode_massage;
    return 0;
}

