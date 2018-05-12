//«адача 2. ”множение разреженных матриц. Ёлементы типа double. ‘ормат хранени¤ матрицы Ц столбцовый (CCS)

//======== !!!!!!!!!!!!! —“ќЋЅ÷ќ¬џ…  !!!!!!!!!!!!! =====================


#include <vector>
#include <iostream>
#include "tbb/task_scheduler_init.h"
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
#include"tbb/tick_count.h"
using namespace tbb;
using namespace std;

struct CCSmatrix
{
	int size;//N
	int countOfElems;
	double *value;//ненулевые значени¤
	int *numberOfRow;//номер строки дл¤ соотв. элемента
	int *ind;

};

class Multiplicator 
{ 
	CCSmatrix A, B;
	vector<int>* rows;
	vector<double>* values;
	int *row_index;
public: 
	Multiplicator(CCSmatrix& _A, CCSmatrix& _B, vector<int>* &_rows, vector<double>* &_values, int *_row_index) : A(_A), B(_B), rows(_rows), values(_values), row_index(_row_index) 
	{} 
	void operator()(const blocked_range<int>& r) const 
	{ 
		int begin = r.begin();
		int end = r.end();
		int N = A.size;
		int i, j, k;
		int *temp = new int[N];
		for (i = begin; i < end; i++)	
		{ 
			memset(temp, -1, N * sizeof(int)); 
			int ind1 = A.ind[i], ind2 = A.ind[i + 1];
			for (j = ind1; j < ind2; j++) 
			{ 
				int col = A.numberOfRow[j];
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
						sum += A.value[aind] * B.value[k]; 
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

// нужно транспонировать ј 

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
	cout<<"starting\n";
	int total_cnt=0;//число элементов
	if (A.size!=B.size)
		throw "size error";
	
	CCSmatrix AT,BT;
	cout<<"AT\n";
	AT=transposeMatrix(A);
	cout<<"AT ready\n";
	BT=transposeMatrix(B);
	cout<<"B1\n";
	B=transposeMatrix(BT);
	cout<<"B2\n";
	cout<<"matrixs prepared\n";
	int N=A.size;
	
	int i, j, k;
	
	vector<int> *rows = new vector<int>[N];
	vector<double> *values = new vector<double>[N];
	int* row_index = new int[N + 1];
	memset(row_index, 0, sizeof(int) * N);
	cout<<"preparing tbb\n";
	task_scheduler_init init(thrds);
	cout<<"all inited\n";


	int grainsize = 2;
	parallel_for(blocked_range<int>(0, A.size, grainsize), Multiplicator(AT, B, rows, values, row_index));

	int NZ = 0; 
	for(i = 0; i < N; i++) 
	{ 
		int tmp = row_index[i];
		row_index[i] = NZ;
		NZ += tmp;
	} 
	row_index[N] = NZ;
	init_CCSmatrix(N, NZ, res);
	int count = 0; 
	cout<<"start of memcpy\n";
	for (i = 0; i < N; i++) 
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
	double t1;
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

	cout<<"start\n";
	
	tick_count t0= tick_count::now();
	cout<"t0 calculated\n";
	el_cnt=multiply(A_test,B_test,rslt,num_thrd);
	t1 = (tick_count::now() - t0).seconds();
	

	cout<<"successfully calculated \n"<<endl;
	cout<<"time is "<<t1<<endl;
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