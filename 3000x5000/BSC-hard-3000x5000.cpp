
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
    int arr[5000]= {0};
    int massage[5000];
    for(int i=0; i<5000; i++)
    {
        cout<<massage[i]<<" ";
    }
    cout<<endl;
    for (int i = 0; i < 5000; i++)
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
    //delete(check_nodes);
    //destroy(H,3000,5000);
    return check_nodes;
}
int **check_node_eq_colon()
{
    //create_Hmatrix();
    int **check_nodes;
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
//--------------------------------------------
int bit_flip_algo(int **check_node,int **check_node_colon,int error_massage[])
{
    int error;

    int decode_massage[5000];
    //int **E;
    //int *decode_massage = BSC_channal(origal_massage, proba);
    for(int i=0; i<5000; i++)
    {
        decode_massage[i]=error_massage[i];
    }
    //int E[3000][5000]= {0};
    vector<vector<int>> E( 3000, vector<int> (5000, 0));
    for(int itr=0; itr<30; itr++)
    {

        for (int i = 0; i < 3000; i++)
        {
            //E[i]=new int[5000];
            for (int j = 0; j<5; j++)            //check_node[i][j]
            {
                int sum = 0;
                for(int k=0; k<5; k++)
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
        /*for(int i=0; i<5000; i++)
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
        /*for(int i=0;i<3000;i++)
        {
            for(int j=0;j<5;j++)
            {
                if(E[i][check_node[i][j]]!=error_massage[check_node[i][j]])
                {
                    decode_massage[check_node[i][j]]=(decode_massage[check_node[i][j]]+1)%2;
                }
            }
        }*/
        for(int i=0;i<5000;i++)
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
            else
            {
                decode_massage[i]=0;
            }
        }
        int e=0;
        for(int i=0;i<5000;i++)
        {
            if(decode_massage[i]!=0)
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
    create_Hmatrix();
    /*int origal_massage[5000]= {0};
    for (int i = 0; i < 5000; i++)
    {
        cout<<origal_massage[i]<<" ";
        //cout << origal_massage[i] << " ";
    }*/
    cout<<endl;
    //double proba=0;
    int **check_node = check_node_eq();
    int **check_node_colon=check_node_eq_colon();
    for(double proba=0; proba<=1; proba+=0.1)
    {


        int result,suscess=0,lose=0;
        for(int i=0; i<10000; i++)
        {
            int massage[5000]= {0};
            for (int i = 0; i < 5000; i++)
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
    destroy(H,3000,5000);
    //destroy(H,3000,5000);
    //delete[] decode_massage;
    return 0;
}
