//������ 2. ��������� ����������� ������. �������� ���� double. ������ �������� ������� � ���������� (CCS)

//======== !!!!!!!!!!!!! ����������  !!!!!!!!!!!!! =====================

#include <omp.h>
#include <vector>
#include <iostream>
using namespace std;

struct CCSmatrix
{
	int size;//N
	int countOfElems;
	double *value;//��������� ��������
	int *numberOfRow;//����� ������ ��� �����. ��������
	int *ind;

};




void init_CCSmatrix(int sz, int cnt, CCSmatrix &matr)
{
	matr.size=sz;
	matr.countOfElems=cnt;
	matr.value=new double[cnt];
	matr.numberOfRow=new int[cnt];
	matr.ind=new int[sz+1];
	
	memset(matr.ind,0,sizeof(int)*(sz+1));
	memset(matr.value,0,sizeof(double)*cnt);
	memset(matr.numberOfRow,0,sizeof(int)*cnt);
	
}

// ����� ��������������� � 

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

int multiply(CCSmatrix A, CCSmatrix B, CCSmatrix &res,int thrds)
{
	
	int total_cnt=0;//����� ���������
	if (A.size!=B.size)
		throw "size error";
	
	CCSmatrix AT;
	AT=transposeMatrix(A);
	
	B=transposeMatrix(B);
	B=transposeMatrix(B);

	int N=A.size;
	int chunk=20;
	int i, j, k;
	
	vector<int> *rows = new vector<int>[N];
	vector<double> *values = new vector<double>[N];
	int* row_index = new int[N + 1];
	memset(row_index, 0, sizeof(int) * N);
	
#pragma omp parallel num_threads(thrds)
	{ 
		int *temp = new int[N];
		
#pragma omp for private(j,k) schedule(dynamic)
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
					rows[i].push_back(j); 
					values[i].push_back(sum); 
					row_index[i]++;
				} 
			} 
		} 
		delete [] temp;
	}
	cout<<"parallel is nice\n";
		int NZ = 0;
		for(i = 0; i < N; i++) 
		{ 
			int tmp = row_index[i];
			row_index[i] = NZ;
			NZ += tmp; 
		} 
		row_index[N] = NZ;
		init_CCSmatrix(N,NZ,res);
		cout<<"res is inited\n";
		int count = 0;
		cout<<"start of copying vectors\n";
		for (i = 0; i < N; i++) //��� � ���������� ����. ��� �����
		{ 
			int size = rows[i].size();
			if(size!=0)
			{
				
				memcpy(&res.numberOfRow[count], &rows[i][0], size * sizeof(int));
				
				memcpy(&res.value[count], &values[i][0], size * sizeof(double));
				
				count += size; 
			}
		
			
			
		} 
		
		memcpy(res.ind, &row_index[0], (N + 1) * sizeof(int));
		
		delete [] row_index;
		delete [] rows;
		delete [] values;	
		res=transposeMatrix(res);
		
	return NZ;
}
int main(int argc, char * argv[])
{
	double t1,t2;
	char *file_name,*file_output;
	int m_size,not_null_elements_in_one_col,k,Index,el_cnt;
	int num_thrd = 1;
	if (argc > 1)
	{
		file_name=argv[1];
		file_output=argv[2];
		num_thrd=atoi(argv[3]);
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

	
	t1=omp_get_wtime();
	el_cnt=multiply(A_test,B_test,rslt,num_thrd);
	t2=omp_get_wtime();
	double total_time=t2-t1;

	cout<<"successfully calculated \n"<<"time is "<<total_time<<endl;
	cout<<"------------------------------\n";
	cout<<"res_test \n";
	fl=fopen(file_output,"wb");
	
	cout<<el_cnt<<" is count of res elems\n";
	fwrite(rslt.value,sizeof(*rslt.value),el_cnt,fl);
	fwrite(rslt.numberOfRow,sizeof(*rslt.numberOfRow),el_cnt,fl);
	fwrite(rslt.ind,sizeof(*rslt.ind),test_size+1,fl);
	fclose(fl);
	cout<<"successfully writed\n";
	return 0;
}