#include <iostream>
#include <cstdlib>
#include <random>
#include <algorithm>
#include <chrono>


using namespace std;




struct CCSmatrix
{
	int size;//N
	int countOfElems;
	double *value;//ненулевые значени¤
	int *numberOfRow;//номер строки дл¤ соотв. элемента
	int *ind;

};




void init_CCSmatrix(int sz, int cnt, CCSmatrix &matr)
{
	matr.size=sz;
	matr.countOfElems=cnt;
	matr.value=new double[cnt];
	matr.numberOfRow=new int[cnt];
	matr.ind=new int[sz+1];
	for (int i=0;i<sz+1;i++)
		matr.ind[i]=0;
	for (int i=0;i<cnt;i++)
	{
		matr.value[i]=0;
		matr.numberOfRow[i]=-1;
	}
}



int main(int argc, char * argv[])
{
	char *file_name;
	int m_size,not_null_elements_in_one_col,k,Index;
	
	if (argc > 1)
	{
		m_size =atoi(argv[1]);
		not_null_elements_in_one_col=atoi(argv[2]);
		if(m_size<=0)
		{
			cout<<"wrong size\n";
			return -1;
		}
		if(not_null_elements_in_one_col<=0)
		{
			cout<<"wrong count of elements\n";
			return -1;
		}
		if(m_size<not_null_elements_in_one_col)
		{
			cout<<"wrong count of elements\n";
			return -1;
		}
		file_name=argv[3];
	}
	default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
	uniform_real_distribution <double> distribution(-1e4, 1e4);
	int minNum,maxNum;
	Index=0;
	if (argc > 1)
	{
		cout<<"test size "<<m_size<<endl;
		cout<<"test count "<<not_null_elements_in_one_col<<endl;
		cout<<"test name "<<file_name<<endl;
	}
	else
	{
		cout<<"Enter size of matrix: ";
		cin>>m_size;
		cout<<"Enter count of not null elements in one col: ";
		cin>>not_null_elements_in_one_col;
		cout<<"Enter file name: ";
		cin>>file_name;
	}

	FILE *fl=fopen(file_name,"wb");
	fwrite(&m_size,sizeof(m_size),1,fl);//запись размерности матрицы в файл
	fwrite(&not_null_elements_in_one_col,sizeof(not_null_elements_in_one_col),1,fl);


	k=m_size/not_null_elements_in_one_col; 
	if(m_size%not_null_elements_in_one_col!=0)
		k++;
	
	CCSmatrix A,B;
	init_CCSmatrix(m_size,not_null_elements_in_one_col*m_size,A);
	init_CCSmatrix(m_size,not_null_elements_in_one_col*m_size,B);
	//A
	//values
	for (int u=0;u<m_size*not_null_elements_in_one_col;u++)
	{
		A.value[u]=distribution(generator);
	}

	//rows

	for (int j=0;j<m_size;j++)//по каждой колонке
	{
		for(int i=0;i<not_null_elements_in_one_col;i++)
		{ 
			
			minNum=k*i;
			maxNum=min(k*(i+1),m_size);
			random_device rd;    
			mt19937 gen(rd()); 
			uniform_int_distribution<unsigned long long> dist(minNum,maxNum+1); 	
			A.numberOfRow[Index]=dist(gen);
			Index++;
			
		}
	}

	//ind
	A.ind[0]=0;
	for (int y=1;y<A.size+1;y++)
	{
		A.ind[y]=A.ind[y-1]+not_null_elements_in_one_col;
	}
	fwrite(A.value,sizeof(*A.value),m_size*not_null_elements_in_one_col,fl);
	fwrite(A.numberOfRow,sizeof(*A.numberOfRow),m_size*not_null_elements_in_one_col,fl);
	fwrite(A.ind,sizeof(*A.ind),m_size+1,fl);

//==================================================================
	//B
	Index=0;
	//values
	for (int u=0;u<m_size*not_null_elements_in_one_col;u++)
	{
		B.value[u]=distribution(generator);
	}

	//rows

	for (int j=0;j<m_size;j++)//по каждой колонке
	{
		for(int i=0;i<not_null_elements_in_one_col;i++)
		{ 
			minNum=k*i;
			maxNum=min(k*(i+1),m_size);
			random_device rd;    
			mt19937 gen(rd()); 
			uniform_int_distribution<unsigned long long> dist(minNum,maxNum+1); 			
			B.numberOfRow[Index]=dist(gen);
			Index++;
		}
	}

	//ind
	B.ind[0]=0;
	for (int y=1;y<B.size+1;y++)
	{
		B.ind[y]=B.ind[y-1]+not_null_elements_in_one_col;
	}
	fwrite(B.value,sizeof(*B.value),m_size*not_null_elements_in_one_col,fl);
	fwrite(B.numberOfRow,sizeof(*B.numberOfRow),m_size*not_null_elements_in_one_col,fl);
	fwrite(B.ind,sizeof(*B.ind),m_size+1,fl);

	fclose(fl);

	
	cout<<"======================================================\n";
	

	return 0;
}