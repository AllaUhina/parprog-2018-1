//Задача 2. Умножение разреженных матриц. Элементы типа double. Формат хранения матрицы – столбцовый (CCS)

//======== !!!!!!!!!!!!! СТОЛБЦОВЫЙ  !!!!!!!!!!!!! =====================


#include <vector>
#include <iostream>
using namespace std;

struct CCSmatrix
{
	int size;//N
	int countOfElems;
	double *value;//ненулевые значения
	int *numberOfRow;//номер строки для соотв. элемента
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
		matr.numberOfRow[i]=0;
	}
}

// нужно транспонировать А 

CCSmatrix transposeMatrix(CCSmatrix &matr)
{
	CCSmatrix res;
	init_CCSmatrix(matr.size,matr.countOfElems,res);
	
	for (int i=0;i<matr.countOfElems;i++)
		res.ind[matr.numberOfRow[i]+1]++;

	int S=0;
	int tmp;
	for(int i=1;i<=matr.size;i++)
	{
		tmp=res.ind[i];
		res.ind[i]=S;
		S=S+tmp;
	}

	for (int i=0; i<matr.size;i++)
	{
		int j1=matr.ind[i];
		int j2=matr.ind[i+1];
		int row=i;
		for(int j=j1;j<j2;j++)
		{
			double val=matr.value[j];
			int ind1=matr.numberOfRow[j];
			int ind2=res.ind[min(ind1+1,matr.size-1)];
			res.value[ind2]=val;
			res.numberOfRow[ind2]=row;
			res.ind[ind1+1]++;
		}
	}

	return res;
}

int multiply(CCSmatrix A, CCSmatrix B, CCSmatrix &res)
{
	int total_cnt=0;//число элементов
	if (A.size!=B.size)
		throw "size error";

	CCSmatrix AT;
	AT=transposeMatrix(A);
	
	B=transposeMatrix(B);
	B=transposeMatrix(B);

	int N=AT.size;
	vector<int> columns;
	vector<double> values;
	vector<int> row_index;
	int i, j, k;
	int NZ = 0;
	int *temp = new int[N];
	row_index.push_back(0);
	for (i = 0; i < N; i++) 
	{ 
		memset(temp, -1, N * sizeof(int)); 
		int ind1 = AT.ind[i], ind2 = AT.ind[i + 1]; 
		for (j = ind1; j < ind2; j++)
		{
			int col = AT.numberOfRow[j];
			temp[col] = j; 
		} 
		for (j = 0; j < N; j++) 
		{ 
			double sum = 0;
			int ind3 = B.ind[j], ind4 = B.ind[j + 1];
			for (k = ind3; k < ind4; k++) 
			{ 
				int bcol = B.numberOfRow[k];
				int aind = temp[bcol];
				if (aind != -1)
					sum += AT.value[aind] * B.value[k]; 
			}

				if (fabs(sum) > 0) 
				{ 
					columns.push_back(j); 
					values.push_back(sum); 
					NZ++;
				} 
			} 
		row_index.push_back(NZ);
	} 
	init_CCSmatrix(N,NZ,res);
	for (j = 0; j < NZ; j++) 
	{ 
		res.numberOfRow[j] = columns[j];
		res.value[j] = values[j];
	}
	for(i = 0; i <= N; i++) 
		res.ind[i] = row_index[i];
	delete [] temp;
	res=transposeMatrix(res);
	return res.countOfElems;
}

int main(int argc, char * argv[])
{
	char *file_name,*file_output;
	int m_size,not_null_elements_in_one_col,k,Index,el_cnt;
	int num_threads = 1;
	if (argc > 1)
	{
		file_name=argv[1];
		file_output=argv[2];
	}
	else
	{
		file_name="1";
		file_output="1tst.ans";
	}

cout<<"======================================================\n";
	FILE *fl=fopen(file_name,"rb");
	int test_size,test_count,buf_Row,buf_Ind;
	double buf_d;
	CCSmatrix A_test,B_test,rslt;
	
	fread(&test_size,sizeof(test_size),1,fl);
	cout<<"we have "<<test_size<<" size"<<endl;
	fread(&test_count,sizeof(test_count),1,fl);
	cout<<"we have "<<test_count<<" count"<<endl;
	init_CCSmatrix(test_size,test_count*test_size,A_test);
	init_CCSmatrix(test_size,test_count*test_size,B_test);

	

	fread(A_test.value,sizeof(*A_test.value),test_size*test_count,fl);
	fread(A_test.numberOfRow,sizeof(*A_test.numberOfRow),test_size*test_count,fl);
	fread(A_test.ind,sizeof(*A_test.ind),test_size+1,fl);

	fread(B_test.value,sizeof(*B_test.value),test_size*test_count,fl);
	fread(B_test.numberOfRow,sizeof(*B_test.numberOfRow),test_size*test_count,fl);
	fread(B_test.ind,sizeof(*B_test.ind),test_size+1,fl);

	
	
	el_cnt=multiply(A_test,B_test,rslt);

	//запись результата в файл
	/*cout<<"vals\n";
	for(int i=0;i<el_cnt;i++)
		cout<<rslt.value[i]<<" | ";
	cout<<"rows\n";
	for(int i=0;i<el_cnt;i++)
		cout<<rslt.numberOfRow[i]<<" | ";
	cout<<"inds\n";
	for(int i=0;i<test_size+1;i++)
		cout<<rslt.ind[i]<<" | ";*/


	cout<<"successfully calculated \n";
	cout<<"------------------------------\n";
	cout<<"res_test \n";
	fl=fopen(file_output,"wb");
	//fwrite(&el_cnt,sizeof(el_cnt),1,fl);//число ненул эл-тов
	//fwrite(&test_size,sizeof(test_size),1,fl);//размерность
	cout<<el_cnt<<" is count of res elems\n";
	fwrite(rslt.value,sizeof(*rslt.value),el_cnt,fl);
	fwrite(rslt.numberOfRow,sizeof(*rslt.numberOfRow),el_cnt,fl);
	fwrite(rslt.ind,sizeof(*rslt.ind),test_size+1,fl);
	fclose(fl);
	cout<<"successfully writed\n";
	return 0;
}