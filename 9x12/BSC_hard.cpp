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
int bit_flip_algo(int **check_node,int **check_node_colon,int error_massage[])
{
    int error;

    int decode_massage[12];
    //int **E;
    //int *decode_massage = BSC_channal(origal_massage, proba);
    for(int i=0; i<12; i++)
    {
        decode_massage[i]=error_massage[i];
    }
    //vector<vector<int>> E( 9, vector<int> (12, 0));
    int E[9][12]= {0};
    for(int q=0; q<50; q++)
    {
        //int E[9][12]= {0};
        for (int i = 0; i < 9; i++)
        {
            //E[i]=new int[12];
            for (int j = 0; j<4; j++)            //check_node[i][j]
            {
                int sum = 0;
                for(int k=0; k<4; k++)
                {
                    if(j!=k)
                    {
                        //cout<<"ertyuio"<<endl;
                        sum += decode_massage[check_node[i][k]];
                    }
                }
                E[i][check_node[i][j]]= sum % 2;

            }
        }
        /*for(int i=0; i<12; i++)
        {
            if((E[check_node_colon[i][0]][i]==E[check_node_colon[i][1]][i]) && (E[check_node_colon[i][0]][i]==E[check_node_colon[i][2]][i]==0))
            {
                decode_massage[i]=E[check_node_colon[i][0]][i];
            }
            else
            {
                decode_massage[i]=error_massage[i];
            }
        }*/
        //int e=0;
        for(int i=0;i<12;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(E[check_node_colon[i][j]][i]!=error_massage[i])
                {
                    decode_massage[i]=(decode_massage[i]+1)%2;
                }
            }
        }
        /*for(int i=0;i<12;i++)
        {
            int sum0=0,sum1=0;
            for(int j=0;j<3;j++)
            {
                if(E[check_node_colon[i][j]][i]==0)
                {
                    sum0++;
                }
                else
                {
                    sum1++;
                }
            }
            if(decode_massage[i]==1)
            {
                sum1++;
            }
            else{sum0++;}
            if(sum0>sum1)
            {
                decode_massage[i]=0;
            }
            else if(sum1>sum0 )
            {
                decode_massage[i]=1;
            }
        }*/
        int e=0;
        for(int i=0;i<9;i++)
        {
            int l=0;
            for(int j=0;j<4;j++)
            {
                l+=decode_massage[check_node[i][j]];
            }
            if(l!=0)
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
    /*int origal_massage[12]= {0};
    for (int i = 0; i < 12; i++)
    {
        cout<<origal_massage[i]<<" ";
        //cout << origal_massage[i] << " ";
    }*/
    cout<<endl;
    //double proba=0;
    int **check_node = check_node_eq();
    int **check_node_colon=check_node_eq_colon();
    /*for(int i=0;i<9;i++)
    {
        for(int j=0;j<4;j++)
        {
            cout<<check_node[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<endl;
    for(int i=0;i<12;i++)
    {
        for(int j=0;j<3;j++)
        {
            cout<<check_node_colon[i][j]<<" ";
        }
        cout<<endl;
    }*/
    // double proba=0;
    for(double proba=0; proba<=1; proba+=0.1)
    {


        int result,suscess=0,lose=0;
        for(int i=0; i<10000; i++)
        {
            int massage[12]= {0};
            for (int i = 0; i < 12; i++)
            {
                //cout<<fRand()<<" ";
                if (fRand() < proba)
                {
                    massage[i]=1;
                }
            }

            result=bit_flip_algo(check_node,check_node_colon,massage);

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
        out1.open("Ncurr_Nsim_Y_BSC-hard.txt",ios::app);
        out1<<(double)suscess/10000<<" ";
        out1.close();
        //cout<<k<<endl;
        // proba+=0.01;
    }

    destroy(check_node_colon,5000,3);
    destroy(check_node,3000,5);
    //delete[] decode_massage;
    return 0;
}
